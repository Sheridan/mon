/* %Id% */
#include "st.h"
#include "signals-helper.h"
#include "csensor.h"
#include <dlfcn.h>
#include "cdefinitionparcer.h"
#include "stl-helper.h"

namespace mon
{
namespace daemons
{
namespace node
{

CSensor::CSensor(const std::string &i_name)
  : mon::lib::base::CTimer(1),
    m_name(i_name)
{
  m_handle            = NULL;
  initSensor          = NULL;
  getName             = NULL;
  getDefinition       = NULL;
  getDefinitionLength = NULL;
  getStatistics       = NULL;
  getFrameAvialable   = NULL;
  MON_LOG_DBG("Loading sensor '" MON_GENERATED_SENSORS_PATH "/lib"+m_name+".so'");
  m_handle = dlopen(std::string(MON_GENERATED_SENSORS_PATH "/lib"+m_name+".so").c_str(), RTLD_NOW);
  if (!m_handle)
  {
    MON_LOG_ERR("Sensor " << m_name << " loading error: " << dlerror());
    MON_ABORT;
  }
}

CSensor::~CSensor()
{
  unload();
}

#define MON_IMPORT_ERROR(_name) \
  if ((error = dlerror()) != NULL) \
  { \
    MON_LOG_ERR("Error importing function `" #_name "` from sensor `" << m_name << "`: " << error); \
    MON_ABORT; \
  }
#define MON_IMPORT(_type, _name) _name = (_type) dlsym(m_handle, #_name); MON_IMPORT_ERROR(_name);

void CSensor::load()
{
  if (m_handle)
  {
    char *error; error = NULL;
    MON_IMPORT(TFInitSensor         , initSensor         );
    MON_IMPORT(TFGetName            , getName            );
    MON_IMPORT(TFGetDefinition      , getDefinition      );
    MON_IMPORT(TFGetDefinitionLength, getDefinitionLength);
    MON_IMPORT(TFGetStatistics      , getStatistics      );
    MON_IMPORT(TFGetFrameAvialable  , getFrameAvialable );
    initSensor(MON_ST_LOGGER, MON_ST_CONFIG->folder("sensors")->folder(m_name));
    m_definition = new mon::lib::sensordata::CDefinition();
    mon::lib::sensordata::CDefinitionParcer parcer(m_definition, getDefinition());
    parcer.parce();
    timerStart();
  }
}

void CSensor::unload()
{
  if (m_handle)
  {
    timerStop();
    while (timerActive()) { sleep(1); }
    initSensor          = NULL;
    getName             = NULL;
    getDefinition       = NULL;
    getDefinitionLength = NULL;
    getStatistics       = NULL;
    getFrameAvialable   = NULL;
    dlclose(m_handle);
    m_handle = NULL;
  }
}

void CSensor::onTimer()
{
  mon::lib::sensordata::TFramesNames fn = m_definition->frames();
  MON_STL_LIST_FOREACH(frame_name, mon::lib::sensordata::TFramesNames, fn)
  {
    MON_LOG_DBG(getStatistics(MON_STL_LIST_VALUE(frame_name).c_str()));
  }
}

}
}
}
