#include "cremotenodesensor.h"
#include "cremotenode.h"
#include "collector_st.h"
namespace mon
{
namespace daemons
{
namespace collector
{

CRemoteNodeSensor::CRemoteNodeSensor(const std::string &name, CRemoteNode *parentNode) :
  m_sensorName(name), m_parentNode(parentNode)
{
  MON_LOG_DBG("Remote Node Sensor: '" << m_sensorName << "'");
}

CRemoteNodeSensor::~CRemoteNodeSensor()
{

}

}
}
}
