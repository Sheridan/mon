#ifndef CREMOTENODESENSOR_H
#define CREMOTENODESENSOR_H
#include <string>
#include <list>

namespace mon
{
namespace daemons
{
namespace collector
{

class CRemoteNode;

class CRemoteNodeSensor
{
public:
  CRemoteNodeSensor(const std::string &name, CRemoteNode *parentNode);
  ~CRemoteNodeSensor();
private:
  std::string m_sensorName;
  CRemoteNode *m_parentNode;
};

typedef std::list<CRemoteNodeSensor *> TRemoteNodeSensors;

}
}
}
#endif // CREMOTENODESENSOR_H
