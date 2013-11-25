/* %Id% */
#ifndef CSENSOR_H
#define CSENSOR_H
#include <string>
#include "defines/class-helper.h"
#include "libraryes/logger/logger.h"
#include "libraryes/config/config.h"
#include "libraryes/sensordata/data/cdefinition.h"
#include "daemons/node/sensor/cframe.h"
#include "libraryes/model/csensor.h"

namespace mon
{
namespace daemons
{
namespace node
{

class CSensors;

using TFInitSensor          = void               (*)(mon::lib::logger::CLogger *, mon::lib::config::CFolder *);
using TFGetName             = const char        *(*)(void);
using TFGetDefinition       = const char        *(*)(void);
using TFGetDefinitionLength = const unsigned int (*)(void);

//! Сенсор ноды, посредник между нодой и библиотекой
class CSensor : public mon::lib::model::CSensor
{
  public:
    CSensor(CSensors *parent, const std::string &name);
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


}
}
}
#endif // CSENSOR_H
