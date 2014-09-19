#ifndef CPARCERFILE_H
#define CPARCERFILE_H
#include <stdio.h>
#include "libraryes/base/parcer/cparcer.h"

namespace mon
{
namespace lib
{
namespace base
{

//! Парсер, читающий исходник из файла
class CParcerFile : public CParcer
{
    MON_READONLY_PROPERTY(std::string, filename)
  public:
    CParcerFile(const std::string &i_filename);
    ~CParcerFile();

  private:
    FILE    *m_file;

    TStdStringCharacter goOneCharacterForward() final;
    TStdStringCharacter goOneCharacterBack() final;

  protected:
    bool fileExists(const std::string &filename);
};

}
}
}
#endif // CPARCERFILE_H
