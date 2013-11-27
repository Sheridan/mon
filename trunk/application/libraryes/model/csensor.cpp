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
    m_parentNode(parent)
{
  setDefinition(definitionText);
}

CSensor::CSensor(CNode *parent, const std::string &sensorName)
  : m_name(sensorName),
    m_parentNode(parent),
    m_definition(nullptr),
    m_definitionText("")
{

}

CSensor::~CSensor()
{
  delete m_definition;
}

lib::sensordata::TFramesNames &CSensor::frames()
{
  return m_definition->frames();
}

void CSensor::setDefinition(const std::string &def)
{
  m_definitionText = def;
  MON_LOG_DBG("--------------<<<<<<<<<<<<" << m_definitionText)
  m_definition = new mon::lib::sensordata::CDefinition();
  mon::lib::sensordata::CDefinitionParcer p = {m_definition, m_definitionText};
  p.parce();
}


}
}
}
