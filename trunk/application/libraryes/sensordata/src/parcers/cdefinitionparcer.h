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
  public:
    CDefinitionParcer(CDefinition *target, const std::string &definition);
    ~CDefinitionParcer();
    void parce();

  private:
    std::string  m_definitionText;
    int          m_currentIndex;
    CDefinition *m_definition;

    CFrame *parceFrame();

    void readFrequences(CFrame *frame);
    void readFlags     (CFrame *frame);
    void readTags      (CFrame *frame);
    void readFields    (CFrame *frame);
    void readFrameType (CFrame *frame);
    void readField     (CFrame *frame, const std::string &name);

    void skipToSemicolon();
    std::string readStringValue();
    EFieldDataType readFieldType ();

};

}
}
}
#endif // CDEFINITIONPARCER_H
