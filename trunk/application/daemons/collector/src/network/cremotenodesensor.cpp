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
  m_parentNode(parentNode), m_sensorName(name)
{
  MON_LOG_DBG("Remote Node Sensor: '" << m_sensorName << "'");
}

CRemoteNodeSensor::~CRemoteNodeSensor()
{

}

}
}
}
