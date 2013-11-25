/* %Id% */
#include <unistd.h>
#include "defines/st.h"
#include "daemons/node/sensor/csensorsmanager.h"

namespace mon
{
namespace daemons
{
namespace node
{

CSensors::CSensors() : mon::lib::base::CSingletonMember(MON_SENSORS_MANAGER_ST_MEMBER_ID)
{
}

CSensors::~CSensors()
{
}

void CSensors::load()
{
  MON_OPTION_FOREACH_FOLDER(folder, MON_ST_CONFIG->folder("sensors"))
  {
    CSensor *t_sensor = new CSensor(folder->name());
    m_sensors[folder->name()] = t_sensor;
    t_sensor->load();
  }
}

std::string CSensors::getGensorsNamesList(const char &delimiter)
{
  std::string result;
  for(auto &sensor : m_sensors)
  {
    result += std::string(sensor.second->getName()) + delimiter;
  }
  return result.substr(0, result.length()-1);
}

CSensor *CSensors::sensor(const std::string &name)
{
  if(m_sensors.count(name) == 0)
  {
    MON_LOG_ERR("Requested sensor ("<< name <<") not exists");
    MON_ABORT;
  }
  return m_sensors[name];
}

}
}
}
