#ifndef CTIMER_H
#define CTIMER_H
#include "class-helper.h"
#include "threads-helper.h"

namespace mon
{
namespace lib
{
namespace base
{

//! Таймер
class CTimer
{
    MON_THREADED_FUNCTION_DECLARE(ticks)
    MON_PROPERTY(float, timeout) //!> Время между вызовами, СЕКУНДЫ!!!

  public:
    CTimer(const float &timeout);
    CTimer();
    virtual ~CTimer();

  protected:
    void timerStop();
    void timerStart();
    bool timerActive();
    virtual void onTimer() = 0; //!> Это вызывается по таймауту
};

}
}
}
#endif // CTIMER_H
