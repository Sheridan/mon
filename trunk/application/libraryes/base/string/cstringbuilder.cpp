/* %Id% */
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include "libraryes/base/string/cstringbuilder.h"

using std::snprintf;
#define MON_SB_SPRINTF(_template,_value) \
  { \
    char *result = nullptr; \
    int len = 0; \
    len = snprintf(result, 0, _template, _value); \
    if(len > 0) \
    { \
      result = static_cast<char *>(malloc(sizeof(char) * len)); \
      snprintf(result, len + 1, _template, _value); \
      MON_SB_CONCAT(m_string, result) \
      free(result); \
    } \
  }

//#define MON_SB_SPRINTF(_template,_value) MON_SB_CONCAT(m_string, std::sprintf(_template,_value));

namespace mon
{
namespace lib
{
namespace base
{

CStringBuilderBase::CStringBuilderBase(const std::string &init) : m_string(init) {}
CStringBuilderBase::~CStringBuilderBase() {}

#define MON_SB_CONCAT(_dest,_val) _dest += _val;
void CStringBuilderBase::append(const int                 &val) { MON_SB_SPRINTF("%d"   , val                   ); }
void CStringBuilderBase::append(const unsigned int        &val) { MON_SB_SPRINTF("%u"   , val                   ); }
void CStringBuilderBase::append(const short               &val) { MON_SB_SPRINTF("%hi"  , val                   ); }
void CStringBuilderBase::append(const unsigned short      &val) { MON_SB_SPRINTF("%hu"  , val                   ); }
void CStringBuilderBase::append(const long                &val) { MON_SB_SPRINTF("%li"  , val                   ); }
void CStringBuilderBase::append(const unsigned long       &val) { MON_SB_SPRINTF("%lu"  , val                   ); }
void CStringBuilderBase::append(const long long           &val) { MON_SB_SPRINTF("%lli" , val                   ); }
void CStringBuilderBase::append(const unsigned long long  &val) { MON_SB_SPRINTF("%llu" , val                   ); }
void CStringBuilderBase::append(const double              &val) { MON_SB_SPRINTF("%f"   , val                   ); }
void CStringBuilderBase::append(const char                *val) { MON_SB_CONCAT(m_string, std::string(val)      ); }
void CStringBuilderBase::append(const char                &val) { MON_SB_SPRINTF("%c"   , val                   ); }
void CStringBuilderBase::append(const unsigned char       &val) { MON_SB_SPRINTF("%c"   , val                   ); }
void CStringBuilderBase::append(const bool                &val) { MON_SB_CONCAT(m_string, val ? "true" : "false"); }
void CStringBuilderBase::append(const std::string         &val) { MON_SB_CONCAT(m_string, val                   ); }
void CStringBuilderBase::append(const float               &val) { MON_SB_SPRINTF("%f"   , val                   ); }
void CStringBuilderBase::append(const mon::lib::protocol::EProtocolMessageType &val) { append(static_cast<int>(val)); }
#undef MON_SB_CONCAT

#define MON_SB_CONCAT(_dest,_val) _dest = _val + _dest;
void CStringBuilderBase::preface(const int                 &val) { MON_SB_SPRINTF("%d"   , val                   ); }
void CStringBuilderBase::preface(const unsigned int        &val) { MON_SB_SPRINTF("%u"   , val                   ); }
void CStringBuilderBase::preface(const short               &val) { MON_SB_SPRINTF("%hi"  , val                   ); }
void CStringBuilderBase::preface(const unsigned short      &val) { MON_SB_SPRINTF("%hu"  , val                   ); }
void CStringBuilderBase::preface(const long                &val) { MON_SB_SPRINTF("%li"  , val                   ); }
void CStringBuilderBase::preface(const unsigned long       &val) { MON_SB_SPRINTF("%lu"  , val                   ); }
void CStringBuilderBase::preface(const long long           &val) { MON_SB_SPRINTF("%lli" , val                   ); }
void CStringBuilderBase::preface(const unsigned long long  &val) { MON_SB_SPRINTF("%llu" , val                   ); }
void CStringBuilderBase::preface(const double              &val) { MON_SB_SPRINTF("%f"   , val                   ); }
void CStringBuilderBase::preface(const char                *val) { MON_SB_CONCAT(m_string, std::string(val)      ); }
void CStringBuilderBase::preface(const char                &val) { MON_SB_SPRINTF("%c"   , val                   ); }
void CStringBuilderBase::preface(const unsigned char       &val) { MON_SB_SPRINTF("%c"   , val                   ); }
void CStringBuilderBase::preface(const bool                &val) { MON_SB_CONCAT(m_string, val ? "true" : "false"); }
void CStringBuilderBase::preface(const std::string         &val) { MON_SB_CONCAT(m_string, val                   ); }
void CStringBuilderBase::preface(const float               &val) { MON_SB_SPRINTF("%f"   , val                   ); }
void CStringBuilderBase::preface(const mon::lib::protocol::EProtocolMessageType &val) { preface(static_cast<int>(val)); }

void CStringBuilderBase::removeLast(const int &characters) { m_string.erase(m_string.end()-characters, m_string.end()); }

const std::string &CStringBuilderBase::string() const { return m_string ; }

}
}
}
