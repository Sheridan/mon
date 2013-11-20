/* %Id% */
#include "libraryes/base/string/cvariant.h"
#include "defines/st.h"
#include "defines/signals-helper.h"
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
unsigned int       toUInt  (const std::string &val)        { return static_cast<unsigned int>  (std::stoul(val)); }
short              toShort (const std::string &val)        { return static_cast<short>         (std::stoi(val)) ; }
unsigned short     toUShort(const std::string &val)        { return static_cast<unsigned short>(std::stoi(val)) ; }
long               toLong  (const std::string &val)        { return std::stol  (val)   ; }
unsigned long      toULong (const std::string &val)        { return std::stoul (val)   ; }
long long          toLLong (const std::string &val)        { return std::stoll (val)   ; }
unsigned long long toULLong(const std::string &val)        { return std::stoull(val)   ; }
float              toFloat (const std::string &val)        { return std::stof  (val)   ; }
double             toDouble(const std::string &val)        { return std::stod  (val)   ; }

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
  MON_MUTEX_DESTROY(variant)
}

void CVariant::reset()
{
  MON_MUTEX_LOCK(variant)
  if(m_contentType == EContentType::String)
  {
    free(m_value.m_string);
    m_value.m_string = nullptr;
  }
  m_contentType = EContentType::Unknown;
  MON_MUTEX_UNLOCK(variant)
}

bool CVariant::isEmpty()
{
  return m_contentType == EContentType::Unknown;
}

void CVariant::set(const bool               &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::Bool  ; m_value.m_bool   = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const int                &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::Int   ; m_value.m_int    = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const unsigned int       &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::UInt  ; m_value.m_uint   = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const short              &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::Short ; m_value.m_short  = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const unsigned short     &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::UShort; m_value.m_ushort = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const long               &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::Long  ; m_value.m_long   = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const unsigned long      &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::ULong ; m_value.m_ulong  = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const long long          &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::LLong ; m_value.m_llong  = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const unsigned long long &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::ULLong; m_value.m_ullong = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const float              &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::Float ; m_value.m_float  = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const double             &val) { reset(); MON_MUTEX_LOCK(variant); m_contentType = EContentType::Double; m_value.m_double = val; MON_MUTEX_UNLOCK(variant); }
void CVariant::set(const std::string        &val)
{
  reset();
  MON_MUTEX_LOCK(variant);
  m_contentType = mon::lib::base::EContentType::String;
  m_value.m_string = static_cast<char *>(malloc(strlen(val.c_str()) + 1));
  strcpy(m_value.m_string, val.c_str());
  MON_MUTEX_UNLOCK(variant);
}

bool CVariant::tryConvert(const bool               &val) { if(!isEmpty()) { if(m_contentType != EContentType::Bool  ) { set(toBool   ()); } return true; } return false; }
bool CVariant::tryConvert(const int                &val) { if(!isEmpty()) { if(m_contentType != EContentType::Int   ) { set(toInt    ()); } return true; } return false; }
bool CVariant::tryConvert(const unsigned int       &val) { if(!isEmpty()) { if(m_contentType != EContentType::UInt  ) { set(toUInt   ()); } return true; } return false; }
bool CVariant::tryConvert(const short              &val) { if(!isEmpty()) { if(m_contentType != EContentType::Short ) { set(toShort  ()); } return true; } return false; }
bool CVariant::tryConvert(const unsigned short     &val) { if(!isEmpty()) { if(m_contentType != EContentType::UShort) { set(toUShort ()); } return true; } return false; }
bool CVariant::tryConvert(const long               &val) { if(!isEmpty()) { if(m_contentType != EContentType::Long  ) { set(toLong   ()); } return true; } return false; }
bool CVariant::tryConvert(const unsigned long      &val) { if(!isEmpty()) { if(m_contentType != EContentType::ULong ) { set(toULong  ()); } return true; } return false; }
bool CVariant::tryConvert(const long long          &val) { if(!isEmpty()) { if(m_contentType != EContentType::LLong ) { set(toLLong  ()); } return true; } return false; }
bool CVariant::tryConvert(const unsigned long long &val) { if(!isEmpty()) { if(m_contentType != EContentType::ULLong) { set(toULLong ()); } return true; } return false; }
bool CVariant::tryConvert(const float              &val) { if(!isEmpty()) { if(m_contentType != EContentType::Float ) { set(toFloat  ()); } return true; } return false; }
bool CVariant::tryConvert(const double             &val) { if(!isEmpty()) { if(m_contentType != EContentType::Double) { set(toDouble ()); } return true; } return false; }
bool CVariant::tryConvert(const std::string        &val) { if(!isEmpty()) { if(m_contentType != EContentType::String) { set(toString ()); } return true; } return false; }

