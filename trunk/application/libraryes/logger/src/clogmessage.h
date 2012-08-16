/* %Id% */
#ifndef CLOGMESSAGE_H
#define CLOGMESSAGE_H
#include <string>

namespace mon
{
namespace lib
{
namespace logger
{

enum EPriority
{
  pError   = 0,
  pWarning = 1,
  pInfo    = 2
  #ifdef MON_DEBUG
  ,pDebug   = 3
  #endif
};


class CLogMessage
{
public:
  CLogMessage(const EPriority &priority);
  ~CLogMessage();

  CLogMessage &operator<<(const int           &val);
  CLogMessage &operator<<(const unsigned int  &val);
  CLogMessage &operator<<(const double        &val);
  CLogMessage &operator<<(const float         &val);
  CLogMessage &operator<<(const bool          &val);
  CLogMessage &operator<<(const std::string   &val);
  CLogMessage &operator<<(const char          *val);
  CLogMessage &operator<<(const char          &val);
  CLogMessage &operator<<(const unsigned char &val);

  const std::string &msg() const;
  const EPriority   &pri() const;

private:
  EPriority m_priority;
  std::string m_message;
};

}
}
}
#endif // CLOGMESSAGE_H
