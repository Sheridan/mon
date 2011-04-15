#ifndef CVARIANT_H
#define CVARIANT_H
#include <string>

namespace mon
{
namespace lib
{
namespace config
{

enum EContenType
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
  CVariant();
  CVariant(const bool        &val);
  CVariant(const int         &val);
  CVariant(const double      &val);
  CVariant(const std::string &val);
  CVariant(const CVariant    &val);
  virtual ~CVariant();
  void set(const bool        &val);
  void set(const int         &val);
  void set(const double      &val);
  void set(const std::string &val);
  void set(const CVariant    &val);
  bool        get(const bool        &def);
  int         get(const int         &def);
  double      get(const double      &def);
  std::string get(const std::string &def);
  void reset();
  bool isEmpty();
  const bool        toBool      () const;
  const int         toInt       () const;
  const double      toFloat     () const;
  const std::string toString    () const;
  const EContenType &contentType() const;

private:
  EContenType m_contentType;
  UContent    m_value;
};

}
}
}
#endif // CVARIANT_H