void CVariant::initialize()
{
  MON_MUTEX_INITIALIZE(variant)
}

const bool CVariant::toBool()
{
  bool result = false;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = m_value.m_bool                             ; break;
    case EContentType::Int:     result = m_value.m_int    > 0                       ; break;
    case EContentType::UInt:    result = m_value.m_uint   > 0                       ; break;
    case EContentType::Short:   result = m_value.m_short  > 0                       ; break;
    case EContentType::UShort:  result = m_value.m_ushort > 0                       ; break;
    case EContentType::Long:    result = m_value.m_long   > 0                       ; break;
    case EContentType::ULong:   result = m_value.m_ulong  > 0                       ; break;
    case EContentType::LLong:   result = m_value.m_llong  > 0                       ; break;
    case EContentType::ULLong:  result = m_value.m_ullong > 0                       ; break;
    case EContentType::Float:   result = m_value.m_float  > 0                       ; break;
    case EContentType::Double:  result = m_value.m_double > 0                       ; break;
    case EContentType::String:  result = mon::lib::base::toBool(m_value.m_string)   ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined bool option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const int CVariant::toInt()
{
  int result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<int>(m_value.m_bool)          ; break;
    case EContentType::Int:     result = m_value.m_int                             ; break;
    case EContentType::UInt:    result = static_cast<int>(m_value.m_uint)          ; break;
    case EContentType::Short:   result = static_cast<int>(m_value.m_short)         ; break;
    case EContentType::UShort:  result = static_cast<int>(m_value.m_ushort)        ; break;
    case EContentType::Long:    result = static_cast<int>(m_value.m_long)          ; break;
    case EContentType::ULong:   result = static_cast<int>(m_value.m_ulong)         ; break;
    case EContentType::LLong:   result = static_cast<int>(m_value.m_llong)         ; break;
    case EContentType::ULLong:  result = static_cast<int>(m_value.m_ullong)        ; break;
    case EContentType::Float:   result = static_cast<int>(m_value.m_float)         ; break;
    case EContentType::Double:  result = static_cast<int>(m_value.m_double)        ; break;
    case EContentType::String:  result = mon::lib::base::toInt(m_value.m_string)   ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined int option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const unsigned int CVariant::toUInt()
{
  unsigned int result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<unsigned int>(m_value.m_bool)     ; break;
    case EContentType::Int:     result = static_cast<unsigned int>(m_value.m_int)      ; break;
    case EContentType::UInt:    result = m_value.m_uint                                ; break;
    case EContentType::Short:   result = static_cast<unsigned int>(m_value.m_short)    ; break;
    case EContentType::UShort:  result = static_cast<unsigned int>(m_value.m_ushort)   ; break;
    case EContentType::Long:    result = static_cast<unsigned int>(m_value.m_long)     ; break;
    case EContentType::ULong:   result = static_cast<unsigned int>(m_value.m_ulong)    ; break;
    case EContentType::LLong:   result = static_cast<unsigned int>(m_value.m_llong)    ; break;
    case EContentType::ULLong:  result = static_cast<unsigned int>(m_value.m_ullong)   ; break;
    case EContentType::Float:   result = static_cast<unsigned int>(m_value.m_float)    ; break;
    case EContentType::Double:  result = static_cast<unsigned int>(m_value.m_double)   ; break;
    case EContentType::String:  result = mon::lib::base::toUInt(m_value.m_string)      ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const short CVariant::toShort()
{
  short result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<short>(m_value.m_bool)            ; break;
    case EContentType::Int:     result = static_cast<short>(m_value.m_int)             ; break;
    case EContentType::UInt:    result = static_cast<short>(m_value.m_uint)            ; break;
    case EContentType::Short:   result = m_value.m_short                               ; break;
    case EContentType::UShort:  result = static_cast<short>(m_value.m_ushort)          ; break;
    case EContentType::Long:    result = static_cast<short>(m_value.m_long)            ; break;
    case EContentType::ULong:   result = static_cast<short>(m_value.m_ulong)           ; break;
    case EContentType::LLong:   result = static_cast<short>(m_value.m_llong)           ; break;
    case EContentType::ULLong:  result = static_cast<short>(m_value.m_ullong)          ; break;
    case EContentType::Float:   result = static_cast<short>(m_value.m_float)           ; break;
    case EContentType::Double:  result = static_cast<short>(m_value.m_double)          ; break;
    case EContentType::String:  result = mon::lib::base::toShort(m_value.m_string)     ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const unsigned short CVariant::toUShort()
{
  unsigned short result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<unsigned short>(m_value.m_bool)   ; break;
    case EContentType::Int:     result = static_cast<unsigned short>(m_value.m_int)    ; break;
    case EContentType::UInt:    result = static_cast<unsigned short>(m_value.m_uint)   ; break;
    case EContentType::Short:   result = static_cast<unsigned short>(m_value.m_short)  ; break;
    case EContentType::UShort:  result = m_value.m_ushort                              ; break;
    case EContentType::Long:    result = static_cast<unsigned short>(m_value.m_long)   ; break;
    case EContentType::ULong:   result = static_cast<unsigned short>(m_value.m_ulong)  ; break;
    case EContentType::LLong:   result = static_cast<unsigned short>(m_value.m_llong)  ; break;
    case EContentType::ULLong:  result = static_cast<unsigned short>(m_value.m_ullong) ; break;
    case EContentType::Float:   result = static_cast<unsigned short>(m_value.m_float)  ; break;
    case EContentType::Double:  result = static_cast<unsigned short>(m_value.m_double) ; break;
    case EContentType::String:  result = mon::lib::base::toUShort(m_value.m_string)    ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const long CVariant::toLong()
{
  long result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<long>(m_value.m_bool)             ; break;
    case EContentType::Int:     result = static_cast<long>(m_value.m_int)              ; break;
    case EContentType::UInt:    result = static_cast<long>(m_value.m_uint)             ; break;
    case EContentType::Short:   result = static_cast<long>(m_value.m_short)            ; break;
    case EContentType::UShort:  result = static_cast<long>(m_value.m_ushort)           ; break;
    case EContentType::Long:    result = m_value.m_long                                ; break;
    case EContentType::ULong:   result = static_cast<long>(m_value.m_ulong)            ; break;
    case EContentType::LLong:   result = static_cast<long>(m_value.m_llong)            ; break;
    case EContentType::ULLong:  result = static_cast<long>(m_value.m_ullong)           ; break;
    case EContentType::Float:   result = static_cast<long>(m_value.m_float)            ; break;
    case EContentType::Double:  result = static_cast<long>(m_value.m_double)           ; break;
    case EContentType::String:  result = mon::lib::base::toLong(m_value.m_string)      ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const unsigned long CVariant::toULong()
{
  unsigned long result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<unsigned long>(m_value.m_bool)    ; break;
    case EContentType::Int:     result = static_cast<unsigned long>(m_value.m_int)     ; break;
    case EContentType::UInt:    result = static_cast<unsigned long>(m_value.m_uint)    ; break;
    case EContentType::Short:   result = static_cast<unsigned long>(m_value.m_short)   ; break;
    case EContentType::UShort:  result = static_cast<unsigned long>(m_value.m_ushort)  ; break;
    case EContentType::Long:    result = static_cast<unsigned long>(m_value.m_long)    ; break;
    case EContentType::ULong:   result = m_value.m_ulong                               ; break;
    case EContentType::LLong:   result = static_cast<unsigned long>(m_value.m_llong)   ; break;
    case EContentType::ULLong:  result = static_cast<unsigned long>(m_value.m_ullong)  ; break;
    case EContentType::Float:   result = static_cast<unsigned long>(m_value.m_float)   ; break;
    case EContentType::Double:  result = static_cast<unsigned long>(m_value.m_double)  ; break;
    case EContentType::String:  result = mon::lib::base::toULong(m_value.m_string)     ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const long long CVariant::toLLong()
{
  long long result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<long long>(m_value.m_bool)        ; break;
    case EContentType::Int:     result = static_cast<long long>(m_value.m_int)         ; break;
    case EContentType::UInt:    result = static_cast<long long>(m_value.m_uint)        ; break;
    case EContentType::Short:   result = static_cast<long long>(m_value.m_short)       ; break;
    case EContentType::UShort:  result = static_cast<long long>(m_value.m_ushort)      ; break;
    case EContentType::Long:    result = static_cast<long long>(m_value.m_long)        ; break;
    case EContentType::ULong:   result = static_cast<long long>(m_value.m_ulong)       ; break;
    case EContentType::LLong:   result = m_value.m_llong                               ; break;
    case EContentType::ULLong:  result = static_cast<long long>(m_value.m_ullong)      ; break;
    case EContentType::Float:   result = static_cast<long long>(m_value.m_float)       ; break;
    case EContentType::Double:  result = static_cast<long long>(m_value.m_double)      ; break;
    case EContentType::String:  result = mon::lib::base::toULong(m_value.m_string)     ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const unsigned long long CVariant::toULLong()
{
  unsigned long long result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<unsigned long long>(m_value.m_bool)  ; break;
    case EContentType::Int:     result = static_cast<unsigned long long>(m_value.m_int)   ; break;
    case EContentType::UInt:    result = static_cast<unsigned long long>(m_value.m_uint)  ; break;
    case EContentType::Short:   result = static_cast<unsigned long long>(m_value.m_short) ; break;
    case EContentType::UShort:  result = static_cast<unsigned long long>(m_value.m_ushort); break;
    case EContentType::Long:    result = static_cast<unsigned long long>(m_value.m_long)  ; break;
    case EContentType::ULong:   result = static_cast<unsigned long long>(m_value.m_ulong) ; break;
    case EContentType::LLong:   result = static_cast<unsigned long long>(m_value.m_llong) ; break;
    case EContentType::ULLong:  result = m_value.m_ullong                                 ; break;
    case EContentType::Float:   result = static_cast<unsigned long long>(m_value.m_float) ; break;
    case EContentType::Double:  result = static_cast<unsigned long long>(m_value.m_double); break;
    case EContentType::String:  result = mon::lib::base::toULLong(m_value.m_string)       ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined int option, return default")       ; break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const float CVariant::toFloat()
{
  float result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<float>(m_value.m_bool)          ; break;
    case EContentType::Int:     result = static_cast<float>(m_value.m_int)           ; break;
    case EContentType::UInt:    result = static_cast<float>(m_value.m_uint)          ; break;
    case EContentType::Short:   result = static_cast<float>(m_value.m_short)         ; break;
    case EContentType::UShort:  result = static_cast<float>(m_value.m_ushort)        ; break;
    case EContentType::Long:    result = static_cast<float>(m_value.m_long)          ; break;
    case EContentType::ULong:   result = static_cast<float>(m_value.m_ulong)         ; break;
    case EContentType::LLong:   result = static_cast<float>(m_value.m_llong)         ; break;
    case EContentType::ULLong:  result = static_cast<float>(m_value.m_ullong)        ; break;
    case EContentType::Float:   result = m_value.m_float                             ; break;
    case EContentType::Double:  result = static_cast<float>(m_value.m_double)        ; break;
    case EContentType::String:  result = mon::lib::base::toDouble(m_value.m_string)  ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined float option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const double CVariant::toDouble()
{
  double result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<double>(m_value.m_bool)         ; break;
    case EContentType::Int:     result = static_cast<double>(m_value.m_int)          ; break;
    case EContentType::UInt:    result = static_cast<double>(m_value.m_uint)         ; break;
    case EContentType::Short:   result = static_cast<double>(m_value.m_short)        ; break;
    case EContentType::UShort:  result = static_cast<double>(m_value.m_ushort)       ; break;
    case EContentType::Long:    result = static_cast<double>(m_value.m_long)         ; break;
    case EContentType::ULong:   result = static_cast<double>(m_value.m_ulong)        ; break;
    case EContentType::LLong:   result = static_cast<double>(m_value.m_llong)        ; break;
    case EContentType::ULLong:  result = static_cast<double>(m_value.m_ullong)       ; break;
    case EContentType::Float:   result = static_cast<double>(m_value.m_float)        ; break;
    case EContentType::Double:  result = m_value.m_double                            ; break;
    case EContentType::String:  result = mon::lib::base::toDouble(m_value.m_string)  ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined float option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const std::string CVariant::toString()
{
  std::string result = std::string();
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = mon::lib::base::toString(m_value.m_bool)     ; break;
    case EContentType::Int:     result = mon::lib::base::toString(m_value.m_int)      ; break;
    case EContentType::UInt:    result = mon::lib::base::toString(m_value.m_uint)     ; break;
    case EContentType::Short:   result = mon::lib::base::toString(m_value.m_short)    ; break;
    case EContentType::UShort:  result = mon::lib::base::toString(m_value.m_ushort)   ; break;
    case EContentType::Long:    result = mon::lib::base::toString(m_value.m_long)     ; break;
    case EContentType::ULong:   result = mon::lib::base::toString(m_value.m_ulong)    ; break;
    case EContentType::LLong:   result = mon::lib::base::toString(m_value.m_llong)    ; break;
    case EContentType::ULLong:  result = mon::lib::base::toString(m_value.m_ullong)   ; break;
    case EContentType::Float:   result = mon::lib::base::toString(m_value.m_float)    ; break;
    case EContentType::Double:  result = mon::lib::base::toString(m_value.m_double)   ; break;
    case EContentType::String:  result = std::string(m_value.m_string)                ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined string option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const EContentType &CVariant::contentType() const
{
  return m_contentType;
}

}
}
}
