#ifndef CDEFINITIONGENERATOR_H
#define CDEFINITIONGENERATOR_H
#include <string>
#include "libraryes/sensordata/data/cdefinition.h"
#include "libraryes/base/string/cstringbuilder.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

//! Генератор описания сенсора
class CDefinitionGenerator
{
  public:
    CDefinitionGenerator(CDefinition *definition);
    virtual ~CDefinitionGenerator();
    const std::string &generate();

  private:
    CDefinition *m_definition;                //!< Объектное описание сенсора, источник генерирования
    mon::lib::base::CStringBuilder *m_result; //!< Для сборки описания сенсора

    void generateFrame(CFrame *frame);
    void generateFrequencyes(CFrame *frame);
    void generateFlags(CFrame *frame);
    void generateTags(CFrame *frame);
    void generateFields(CFrame *frame);
    void generateField(CField *field);
};




}
}
}
#endif // CDEFINITIONGENERATOR_H
