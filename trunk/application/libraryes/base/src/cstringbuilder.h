/* %Id% */
#ifndef CSTRINGBUILDER_H
#define CSTRINGBUILDER_H
#include <string>

#define MON_STRING_BUILDER(_class) \
  public: \
  _class &operator<<(const int           &val) { append(val); return *this; } \
  _class &operator<<(const unsigned int  &val) { append(val); return *this; } \
  _class &operator<<(const double        &val) { append(val); return *this; } \
  _class &operator<<(const float         &val) { append(val); return *this; } \
  _class &operator<<(const bool          &val) { append(val); return *this; } \
  _class &operator<<(const std::string   &val) { append(val); return *this; } \
  _class &operator<<(const char          *val) { append(val); return *this; } \
  _class &operator<<(const char          &val) { append(val); return *this; } \
  _class &operator<<(const unsigned char &val) { append(val); return *this; } \
  _class &operator+(const int           &val) { append(val); return *this; } \
  _class &operator+(const unsigned int  &val) { append(val); return *this; } \
  _class &operator+(const double        &val) { append(val); return *this; } \
  _class &operator+(const float         &val) { append(val); return *this; } \
  _class &operator+(const bool          &val) { append(val); return *this; } \
  _class &operator+(const std::string   &val) { append(val); return *this; } \
  _class &operator+(const char          *val) { append(val); return *this; } \
  _class &operator+(const char          &val) { append(val); return *this; } \
  _class &operator+(const unsigned char &val) { append(val); return *this; }

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

class CStringBuilder
{
    MON_STRING_BUILDER(CStringBuilder)
  public:
    CStringBuilder(const std::string &init = "");

    virtual void append(const int           &val);
    virtual void append(const unsigned int  &val);
    virtual void append(const double        &val);
    virtual void append(const float         &val);
    virtual void append(const bool          &val);
    virtual void append(const std::string   &val);
    virtual void append(const char          *val);
    virtual void append(const char          &val);
    virtual void append(const unsigned char &val);

    virtual void preface(const int           &val);
    virtual void preface(const unsigned int  &val);
    virtual void preface(const double        &val);
    virtual void preface(const float         &val);
    virtual void preface(const bool          &val);
    virtual void preface(const std::string   &val);
    virtual void preface(const char          *val);
    virtual void preface(const char          &val);
    virtual void preface(const unsigned char &val);

    void removeLast(const int &characters = 1);

    const std::string &msg() const;

  private:
    std::string m_message;
};

}
}
}
#endif // CSTRINGBUILDER_H
