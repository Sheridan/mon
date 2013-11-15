#ifndef CREMOTENODESENSOR_H
#define CREMOTENODESENSOR_H
#include <string>
#include <list>
#include "cdefinition.h"
#include "class-helper.h"

namespace mon
{
namespace daemons
{
namespace collector
{

class CRemoteNode;

//! Сенсор удаленной ноды
class CRemoteNodeSensor
{
    MON_READONLY_PROPERTY(std::string, name)
public:
  CRemoteNodeSensor(const std::string &name, const std::string &definition, CRemoteNode *parentNode);
  ~CRemoteNodeSensor();
private:
  CRemoteNode *m_parentNode;
  mon::lib::sensordata::CDefinition *m_definition;
};

//! Список сенсоров удаленной ноды
typedef std::list<CRemoteNodeSensor *> TRemoteNodeSensors;

}
}
}
#endif // CREMOTENODESENSOR_H
