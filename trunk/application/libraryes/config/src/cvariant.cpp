#include "cvariant.h"
#include "st.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
namespace mon
{
namespace lib
{
namespace config
{

CVariant::CVariant(                       ) { m_contentType = ctUnknown; reset();  }
CVariant::CVariant(const bool         &val) { m_contentType = ctUnknown; set(val); }
CVariant::CVariant(const int          &val) { m_contentType = ctUnknown; set(val); }
CVariant::CVariant(const double       &val) { m_contentType = ctUnknown; set(val); }
CVariant::CVariant(const std::string  &val) { m_contentType = ctUnknown; set(val); }
CVariant::CVariant(const CVariant     &val) { m_contentType = ctUnknown; set(val); }

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
  m_contentType = ctString;
  m_value.m_string = static_cast<char *>(malloc(strlen(val.c_str()) + 1));
  strcpy(m_value.m_string, val.c_str());
}

void CVariant::set(const CVariant &val)
{
  switch(val.contentType())
  {
    case ctBool:   set(val.toBool  ()); break;
    case ctInt:    set(val.toInt   ()); break;
    case ctFloat:  set(val.toFloat ()); break;
    case ctString: set(val.toString()); break;
    case ctUnknown: reset(); break;
  }
}

bool        CVariant::get(const bool        &def) { if(m_contentType != ctBool)   { set(def); } return m_value.m_bool  ; }
int         CVariant::get(const int         &def) { if(m_contentType != ctInt)    { set(def); } return m_value.m_int   ; }
double      CVariant::get(const double      &def) { if(m_contentType != ctFloat)  { set(def); } return m_value.m_float ; }
std::string CVariant::get(const std::string &def) { if(m_contentType != ctString) { set(def); } return m_value.m_string; }

const bool CVariant::toBool() const
{
  switch(m_contentType)
  {
    case ctBool:   return  m_value.m_bool;
    case ctInt:    return  m_value.m_int   > 0;
    case ctFloat:  return  m_value.m_float > 0;
    case ctString: return  m_value.m_string != NULL;
    case ctUnknown: MON_LOG_WRN("Undefined bool option, return default"); return true;
  }
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
  }
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
  }
}

const std::string CVariant::toString() const
{
  char *val = NULL;
  int len = 0;
  switch(m_contentType)
  {
    case ctString:
      return m_value.m_string;
    case ctFloat:
      {
        len = snprintf(val, 0, "%f", m_value.m_float);
        if(len > 0)
        {
          val = static_cast<char *>(malloc(sizeof(char) * len));
          snprintf(val, len + 1, "%f", m_value.m_float);
        }
      }
      break;
    case ctInt:
      {
        len = snprintf(val, 0, "%d", m_value.m_int);
        if(len > 0)
        {
          val = static_cast<char *>(malloc(sizeof(char) * len));
          snprintf(val, len + 1, "%d", m_value.m_int);
        }
      }
      break;
    case ctBool:
      return m_value.m_bool ? "true" : "false";
    case ctUnknown: MON_LOG_WRN("Undefined string option, return default"); return "undef";
  }
  return std::string(val);
}

const EContenType &CVariant::contentType() const
{
  return m_contentType;
}

}
}
}
