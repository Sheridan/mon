/* %Id% */
#include "cvariant.h"
#include "st.h"
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

int    toInt   (const std::string &val)      { MON_VARIANT_FROM_STRING(int)   ; }
bool   toBool  (const std::string &val)      { MON_VARIANT_FROM_STRING(bool)  ; }
float  toFloat (const std::string &val)      { MON_VARIANT_FROM_STRING(float) ; }
double toDouble(const std::string &val)      { MON_VARIANT_FROM_STRING(double); }
std::string toString(const int    &val)      { MON_VARIANT_TO_STRING }
std::string toString(const bool   &val)      { MON_VARIANT_TO_STRING }
std::string toString(const float  &val)      { MON_VARIANT_TO_STRING }
std::string toString(const double &val)      { MON_VARIANT_TO_STRING }
unsigned int toUInt (const std::string &val) { MON_VARIANT_FROM_STRING(unsigned int); }


CVariant::~CVariant()
{
  reset();
}

void CVariant::reset()
{
  if(m_contentType == ctString)
  {
    free(m_value.m_string);
    m_value.m_string = NULL;
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

void CVariant::set(const CVariant &val)
{
  switch(val.contentType())
  {
    case ctBool:    set(val.toBool  ()); break;
    case ctInt:     set(val.toInt   ()); break;
    case ctFloat:   set(val.toFloat ()); break;
    case ctString:  set(val.toString()); break;
    case ctUnknown: reset(); break;
  }
}

const bool CVariant::toBool() const
{
  switch(m_contentType)
  {
    case ctBool:   return  m_value.m_bool;
    case ctInt:    return  m_value.m_int   > 0;
    case ctFloat:  return  m_value.m_float > 0;
    case ctString: return  m_value.m_string != NULL;
    case ctUnknown: MON_LOG_WRN("Undefined bool option, return default"); return true;
  } return true;
}

const int CVariant::toInt() const
{
  switch(m_contentType)
  {
    case ctInt:    return m_value.m_int;
    case ctBool:   return static_cast<int>(m_value.m_bool);
    case ctFloat:  return static_cast<int>(m_value.m_float);
    case ctString: return strtol(m_value.m_string, NULL, 10);
    case ctUnknown: MON_LOG_WRN("Undefined int option, return default"); return 0;
  } return 0;
}

const double CVariant::toFloat() const
{
  switch(m_contentType)
  {
    case ctFloat:  return m_value.m_float;
    case ctInt:    return static_cast<double>(m_value.m_int);
    case ctBool:   return static_cast<double>(m_value.m_bool);
    case ctString: return strtod(m_value.m_string, NULL);
    case ctUnknown: MON_LOG_WRN("Undefined float option, return default"); return 0;
  } return 0;
}

const std::string CVariant::toString() const
{

  switch(m_contentType)
  {
    case ctString:return m_value.m_string;
    case ctFloat: return mon::lib::base::toString(m_value.m_float);
    case ctInt:   return mon::lib::base::toString(m_value.m_int);
    case ctBool:  return m_value.m_bool ? "true" : "false";
    case ctUnknown: MON_LOG_WRN("Undefined string option, return default"); return "undef";
  } return "undef";
}

const EContentType &CVariant::contentType() const
{
  return m_contentType;
}

}
}
}
