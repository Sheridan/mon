/* %Id% */
#include "cvariant.h"
#include "st.h"
#include "signals-helper.h"
#include <sstream>
#include <stdlib.h>

namespace mon
{
namespace lib
{
namespace base
{

#define MON_VARIANT_FROM_STRING(_type) _type res; std::istringstream(val) >> res; return res;
#define MON_VARIANT_TO_STRING std::string res; std::stringstream buf; buf << val; buf >> res; return res;

int                toInt   (const std::string &val)        { MON_VARIANT_FROM_STRING(int)   ; }
bool               toBool  (const std::string &val)        { MON_VARIANT_FROM_STRING(bool)  ; }
float              toFloat (const std::string &val)        { MON_VARIANT_FROM_STRING(float) ; }
double             toDouble(const std::string &val)        { MON_VARIANT_FROM_STRING(double); }
unsigned int       toUInt  (const std::string &val)        { MON_VARIANT_FROM_STRING(unsigned int); }
unsigned long long toULLong(const std::string &val)        { MON_VARIANT_FROM_STRING(unsigned long long); }
std::string        toString(const int    &val)             { return std::to_string(val); }
std::string        toString(const bool   &val)             { return std::to_string(val); }
std::string        toString(const float  &val)             { return std::to_string(val); }
std::string        toString(const double &val)             { return std::to_string(val); }
std::string        toString(const unsigned int  &val)      { return std::to_string(val); }
std::string        toString(const unsigned long long &val) { return std::to_string(val); }

CVariant::~CVariant()
{
  reset();
}

void CVariant::reset()
{
  if(m_contentType == ctString)
  {
    free(m_value.m_string);
    m_value.m_string = nullptr;
  }
  m_contentType = ctUnknown;
}

bool CVariant::isEmpty()
{
  return m_contentType == ctUnknown;
}

void CVariant::set(const bool &val)
{
  reset();
  m_contentType = ctBool;
  m_value.m_bool = val;
}

void CVariant::set(const int &val)
{
  reset();
  m_contentType = ctInt;
  m_value.m_int = val;
}

void CVariant::set(const double &val)
{
  reset();
  m_contentType = ctFloat;
  m_value.m_float = val;
}

void CVariant::set(const std::string &val)
{
  reset();
  m_contentType = mon::lib::base::ctString;
  m_value.m_string = static_cast<char *>(malloc(strlen(val.c_str()) + 1));
  strcpy(m_value.m_string, val.c_str());
}

void CVariant::set(const unsigned int &val)
{
  reset();
  m_contentType = ctUInt;
  m_value.m_uint = val;
}

void CVariant::set(const unsigned long long &val)
{
  reset();
  m_contentType = ctULLong;
  m_value.m_ull = val;
}

const bool CVariant::toBool() const
{
  switch(m_contentType)
  {
    case ctBool:      return  m_value.m_bool;
    case ctInt:       return  m_value.m_int   > 0;
    case ctUInt:      return  m_value.m_uint  > 0;
    case ctULLong:    return  m_value.m_ull   > 0;
    case ctFloat:     return  m_value.m_float > 0;
    case ctString:    return  m_value.m_string != nullptr;
    case ctUnknown: MON_LOG_WRN("Undefined bool option, return default"); return true;
  } return true;
}

const int CVariant::toInt() const
{
  switch(m_contentType)
  {
    case ctInt:       return m_value.m_int;
    case ctBool:      return static_cast<int>(m_value.m_bool);
    case ctFloat:     return static_cast<int>(m_value.m_float);
    case ctUInt:      return static_cast<int>(m_value.m_uint);
    case ctULLong:    return static_cast<int>(m_value.m_ull);
    case ctString:    return strtol(m_value.m_string, nullptr, 10);
    case ctUnknown: MON_LOG_WRN("Undefined int option, return default"); return 0;
  } return 0;
}

const double CVariant::toFloat() const
{
  switch(m_contentType)
  {
    case ctFloat:    return m_value.m_float;
    case ctInt:      return static_cast<double>(m_value.m_int);
    case ctBool:     return static_cast<double>(m_value.m_bool);
    case ctUInt:     return static_cast<double>(m_value.m_uint);
    case ctULLong:   return static_cast<double>(m_value.m_ull);
    case ctString:   return strtod(m_value.m_string, nullptr);
    case ctUnknown: MON_LOG_WRN("Undefined float option, return default"); return 0;
  } return 0;
}

const std::string CVariant::toString() const
{
  switch(m_contentType)
  {
    case ctString:    return m_value.m_string;
    case ctFloat:     return mon::lib::base::toString(m_value.m_float);
    case ctInt:       return mon::lib::base::toString(m_value.m_int);
    case ctUInt:      return mon::lib::base::toString(m_value.m_uint);
    case ctULLong:    return mon::lib::base::toString(m_value.m_ull);
    case ctBool:      return m_value.m_bool ? "true" : "false";
    case ctUnknown: MON_LOG_WRN("Undefined string option, return default"); return "undef";
  } return "undef";
}


const unsigned int CVariant::toUInt() const
{
  switch(m_contentType)
  {
    case ctUInt:      return m_value.m_uint;
    case ctInt:       return static_cast<unsigned int>(m_value.m_int);
    case ctBool:      return static_cast<unsigned int>(m_value.m_bool);
    case ctFloat:     return static_cast<unsigned int>(m_value.m_float);
    case ctULLong:    return static_cast<unsigned int>(m_value.m_ull);
    case ctString:    return strtol(m_value.m_string, nullptr, 10);
    case ctUnknown: MON_LOG_WRN("Undefined variant option, return default"); return 0;
  } return 0;
}

const unsigned long long CVariant::toULLong() const
{
  switch(m_contentType)
  {
    case ctULLong:    return m_value.m_ull;
    case ctInt:       return static_cast<unsigned long long>(m_value.m_int);
    case ctBool:      return static_cast<unsigned long long>(m_value.m_bool);
    case ctFloat:     return static_cast<unsigned long long>(m_value.m_float);
    case ctUInt:      return static_cast<unsigned long long>(m_value.m_uint);
    case ctString:    return strtol(m_value.m_string, nullptr, 10);
    case ctUnknown: MON_LOG_WRN("Undefined int option, return default"); return 0;
  } return 0;
}

const EContentType &CVariant::contentType() const
{
  return m_contentType;
}

}
}
}
