/* %Id% */
#ifndef CDEFINITIONPARCER_H
#define CDEFINITIONPARCER_H
#include <string>
#include "cdefinition.h"
#include "class-helper.h"
#include "cparcerstring.h"
#include "cfrequency.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

enum EFrequencyCurrentReading
{
  fcrKeyword,
  fcrValue,
  fcrMeasurment
};

class CDefinitionParcer : public mon::lib::base::CParcerString
{
    CDefinitionParcer(CDefinition *target, const std::string &definition);
    ~CDefinitionParcer();
    void parce();

  private:
    std::string  m_definitionText;
    int          m_currentIndex;
    CDefinition *m_definition;

    CObject *parceObject();

    void readFrequences(CObject *obj);
    void readType      (CObject *obj);
    void readFlags     (CObject *obj);
    void readTags      (CObject *obj);
    void readFields    (CObject *obj);
    void readField     (CObject *obj, const std::string &name);

    void skipToSemicolon();
    std::string readStringValue();
    std::string readValue();

};

}
}
}
#endif // CDEFINITIONPARCER_H
