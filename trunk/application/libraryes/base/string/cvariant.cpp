/* %Id% */
#include <sstream>
#include <stdlib.h>
#include <string>
#include "defines/st.h"
#include "defines/signals-helper.h"
#include "libraryes/base/string/cvariant.h"

namespace mon
{
namespace lib
{
namespace base
{

bool               toBool  (const std::string &val) { return val.compare("true") == 0; }
char               toChar  (const std::string &val) { return val[0]; }
int                toInt   (const std::string &val) { return std::stoi(val)     ; }
unsigned int       toUInt  (const std::string &val) { return static_cast<unsigned int>  (std::stoul(val)); }
short              toShort (const std::string &val) { return static_cast<short>         (std::stoi (val)); }
unsigned short     toUShort(const std::string &val) { return static_cast<unsigned short>(std::stoi (val)); }
long               toLong  (const std::string &val) { return std::stol  (val)   ; }
unsigned long      toULong (const std::string &val) { return std::stoul (val)   ; }
long long          toLLong (const std::string &val) { return std::stoll (val)   ; }
unsigned long long toULLong(const std::string &val) { return std::stoull(val)   ; }
float              toFloat (const std::string &val) { return std::stof  (val)   ; }
double             toDouble(const std::string &val) { return std::stod  (val)   ; }

std::string        toString(const bool               &val) { return val ? "true" : "false"; }
std::string        toString(const char               &val) { std::string s = "0"; s[0] = val; return s; }
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

CVariant::CVariant ( const CVariant &val )
{
  initialize();
  switch(val.m_contentType)
  {
    case EContentType::Bool:    set(*(val.m_value.m_bool  )); break;
    case EContentType::Char:    set(*(val.m_value.m_char  )); break;
    case EContentType::Int:     set(*(val.m_value.m_int   )); break;
    case EContentType::UInt:    set(*(val.m_value.m_uint  )); break;
    case EContentType::Short:   set(*(val.m_value.m_short )); break;
    case EContentType::UShort:  set(*(val.m_value.m_ushort)); break;
    case EContentType::Long:    set(*(val.m_value.m_long  )); break;
    case EContentType::ULong:   set(*(val.m_value.m_ulong )); break;
    case EContentType::LLong:   set(*(val.m_value.m_llong )); break;
    case EContentType::ULLong:  set(*(val.m_value.m_ullong)); break;
    case EContentType::Float:   set(*(val.m_value.m_float )); break;
    case EContentType::Double:  set(*(val.m_value.m_double)); break;
    case EContentType::String:  set(*(val.m_value.m_string)); break;
    case EContentType::Unknown:                               break;
  }
}

CVariant::~CVariant()
{
  reset();
  MON_MUTEX_DESTROY(variant)
}

void CVariant::initialize ()
{
  m_contentType = EContentType::Unknown;
  MON_MUTEX_INITIALIZE(variant);
}

void CVariant::reset()
{
  MON_MUTEX_LOCK(variant)
  switch(m_contentType)
  {
    case EContentType::Bool:    delete m_value.m_bool  ; break;
    case EContentType::Char:    delete m_value.m_char  ; break;
    case EContentType::Int:     delete m_value.m_int   ; break;
    case EContentType::UInt:    delete m_value.m_uint  ; break;
    case EContentType::Short:   delete m_value.m_short ; break;
    case EContentType::UShort:  delete m_value.m_ushort; break;
    case EContentType::Long:    delete m_value.m_long  ; break;
    case EContentType::ULong:   delete m_value.m_ulong ; break;
    case EContentType::LLong:   delete m_value.m_llong ; break;
    case EContentType::ULLong:  delete m_value.m_ullong; break;
    case EContentType::Float:   delete m_value.m_float ; break;
    case EContentType::Double:  delete m_value.m_double; break;
    case EContentType::String:  delete m_value.m_string; break;
    case EContentType::Unknown:                          break;
  }
  m_contentType = EContentType::Unknown;
  MON_MUTEX_UNLOCK(variant)
}

bool CVariant::isEmpty()
{
  return m_contentType == EContentType::Unknown;
}

#define MON_VARIANT_SET_TEMPLATE(_type,_contentType,_unionMember) \
  if(!isEmpty()) { reset(); } MON_MUTEX_LOCK(variant); m_contentType = EContentType::_contentType; m_value._unionMember = new _type(val); MON_MUTEX_UNLOCK(variant);

void CVariant::set(const bool               &val) { MON_VARIANT_SET_TEMPLATE(bool              ,Bool  ,m_bool)  ; }
void CVariant::set(const char               &val) { MON_VARIANT_SET_TEMPLATE(char              ,Char  ,m_char)  ; }
void CVariant::set(const int                &val) { MON_VARIANT_SET_TEMPLATE(int               ,Int   ,m_int)   ; }
void CVariant::set(const unsigned int       &val) { MON_VARIANT_SET_TEMPLATE(unsigned int      ,UInt  ,m_uint)  ; }
void CVariant::set(const short              &val) { MON_VARIANT_SET_TEMPLATE(short             ,Short ,m_short) ; }
void CVariant::set(const unsigned short     &val) { MON_VARIANT_SET_TEMPLATE(unsigned short    ,UShort,m_ushort); }
void CVariant::set(const long               &val) { MON_VARIANT_SET_TEMPLATE(long              ,Long  ,m_long)  ; }
void CVariant::set(const unsigned long      &val) { MON_VARIANT_SET_TEMPLATE(unsigned long     ,ULong ,m_ulong) ; }
void CVariant::set(const long long          &val) { MON_VARIANT_SET_TEMPLATE(long long         ,LLong ,m_llong) ; }
void CVariant::set(const unsigned long long &val) { MON_VARIANT_SET_TEMPLATE(unsigned long long,ULLong,m_ullong); }
void CVariant::set(const float              &val) { MON_VARIANT_SET_TEMPLATE(float             ,Float ,m_float) ; }
void CVariant::set(const double             &val) { MON_VARIANT_SET_TEMPLATE(double            ,Double,m_double); }
void CVariant::set(const std::string        &val) { MON_VARIANT_SET_TEMPLATE(std::string       ,String,m_string); }
void CVariant::set(const char               *val) { MON_VARIANT_SET_TEMPLATE(std::string       ,String,m_string); }

#define MON_VARIANT_TRYCONVERT_TEMPLATE(_contentType) \
  if(!isEmpty()) { if(m_contentType != EContentType::_contentType  ) { set(to##_contentType()); } return true; } return false;

bool CVariant::tryConvert(const bool               &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(Bool  ); }
bool CVariant::tryConvert(const char               &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(Char  ); }
bool CVariant::tryConvert(const int                &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(Int   ); }
bool CVariant::tryConvert(const unsigned int       &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(UInt  ); }
bool CVariant::tryConvert(const short              &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(Short ); }
bool CVariant::tryConvert(const unsigned short     &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(UShort); }
bool CVariant::tryConvert(const long               &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(Long  ); }
bool CVariant::tryConvert(const unsigned long      &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(ULong ); }
bool CVariant::tryConvert(const long long          &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(LLong ); }
bool CVariant::tryConvert(const unsigned long long &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(ULLong); }
bool CVariant::tryConvert(const float              &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(Float ); }
bool CVariant::tryConvert(const double             &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(Double); }
bool CVariant::tryConvert(const std::string        &val) { MON_VARIANT_TRYCONVERT_TEMPLATE(String); }

const bool CVariant::toBool()  const
{
  bool result = false;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = *(m_value.m_bool)                                   ; break;
    case EContentType::Char:    result = *(m_value.m_char  ) > 0 &&  *(m_value.m_char) != 'f'; break;
    case EContentType::Int:     result = *(m_value.m_int   ) > 0                             ; break;
    case EContentType::UInt:    result = *(m_value.m_uint  ) > 0                             ; break;
    case EContentType::Short:   result = *(m_value.m_short ) > 0                             ; break;
    case EContentType::UShort:  result = *(m_value.m_ushort) > 0                             ; break;
    case EContentType::Long:    result = *(m_value.m_long  ) > 0                             ; break;
    case EContentType::ULong:   result = *(m_value.m_ulong ) > 0                             ; break;
    case EContentType::LLong:   result = *(m_value.m_llong ) > 0                             ; break;
    case EContentType::ULLong:  result = *(m_value.m_ullong) > 0                             ; break;
    case EContentType::Float:   result = *(m_value.m_float ) > 0                             ; break;
    case EContentType::Double:  result = *(m_value.m_double) > 0                             ; break;
    case EContentType::String:  result = mon::lib::base::toBool(*(m_value.m_string))         ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined bool option, return default")         ; break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const char CVariant::toChar()  const
{
  char result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = *(m_value.m_bool) ? 't' : 'f'              ; break;
    case EContentType::Char:    result = *(m_value.m_char)                          ; break;
    case EContentType::Int:     result = static_cast<char>(*(m_value.m_int   ))     ; break;
    case EContentType::UInt:    result = static_cast<char>(*(m_value.m_uint  ))     ; break;
    case EContentType::Short:   result = static_cast<char>(*(m_value.m_short ))     ; break;
    case EContentType::UShort:  result = static_cast<char>(*(m_value.m_ushort))     ; break;
    case EContentType::Long:    result = static_cast<char>(*(m_value.m_long  ))     ; break;
    case EContentType::ULong:   result = static_cast<char>(*(m_value.m_ulong ))     ; break;
    case EContentType::LLong:   result = static_cast<char>(*(m_value.m_llong ))     ; break;
    case EContentType::ULLong:  result = static_cast<char>(*(m_value.m_ullong))     ; break;
    case EContentType::Float:   result = static_cast<char>(*(m_value.m_float ))     ; break;
    case EContentType::Double:  result = static_cast<char>(*(m_value.m_double))     ; break;
    case EContentType::String:  result = mon::lib::base::toChar(*(m_value.m_string)); break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined int option, return default") ; break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const int CVariant::toInt()  const
{
  int result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<int>(*(m_value.m_bool  ))     ; break;
    case EContentType::Char:    result = static_cast<int>(*(m_value.m_char  ))     ; break;
    case EContentType::Int:     result = *(m_value.m_int)                          ; break;
    case EContentType::UInt:    result = static_cast<int>(*(m_value.m_uint  ))     ; break;
    case EContentType::Short:   result = static_cast<int>(*(m_value.m_short ))     ; break;
    case EContentType::UShort:  result = static_cast<int>(*(m_value.m_ushort))     ; break;
    case EContentType::Long:    result = static_cast<int>(*(m_value.m_long  ))     ; break;
    case EContentType::ULong:   result = static_cast<int>(*(m_value.m_ulong ))     ; break;
    case EContentType::LLong:   result = static_cast<int>(*(m_value.m_llong ))     ; break;
    case EContentType::ULLong:  result = static_cast<int>(*(m_value.m_ullong))     ; break;
    case EContentType::Float:   result = static_cast<int>(*(m_value.m_float ))     ; break;
    case EContentType::Double:  result = static_cast<int>(*(m_value.m_double))     ; break;
    case EContentType::String:  result = mon::lib::base::toInt(*(m_value.m_string)); break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined int option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const unsigned int CVariant::toUInt()  const
{
  unsigned int result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<unsigned int>(*(m_value.m_bool  )); break;
    case EContentType::Char:    result = static_cast<unsigned int>(*(m_value.m_char  )); break;
    case EContentType::Int:     result = static_cast<unsigned int>(*(m_value.m_int   )); break;
    case EContentType::UInt:    result = *(m_value.m_uint)                             ; break;
    case EContentType::Short:   result = static_cast<unsigned int>(*(m_value.m_short )); break;
    case EContentType::UShort:  result = static_cast<unsigned int>(*(m_value.m_ushort)); break;
    case EContentType::Long:    result = static_cast<unsigned int>(*(m_value.m_long  )); break;
    case EContentType::ULong:   result = static_cast<unsigned int>(*(m_value.m_ulong )); break;
    case EContentType::LLong:   result = static_cast<unsigned int>(*(m_value.m_llong )); break;
    case EContentType::ULLong:  result = static_cast<unsigned int>(*(m_value.m_ullong)); break;
    case EContentType::Float:   result = static_cast<unsigned int>(*(m_value.m_float )); break;
    case EContentType::Double:  result = static_cast<unsigned int>(*(m_value.m_double)); break;
    case EContentType::String:  result = mon::lib::base::toUInt(*(m_value.m_string))   ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const short CVariant::toShort()  const
{
  short result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<short>(*(m_value.m_bool  ))       ; break;
    case EContentType::Char:    result = static_cast<short>(*(m_value.m_char  ))       ; break;
    case EContentType::Int:     result = static_cast<short>(*(m_value.m_int   ))       ; break;
    case EContentType::UInt:    result = static_cast<short>(*(m_value.m_uint  ))       ; break;
    case EContentType::Short:   result = *(m_value.m_short)                            ; break;
    case EContentType::UShort:  result = static_cast<short>(*(m_value.m_ushort))       ; break;
    case EContentType::Long:    result = static_cast<short>(*(m_value.m_long  ))       ; break;
    case EContentType::ULong:   result = static_cast<short>(*(m_value.m_ulong ))       ; break;
    case EContentType::LLong:   result = static_cast<short>(*(m_value.m_llong ))       ; break;
    case EContentType::ULLong:  result = static_cast<short>(*(m_value.m_ullong))       ; break;
    case EContentType::Float:   result = static_cast<short>(*(m_value.m_float ))       ; break;
    case EContentType::Double:  result = static_cast<short>(*(m_value.m_double))       ; break;
    case EContentType::String:  result = mon::lib::base::toShort(*(m_value.m_string))  ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const unsigned short CVariant::toUShort()  const
{
  unsigned short result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<unsigned short>(*(m_value.m_bool  )); break;
    case EContentType::Char:    result = static_cast<unsigned short>(*(m_value.m_char  )); break;
    case EContentType::Int:     result = static_cast<unsigned short>(*(m_value.m_int   )); break;
    case EContentType::UInt:    result = static_cast<unsigned short>(*(m_value.m_uint  )); break;
    case EContentType::Short:   result = static_cast<unsigned short>(*(m_value.m_short )); break;
    case EContentType::UShort:  result = *(m_value.m_ushort)                             ; break;
    case EContentType::Long:    result = static_cast<unsigned short>(*(m_value.m_long  )); break;
    case EContentType::ULong:   result = static_cast<unsigned short>(*(m_value.m_ulong )); break;
    case EContentType::LLong:   result = static_cast<unsigned short>(*(m_value.m_llong )); break;
    case EContentType::ULLong:  result = static_cast<unsigned short>(*(m_value.m_ullong)); break;
    case EContentType::Float:   result = static_cast<unsigned short>(*(m_value.m_float )); break;
    case EContentType::Double:  result = static_cast<unsigned short>(*(m_value.m_double)); break;
    case EContentType::String:  result = mon::lib::base::toUShort(*(m_value.m_string))   ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default")  ; break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const long CVariant::toLong()  const
{
  long result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<long>(*(m_value.m_bool  ))        ; break;
    case EContentType::Char:    result = static_cast<long>(*(m_value.m_char  ))        ; break;
    case EContentType::Int:     result = static_cast<long>(*(m_value.m_int   ))        ; break;
    case EContentType::UInt:    result = static_cast<long>(*(m_value.m_uint  ))        ; break;
    case EContentType::Short:   result = static_cast<long>(*(m_value.m_short ))        ; break;
    case EContentType::UShort:  result = static_cast<long>(*(m_value.m_ushort))        ; break;
    case EContentType::Long:    result = *(m_value.m_long)                             ; break;
    case EContentType::ULong:   result = static_cast<long>(*(m_value.m_ulong ))        ; break;
    case EContentType::LLong:   result = static_cast<long>(*(m_value.m_llong ))        ; break;
    case EContentType::ULLong:  result = static_cast<long>(*(m_value.m_ullong))        ; break;
    case EContentType::Float:   result = static_cast<long>(*(m_value.m_float ))        ; break;
    case EContentType::Double:  result = static_cast<long>(*(m_value.m_double))        ; break;
    case EContentType::String:  result = mon::lib::base::toLong(*(m_value.m_string))   ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const unsigned long CVariant::toULong()  const
{
  unsigned long result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<unsigned long>(*(m_value.m_bool  )); break;
    case EContentType::Char:    result = static_cast<unsigned long>(*(m_value.m_char  )); break;
    case EContentType::Int:     result = static_cast<unsigned long>(*(m_value.m_int   )); break;
    case EContentType::UInt:    result = static_cast<unsigned long>(*(m_value.m_uint  )); break;
    case EContentType::Short:   result = static_cast<unsigned long>(*(m_value.m_short )); break;
    case EContentType::UShort:  result = static_cast<unsigned long>(*(m_value.m_ushort)); break;
    case EContentType::Long:    result = static_cast<unsigned long>(*(m_value.m_long  )); break;
    case EContentType::ULong:   result = *(m_value.m_ulong)                             ; break;
    case EContentType::LLong:   result = static_cast<unsigned long>(*(m_value.m_llong )); break;
    case EContentType::ULLong:  result = static_cast<unsigned long>(*(m_value.m_ullong)); break;
    case EContentType::Float:   result = static_cast<unsigned long>(*(m_value.m_float )); break;
    case EContentType::Double:  result = static_cast<unsigned long>(*(m_value.m_double)); break;
    case EContentType::String:  result = mon::lib::base::toULong(*(m_value.m_string))   ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default") ; break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const long long CVariant::toLLong()  const
{
  long long result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<long long>(*(m_value.m_bool  ))   ; break;
    case EContentType::Char:    result = static_cast<long long>(*(m_value.m_char  ))   ; break;
    case EContentType::Int:     result = static_cast<long long>(*(m_value.m_int   ))   ; break;
    case EContentType::UInt:    result = static_cast<long long>(*(m_value.m_uint  ))   ; break;
    case EContentType::Short:   result = static_cast<long long>(*(m_value.m_short ))   ; break;
    case EContentType::UShort:  result = static_cast<long long>(*(m_value.m_ushort))   ; break;
    case EContentType::Long:    result = static_cast<long long>(*(m_value.m_long  ))   ; break;
    case EContentType::ULong:   result = static_cast<long long>(*(m_value.m_ulong ))   ; break;
    case EContentType::LLong:   result = *(m_value.m_llong)                            ; break;
    case EContentType::ULLong:  result = static_cast<long long>(*(m_value.m_ullong))   ; break;
    case EContentType::Float:   result = static_cast<long long>(*(m_value.m_float ))   ; break;
    case EContentType::Double:  result = static_cast<long long>(*(m_value.m_double))   ; break;
    case EContentType::String:  result = mon::lib::base::toLLong(*(m_value.m_string)) ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined variant option, return default"); break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const unsigned long long CVariant::toULLong()  const
{
  unsigned long long result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<unsigned long long>(*(m_value.m_bool  )); break;
    case EContentType::Char:    result = static_cast<unsigned long long>(*(m_value.m_char  )); break;
    case EContentType::Int:     result = static_cast<unsigned long long>(*(m_value.m_int   )); break;
    case EContentType::UInt:    result = static_cast<unsigned long long>(*(m_value.m_uint  )); break;
    case EContentType::Short:   result = static_cast<unsigned long long>(*(m_value.m_short )); break;
    case EContentType::UShort:  result = static_cast<unsigned long long>(*(m_value.m_ushort)); break;
    case EContentType::Long:    result = static_cast<unsigned long long>(*(m_value.m_long  )); break;
    case EContentType::ULong:   result = static_cast<unsigned long long>(*(m_value.m_ulong )); break;
    case EContentType::LLong:   result = static_cast<unsigned long long>(*(m_value.m_llong )); break;
    case EContentType::ULLong:  result = *(m_value.m_ullong)                                 ; break;
    case EContentType::Float:   result = static_cast<unsigned long long>(*(m_value.m_float )); break;
    case EContentType::Double:  result = static_cast<unsigned long long>(*(m_value.m_double)); break;
    case EContentType::String:  result = mon::lib::base::toULLong(*(m_value.m_string))       ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined int option, return default")          ; break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const float CVariant::toFloat()  const
{
  float result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<float>(*(m_value.m_bool  ))      ; break;
    case EContentType::Char:    result = static_cast<float>(*(m_value.m_char  ))      ; break;
    case EContentType::Int:     result = static_cast<float>(*(m_value.m_int   ))      ; break;
    case EContentType::UInt:    result = static_cast<float>(*(m_value.m_uint  ))      ; break;
    case EContentType::Short:   result = static_cast<float>(*(m_value.m_short ))      ; break;
    case EContentType::UShort:  result = static_cast<float>(*(m_value.m_ushort))      ; break;
    case EContentType::Long:    result = static_cast<float>(*(m_value.m_long  ))      ; break;
    case EContentType::ULong:   result = static_cast<float>(*(m_value.m_ulong ))      ; break;
    case EContentType::LLong:   result = static_cast<float>(*(m_value.m_llong ))      ; break;
    case EContentType::ULLong:  result = static_cast<float>(*(m_value.m_ullong))      ; break;
    case EContentType::Float:   result = *(m_value.m_float)                           ; break;
    case EContentType::Double:  result = static_cast<float>(*(m_value.m_double))      ; break;
    case EContentType::String:  result = mon::lib::base::toFloat(*(m_value.m_string)) ; break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined float option, return default") ; break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const double CVariant::toDouble()  const
{
  double result = 0;
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = static_cast<double>(*(m_value.m_bool  ))     ; break;
    case EContentType::Char:    result = static_cast<double>(*(m_value.m_char  ))     ; break;
    case EContentType::Int:     result = static_cast<double>(*(m_value.m_int   ))     ; break;
    case EContentType::UInt:    result = static_cast<double>(*(m_value.m_uint  ))     ; break;
    case EContentType::Short:   result = static_cast<double>(*(m_value.m_short ))     ; break;
    case EContentType::UShort:  result = static_cast<double>(*(m_value.m_ushort))     ; break;
    case EContentType::Long:    result = static_cast<double>(*(m_value.m_long  ))     ; break;
    case EContentType::ULong:   result = static_cast<double>(*(m_value.m_ulong ))     ; break;
    case EContentType::LLong:   result = static_cast<double>(*(m_value.m_llong ))     ; break;
    case EContentType::ULLong:  result = static_cast<double>(*(m_value.m_ullong))     ; break;
    case EContentType::Float:   result = static_cast<double>(*(m_value.m_float ))     ; break;
    case EContentType::Double:  result = *(m_value.m_double)                          ; break;
    case EContentType::String:  result = mon::lib::base::toDouble(*(m_value.m_string)); break;
    case EContentType::Unknown: MON_LOG_WRN("Undefined float option, return default") ; break;
  }
  MON_MUTEX_UNLOCK(variant);
  return result;
}

const std::string CVariant::toString()  const
{
  std::string result = "";
  MON_MUTEX_LOCK(variant);
  switch(m_contentType)
  {
    case EContentType::Bool:    result = mon::lib::base::toString(*(m_value.m_bool  )); break;
    case EContentType::Char:    result = mon::lib::base::toString(*(m_value.m_char  )); break;
    case EContentType::Int:     result = mon::lib::base::toString(*(m_value.m_int   )); break;
    case EContentType::UInt:    result = mon::lib::base::toString(*(m_value.m_uint  )); break;
    case EContentType::Short:   result = mon::lib::base::toString(*(m_value.m_short )); break;
    case EContentType::UShort:  result = mon::lib::base::toString(*(m_value.m_ushort)); break;
    case EContentType::Long:    result = mon::lib::base::toString(*(m_value.m_long  )); break;
    case EContentType::ULong:   result = mon::lib::base::toString(*(m_value.m_ulong )); break;
    case EContentType::LLong:   result = mon::lib::base::toString(*(m_value.m_llong )); break;
    case EContentType::ULLong:  result = mon::lib::base::toString(*(m_value.m_ullong)); break;
    case EContentType::Float:   result = mon::lib::base::toString(*(m_value.m_float )); break;
    case EContentType::Double:  result = mon::lib::base::toString(*(m_value.m_double)); break;
    case EContentType::String:  result = *(m_value.m_string)                          ; break;
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
