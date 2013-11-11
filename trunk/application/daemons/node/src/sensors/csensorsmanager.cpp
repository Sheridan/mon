/* %Id% */
#include "csensorsmanager.h"
#include "st.h"
#include <unistd.h>

namespace mon
{
namespace daemons
{
namespace node
{

CSensorsManager::CSensorsManager() : mon::lib::base::CSingletonMember(MON_SENSORS_MANAGER_ST_MEMBER_ID)
{
}

CSensorsManager::~CSensorsManager()
{
}

void CSensorsManager::load()
{
  MON_OPTION_FOREACH_FOLDER(folder, MON_ST_CONFIG->folder("sensors"))
  {
    MON_LOG_DBG("Loading sensor " << MON_STL_LIST_VALUE(folder)->name())
    CSensor *t_sensor = new CSensor(MON_STL_LIST_VALUE(folder)->name());
    m_sensors.push_back(t_sensor);
    t_sensor->load();
    if(t_sensor->getSensorAvialable(NULL))
    {
      MON_LOG_NFO("Sensor " << t_sensor->getName(NULL) << " loaded");
    }
  }
}

std::string CSensorsManager::getGensorsNamesList(const std::string &delimiter)
{
  std::string result;
  MON_STL_LIST_FOREACH(sensor, TSensors, m_sensors)
  {
    result += std::string(MON_STL_LIST_VALUE(sensor)->getName(NULL)) + delimiter;
  }
  return result.substr(0, result.length()-1);
}

CSensor *CSensorsManager::sensor(const std::string &name)
{
    MON_STL_LIST_FOREACH(sensor, TSensors, m_sensors)
    {
        if(name.compare(MON_STL_LIST_VALUE(sensor)->getName(NULL)) == 0)
        {
            return MON_STL_LIST_VALUE(sensor);
        }
    }
    return NULL;
}

}
}
}
