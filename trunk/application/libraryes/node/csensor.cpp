#include "libraryes/node/csensor.h"
#include "libraryes/node/cnode.h"
#include "libraryes/sensordata/parcers/cdefinitionparcer.h"
namespace mon
{
namespace lib
{
namespace node
{

CSensor::CSensor(CNode *parent, const std::string &sensorName, const std::string &definitionText)
  : m_name(sensorName),
    m_parentNode(parent),
    m_definitionText(definitionText)
{
  m_definition = new mon::lib::sensordata::CDefinition();
  mon::lib::sensordata::CDefinitionParcer p = {m_definition, m_definitionText};
  p.parce();
}

CSensor::~CSensor()
{
  delete m_definition;
}



}
}
}
