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

class CCollectorRemoteNode;

//! Сенсор удаленной ноды
class CCollectorRemoteNodeSensor
{
    MON_READONLY_PROPERTY(std::string, name)
  public:
    CCollectorRemoteNodeSensor(const std::string &name, const std::string &definition, CCollectorRemoteNode *parentNode);
    ~CCollectorRemoteNodeSensor();
    mon::lib::sensordata::TFramesNames &frames();
  private:
    CCollectorRemoteNode *m_parentNode;
    mon::lib::sensordata::CDefinition *m_definition;
};

//! Список сенсоров удаленной ноды
typedef std::list<CCollectorRemoteNodeSensor *> TCollectorRemoteNodeSensors;

}
}
}
#endif // CREMOTENODESENSOR_H
