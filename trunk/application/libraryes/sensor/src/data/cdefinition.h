/* %Id% */
#ifndef CDEFINITION_H
#define CDEFINITION_H
#include "class-helper.h"
#include <string>
#include <set>
#include <list>
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

struct SUpdateFrequences
{
    float maxFrequence;
    float defaultFrequence;
    float currentFrequence;
    SUpdateFrequences() { maxFrequence = 0; defaultFrequence = 0; currentFrequence = 0; }
    SUpdateFrequences(const float &m, const float &d, const float &c)
    { maxFrequence = m; defaultFrequence = d; currentFrequence = c; }
};

enum EFlags
{
  fProvideStatistics,  // Может выдавать статистику
  fProvideInformation, // Может выдавать информацию
  fCanBeAggregated     // Данные могут аггрегироваться
};

typedef std::set<EFlags>       TFlags;
typedef std::set<std::string>  TTags;
typedef std::list<SField>      TFields;

class CDefinition
{
    MON_PROPERTY(std::string      , label                       )
    MON_PROPERTY(unsigned int     , exemplars                   )
    MON_PROPERTY(SUpdateFrequences, statisticalUpdateFrequences )
    MON_PROPERTY(SUpdateFrequences, informationUpdateFrequences )
    MON_READONLY_PROPERTY(TFlags  , flags                       )
    MON_READONLY_PROPERTY(TTags   , tags                        )
    MON_READONLY_PROPERTY(TFields , informationFields           )
    MON_READONLY_PROPERTY(TFields , statisticalFields           )
  public:
    CDefinition();
    ~CDefinition();
    std::string generateText();

  private:
    void addFlag(const EFlags &flag);
    bool hasFlag(const EFlags &flag);
    void addTag (const std::string &tag);
    bool hasTag (const std::string &tag);
    void addInformationField(const std::string &name, const std::string &label, const EDataType &type, const std::string &description);
    void addStatisticalField(const std::string &name, const std::string &label, const EDataType &type, const std::string &description);

};

}
}
}
#endif // CDEFINITION_H
