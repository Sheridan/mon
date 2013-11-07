/* %Id% */
#ifndef CVARIANT_H
#define CVARIANT_H
#include <string>

namespace mon
{
namespace lib
{
namespace base
{

int          toInt   (const std::string &val);
bool         toBool  (const std::string &val);
float        toFloat (const std::string &val);
double       toDouble(const std::string &val);
std::string  toString(const int         &val);
std::string  toString(const bool        &val);
std::string  toString(const float       &val);
std::string  toString(const double      &val);
unsigned int toUInt  (const std::string &val);
unsigned long long toULLong  (const std::string &val);

enum EContentType
{
  ctUnknown,
  ctBool,
  ctInt,
  ctFloat,
  ctString
};

union UContent
{
  bool   m_bool  ;
  int    m_int   ;
  double m_float ;
  char * m_string;
};

class CVariant
{
public:
  CVariant(                       ) { reset();  }
  CVariant(const bool         &val) { set(val); }
  CVariant(const int          &val) { set(val); }
  CVariant(const double       &val) { set(val); }
  CVariant(const std::string  &val) { set(val); }
  CVariant(const CVariant     &val) { set(val); }
  virtual ~CVariant();
  void reset();
  bool isEmpty();
  const bool          toBool      () const;
  const int           toInt       () const;
  const double        toFloat     () const;
  const std::string   toString    () const;
  const EContentType &contentType () const;

  void set(const bool        &val);
  void set(const int         &val);
  void set(const double      &val);
  void set(const std::string &val);
  void set(const CVariant    &val);

protected:
  EContentType m_contentType;
  UContent     m_value;
};

}
}
}
#endif // CVARIANT_H
