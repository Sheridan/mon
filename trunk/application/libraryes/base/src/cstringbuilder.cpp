/* %Id% */
#include "cstringbuilder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MON_SB_SPRINTF(_template,_value) \
  { \
    char *result = NULL; \
    int len = 0; \
    len = snprintf(result, 0, _template, _value); \
    if(len > 0) \
    { \
      result = static_cast<char *>(malloc(sizeof(char) * len)); \
      snprintf(result, len + 1, _template, _value); \
      MON_SB_CONCAT(m_message, result) \
      free(result); \
    } \
  }

namespace mon
{
namespace lib
{
namespace base
{

CStringBuilder::CStringBuilder(const std::string &init) : m_message(init) {}

#define MON_SB_CONCAT(_dest,_val) _dest += _val;
void CStringBuilder::append(const int                 &val) { MON_SB_SPRINTF("%d"    , val                   ); }
void CStringBuilder::append(const unsigned int        &val) { MON_SB_SPRINTF("%u"    , val                   ); }
void CStringBuilder::append(const unsigned long long  &val) { MON_SB_SPRINTF("%llu"  , val                   ); }
void CStringBuilder::append(const double              &val) { MON_SB_SPRINTF("%f"    , val                   ); }
void CStringBuilder::append(const char                *val) { MON_SB_CONCAT(m_message, std::string(val)      ); }
void CStringBuilder::append(const char                &val) { MON_SB_SPRINTF("%c"    , val                   ); }
void CStringBuilder::append(const unsigned char       &val) { MON_SB_SPRINTF("%c"    , val                   ); }
void CStringBuilder::append(const bool                &val) { MON_SB_CONCAT(m_message, val ? "true" : "false"); }
void CStringBuilder::append(const std::string         &val) { MON_SB_CONCAT(m_message, val                   ); }
void CStringBuilder::append(const float               &val) { MON_SB_SPRINTF("%f"    , val                   ); }
#undef MON_SB_CONCAT

#define MON_SB_CONCAT(_dest,_val) _dest = _val + _dest;
void CStringBuilder::preface(const int                 &val) { MON_SB_SPRINTF("%d"    , val                   ); }
void CStringBuilder::preface(const unsigned int        &val) { MON_SB_SPRINTF("%u"    , val                   ); }
void CStringBuilder::preface(const unsigned long long  &val) { MON_SB_SPRINTF("%llu"  , val                   ); }
void CStringBuilder::preface(const double              &val) { MON_SB_SPRINTF("%f"    , val                   ); }
void CStringBuilder::preface(const char                *val) { MON_SB_CONCAT(m_message, std::string(val)      ); }
void CStringBuilder::preface(const char                &val) { MON_SB_SPRINTF("%c"    , val                   ); }
void CStringBuilder::preface(const unsigned char       &val) { MON_SB_SPRINTF("%c"    , val                   ); }
void CStringBuilder::preface(const bool                &val) { MON_SB_CONCAT(m_message, val ? "true" : "false"); }
void CStringBuilder::preface(const std::string         &val) { MON_SB_CONCAT(m_message, val                   ); }
void CStringBuilder::preface(const float               &val) { MON_SB_SPRINTF("%f"    , val                   ); }

void CStringBuilder::removeLast(const int &characters) { m_message.erase(m_message.end()-characters, m_message.end()); }

const std::string &CStringBuilder::msg() const { return m_message ; }

}
}
}
