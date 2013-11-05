/* %Id% */
#include "csensorsmanager.h"
#include "st.h"

#define MON_FOREACH_SENSOR(_name) \
   for(mon::daemons::node::TSensors::iterator _name = m_sensors.begin(); \
    _name != m_sensors.end(); \
    ++_name)


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
    MON_LOG_DBG("Loading sensor " << (*folder)->name())
    CSensor *t_sensor = new CSensor((*folder)->name());
    m_sensors.push_back(t_sensor);
    t_sensor->load();
    if(t_sensor->getSensorAvialable(NULL))
    {
      MON_LOG_DBG("Sensor " << t_sensor->getName(NULL) << " loaded");
    }
  }
}

std::string CSensorsManager::getGensorsNamesList(const std::string &delimiter)
{
  std::string result;
  MON_FOREACH_SENSOR(sensor)
  {
    result += std::string((*sensor)->getName(NULL)) + delimiter;
  }
  return result.substr(0, result.length()-1);
}

CSensor *CSensorsManager::sensor(const std::string &name)
{
    MON_FOREACH_SENSOR(sensor)
    {
        if(name.compare((*sensor)->getName(NULL)) == 0)
        {
            return (*sensor);
        }
    }
    return NULL;
}

}
}
}
