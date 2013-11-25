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

CSensors::CSensors()
  : mon::lib::base::CSingletonMember(MON_SENSORS_MANAGER_ST_MEMBER_ID),
    mon::lib::model::CNode("me")
{
}

CSensors::~CSensors()
{
}

void CSensors::load()
{
  MON_OPTION_FOREACH_FOLDER(folder, MON_ST_CONFIG->folder("sensors"))
  {
    CSensor *tmpSensor = new CSensor(this, folder->name());
    add(tmpSensor);
    tmpSensor->load();
  }
}

std::string CSensors::getGensorsNamesList(const char &delimiter)
{
  std::string result;
  for(std::string &sensorName : names())
  {
    result += sensorName + delimiter;
  }
  return result.substr(0, result.length()-1);
}

CSensor *CSensors::sensor(const std::string &name)
{
  return static_cast<CSensor *>(item(name));
}

}
}
}
