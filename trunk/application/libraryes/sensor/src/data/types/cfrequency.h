// %Id%
#ifndef CFREQUENCY_H
#define CFREQUENCY_H
//#include "class-helper.h"
namespace mon
{
namespace lib
{
namespace sensor
{

enum EFrequenceType
{
  ftHz, // Обычное упоминание частоты
  ftSPP // Secunds per pulse, один раз в икс секунд
};

class CFrequency
{
  public:
    CFrequency(const EFrequenceType &i_type, const float &i_frequency);
    float asHz ();
    float asSPP();

  private:
    EFrequenceType  m_type;
    float           m_frequency;
};

}
}
}
#endif // CFREQUENCY_H
