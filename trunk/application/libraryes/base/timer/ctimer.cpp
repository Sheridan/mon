#include <unistd.h>
#include "defines/st.h"
#include "defines/infinity-cycle-helper.h"
#include "libraryes/base/timer/ctimer.h"

namespace mon
{
namespace lib
{
namespace base
{

CTimer::CTimer(const float &timeout)
  :m_timeout(timeout)
{
  MON_THREADED_FUNCTION_INIT(ticks)
}

CTimer::CTimer() : CTimer(1)
{
  MON_THREADED_FUNCTION_INIT(ticks)
}

CTimer::~CTimer()
{
  timerStop();
}

MON_THREADED_FUNCTION_IMPLEMENT(CTimer, ticks)
{
  MON_INFINITY_LOOP_BEGIN(ticks_loop)
      MON_THREADED_ABORT_IF_NEED(ticks);
      usleep(m_timeout * 1000000);
      MON_THREADED_FUNCTION_DISABLE_CANCEL
//      MON_LOG_DBG("Timer tick")
      onTimer();
      MON_THREADED_FUNCTION_ENABLE_CANCEL
  MON_INFINITY_LOOP_END(ticks_loop)
}

void CTimer::timerStop()
{
  MON_THREADED_FUNCTION_ABORT(ticks)
  while (timerActive()) { usleep(1000000); }
}

void CTimer::timerStart()
{
  ticks();
}

bool CTimer::timerActive()
{
  return MON_THREADED_IS_ACTIVE(ticks);
}

}
}
}
