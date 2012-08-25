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
namespace sensor
{

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
    void readFrequency(const EFrequencyClasses &ftype, CObject *obj);
    void skipToSemicolon();
    std::string readStringValue();

};

}
}
}
#endif // CDEFINITIONPARCER_H
