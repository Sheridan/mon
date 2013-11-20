/* %Id% */
#ifndef CSENSOR_H
#define CSENSOR_H
#include <map>
#include <string>
#include "defines/class-helper.h"
#include "libraryes/logger/logger.h"
#include "libraryes/config/config.h"
#include "libraryes/sensordata/data/cdefinition.h"
#include "daemons/node/sensor/cframe.h"

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

//! Сенсор ноды, посредник между нодой и библиотекой
class CSensor
{
    MON_READONLY_PROPERTY(std::string, name)
    MON_READONLY_PROPERTY(mon::lib::sensordata::CDefinition *, definition)
  public:
    CSensor(const std::string &i_name);
    ~CSensor();
    void load();
    void unload();
    CFrame *frame(const std::string &name);
    TFInitSensor          initSensor;
    TFGetName             getName;
    TFGetDefinition       getDefinition;
    TFGetDefinitionLength getDefinitionLength;

  private:
    void * m_handle;
    TFramesMap m_frames;


};

typedef std::map<std::string, CSensor *> TSensorsMap;

}
}
}
#endif // CSENSOR_H
