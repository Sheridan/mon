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

CSensor::CSensor(CNode *parentNode, const std::string &nodeName, const std::string &nodeDefinition)
  : mon::lib::model::CSensor(parentNode, nodeName, nodeDefinition)
{
  MON_LOG_DBG("!!!!!!!!!!!!!!!!" << nodeDefinition)
}

CSensor::~CSensor()
{}

}
}
}
