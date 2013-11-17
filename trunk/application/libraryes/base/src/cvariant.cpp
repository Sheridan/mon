/* %Id% */
#include "cvariant.h"
#include "st.h"
#include "signals-helper.h"
#include <sstream>
#include <stdlib.h>
#include <string>

namespace mon
{
namespace lib
{
namespace base
{

bool               toBool  (const std::string &val)        { return val.compare("true") == 0; }
int                toInt   (const std::string &val)        { return std::stoi(val)     ; }
unsigned int       toUInt  (const std::string &val)        { return static_cast<unsigned int>(std::stoul(val))    ; }
short              toShort (const std::string &val)        { return static_cast<short>(std::stoi(val)); }
unsigned short     toUShort(const std::string &val)        { return static_cast<unsigned short>(std::stoi(val)); }
long               toLong  (const std::string &val)        { return std::stol(val)   ; }
unsigned long      toULong (const std::string &val)        { return std::stoul(val)   ; }
long long          toLLong (const std::string &val)        { return std::stoll(val)   ; }
unsigned long long toULLong(const std::string &val)        { return std::stoull(val)   ; }
float              toFloat (const std::string &val)        { return std::stof(val)     ; }
double             toDouble(const std::string &val)        { return std::stod(val)     ; }
std::string        toString(const bool               &val) { return val ? "true" : "false"; }
std::string        toString(const int                &val) { return std::to_string(val); }
std::string        toString(const unsigned int       &val) { return std::to_string(val); }
std::string        toString(const short              &val) { return std::to_string(val); }
std::string        toString(const unsigned short     &val) { return std::to_string(val); }
std::string        toString(const long               &val) { return std::to_string(val); }
std::string        toString(const unsigned long      &val) { return std::to_string(val); }
std::string        toString(const long long          &val) { return std::to_string(val); }
std::string        toString(const unsigned long long &val) { return std::to_string(val); }
std::string        toString(const float              &val) { return std::to_string(val); }
std::string        toString(const double             &val) { return std::to_string(val); }

CVariant::~CVariant()
{
  reset();
}

void CVariant::reset()
{
  if(m_contentType == EContentType::String)
  {
    free(m_value.m_string);
    m_value.m_string = nullptr;
  }
  m_contentType = EContentType::Unknown;
}

bool CVariant::isEmpty()
{
  return m_contentType == EContentType::Unknown;
}

void CVariant::set(const bool               &val) { reset(); m_contentType = EContentType::Bool  ; m_value.m_bool   = val; }
void CVariant::set(const int                &val) { reset(); m_contentType = EContentType::Int   ; m_value.m_int    = val; }
void CVariant::set(const unsigned int       &val) { reset(); m_contentType = EContentType::UInt  ; m_value.m_uint   = val; }
void CVariant::set(const short              &val) { reset(); m_contentType = EContentType::Short ; m_value.m_short  = val; }
void CVariant::set(const unsigned short     &val) { reset(); m_contentType = EContentType::UShort; m_value.m_ushort = val; }
void CVariant::set(const long               &val) { reset(); m_contentType = EContentType::Long  ; m_value.m_long   = val; }
void CVariant::set(const unsigned long      &val) { reset(); m_contentType = EContentType::ULong ; m_value.m_ulong  = val; }
void CVariant::set(const long long          &val) { reset(); m_contentType = EContentType::LLong ; m_value.m_llong  = val; }
void CVariant::set(const unsigned long long &val) { reset(); m_contentType = EContentType::ULLong; m_value.m_ullong = val; }
void CVariant::set(const float              &val) { reset(); m_contentType = EContentType::Float ; m_value.m_float  = val; }
void CVariant::set(const double             &val) { reset(); m_contentType = EContentType::Double; m_value.m_double = val; }
void CVariant::set(const std::string        &val)
{
  reset();
  m_contentType = mon::lib::base::EContentType::String;
  m_value.m_string = static_cast<char *>(malloc(strlen(val.c_str()) + 1));
  strcpy(m_value.m_string, val.c_str());
}

const bool CVariant::toBool() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return  m_value.m_bool;
    case EContentType::Int:     return  m_value.m_int   > 0;
    case EContentType::UInt:    return  m_value.m_uint  > 0;
    case EContentType::Short:   return  m_value.m_short > 0;
    case EContentType::UShort:  return  m_value.m_ushort> 0;
    case EContentType::Long:    return  m_value.m_long  > 0;
    case EContentType::ULong:   return  m_value.m_ulong > 0;
    case EContentType::LLong:   return  m_value.m_llong > 0;
    case EContentType::ULLong:  return  m_value.m_ullong> 0;
    case EContentType::Float:   return  m_value.m_float > 0;
    case EContentType::Double:  return  m_value.m_double> 0;
    case EContentType::String:  return  mon::lib::base::toBool(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined bool option, return default"); return false;
  } return false;
}

const int CVariant::toInt() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return static_cast<int>(m_value.m_bool);
    case EContentType::Int:     return m_value.m_int;
    case EContentType::UInt:    return static_cast<int>(m_value.m_uint);
    case EContentType::Short:   return static_cast<int>(m_value.m_short);
    case EContentType::UShort:  return static_cast<int>(m_value.m_ushort);
    case EContentType::Long:    return static_cast<int>(m_value.m_long);
    case EContentType::ULong:   return static_cast<int>(m_value.m_ulong);
    case EContentType::LLong:   return static_cast<int>(m_value.m_llong);
    case EContentType::ULLong:  return static_cast<int>(m_value.m_ullong);
    case EContentType::Float:   return static_cast<int>(m_value.m_float);
    case EContentType::Double:  return static_cast<int>(m_value.m_double);
    case EContentType::String:  return mon::lib::base::toInt(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined int option, return default"); return 0;
  } return 0;
}

const unsigned int CVariant::toUInt() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return static_cast<unsigned int>(m_value.m_bool);
    case EContentType::Int:     return static_cast<unsigned int>(m_value.m_int);
    case EContentType::UInt:    return m_value.m_uint;
    case EContentType::Short:   return static_cast<unsigned int>(m_value.m_short);
    case EContentType::UShort:  return static_cast<unsigned int>(m_value.m_ushort);
    case EContentType::Long:    return static_cast<unsigned int>(m_value.m_long);
    case EContentType::ULong:   return static_cast<unsigned int>(m_value.m_ulong);
    case EContentType::LLong:   return static_cast<unsigned int>(m_value.m_llong);
    case EContentType::ULLong:  return static_cast<unsigned int>(m_value.m_ullong);
    case EContentType::Float:   return static_cast<unsigned int>(m_value.m_float);
    case EContentType::Double:  return static_cast<unsigned int>(m_value.m_double);
    case EContentType::String:  return mon::lib::base::toUInt(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); return 0;
  } return 0;
}

