/* %Id% */
#include "libraryes/logger/clogmessage.h"

namespace mon
{
namespace lib
{
namespace logger
{

CLogMessage::CLogMessage(const EPriority &priority)
  : mon::lib::base::CStringBuilderBase(), m_priority(priority)
{}

CLogMessage::~CLogMessage()
{}

const EPriority &CLogMessage::pri() const { return m_priority; }

}
}
}
