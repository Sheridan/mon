/* %Id% */
#include "clogger.h"
#include "clogmessage.h"
#include <string.h>
#include <syslog.h>
#include <time.h>

namespace mon
{
namespace lib
{
namespace logger
{

CLogger::CLogger()
{
  MON_MUTEX_INITIALIZE(log);
  MON_MUTEX_LOCK(log);
  m_filename    = "";
  m_outFile     = false;
  m_outConsole  = true;
  m_outSyslog   = true;
#ifdef MON_DEBUG
  m_maxPriority = pDebug;
#else
  m_maxPriority = pWarning;
#endif
  strcpy(m_priorityesNames[pError  ], "err\0");
  strcpy(m_priorityesNames[pWarning], "wrn\0");
  strcpy(m_priorityesNames[pInfo   ], "nfo\0");
#ifdef MON_DEBUG
  strcpy(m_priorityesNames[pDebug  ], "dbg\0");
#endif
  MON_MUTEX_UNLOCK(log);
}

CLogger::~CLogger()
{
  MON_MUTEX_DESTROY(log);
}

void CLogger::log(const CLogMessage &message)
{
  log(message.string(), message.pri());
}

void CLogger::log(const std::string &message, EPriority priority)
{
  if ( priority <= m_maxPriority && (m_outFile || m_outConsole || m_outSyslog))
  {
    MON_MUTEX_LOCK(log);
    if ( m_outFile &&  !m_filename.empty() ) { logToFile   (message, priority); }
    if ( m_outConsole                      ) { logToConsole(message, priority); }
    if ( m_outSyslog                       ) { logToSyslog (message, priority); }
    MON_MUTEX_UNLOCK(log);
  }
}

void CLogger::logToFile   (const std::string &message, const EPriority &priority)
{
  FILE *stream = fopen(m_filename.c_str(), "a");
  logToStream(message, priority, stream);
  fclose(stream);
}

void CLogger::logToConsole(const std::string &message, const EPriority &priority)
{
  logToStream(message, priority, priority <= pWarning ? stderr : stdout);
}

void CLogger::logToSyslog (const std::string &message, const EPriority &priority)
{
  int sl_priority = 0;
  switch (priority)
  {
    case pError  : sl_priority = LOG_ERR    ; break;
    case pInfo   : sl_priority = LOG_INFO   ; break;
    case pWarning: sl_priority = LOG_WARNING; break;
#ifdef MON_DEBUG
    case pDebug  : sl_priority = LOG_DEBUG  ; break;
#endif
  }
  syslog(sl_priority, "%s", message.c_str());
}

void CLogger::logToStream (const std::string &message, const EPriority &priority, FILE *stream)
{
  time_t now;
  tm *curtime;
  char time_buf[20]; //2010.01.01 19:55:15
  time(&now);
  curtime = localtime(&now);
  strftime(time_buf, sizeof(time_buf), "%Y.%m.%d %H:%M:%S", curtime);
  fprintf(stream, "%s %s %s\n", time_buf, m_priorityesNames[priority], message.c_str());
}

#define MON_SET_LOG_OPTION(_to,_from) \
  MON_MUTEX_LOCK(log); \
  _to = _from; \
  MON_MUTEX_UNLOCK(log);

void CLogger::setLogFilename    (const std::string &filename) { MON_SET_LOG_OPTION(m_filename   , filename); }
void CLogger::setMaxLogPriority (const EPriority &priority  ) { MON_SET_LOG_OPTION(m_maxPriority, priority); }
void CLogger::enableOutToFile   (bool enable                ) { MON_SET_LOG_OPTION(m_outFile    , enable  ); }
void CLogger::enableOutToConsole(bool enable                ) { MON_SET_LOG_OPTION(m_outConsole , enable  ); }
void CLogger::enableOutToSyslog (bool enable                ) { MON_SET_LOG_OPTION(m_outSyslog  , enable  ); }

}
}
}

