#include "cremotenodesensor.h"
#include "cremotenode.h"
#include "collector_st.h"
#include "cdefinitionparcer.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CRemoteNodeSensor::CRemoteNodeSensor(const std::string &name, const std::string &definition, CRemoteNode *parentNode) :
  m_name(name), m_parentNode(parentNode)
{
  m_definition = new mon::lib::sensordata::CDefinition();
  mon::lib::sensordata::CDefinitionParcer parcer = { m_definition, definition };
  parcer.parce();
//  MON_LOG_DBG("Remote Node Sensor: '" << m_name << "' prepared");
}

CRemoteNodeSensor::~CRemoteNodeSensor()
{
  delete m_definition;
}

lib::sensordata::TFramesNames &CRemoteNodeSensor::frames()
{
  return m_definition->frames();
}

}
}
}
