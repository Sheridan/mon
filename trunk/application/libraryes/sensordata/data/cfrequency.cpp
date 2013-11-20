// %Id%
#include "libraryes/sensordata/data/cfrequency.h"
#include "libraryes/base/string/cvariant.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

float SPP2Hz(float val) { return 1/val; }
float Hz2SPP(float val) { return 1/val; }

CFrequency::CFrequency(const EFrequencyMeasurment &i_measurment, const float &i_frequency)
  : m_measurment(i_measurment), m_frequency(i_frequency)
{
}

float CFrequency::asHz()
{
  switch(m_measurment)
  {
    case EFrequencyMeasurment::Hz : { return m_frequency;  }
    case EFrequencyMeasurment::SPP: { return SPP2Hz(m_frequency);}
  }
  return 0;
}

float CFrequency::asSPP()
{
  switch(m_measurment)
  {
    case EFrequencyMeasurment::Hz : { return Hz2SPP(m_frequency); }
    case EFrequencyMeasurment::SPP: { return m_frequency  ; }
  }
  return 0;
}

}
}
}
