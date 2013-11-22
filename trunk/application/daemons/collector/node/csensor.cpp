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

CSensor::CSensor(CNode *parentNode, const std::string &name, const std::string &definition)
  : mon::lib::model::CSensor(parentNode, name, definition)
{}

CSensor::~CSensor()
{}

}
}
}
