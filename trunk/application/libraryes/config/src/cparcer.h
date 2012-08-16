/* %Id% */
#ifndef CPARCER_H
#define CPARCER_H
#include <string>
#include "cfolder.h"
#include <stdio.h>

namespace mon
{
namespace lib
{
namespace config
{

typedef std::string::value_type TCFChar;

class CParcer
{
public:
  CParcer(const std::string &filename, CFolder *root);
  ~CParcer();
  void parce();

private:
  std::string m_filename;
  FILE    *m_file;
  CFolder *m_root;

  // flags
  bool     m_eof;
  bool     m_error;

  // statistic
  unsigned int m_linesCount;
  unsigned int m_charactersCount;
  unsigned int m_currentLineCharactersCount;

  TCFChar readChar();
  void stepBack();
  void skipComment();
  std::string readString(const TCFChar &stringOpenChar);

  void readFolder(CFolder *folder, const TCFChar &lastFolderDelimiter = 0);
  void readValue(CFile *file);
  bool convertBool(const char *buffer);
};

}
}
}

#endif // CPARCER_H