const short CVariant::toShort() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return static_cast<short>(m_value.m_bool);
    case EContentType::Int:     return static_cast<short>(m_value.m_int);
    case EContentType::UInt:    return static_cast<short>(m_value.m_uint);
    case EContentType::Short:   return m_value.m_short;
    case EContentType::UShort:  return static_cast<short>(m_value.m_ushort);
    case EContentType::Long:    return static_cast<short>(m_value.m_long);
    case EContentType::ULong:   return static_cast<short>(m_value.m_ulong);
    case EContentType::LLong:   return static_cast<short>(m_value.m_llong);
    case EContentType::ULLong:  return static_cast<short>(m_value.m_ullong);
    case EContentType::Float:   return static_cast<short>(m_value.m_float);
    case EContentType::Double:  return static_cast<short>(m_value.m_double);
    case EContentType::String:  return mon::lib::base::toShort(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); return 0;
  } return 0;
}

const unsigned short CVariant::toUShort() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return static_cast<unsigned short>(m_value.m_bool);
    case EContentType::Int:     return static_cast<unsigned short>(m_value.m_int);
    case EContentType::UInt:    return static_cast<unsigned short>(m_value.m_uint);
    case EContentType::Short:   return static_cast<unsigned short>(m_value.m_short);
    case EContentType::UShort:  return m_value.m_ushort;
    case EContentType::Long:    return static_cast<unsigned short>(m_value.m_long);
    case EContentType::ULong:   return static_cast<unsigned short>(m_value.m_ulong);
    case EContentType::LLong:   return static_cast<unsigned short>(m_value.m_llong);
    case EContentType::ULLong:  return static_cast<unsigned short>(m_value.m_ullong);
    case EContentType::Float:   return static_cast<unsigned short>(m_value.m_float);
    case EContentType::Double:  return static_cast<unsigned short>(m_value.m_double);
    case EContentType::String:  return mon::lib::base::toUShort(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); return 0;
  } return 0;
}

