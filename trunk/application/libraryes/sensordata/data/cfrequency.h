// %Id%
#ifndef CFREQUENCY_H
#define CFREQUENCY_H
#include <string>

namespace mon
{
namespace lib
{
namespace sensordata
{

//! Типы частот описания фрейма
enum EFrequencyPurpose
{
  fpMax,     //!< Максимальная частота
  fpDefault  //!< Частота по умолчанию
};

//! Типы частот
enum class EFrequencyMeasurment
{
  Hz, //!< Обычное упоминание частоты
  SPP //!< Secunds per pulse, один раз в икс секунд
};

float SPP2Hz(float val);
float Hz2SPP(float val);

//! Частота сбора данных с фрейма
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
