#ifndef CNODESENSORFRAME_H
#define CNODESENSORFRAME_H
#include <map>
#include <string>
#include "defines/class-helper.h"
#include "libraryes/base/timer/ctimer.h"
#include "libraryes/sensordata/data/cstatisticcache.h"
#include "libraryes/base/sequrity/csystemrights.h"

namespace mon
{
namespace daemons
{
namespace node
{

using TFGetStatistics       = const char        *(*)(const char *);
using TFGetFrameAvialable   = const bool         (*)(const char *);
class CSensor;

//! Фрейм ноды, непосредственно берущий данные из сенсора
class CFrame :
    mon::lib::base::CTimer,
    mon::lib::base::CSystemRights
{
    MON_READONLY_PROPERTY(std::string, name)
  public:
    CFrame(CSensor *parent, TFGetStatistics getstat, TFGetFrameAvialable getfa, const std::string &name);
    virtual ~CFrame();
    std::string requestCachedData();
  private:
    TFGetStatistics       getStatistics;
    TFGetFrameAvialable   getFrameAvialable;
    mon::lib::sensordata::CStatisticCache *m_cache;
    void onTimer() final;
    CSensor *m_parentSensor;
    std::string m_effectiveUser;
    std::string m_effectiveGroup;
};

typedef std::map<std::string, CFrame *> TFramesMap;

}
}
}
#endif // CNODESENSORFRAME_H
