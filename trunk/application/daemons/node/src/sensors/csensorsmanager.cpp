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
    MON_LOG_DBG("Loading sensor " << folder->name())
    CSensor *t_sensor = new CSensor(folder->name());
    m_sensors.push_back(t_sensor);
    t_sensor->load();
    if(t_sensor->getFrameAvialable(nullptr))
    {
      MON_LOG_NFO("Sensor " << t_sensor->getName() << " loaded");
    }
  }
}

std::string CSensorsManager::getGensorsNamesList(const std::string &delimiter)
{
  std::string result;
  for(auto &sensor : m_sensors)
  {
    result += std::string(sensor->getName()) + delimiter;
  }
  return result.substr(0, result.length()-1);
}

CSensor *CSensorsManager::sensor(const std::string &name)
{
    for(auto &sensor : m_sensors)
    {
        if(name.compare(sensor->getName()) == 0)
        {
            return sensor;
        }
    }
    return nullptr;
}

}
}
}
