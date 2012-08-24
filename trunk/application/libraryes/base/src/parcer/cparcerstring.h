#ifndef CPARCERSTRING_H
#define CPARCERSTRING_H
#include "cparcer.h"

namespace mon
{
namespace lib
{
namespace base
{

class CParcerString : public CParcer
{
    MON_READONLY_PROPERTY(std::string           , text      )
    MON_READONLY_PROPERTY(std::string::size_type, textLength)
    MON_READONLY_PROPERTY(std::string::size_type, textIndex )
  public:
    CParcerString(const std::string &i_text);
    ~CParcerString();

  private:
    TStdStringCharacter goOneCharacterForward();
    TStdStringCharacter goOneCharacterBack();
};

}
}
}
#endif // CPARCERSTRING_H
