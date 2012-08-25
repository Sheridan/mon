// %Id%
#include "cfrequency.h"
namespace mon
{
namespace lib
{
namespace sensor
{

CFrequency::CFrequency(const EFrequenceType &i_type, const float &i_frequency)
  : m_type(i_type), m_frequency(i_frequency)
{
}

float CFrequency::asHz()
{
  switch(m_type)
  {
    case ftHz : { return m_frequency;  }
    case ftSPP: { return 1/m_frequency;}
  }
  return 0;
}

float CFrequency::asSPP()
{
  switch(m_type)
  {
    case ftHz : { return 1/m_frequency; }
    case ftSPP: { return m_frequency  ; }
  }
  return 0;
}

}
}
}
