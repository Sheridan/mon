#include "daemons/collector/node/csensor.h"
#include "daemons/collector/node/cnode.h"
#include "daemons/collector/collector_st.h"
#include "libraryes/sensordata/parcers/cdefinitionparcer.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CSensor::CSensor(const std::string &name, const std::string &definition, CNode *parentNode) :
  m_name(name), m_parentNode(parentNode)
{
  m_definition = new mon::lib::sensordata::CDefinition();
  mon::lib::sensordata::CDefinitionParcer parcer = { m_definition, definition };
  parcer.parce();
//  MON_LOG_DBG("Remote Node Sensor: '" << m_name << "' prepared");
}

CSensor::~CSensor()
{
  delete m_definition;
}

lib::sensordata::TFramesNames &CSensor::frames()
{
  return m_definition->frames();
}

}
}
}
