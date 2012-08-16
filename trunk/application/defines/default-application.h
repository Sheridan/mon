/* %Id% */
#ifndef defaulMonApplication
#define defaulMonApplication
#include "global.h"

#ifdef MON_DEBUG
  #define MON_MAX_LOG_PRI mon::lib::logger::pDebug
#else
  #define MON_MAX_LOG_PRI mon::lib::logger::pInfo
#endif

#define MON_DEFAULT_APPLICATION_INIT \
  MON_ST_CONFIG->load(MON_CONF_FILE); \
  MON_ST_CONFIG->cd(MON_ST_CONFIG->folder(MON_MODULE_NAME)); \
  MON_CFOLDER *init_fldr = MON_ST_CONFIG->folder("logger"); \
  MON_ST_LOGGER->setMaxLogPriority (static_cast<mon::lib::logger::EPriority>(init_fldr->file("max_priority")->get(static_cast<int>(MON_MAX_LOG_PRI)))); \
  MON_ST_LOGGER->setLogFilename    (                                         init_fldr->file("filename")    ->get(std::string     (MON_LOG_FILE    ))); \
  init_fldr = init_fldr->folder("destination"); \
  MON_ST_LOGGER->enableOutToFile   (init_fldr->file("file")   ->get(true)); \
  MON_ST_LOGGER->enableOutToConsole(init_fldr->file("console")->get(true)); \
  MON_ST_LOGGER->enableOutToSyslog (init_fldr->file("syslog") ->get(true));

//

#endif // defaulMonApplication
