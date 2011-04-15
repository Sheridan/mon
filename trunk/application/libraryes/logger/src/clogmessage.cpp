#include "clogmessage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MON_LOGMESSAGE_SPRINTF(_template,_value) \
  { \
    char *result = NULL; \
    int len = 0; \
    len = snprintf(result, 0, _template, _value); \
    if(len > 0) \
    { \
      result = static_cast<char *>(malloc(sizeof(char) * len)); \
      snprintf(result, len + 1, _template, _value); \
      m_message += result; \
      free(result); \
    } \
  }

namespace mon
{
namespace lib
{
namespace logger
{

CLogMessage::CLogMessage(const EPriority &priority)
{
  m_message = "";
  m_priority = priority;
}

CLogMessage::~CLogMessage()
{}

CLogMessage &CLogMessage::operator<<(const int           &val) { MON_LOGMESSAGE_SPRINTF("%d", val)  ; return *this; }
CLogMessage &CLogMessage::operator<<(const unsigned int  &val) { MON_LOGMESSAGE_SPRINTF("%u", val)  ; return *this; }
CLogMessage &CLogMessage::operator<<(const double        &val) { MON_LOGMESSAGE_SPRINTF("%f", val)  ; return *this; }
CLogMessage &CLogMessage::operator<<(const char          *val) { m_message += std::string(val)      ;  ; return *this; }
CLogMessage &CLogMessage::operator<<(const char          &val) { MON_LOGMESSAGE_SPRINTF("%c", val)  ; return *this; }
CLogMessage &CLogMessage::operator<<(const unsigned char &val) { MON_LOGMESSAGE_SPRINTF("%c", val)  ; return *this; }
CLogMessage &CLogMessage::operator<<(const bool          &val) { m_message += val ? "true" : "false"; return *this; }
CLogMessage &CLogMessage::operator<<(const std::string   &val) { m_message += val                   ; return *this; }
CLogMessage &CLogMessage::operator<<(const float         &val) { return operator<<(static_cast<double>(val))      ; }

const std::string &CLogMessage::msg() const { return m_message ; }
const EPriority   &CLogMessage::pri() const { return m_priority; }


}
}
}
