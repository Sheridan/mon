/* %Id% */
#ifndef COBJECT_H
#define COBJECT_H
#include <string>
#include <set>
#include <list>
#include <map>
#include "cfrequences.h"
#include "class-helper.h"
namespace mon
{
namespace lib
{
namespace sensor
{

enum EDataType
{
  dtUnknown,
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
    SField() { name = ""; label = ""; description = ""; type = dtUnknown; }
    SField(const std::string &in, const std::string &il, const EDataType &it, const std::string &id)
    {name = in; label = il; type = it; description = id;}
};

enum EFlags
{
  fAggregated          // Данные полей статистики представляют собой часть целого. То есть например 10%, 70%, 20%
};

enum EType
{
  tStatistic,
  tInformation
};

typedef std::set<EFlags>       TFlags;
typedef std::set<std::string>  TTags;
typedef std::list<SField>      TFields;

class CObject
{
    MON_PROPERTY(std::string            , label      )
    MON_PROPERTY(unsigned int           , exemplars  )
    MON_READONLY_PROPERTY(TFlags        , flags      )
    MON_READONLY_PROPERTY(TTags         , tags       )
    MON_READONLY_PROPERTY(TFields       , fields     )
    MON_READONLY_PROPERTY(CFrequences  *, frequences)
  public:
    CObject();
    ~CObject();
    std::string generateText();
    void setFrequences(const EFrequenceType &typeMax, const float &frequencyMax, const EFrequenceType &typeDefault, const float &frequencyDefault);
    void addFlag(const EFlags &flag);
    bool hasFlag(const EFlags &flag);
    void addTag (const std::string &tag);
    bool hasTag (const std::string &tag);
    void addField(const std::string &name, const std::string &label, const EDataType &type, const std::string &description);

};

typedef std::map<std::string, CObject *> TObjects;

}
}
}
#endif // COBJECT_H