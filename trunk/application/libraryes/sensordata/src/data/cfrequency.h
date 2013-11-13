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
enum EFrequencyMeasurment
{
  ftHz, //!< Обычное упоминание частоты
  ftSPP //!< Secunds per pulse, один раз в икс секунд
};

//! Частота сбора данных с фрейма
class CFrequency
{
  public:
    CFrequency(const EFrequencyMeasurment &i_measurment, const float &i_frequency);
    CFrequency(const std::string &freq);
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
