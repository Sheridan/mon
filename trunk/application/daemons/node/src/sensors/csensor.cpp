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
  m_handle = NULL;
}

CSensor::~CSensor()
{

}

void CSensor::load()
{
  m_handle = dlopen(std::string(MON_GENERATED_SENSORS_PATH "/lib"+m_name+".so").c_str(), RTLD_NOW);
  if (!m_handle)
  {
    MON_LOG_ERR("Sensor " << m_name << " loading error: " << dlerror());
    MON_ABORT;
  }
}

}
}
}
