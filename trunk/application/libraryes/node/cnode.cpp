#include "libraryes/node/cnode.h"
namespace mon
{
namespace lib
{
namespace node
{

CNode::CNode()
{
  MON_MUTEX_INITIALIZE(sensors)
}

CNode::~CNode()
{
  MON_MUTEX_LOCK(sensors)
  for(CSensor *s : m_sensors)
  {
    delete s;
  }
  m_sensors.clear();
  MON_MUTEX_UNLOCK(sensors)
  MON_MUTEX_DESTROY(sensors)
}

CSensor *CNode::sensor(const std::string &name)
{
  CSensor *result = nullptr;
  MON_MUTEX_LOCK(sensors)
  for(CSensor *s : m_sensors)
  {
    if(name.compare(s->name()) == 0)
    {
      result = s;
      break;
    }
  }
  MON_MUTEX_UNLOCK(sensors)
  return nullptr;
}

void CNode::addSensor(const std::string &name, const std::string &definition)
{
  CSensor *s = new CSensor(this, name, definition);
  MON_MUTEX_LOCK(sensors)
  m_sensors.push_back(s);
  MON_MUTEX_UNLOCK(sensors)
}

}
}
}
