/* %Id% */
#ifndef CSENSOR_H
#define CSENSOR_H
#include <string>
#include "class-helper.h"
#include <list>
#include "logger.h"
#include "config.h"
#include "ctimer.h"
#include "cdefinition.h"
#include "cstatisticcache.h"

namespace mon
{
namespace daemons
{
namespace node
{

using TFInitSensor          = void               (*)(mon::lib::logger::CLogger *, mon::lib::config::CFolder *);
using TFGetName             = const char        *(*)(void);
using TFGetDefinition       = const char        *(*)(void);
using TFGetDefinitionLength = const unsigned int (*)(void);
using TFGetStatistics       = const char        *(*)(const char *);
using TFGetFrameAvialable   = const bool         (*)(const char *);

//! Сенсор ноды, посредник между нодой и библиотекой
class CSensor : mon::lib::base::CTimer
{
    MON_READONLY_PROPERTY(std::string, name)
  public:
    CSensor(const std::string &i_name);
    ~CSensor();
    void load();
    void unload();
    TFInitSensor          initSensor;
    TFGetName             getName;
    TFGetDefinition       getDefinition;
    TFGetDefinitionLength getDefinitionLength;
    TFGetStatistics       getStatistics;
    TFGetFrameAvialable   getFrameAvialable;

  private:
    void * m_handle;
    mon::lib::sensordata::CStatisticCache m_cache;
    mon::lib::sensordata::CDefinition *m_definition;
    void onTimer() final;
};

typedef std::list<CSensor *> TSensors;

}
}
}
#endif // CSENSOR_H
