/* %Id% */

#include "config.h"
#include "logger.h"
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
// ------------------ variables --------------------------------------------------------------------
mon::lib::config::CConfig *config;
mon::lib::logger::CLogger *logger;
std::string sensorFile;
std::string configFile;
std::string object;
int   numberOfGetStatistics     = 10;
float timeBetweenStatisticsCall = 1;
bool  showRawDefinition         = false;
void * sensor_handle;
typedef void               (*TFInitSensor)(mon::lib::logger::CLogger *, mon::lib::config::CFolder *);
typedef const char        *(*TFGetName)            (const char *);
typedef const char        *(*TFGetDefinition)      (const char *);
typedef const unsigned int (*TFGetDefinitionLength)(const char *);
typedef const char        *(*TFGetStatistics)      (const char *);
typedef const bool         (*TFGetSensorAvialable) (const char *);
TFInitSensor          initSensor          = NULL;
TFGetName             getName             = NULL;
TFGetDefinition       getDefinition       = NULL;
TFGetDefinitionLength getDefinitionLength = NULL;
TFGetStatistics       getStatistics       = NULL;
TFGetSensorAvialable  getSensorAvialable  = NULL;
// ------------------ variables --------------------------------------------------------------------
// ------------------ functions --------------------------------------------------------------------
void help()
{
  printf("\n");
  printf("-h, --help                         This help\n");
  printf("-c, --config                       Sensor config file\n");
  printf("-s, --sensor                       Sensor .so file\n");
  printf("-r, --show-raw-definition          Show raw sensor definition\n");
  printf("-n, --number-of-get-statistics     Statistic call count (default 10)\n");
  printf("-t, --time-between-statistics-call Time between statistics call (s) (default 1s)\n");
  printf("-o, --object                       Statistical object\n");
  printf("\n");
  exit(0);
}
void setopts(int argc, char *argv[])
{
  static const char *optString = "hs:c:rn:t:o:";
  static const struct option longOpts[] = {
      { "help"                        , no_argument      , NULL, 'h' },
      { "sensor"                      , required_argument, NULL, 's' },
      { "config"                      , required_argument, NULL, 'c' },
      { "show-raw-definition"         , no_argument      , NULL, 'r' },
      { "number-of-get-statistics"    , required_argument, NULL, 'n' },
      { "time-between-statistics-call", required_argument, NULL, 't' },
      { "object"                      , required_argument, NULL, 'o' },
      { NULL                          , no_argument      , NULL,  0  }};
  int c;
  int option_index = 0;
  while ((c = getopt_long(argc, argv, optString, longOpts, &option_index)) != -1)
  {
    switch (c)
    {
      case 'h': help();                                          break;
      case 's': sensorFile                = std::string(optarg); break;
      case 'c': configFile                = std::string(optarg); break;
      case 'r': showRawDefinition         = true;                break;
      case 'n': numberOfGetStatistics     = atoi(optarg);        break;
      case 't': timeBetweenStatisticsCall = atof(optarg);        break;
      case 'o': object                    = std::string(optarg); break;
    }
  }
  timeBetweenStatisticsCall = timeBetweenStatisticsCall * 1000000;
}

#define MON_IMPORT_ERROR(_name) \
  if ((error = dlerror()) != NULL) \
  { \
    printf("Error importing function `" #_name "` from sensor `%s`: %s\n", sensorFile.c_str(), error); \
    exit(1);   \
  }
#define MON_IMPORT(_type, _name) _name = (_type) dlsym(sensor_handle, #_name); MON_IMPORT_ERROR(_name);
void load()
{
  sensor_handle = dlopen(sensorFile.c_str(), RTLD_NOW);
  if (!sensor_handle)
  {
    printf("Sensor `%s` loading error: %s\n", sensorFile.c_str(), dlerror());
    exit(1);
  }
  char *error; error = NULL;
  MON_IMPORT(TFInitSensor         , initSensor         );
  MON_IMPORT(TFGetName            , getName            );
  MON_IMPORT(TFGetDefinition      , getDefinition      );
  MON_IMPORT(TFGetDefinitionLength, getDefinitionLength);
  MON_IMPORT(TFGetStatistics      , getStatistics      );
  MON_IMPORT(TFGetSensorAvialable , getSensorAvialable );
  initSensor(logger, config->root());
}

void unload()
{
  initSensor          = NULL;
  getName             = NULL;
  getDefinition       = NULL;
  getDefinitionLength = NULL;
  getStatistics       = NULL;
  getSensorAvialable  = NULL;
  dlclose(sensor_handle);
}

// ------------------ functions --------------------------------------------------------------------
// ------------------ main -------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  config = new mon::lib::config::CConfig();
  logger = new mon::lib::logger::CLogger();
  setopts(argc, argv);
  config->load(configFile);
  load();
  printf("Sensor name: %s\n", getName(NULL));
  bool sensorAvialable = getSensorAvialable(object.c_str());
  printf("Sensor avialable? %s.\n", sensorAvialable ? "Yes" : "No");
  if(sensorAvialable)
  {
    if(showRawDefinition) { printf("Sensor definition (%d bytes):\n%s\n", getDefinitionLength(NULL), getDefinition(NULL)); }
    for (int a = 0; a < numberOfGetStatistics; a++)
    {
      printf("%s\n", getStatistics(object.c_str()));
      usleep(timeBetweenStatisticsCall);
    }
  }
  unload();
  delete logger;
  delete config;
  return 0;
}
// ------------------ main -------------------------------------------------------------------------
