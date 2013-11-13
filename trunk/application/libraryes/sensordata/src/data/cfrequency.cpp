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

CFrequency::CFrequency(const std::string &freq)
{
  int index   = freq.find(" ");
  if (index != std::string::npos)
  {
    m_frequency  = mon::lib::base::toFloat(freq.substr(0, index));
    std::string meas = freq.substr(index+1, freq.length()-1);
         if(meas.compare("Hz") == 0) { m_measurment = ftHz; }
    else if(meas.compare("SPP") == 0) { m_measurment = ftSPP; }
  }
  else
  {
    m_frequency  = mon::lib::base::toFloat(freq);
    m_measurment = ftSPP;
  }
}

float CFrequency::asHz()
{
  switch(m_measurment)
  {
    case ftHz : { return m_frequency;  }
    case ftSPP: { return 1/m_frequency;}
  }
  return 0;
}

float CFrequency::asSPP()
{
  switch(m_measurment)
  {
    case ftHz : { return 1/m_frequency; }
    case ftSPP: { return m_frequency  ; }
  }
  return 0;
}

}
}
}
