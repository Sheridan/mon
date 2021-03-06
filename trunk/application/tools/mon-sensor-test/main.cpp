/* %Id% */

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>

#define MON_ST_LOGGER logger
#define MON_ST_CONFIG config

#include "defines/logger-helper.h"
#include "libraryes/config/config.h"
#include "libraryes/logger/logger.h"
#include "libraryes/sensordata/parcers/cdefinitionparcer.h"
#include "libraryes/sensordata/parcers/cdefinitiongenerator.h"
#include "daemons/node/sensor/csensor.h"
namespace mon
{
namespace applications
{
namespace tool
{
namespace sensortest
{
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
  printf("-f, --frame                        Statistical frame\n");
  printf("\n");
  exit(0);
}
void setopts(int argc, char *argv[])
{
  static const char *optString = "hs:c:rn:t:f:";
  static const struct option longOpts[] = {
      { "help"                        , no_argument      , nullptr, 'h' },
      { "sensor"                      , required_argument, nullptr, 's' },
      { "config"                      , required_argument, nullptr, 'c' },
      { "show-raw-definition"         , no_argument      , nullptr, 'r' },
      { "number-of-get-statistics"    , required_argument, nullptr, 'n' },
      { "time-between-statistics-call", required_argument, nullptr, 't' },
      { "frame"                       , required_argument, nullptr, 'f' },
      { nullptr                       , no_argument      , nullptr,  0  }};
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
      case 'f': frame                     = std::string(optarg); break;
    }
  }
  timeBetweenStatisticsCall = timeBetweenStatisticsCall * 1000000;
}

std::string parceAndGenerate(const std::string &def)
{
  mon::lib::sensordata::CDefinition *definition = new mon::lib::sensordata::CDefinition();
  MON_LOG_DBG("Parcing definition...");
  mon::lib::sensordata::CDefinitionParcer *parcer = new mon::lib::sensordata::CDefinitionParcer(definition, def);
  parcer->parce();
  MON_LOG_DBG("Parcing definition done");
  MON_LOG_DBG("Generating definition...");
  mon::lib::sensordata::CDefinitionGenerator *generator = new mon::lib::sensordata::CDefinitionGenerator(definition);
  MON_LOG_NFO("Sensor generated definition :");
  std::string result = generator->generate();
  MON_LOG_NFO(result);
  MON_LOG_DBG("Generating definition done");
  delete generator;
  delete parcer;
  delete definition;
  return result;
}

// ------------------ functions --------------------------------------------------------------------
// ------------------ main -------------------------------------------------------------------------
int nsmain(int argc, char *argv[])
{
  config = new mon::lib::config::CConfig();
  logger = new mon::lib::logger::CLogger();
  logger->enableOutToConsole();
  logger->enableOutToFile(false);
  logger->enableOutToSyslog(false);
  setopts(argc, argv);
  config->load(configFile);
  sensor = new mon::daemons::node::CSensor(sensorFile);
  sensor->load();
  MON_LOG_NFO("Sensor name: " << sensor->getName());
  bool frameAvialable = true; //sensor->getFrameAvialable(frame.c_str());
  MON_LOG_NFO("Sensor avialable? " << frameAvialable);
  if(frameAvialable)
  {
    if(showDefinition)
    {
      MON_LOG_NFO("Sensor raw definition (" << sensor->getDefinitionLength() << " bytes)");
      MON_LOG_NFO(sensor->getDefinition());
      std::string first = parceAndGenerate(std::string(sensor->getDefinition()));
      std::string second = parceAndGenerate(first);
      //parceAndGenerate(parceAndGenerate(second));
      MON_LOG_NFO("Definition parcer and generator work fine? " << (first.compare(second) == 0));
    }
    for (int a = 0; a < numberOfGetStatistics; a++)
    {
      //MON_LOG_NFO(sensor->getStatistics(frame.c_str()));
      usleep(timeBetweenStatisticsCall);
    }
  }
  delete sensor;
  delete logger;
  delete config;
  return 0;
}

}
}
}
}

int main(int argc, char *argv[]) { return mon::applications::tool::sensortest::nsmain(argc, argv); }
// ------------------ main -------------------------------------------------------------------------
