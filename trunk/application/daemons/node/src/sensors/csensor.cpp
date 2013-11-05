/* %Id% */
#include "st.h"
#include "signals-helper.h"
#include "csensor.h"
#include <dlfcn.h>
namespace mon
{
namespace daemons
{
namespace node
{

CSensor::CSensor(const std::string &i_name) : m_name(i_name)
{
  m_handle = dlopen(std::string(MON_GENERATED_SENSORS_PATH "/lib"+m_name+".so").c_str(), RTLD_NOW);
  if (!m_handle)
  {
    MON_LOG_ERR("Sensor " << m_name << " loading error: " << dlerror());
    MON_ABORT;
  }
}

CSensor::~CSensor()
{
  if (m_handle)
  {
    dlclose(m_handle);
  }
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
  char *error; error = NULL;
  MON_IMPORT(TFInitSensor         , initSensor         );
  MON_IMPORT(TFGetName            , getName            );
  MON_IMPORT(TFGetDefinition      , getDefinition      );
  MON_IMPORT(TFGetDefinitionLength, getDefinitionLength);
  MON_IMPORT(TFGetStatistics      , getStatistics      );
  MON_IMPORT(TFGetSensorAvialable , getSensorAvialable );
  initSensor(MON_ST_LOGGER, MON_ST_CONFIG->folder("sensors")->folder(m_name));
}

}
}
}
