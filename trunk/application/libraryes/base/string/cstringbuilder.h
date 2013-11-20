/* %Id% */
#ifndef CSTRINGBUILDER_H
#define CSTRINGBUILDER_H
#include <string>
#include "defines/protocol-control.h"

#define MON_STRING_BUILDER_BASE(_class,_implement) \
  public: \
  virtual _class &operator<<(const int                 &val) _implement; \
  virtual _class &operator<<(const unsigned int        &val) _implement; \
  virtual _class &operator<<(const unsigned long long  &val) _implement; \
  virtual _class &operator<<(const double              &val) _implement; \
  virtual _class &operator<<(const float               &val) _implement; \
  virtual _class &operator<<(const bool                &val) _implement; \
  virtual _class &operator<<(const std::string         &val) _implement; \
  virtual _class &operator<<(const char                *val) _implement; \
  virtual _class &operator<<(const char                &val) _implement; \
  virtual _class &operator<<(const unsigned char       &val) _implement; \
  virtual _class &operator+(const int                 &val) _implement; \
  virtual _class &operator+(const unsigned int        &val) _implement; \
  virtual _class &operator+(const unsigned long long  &val) _implement; \
  virtual _class &operator+(const double              &val) _implement; \
  virtual _class &operator+(const float               &val) _implement; \
  virtual _class &operator+(const bool                &val) _implement; \
  virtual _class &operator+(const std::string         &val) _implement; \
  virtual _class &operator+(const char                *val) _implement; \
  virtual _class &operator+(const char                &val) _implement; \
  virtual _class &operator+(const unsigned char       &val) _implement; \
  virtual _class &operator<<(mon::lib::protocol::EProtocolMessageType &val) _implement; \
  virtual _class &operator+(mon::lib::protocol::EProtocolMessageType &val) _implement;

#define MON_STRING_BUILDER_DEFAULT_IMPLEMENT final { append(val); return *this; }
#define MON_STRING_BUILDER(_class) MON_STRING_BUILDER_BASE(_class, MON_STRING_BUILDER_DEFAULT_IMPLEMENT)

//  _class &operator>>(const int           &val) { preface(val); return *this; }
//  _class &operator>>(const unsigned int  &val) { preface(val); return *this; }
//  _class &operator>>(const double        &val) { preface(val); return *this; }
//  _class &operator>>(const float         &val) { preface(val); return *this; }
//  _class &operator>>(const bool          &val) { preface(val); return *this; }
//  _class &operator>>(const std::string   &val) { preface(val); return *this; }
//  _class &operator>>(const char          *val) { preface(val); return *this; }
//  _class &operator>>(const char          &val) { preface(val); return *this; }
//  _class &operator>>(const unsigned char &val) { preface(val); return *this; }
//  _class &operator-(const int           &val) { preface(val); return *this; }
//  _class &operator-(const unsigned int  &val) { preface(val); return *this; }
//  _class &operator-(const double        &val) { preface(val); return *this; }
//  _class &operator-(const float         &val) { preface(val); return *this; }
//  _class &operator-(const bool          &val) { preface(val); return *this; }
//  _class &operator-(const std::string   &val) { preface(val); return *this; }
//  _class &operator-(const char          *val) { preface(val); return *this; }
//  _class &operator-(const char          &val) { preface(val); return *this; }
//  _class &operator-(const unsigned char &val) { preface(val); return *this; }

namespace mon
{
namespace lib
{
namespace base
{

//! Конкатенатор строк из чего попало
class CStringBuilderBase
{
    MON_STRING_BUILDER_BASE(CStringBuilderBase,=0)
  public:
    CStringBuilderBase(const std::string &init = "");
    virtual ~CStringBuilderBase();

    virtual void append(const int                 &val);
    virtual void append(const unsigned int        &val);
    virtual void append(const short               &val);
    virtual void append(const unsigned short      &val);
    virtual void append(const long                &val);
    virtual void append(const unsigned long       &val);
    virtual void append(const long long           &val);
    virtual void append(const unsigned long long  &val);
    virtual void append(const double              &val);
    virtual void append(const float               &val);
    virtual void append(const bool                &val);
    virtual void append(const std::string         &val);
    virtual void append(const char                *val);
    virtual void append(const char                &val);
    virtual void append(const unsigned char       &val);
    virtual void append(const mon::lib::protocol::EProtocolMessageType &val);

    virtual void preface(const int                 &val);
    virtual void preface(const unsigned int        &val);
    virtual void preface(const short               &val);
    virtual void preface(const unsigned short      &val);
    virtual void preface(const long                &val);
    virtual void preface(const unsigned long       &val);
    virtual void preface(const long long           &val);
    virtual void preface(const unsigned long long  &val);
    virtual void preface(const double              &val);
    virtual void preface(const float               &val);
    virtual void preface(const bool                &val);
    virtual void preface(const std::string         &val);
    virtual void preface(const char                *val);
    virtual void preface(const char                &val);
    virtual void preface(const unsigned char       &val);
    virtual void preface(const mon::lib::protocol::EProtocolMessageType &val);

    void removeLast(const int &characters = 1);

    const std::string &string() const;

  private:
    std::string m_string;
};

class CStringBuilder : public CStringBuilderBase
{
    MON_STRING_BUILDER(CStringBuilder)
  public:
      CStringBuilder(const std::string &init = "") : CStringBuilderBase(init) {}
     ~CStringBuilder() {}
};

}
}
}
#endif // CSTRINGBUILDER_H
