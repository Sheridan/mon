/* %Id% */
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
class CConfigurationGenerator
{
public:
  CConfigurationGenerator(const std::string &filename, CFolder *root);
  virtual ~CConfigurationGenerator();
  void generate();

private:
  std::string m_filename;
  FILE    *m_file;
  CFolder *m_root;
  bool     m_error;

  void writeFolder(CFolder *folder);
  void writeFile  (CFile *file);
  void writeIndent(const int &indent);
  std::string replaceSpetial(const std::string &source);
};

}
}
}
#endif // CGENERATOR_H
