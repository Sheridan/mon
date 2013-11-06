/* %Id% */
#ifndef COBJECT_H
#define COBJECT_H
#include <string>
#include <set>
#include <list>
#include <map>
#include "cfrequency.h"
#include "class-helper.h"
namespace mon
{
namespace lib
{
namespace sensordata
{

enum EDataType
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

struct SField
{
    std::string name;
    std::string label;
    std::string description;
    EDataType   type;
    SField() { name = ""; label = ""; description = ""; type = dtInteger; }
    SField(const std::string &in, const std::string &il, const EDataType &it, const std::string &id)
    {name = in; label = il; type = it; description = id;}
};

enum EFlags
{
  fAggregated,          // Данные полей статистики представляют собой часть целого. То есть например 10%, 70%, 20%
  fCalculateTotal       // Необходимо суммировать значения полей в отдельное, генерируемое поле
};

enum EType
{
  tStatistic,
  tInformation
};

enum EFrequencyPurpose
{
  fpMax     = 0,
  fpDefault = 1,
  fpCurrent = 2
};

typedef std::set<EFlags>       TFlags;
typedef std::set<std::string>  TTags;
typedef std::list<SField>      TFields;

class CObject
{
    MON_PROPERTY(std::string            , label      )
    MON_PROPERTY(unsigned int           , exemplars  )
    MON_PROPERTY(EType                  , type       )
    MON_READONLY_PROPERTY(TFlags        , flags      )
    MON_READONLY_PROPERTY(TTags         , tags       )
    MON_READONLY_PROPERTY(TFields       , fields     )
  public:
    CObject();
    ~CObject();
    std::string generateText();
    void setFrequency(const EFrequencyPurpose &purpose, const EFrequencyMeasurment &measurment, const float &value);
    void addField    (const std::string &name, const std::string &label, const EDataType &type, const std::string &description);
    void addFlag     (const EFlags &flag);
    bool hasFlag     (const EFlags &flag);
    void addTag      (const std::string &tag);
    bool hasTag      (const std::string &tag);

  private:
    CFrequency *m_frequences[3];

};

typedef std::map<std::string, CObject *> TObjects;

}
}
}
#endif // COBJECT_H
