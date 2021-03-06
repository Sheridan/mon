#ifndef CFIELD_H
#define CFIELD_H
#include <list>
#include <string>
#include "defines/class-helper.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

//! Тип данных поля фрейма
enum class EFieldDataType
{
  Percent, //!< Процент
  Bool,    //!< bool
  Short,   //!< short
  UShort,  //!< unsigned short
  Int,     //!< int
  UInt,    //!< unsigned int
  Long,    //!< long int
  ULong,   //!< unsigned long
  Float,   //!< float
  String   //!< Строка
};

//! Поле фрейма
class CField
{
    MON_READONLY_PROPERTY(std::string, name)        //!< Имя поля
    MON_READONLY_PROPERTY(std::string, label)       //!< Метка поля
    MON_READONLY_PROPERTY(EFieldDataType, type)     //!< Тип поля
    MON_READONLY_PROPERTY(std::string, description) //!< Описание поля
  public:
    CField();
    CField(const std::string &name, const std::string &label, const EFieldDataType &type, const std::string &description);
    virtual ~CField();
};

typedef std::list<CField *> TFields;

}
}
}
#endif // CFIELD_H
