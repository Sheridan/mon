#include "libraryes/model/csensor.h"
#include "libraryes/model/cnode.h"
#include "libraryes/sensordata/parcers/cdefinitionparcer.h"
namespace mon
{
namespace lib
{
namespace model
{

CSensor::CSensor(CNode *parent, const std::string &sensorName, const std::string &definitionText)
  : m_name(sensorName),
    m_parentNode(parent),
    m_definition(nullptr)
{
  setDefinition(definitionText);
}

CSensor::CSensor(CNode *parent, const std::string &sensorName)
  : m_name(sensorName),
    m_parentNode(parent),
    m_definitionText(""),
    m_definition(nullptr)
{

}

CSensor::~CSensor()
{
  delete m_definition;
}

void CSensor::setDefinition(const std::string &def)
{
  m_definitionText = def;
}

mon::lib::sensordata::CDefinition *CSensor::definition()
{
  if(!m_definition)
  {
    m_definition = new mon::lib::sensordata::CDefinition();
    mon::lib::sensordata::CDefinitionParcer p = {m_definition, m_definitionText};
    p.parce();
  }
  return m_definition;
}


}
}
}
