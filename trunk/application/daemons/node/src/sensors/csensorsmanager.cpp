/* %Id% */
#include "csensorsmanager.h"
#include "st.h"
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
    MON_LOG_DBG("Sensor " << t_sensor->getName(NULL) << " loaded");
  }
}

}
}
}
