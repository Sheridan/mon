/* %Id% */

#include "config.h"
#include "logger.h"
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "cdefinitionparcer.h"
#include "cdefinitiongenerator.h"
#include "csensor.h"

#define MON_ST_LOGGER logger
#define MON_ST_CONFIG config

// ------------------ variables --------------------------------------------------------------------
mon::lib::config::CConfig *config;
mon::lib::logger::CLogger *logger;
mon::daemons::node::CSensor *sensor;
std::string sensorFile;
std::string configFile;
std::string frame;
int   numberOfGetStatistics     = 10;
float timeBetweenStatisticsCall = 1;
bool  showDefinition         = false;
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
      case 'r': showDefinition            = true;                break;
      case 'n': numberOfGetStatistics     = atoi(optarg);        break;
      case 't': timeBetweenStatisticsCall = atof(optarg);        break;
      case 'o': frame                     = std::string(optarg); break;
    }
  }
  timeBetweenStatisticsCall = timeBetweenStatisticsCall * 1000000;
}
// ------------------ functions --------------------------------------------------------------------
// ------------------ main -------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  config = new mon::lib::config::CConfig();
  logger = new mon::lib::logger::CLogger();
  setopts(argc, argv);
  config->load(configFile);
  sensor = new mon::daemons::node::CSensor(sensorFile);
  sensor->load();
  //load();
  printf("Sensor name: %s\n", sensor->getName(NULL));
  bool sensorAvialable = sensor->getSensorAvialable(frame.c_str());
  printf("Sensor avialable? %s.\n", sensorAvialable ? "Yes" : "No");
  if(sensorAvialable)
  {
    if(showDefinition)
    {
      printf("Sensor raw definition (%d bytes):\n%s\n", sensor->getDefinitionLength(NULL), sensor->getDefinition(NULL));
      mon::lib::sensordata::CDefinition definition;
      mon::lib::sensordata::CDefinitionParcer parcer(&definition, std::string(sensor->getDefinition(NULL)));
      parcer.parce();
      mon::lib::sensordata::CDefinitionGenerator generator(&definition);
      printf("Sensor generated definition :\n%s\n", generator.generate().c_str());
    }
    for (int a = 0; a < numberOfGetStatistics; a++)
    {
      printf("%s\n", sensor->getStatistics(frame.c_str()));
      usleep(timeBetweenStatisticsCall);
    }
  }
  delete sensor;
  delete logger;
  delete config;
  return 0;
}
// ------------------ main -------------------------------------------------------------------------
