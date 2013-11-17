#include "st.h"
#include "cframe.h"
#include "protocol-control.h"

namespace mon
{
namespace daemons
{
namespace node
{

CFrame::CFrame(TFGetStatistics getstat, TFGetFrameAvialable getfa, const std::string &name, const float &timeout)
  : CTimer(timeout),
    m_name(name),
    getStatistics(getstat),
    getFrameAvialable(getfa)

{
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
}

}
}
}
