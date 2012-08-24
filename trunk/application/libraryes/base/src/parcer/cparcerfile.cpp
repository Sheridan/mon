#include "cparcerfile.h"
#include "parcer-helper.h"
#include <stdlib.h>

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

TStdStringCharacter CParcerFile::goOneCharacterForward()
{
  int result = fgetc(m_file);
  m_eof = result == EOF;
  if(result == -1 && !m_eof)
  {
    m_error = true;
    MON_PRINT_FILEOP_ERRNO(m_filename, "Read file error");
    return 0;
  }
  return static_cast<TStdStringCharacter>(result);
}

TStdStringCharacter CParcerFile::goOneCharacterBack()
{
//  MON_LOG_DBG((int)sizeof(TStdStringCharacter)*2); MON_ABORT;
  if(fseek(m_file, ftell(m_file)-(sizeof(TStdStringCharacter)*2), SEEK_SET) == -1)
  {
    m_error = true;
    MON_PRINT_FILEOP_ERRNO(m_filename, "Seek file error");
    return 0;
  }
  return readCharacter();
}

}
}
}
