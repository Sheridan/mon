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

namespace mon
{
namespace daemons
{
namespace node
{

typedef void               (*TFInitSensor)(mon::lib::logger::CLogger *, mon::lib::config::CFolder *);
typedef const char        *(*TFGetName)            (void);
typedef const char        *(*TFGetDefinition)      (void);
typedef const unsigned int (*TFGetDefinitionLength)(void);
typedef const char        *(*TFGetStatistics)      (const char *);
typedef const bool         (*TFGetFrameAvialable)  (const char *);

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
    mon::lib::sensordata::CDefinition *m_definition;
    void onTimer();
};

typedef std::list<CSensor *> TSensors;

}
}
}
#endif // CSENSOR_H
