#ifndef CFIELD_H
#define CFIELD_H
#include <list>
#include <string>
#include "class-helper.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

enum EFieldDataType
{
  dtPercent,
  dtBool,
  dtShort,
  dtUnsignedShort,
  dtInteger,
  dtUnsignedIinteger,
  dtLong,
  dtUnsignedLong,
  dtFloat,
  dtString
};

class CField
{
    MON_READONLY_PROPERTY(std::string, name)
    MON_READONLY_PROPERTY(std::string, label)
    MON_READONLY_PROPERTY(EFieldDataType, type)
    MON_READONLY_PROPERTY(std::string, description)
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
