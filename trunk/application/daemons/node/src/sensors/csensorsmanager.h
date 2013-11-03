/* %Id% */
#ifndef CSENSORSMANAGER_H
#define CSENSORSMANAGER_H
#include "csensor.h"
#include "csingletonmember.h"
namespace mon
{
namespace daemons
{
namespace node
{

class CSensorsManager : public mon::lib::base::CSingletonMember
{
  public:
    CSensorsManager();
    ~CSensorsManager();
    void load();
    std::string getGensorsNamesList(const std::string &delimiter = ":");
  private:
    TSensors m_sensors;
};

}
}
}
#endif // CSENSORSMANAGER_H
