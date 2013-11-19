/* %Id% */
#ifndef CVARIANT_H
#define CVARIANT_H
#include <string>
#include "mutex-helper.h"

namespace mon
{
namespace lib
{
namespace base
{

bool               toBool  (const std::string        &val);
int                toInt   (const std::string        &val);
unsigned int       toUInt  (const std::string        &val);
short              toShort (const std::string        &val);
unsigned short     toUShort(const std::string        &val);
long               toLong  (const std::string        &val);
unsigned long      toULong (const std::string        &val);
long long          toLLong (const std::string        &val);
unsigned long long toULLong(const std::string        &val);
float              toFloat (const std::string        &val);
double             toDouble(const std::string        &val);
std::string        toString(const int                &val);
std::string        toString(const bool               &val);
std::string        toString(const float              &val);
std::string        toString(const double             &val);
std::string        toString(const unsigned int       &val);
std::string        toString(const short              &val);
std::string        toString(const unsigned short     &val);
std::string        toString(const long               &val);
std::string        toString(const unsigned long      &val);
std::string        toString(const long long          &val);
std::string        toString(const unsigned long long &val);

//! Тип контента вариант-типа
enum class EContentType
{
  Bool,    //!< Булев
  Int,     //!< Целое
  UInt,    //!< Беззнаковое целое
  Short,   //!< Малое целое
  UShort,  //!< Беззнаковое малое целое
  Long,    //!< Большое целое
  ULong,   //!< Беззнаковое большое целое
  LLong,   //!< Очень большое число
  ULLong,  //!< Очень большое беззнаковое число
  Float,   //!< Число с плавающей точкой
  Double,  //!< Число с плавающей точкой двойной точности
  String,  //!< Строка
  Unknown  //!< Неизвестный тип
};

//! Объединение для хранения данных вариант-типа
union UContent
{
  bool               m_bool  ;
  int                m_int   ;
  unsigned int       m_uint  ;
  short              m_short ;
  unsigned short     m_ushort;
  long               m_long  ;
  unsigned long      m_ulong ;
  long long          m_llong ;
  unsigned long long m_ullong;
  float              m_float ;
  double             m_double;
  char *             m_string;
};

//! Почти классический вариант.
class CVariant
{
    MON_MUTEX_DECLARE(variant)
  public:
    CVariant(                             ) { initialize(); reset();  }
    CVariant(const bool               &val) { initialize(); set(val); }
    CVariant(const int                &val) { initialize(); set(val); }
    CVariant(const unsigned int       &val) { initialize(); set(val); }
    CVariant(const short              &val) { initialize(); set(val); }
    CVariant(const unsigned short     &val) { initialize(); set(val); }
    CVariant(const long               &val) { initialize(); set(val); }
    CVariant(const unsigned long      &val) { initialize(); set(val); }
    CVariant(const long long          &val) { initialize(); set(val); }
    CVariant(const unsigned long long &val) { initialize(); set(val); }
    CVariant(const float              &val) { initialize(); set(val); }
    CVariant(const double             &val) { initialize(); set(val); }
    CVariant(const std::string        &val) { initialize(); set(val); }
    virtual ~CVariant();

    void reset();
    bool isEmpty();

    const bool               toBool      ();
    const int                toInt       ();
    const unsigned int       toUInt      ();
    const short              toShort     ();
    const unsigned short     toUShort    ();
    const long               toLong      ();
    const unsigned long      toULong     ();
    const long long          toLLong     ();
    const unsigned long long toULLong    ();
    const float              toFloat     ();
    const double             toDouble    ();
    const std::string        toString    ();

    const EContentType &     contentType () const;

    void set(const bool               &val);
    void set(const int                &val);
    void set(const unsigned int       &val);
    void set(const short              &val);
    void set(const unsigned short     &val);
    void set(const long               &val);
    void set(const unsigned long      &val);
    void set(const long long          &val);
    void set(const unsigned long long &val);
    void set(const float              &val);
    void set(const double             &val);
    void set(const std::string        &val);

    bool tryConvert(const bool               &val);
    bool tryConvert(const int                &val);
    bool tryConvert(const unsigned int       &val);
    bool tryConvert(const short              &val);
    bool tryConvert(const unsigned short     &val);
    bool tryConvert(const long               &val);
    bool tryConvert(const unsigned long      &val);
    bool tryConvert(const long long          &val);
    bool tryConvert(const unsigned long long &val);
    bool tryConvert(const float              &val);
    bool tryConvert(const double             &val);
    bool tryConvert(const std::string        &val);

  protected:
    EContentType m_contentType;
    UContent     m_value;

  private:
    void initialize();
};

}
}
}
#endif // CVARIANT_H
