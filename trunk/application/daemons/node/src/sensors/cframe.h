#ifndef CNODESENSORFRAME_H
#define CNODESENSORFRAME_H
#include <string>
#include <map>
#include "class-helper.h"
#include "ctimer.h"
#include "cstatisticcache.h"

namespace mon
{
namespace daemons
{
namespace node
{

using TFGetStatistics       = const char        *(*)(const char *);
using TFGetFrameAvialable   = const bool         (*)(const char *);

class CFrame : mon::lib::base::CTimer
{
    MON_READONLY_PROPERTY(std::string, name)
  public:
    CFrame(TFGetStatistics getstat, TFGetFrameAvialable getfa, const std::string &name, const float &timeout);
    virtual ~CFrame();
    TFGetStatistics       getStatistics;
    TFGetFrameAvialable   getFrameAvialable;
  private:
    mon::lib::sensordata::CStatisticCache *m_cache;
    void onTimer() final;
};

typedef std::map<std::string, CFrame *> TFramesMap;

}
}
}
#endif // CNODESENSORFRAME_H
