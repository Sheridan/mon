// %Id%
#ifndef CFREQUENCY_H
#define CFREQUENCY_H
//#include "class-helper.h"
namespace mon
{
namespace lib
{
namespace sensordata
{

enum EFrequencyMeasurment
{
  ftHz, // Обычное упоминание частоты
  ftSPP // Secunds per pulse, один раз в икс секунд
};

class CFrequency
{
  public:
    CFrequency(const EFrequencyMeasurment &i_measurment, const float &i_frequency);
    float asHz ();
    float asSPP();

  private:
    EFrequencyMeasurment  m_measurment;
    float                 m_frequency;
};

}
}
}
#endif // CFREQUENCY_H