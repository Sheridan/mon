#include "defines/st.h"
#include "daemons/node/sensor/cframe.h"
#include "daemons/node/sensor/csensor.h"
#include "defines/protocol-control.h"

namespace mon
{
namespace daemons
{
namespace node
{

CFrame::CFrame(CSensor *parent, TFGetStatistics getstat, TFGetFrameAvialable getfa, const std::string &name)
  : CTimer(),
    mon::lib::base::CSystemRights(),
    m_name(name),
    getStatistics(getstat),
    getFrameAvialable(getfa),
    m_parentSensor(parent)

{
  mon::lib::config::CFolder *frameConfig;
  float timeout = 1;
  frameConfig = MON_ST_CONFIG->folder("sensors")->folder(m_parentSensor->name())->folder("frames")->folder(m_name);
  if(frameConfig->folder("frequency")->containsFile("hz"))
  {
    timeout = mon::lib::sensordata::Hz2SPP(frameConfig->folder("frequency")->file("hz")->get(m_parentSensor->definition()->frame(m_name)->frequency(mon::lib::sensordata::fpDefault)->asHz()));
  }
  else if(frameConfig->folder("frequency")->containsFile("spp"))
  {
    timeout = frameConfig->folder("frequency")->file("spp")->get(m_parentSensor->definition()->frame(m_name)->frequency(mon::lib::sensordata::fpDefault)->asSPP());
  }
  else
  {
    timeout = m_parentSensor->definition()->frame(m_name)->frequency(mon::lib::sensordata::fpDefault)->asSPP();
    frameConfig->folder("frequency")->file("spp")->set(timeout);
  }
  if(timeout < m_parentSensor->definition()->frame(m_name)->frequency(mon::lib::sensordata::fpMax)->asSPP())
  {
    MON_LOG_WRN("Sensor frame (" << m_parentSensor->name() << ":" << m_name << ") request frequency above maximum "
                "(" << timeout << ">" << m_parentSensor->definition()->frame(m_name)->frequency(mon::lib::sensordata::fpMax)->asSPP() << "). Using maximum value")
    timeout = m_parentSensor->definition()->frame(m_name)->frequency(mon::lib::sensordata::fpMax)->asSPP();
  }
  MON_LOG_NFO("Starting sensor frame (" << m_parentSensor->name() << ":" << m_name << ") statistics mine with frequency " <<
              mon::lib::sensordata::Hz2SPP(timeout) << "Hz (one tick in " << timeout << " secunds)");
  settimeout(timeout);
  m_effectiveUser  = frameConfig->folder("runas")->file("user" )->get(currentUserName ());
  m_effectiveGroup = frameConfig->folder("runas")->file("group")->get(currentGroupName());
  m_cache = new mon::lib::sensordata::CStatisticCache();
  timerStart();
}

CFrame::~CFrame()
{
  timerStop();
  delete m_cache;
}

std::string CFrame::requestCachedData()
{
  std::string result = "";
  lib::sensordata::CStatisticData * data = m_cache->requestData();
  for(std::string dataString : data->data())
  {
    result += dataString + MON_PROTOCOL_DELIMITER(statistic,statistic);
  }
  m_cache->freeData(data);
  return result.substr(0, result.length() - 1);
}

void CFrame::onTimer()
{
  setUserGroup(m_effectiveUser, m_effectiveGroup);
  if(getFrameAvialable(m_name.c_str()))
  {
//#ifdef MON_DEBUG
//    std::string sd = getStatistics(m_name.c_str());
//    MON_LOG_DBG("Sensor data: " << sd);
//    m_cache->store(sd);
//#else
    m_cache->store(getStatistics(m_name.c_str()));
//#endif

  }
  resetUserGroup();
}

}
}
}
