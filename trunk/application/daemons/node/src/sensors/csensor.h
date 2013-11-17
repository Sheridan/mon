/* %Id% */
#ifndef CSENSOR_H
#define CSENSOR_H
#include <string>
#include "class-helper.h"
#include <map>
#include "logger.h"
#include "config.h"

#include "cdefinition.h"
#include "cframe.h"

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
    mon::lib::sensordata::CDefinition *m_definition;

};

typedef std::map<std::string, CSensor *> TSensorsMap;

}
}
}
#endif // CSENSOR_H
