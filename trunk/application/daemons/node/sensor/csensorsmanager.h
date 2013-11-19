/* %Id% */
#ifndef CSENSORSMANAGER_H
#define CSENSORSMANAGER_H
#include "csensor.h"
#include "csingletonmember.h"
#include "protocol-control.h"
namespace mon
{
namespace daemons
{
namespace node
{

//! Менеджер сенсоров ноды
class CSensorsManager : public mon::lib::base::CSingletonMember
{
  public:
    CSensorsManager();
    ~CSensorsManager();
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