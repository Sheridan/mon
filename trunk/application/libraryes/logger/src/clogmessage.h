/* %Id% */
#ifndef CLOGMESSAGE_H
#define CLOGMESSAGE_H
#include "cstringbuilder.h"

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


class CLogMessage : public mon::lib::base::CStringBuilder
{
    MON_STRING_BUILDER(CLogMessage)
public:
  CLogMessage(const EPriority &priority);
  ~CLogMessage();

  const EPriority   &pri() const;

private:
  EPriority m_priority;
};

}
}
}
#endif // CLOGMESSAGE_H
