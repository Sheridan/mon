#include "cparcerfile.h"
#include "parcer-helper.h"

namespace mon
{
namespace lib
{
namespace base
{

CParcerFile::CParcerFile(const std::string &i_filename) : CParcer(), m_filename(i_filename)
{
  m_file = fopen(m_filename.c_str(), "r");
  if(m_file == NULL)
  {
    m_error = true;
    MON_PRINT_FILEOP_ERRNO(m_filename, "Open file error");
  }
}

CParcerFile::~CParcerFile()
{
  if(m_error) { return; }

  if(fclose(m_file) == EOF)
  {
    MON_PRINT_FILEOP_ERRNO(m_filename, "Close file error");
  }
}

SExtractedCharacter CParcerFile::goOneCharacterForward()
{
  int result = fgetc(m_file);
  if(result == -1 && result != EOF)
  {
    m_error = true;
    MON_PRINT_FILEOP_ERRNO(m_filename, "Read file error");
    return SExtractedCharacter();
  }

  m_eof = result == EOF;
  return SExtractedCharacter(static_cast<TStdStringCharacter>(result));
}

SExtractedCharacter CParcerFile::goOneCharacterBack()
{
  if(fseek(m_file, -sizeof(TStdStringCharacter)*2, SEEK_CUR) == -1)
  {
    m_error = true;
    MON_PRINT_FILEOP_ERRNO(m_filename, "Seek");
    return SExtractedCharacter();
  }
  return readCharacter();
}

}
}
}