const long CVariant::toLong() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return static_cast<long>(m_value.m_bool);
    case EContentType::Int:     return static_cast<long>(m_value.m_int);
    case EContentType::UInt:    return static_cast<long>(m_value.m_uint);
    case EContentType::Short:   return static_cast<long>(m_value.m_short);
    case EContentType::UShort:  return static_cast<long>(m_value.m_ushort);
    case EContentType::Long:    return m_value.m_long;
    case EContentType::ULong:   return static_cast<long>(m_value.m_ulong);
    case EContentType::LLong:   return static_cast<long>(m_value.m_llong);
    case EContentType::ULLong:  return static_cast<long>(m_value.m_ullong);
    case EContentType::Float:   return static_cast<long>(m_value.m_float);
    case EContentType::Double:  return static_cast<long>(m_value.m_double);
    case EContentType::String:  return mon::lib::base::toLong(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); return 0;
  } return 0;
}

const unsigned long CVariant::toULong() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return static_cast<unsigned long>(m_value.m_bool);
    case EContentType::Int:     return static_cast<unsigned long>(m_value.m_int);
    case EContentType::UInt:    return static_cast<unsigned long>(m_value.m_uint);
    case EContentType::Short:   return static_cast<unsigned long>(m_value.m_short);
    case EContentType::UShort:  return static_cast<unsigned long>(m_value.m_ushort);
    case EContentType::Long:    return static_cast<unsigned long>(m_value.m_long);
    case EContentType::ULong:   return m_value.m_ulong;
    case EContentType::LLong:   return static_cast<unsigned long>(m_value.m_llong);
    case EContentType::ULLong:  return static_cast<unsigned long>(m_value.m_ullong);
    case EContentType::Float:   return static_cast<unsigned long>(m_value.m_float);
    case EContentType::Double:  return static_cast<unsigned long>(m_value.m_double);
    case EContentType::String:  return mon::lib::base::toULong(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); return 0;
  } return 0;
}

const long long CVariant::toLLong() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return static_cast<long long>(m_value.m_bool);
    case EContentType::Int:     return static_cast<long long>(m_value.m_int);
    case EContentType::UInt:    return static_cast<long long>(m_value.m_uint);
    case EContentType::Short:   return static_cast<long long>(m_value.m_short);
    case EContentType::UShort:  return static_cast<long long>(m_value.m_ushort);
    case EContentType::Long:    return static_cast<long long>(m_value.m_long);
    case EContentType::ULong:   return static_cast<long long>(m_value.m_ulong);
    case EContentType::LLong:   return m_value.m_llong;
    case EContentType::ULLong:  return static_cast<long long>(m_value.m_ullong);
    case EContentType::Float:   return static_cast<long long>(m_value.m_float);
    case EContentType::Double:  return static_cast<long long>(m_value.m_double);
    case EContentType::String:  return mon::lib::base::toULong(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); return 0;
  } return 0;
}

