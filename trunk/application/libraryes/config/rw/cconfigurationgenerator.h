/* %Id% */
#ifndef CGENERATOR_H
#define CGENERATOR_H
#include <stdio.h>
#include "libraryes/config/model/cfolder.h"

namespace mon
{
namespace lib
{
namespace config
{

//! Генератор конфигурации, записывает данные из ветви с подветвями в файл
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
