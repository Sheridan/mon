#ifndef CGENERATOR_H
#define CGENERATOR_H
#include "cfolder.h"
#include <stdio.h>

namespace mon
{
namespace lib
{
namespace config
{
class CGenerator
{
public:
  CGenerator(const std::string &filename, CFolder *root);
  virtual ~CGenerator();
  void generate();

private:
  std::string m_filename;
  FILE    *m_file;
  CFolder *m_root;
  bool     m_error;

  void writeFolder(CFolder *folder, const int &indent, const bool &parentIsSingle);
  void writeFile  (CFile *file);
  void writeIndent(const int &indent);
  std::string replaceSpetial(const std::string &source);
};

}
}
}
#endif // CGENERATOR_H
