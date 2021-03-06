/* %Id% */
#ifndef CLOGGER_H
#define CLOGGER_H
#include <stdio.h>
#include "defines/mutex-helper.h"
#include "libraryes/logger/clogmessage.h"

namespace mon
{
namespace lib
{
namespace logger
{

#ifdef MON_DEBUG
  #define MPN_PRIO_NUM 4
#else
  #define MPN_PRIO_NUM 3
#endif

//! Логгер событий
class CLogger
{
    MON_MUTEX_DECLARE(log)
  public:
    CLogger();
    ~CLogger();
    void setLogFilename    (const std::string &filename);
    void setMaxLogPriority (const EPriority   &priority);

    void enableOutToFile   (bool enable = true);
    void enableOutToConsole(bool enable = true);
    void enableOutToSyslog (bool enable = true);

    void log(const std::string &message, EPriority priority = pInfo);
    void log(const CLogMessage &message);

  private:
    std::string m_filename;
    bool m_outFile;
    bool m_outConsole;
    bool m_outSyslog;
    EPriority m_maxPriority;
    char m_priorityesNames[MPN_PRIO_NUM][4];

    void logToFile   (const std::string &message, const EPriority &priority);
    void logToConsole(const std::string &message, const EPriority &priority);
    void logToSyslog (const std::string &message, const EPriority &priority);
    void logToStream (const std::string &message, const EPriority &priority, FILE *stream);

};

}
}
}
#endif // CLOGGER_H
