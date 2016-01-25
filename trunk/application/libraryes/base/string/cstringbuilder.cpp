/* %Id% */
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include "libraryes/base/string/cstringbuilder.h"
#include "libraryes/base/string/cvariant.h"

namespace mon
{
namespace lib
{
namespace base
{

CStringBuilderBase::CStringBuilderBase(const std::string &init) : m_string(init) {}
CStringBuilderBase::~CStringBuilderBase() {}

#define MON_SB_CONCAT(_val) m_string += _val;
void CStringBuilderBase::append(const int                 &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const unsigned int        &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const short               &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const unsigned short      &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const long                &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const unsigned long       &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const long long           &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const unsigned long long  &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const double              &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const char                *val) { MON_SB_CONCAT(std::string(val)             ); }
void CStringBuilderBase::append(const char                &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const unsigned char       &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const bool                &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const std::string         &val) { MON_SB_CONCAT(val)                          ; }
void CStringBuilderBase::append(const float               &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::append(const mon::lib::protocol::EProtocolMessageType &val) { append(static_cast<int>(val)); }
#undef MON_SB_CONCAT

#define MON_SB_CONCAT(_val) m_string = _val + m_string;
void CStringBuilderBase::preface(const int                 &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const unsigned int        &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const short               &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const unsigned short      &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const long                &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const unsigned long       &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const long long           &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const unsigned long long  &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const double              &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const char                *val) { MON_SB_CONCAT(std::string(val)             ); }
void CStringBuilderBase::preface(const char                &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const unsigned char       &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const bool                &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const std::string         &val) { MON_SB_CONCAT(val)                          ; }
void CStringBuilderBase::preface(const float               &val) { MON_SB_CONCAT(mon::lib::base::toString(val)); }
void CStringBuilderBase::preface(const mon::lib::protocol::EProtocolMessageType &val) { preface(static_cast<int>(val)); }

void CStringBuilderBase::removeLast(const int &characters) { m_string.erase(m_string.end()-characters, m_string.end()); }

const std::string &CStringBuilderBase::string() const { return m_string ; }

}
}
}
