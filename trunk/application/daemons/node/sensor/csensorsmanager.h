/* %Id% */
#ifndef CSENSORSMANAGER_H
#define CSENSORSMANAGER_H
#include "defines/protocol-control.h"
#include "libraryes/base/singleton/csingletonmember.h"
#include "daemons/node/sensor/csensor.h"

namespace mon
{
namespace daemons
{
namespace node
{

//! Менеджер сенсоров ноды
class CSensors : public mon::lib::base::CSingletonMember
{
  public:
    CSensors();
    ~CSensors();
    void load();
    std::string getGensorsNamesList(const char &delimiter);
    CSensor *sensor(const std::string &name);
  private:
    TSensorsMap m_sensors;
};

}
}
}
#endif // CSENSORSMANAGER_H
