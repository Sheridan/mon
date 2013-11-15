// %Id%
#include "cfrequency.h"
#include "cvariant.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

CFrequency::CFrequency(const EFrequencyMeasurment &i_measurment, const float &i_frequency)
  : m_measurment(i_measurment), m_frequency(i_frequency)
{
}

float CFrequency::asHz()
{
  switch(m_measurment)
  {
    case EFrequencyMeasurment::ftHz : { return m_frequency;  }
    case EFrequencyMeasurment::ftSPP: { return 1/m_frequency;}
  }
  return 0;
}

float CFrequency::asSPP()
{
  switch(m_measurment)
  {
    case EFrequencyMeasurment::ftHz : { return 1/m_frequency; }
    case EFrequencyMeasurment::ftSPP: { return m_frequency  ; }
  }
  return 0;
}

}
}
}
