// %Id%
#include "cfrequences.h"
#include <stdio.h>

namespace mon
{
namespace lib
{
namespace sensor
{

CFrequences::CFrequences()
{
  m_max = NULL;
  m_def = NULL;
}

CFrequences::CFrequences(const EFrequenceType &typeMax, const float &frequencyMax, const EFrequenceType &typeDefault, const float &frequencyDefault)
{
  m_max = new CFrequency(typeMax    , frequencyMax    );
  m_def = new CFrequency(typeDefault, frequencyDefault);
}

CFrequences::~CFrequences()
{
  delete m_max;
  delete m_def;
}

}
}
}
