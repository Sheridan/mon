#include "st.h"
#include "cframe.h"

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
  timerStart();
}

CFrame::~CFrame()
{
  timerStop();
  while (timerActive()) { usleep(timeout()*2); }
}

void CFrame::onTimer()
{
  if(getFrameAvialable(m_name.c_str()))
  {
#ifdef MON_DEBUG
    std::string sd = getStatistics(m_name.c_str());
    MON_LOG_DBG("Sensor data: " << sd);
    m_cache.store(sd);
#else
    m_cache.store(getStatistics(m_name.c_str()));
#endif

  }
}

}
}
}
