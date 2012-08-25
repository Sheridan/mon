// %Id%
#ifndef CFREQUENCES_H
#define CFREQUENCES_H
#include "cfrequency.h"
#include "class-helper.h"

namespace mon
{
namespace lib
{
namespace sensor
{

class CFrequences
{
    MON_READONLY_PROPERTY(CFrequency *, max)
    MON_READONLY_PROPERTY(CFrequency *, def)
  public:
    CFrequences();
    CFrequences(const EFrequenceType &typeMax, const float &frequencyMax, const EFrequenceType &typeDefault, const float &frequencyDefault);
    ~CFrequences();
};

}
}
}
#endif // CFREQUENCES_H