const unsigned long long CVariant::toULLong() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return static_cast<unsigned long long>(m_value.m_bool);
    case EContentType::Int:     return static_cast<unsigned long long>(m_value.m_int);
    case EContentType::UInt:    return static_cast<unsigned long long>(m_value.m_uint);
    case EContentType::Short:   return static_cast<unsigned long long>(m_value.m_short);
    case EContentType::UShort:  return static_cast<unsigned long long>(m_value.m_ushort);
    case EContentType::Long:    return static_cast<unsigned long long>(m_value.m_long);
    case EContentType::ULong:   return static_cast<unsigned long long>(m_value.m_ulong);
    case EContentType::LLong:   return static_cast<unsigned long long>(m_value.m_llong);
    case EContentType::ULLong:  return m_value.m_ullong;
    case EContentType::Float:   return static_cast<unsigned long long>(m_value.m_float);
    case EContentType::Double:  return static_cast<unsigned long long>(m_value.m_double);
    case EContentType::String:  return mon::lib::base::toULLong(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined int option, return default"); return 0;
  } return 0;
}

const float CVariant::toFloat() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return static_cast<float>(m_value.m_bool);
    case EContentType::Int:     return static_cast<float>(m_value.m_int);
    case EContentType::UInt:    return static_cast<float>(m_value.m_uint);
    case EContentType::Short:   return static_cast<float>(m_value.m_short);
    case EContentType::UShort:  return static_cast<float>(m_value.m_ushort);
    case EContentType::Long:    return static_cast<float>(m_value.m_long);
    case EContentType::ULong:   return static_cast<float>(m_value.m_ulong);
    case EContentType::LLong:   return static_cast<float>(m_value.m_llong);
    case EContentType::ULLong:  return static_cast<float>(m_value.m_ullong);
    case EContentType::Float:   return m_value.m_float;
    case EContentType::Double:  return static_cast<float>(m_value.m_double);
    case EContentType::String:  return mon::lib::base::toDouble(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined float option, return default"); return 0;
  } return 0;
}

const double CVariant::toDouble() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return static_cast<double>(m_value.m_bool);
    case EContentType::Int:     return static_cast<double>(m_value.m_int);
    case EContentType::UInt:    return static_cast<double>(m_value.m_uint);
    case EContentType::Short:   return static_cast<double>(m_value.m_short);
    case EContentType::UShort:  return static_cast<double>(m_value.m_ushort);
    case EContentType::Long:    return static_cast<double>(m_value.m_long);
    case EContentType::ULong:   return static_cast<double>(m_value.m_ulong);
    case EContentType::LLong:   return static_cast<double>(m_value.m_llong);
    case EContentType::ULLong:  return static_cast<double>(m_value.m_ullong);
    case EContentType::Float:   return static_cast<double>(m_value.m_float);
    case EContentType::Double:  return m_value.m_double;
    case EContentType::String:  return mon::lib::base::toDouble(m_value.m_string);
    case EContentType::Unknown: MON_LOG_WRN("Undefined float option, return default"); return 0;
  } return 0;
}

const std::string CVariant::toString() const
{
  switch(m_contentType)
  {
    case EContentType::Bool:    return mon::lib::base::toString(m_value.m_bool);
    case EContentType::Int:     return mon::lib::base::toString(m_value.m_int);
    case EContentType::UInt:    return mon::lib::base::toString(m_value.m_uint);
    case EContentType::Short:   return mon::lib::base::toString(m_value.m_short);
    case EContentType::UShort:  return mon::lib::base::toString(m_value.m_ushort);
    case EContentType::Long:    return mon::lib::base::toString(m_value.m_long);
    case EContentType::ULong:   return mon::lib::base::toString(m_value.m_ulong);
    case EContentType::LLong:   return mon::lib::base::toString(m_value.m_llong);
    case EContentType::ULLong:  return mon::lib::base::toString(m_value.m_ullong);
    case EContentType::Float:   return mon::lib::base::toString(m_value.m_float);
    case EContentType::Double:  return mon::lib::base::toString(m_value.m_double);
    case EContentType::String:  return m_value.m_string;
    case EContentType::Unknown: MON_LOG_WRN("Undefined string option, return default"); return std::string();
  } return std::string();
}

const EContentType &CVariant::contentType() const
{
  return m_contentType;
}

}
}
}
