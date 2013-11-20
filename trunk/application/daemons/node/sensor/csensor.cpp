/* %Id% */
#include <dlfcn.h>
#include "defines/st.h"
#include "defines/signals-helper.h"
#include "libraryes/sensordata/parcers/cdefinitionparcer.h"
#include "daemons/node/sensor/csensor.h"

namespace mon
{
namespace daemons
{
namespace node
{

CSensor::CSensor(const std::string &i_name)
  : m_name(i_name)
{
  m_handle            = nullptr;
  initSensor          = nullptr;
  getName             = nullptr;
  getDefinition       = nullptr;
  getDefinitionLength = nullptr;
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
  if ((error = dlerror()) != nullptr) \
  { \
    MON_LOG_ERR("Error importing function `" #_name "` from sensor `" << m_name << "`: " << error); \
    MON_ABORT; \
  }
#define MON_IMPORT(_type, _name) _name = (_type) dlsym(m_handle, #_name); MON_IMPORT_ERROR(_name);

void CSensor::load()
{
  if (m_handle)
  {
    char *error; error = nullptr;
    TFGetStatistics       getStatistics;
    TFGetFrameAvialable   getFrameAvialable;
    MON_IMPORT(TFInitSensor         , initSensor         );
    MON_IMPORT(TFGetName            , getName            );
    MON_IMPORT(TFGetDefinition      , getDefinition      );
    MON_IMPORT(TFGetDefinitionLength, getDefinitionLength);
    MON_IMPORT(TFGetStatistics      , getStatistics      );
    MON_IMPORT(TFGetFrameAvialable  , getFrameAvialable  );
    initSensor(MON_ST_LOGGER, MON_ST_CONFIG->folder("sensors")->folder(m_name));
    m_definition = new mon::lib::sensordata::CDefinition();
    mon::lib::sensordata::CDefinitionParcer parcer = {m_definition, getDefinition()};
    parcer.parce();
    for(auto &frame : m_definition->frames())
    {
      m_frames[frame] = new CFrame(this, getStatistics, getFrameAvialable, frame);
    }
  }
}

void CSensor::unload()
{
  if (m_handle)
  {
    for(auto frame : m_frames)
    {
      delete frame.second;
    }
    m_frames.clear();
    initSensor          = nullptr;
    getName             = nullptr;
    getDefinition       = nullptr;
    getDefinitionLength = nullptr;
    dlclose(m_handle);
    m_handle = nullptr;
    delete m_definition;
  }
}

CFrame *CSensor::frame(const std::string &name)
{
  if(m_handle)
  {
    return m_frames[name];
  }
  return nullptr;
}



}
}
}
