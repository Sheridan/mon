#ifndef CDEFINITIONGENERATOR_H
#define CDEFINITIONGENERATOR_H
#include <string>
#include "cdefinition.h"
#include "cstringbuilder.h"

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
};



}
}
}
#endif // CDEFINITIONGENERATOR_H
