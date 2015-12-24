/* %Id% */
#ifndef defaulMonApplication
#define defaulMonApplication
#include "defines/global.h"
#include "libraryes/base/sequrity/csystemrights.h"
#include "libraryes/config/rw/ccmdlineparcer.h"

#ifdef MON_DEBUG
  #define MON_MAX_LOG_PRI mon::lib::logger::pDebug
#else
  #define MON_MAX_LOG_PRI mon::lib::logger::pInfo
#endif

//! Базовая инициализация приложения
#define MON_DEFAULT_APPLICATION_INIT \
  MON_CMD_LINE_ADD_OPTION("c", "config", "Load config from file", MON_CONF_FILE); \
  MON_CMD_LINE_PARCE; \
  MON_ST_CONFIG->load(MON_CMD_LINE_OPTION_VALUE("c").toString()); \
  MON_ST_CONFIG->cd(MON_ST_CONFIG->folder(MON_MODULE_NAME)); \
  MON_CFOLDER *init_fldr = MON_ST_CONFIG->folder("logger"); \
  MON_ST_LOGGER->setMaxLogPriority (static_cast<mon::lib::logger::EPriority>(init_fldr->file("max_priority")->get(static_cast<int>(MON_MAX_LOG_PRI)))); \
  MON_ST_LOGGER->setLogFilename    (                                         init_fldr->file("filename")    ->get(std::string     (MON_LOG_FILE    ))); \
  init_fldr = init_fldr->folder("destination"); \
  MON_ST_LOGGER->enableOutToFile   (init_fldr->file("file")   ->get(true)); \
  MON_ST_LOGGER->enableOutToConsole(init_fldr->file("console")->get(true)); \
  MON_ST_LOGGER->enableOutToSyslog (init_fldr->file("syslog") ->get(true)); \
  mon::lib::base::CSystemRights::setUserGroup( \
                  MON_ST_CONFIG->folder("runas")->file("user" )->get(mon::lib::base::CSystemRights::currentUserName ()),  \
                  MON_ST_CONFIG->folder("runas")->file("group")->get(mon::lib::base::CSystemRights::currentGroupName()));

#endif // defaulMonApplication
