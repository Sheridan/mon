#ifndef CPARCERFILE_H
#define CPARCERFILE_H
#include "cparcer.h"
#include <stdio.h>

namespace mon
{
namespace lib
{
namespace base
{
class CParcerFile : public CParcer
{
    MON_READONLY_PROPERTY(std::string, filename)
  public:
    CParcerFile(const std::string &i_filename);
    ~CParcerFile();

  private:
    FILE    *m_file;
    bool     m_eof;
    bool     m_error;

    SExtractedCharacter goOneCharacterForward();
    SExtractedCharacter goOneCharacterBack();
};

}
}
}
#endif // CPARCERFILE_H
