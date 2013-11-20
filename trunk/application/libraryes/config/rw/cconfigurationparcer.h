/* %Id% */
#ifndef CCONFIGURATIONPARCER_H
#define CCONFIGURATIONPARCER_H
#include <string>
#include "libraryes/config/model/cfolder.h"
#include "libraryes/base/parcer/cparcerfile.h"

namespace mon
{
namespace lib
{
namespace config
{

//! Парсер конфиг-файла
class CConfigurationParcer : mon::lib::base::CParcerFile
{
public:
  CConfigurationParcer(const std::string &filename, CFolder *root);
  ~CConfigurationParcer();
  void parce();

private:
  CFolder *m_root;
  void readFolder(CFolder *folder, const mon::lib::base::TStdStringCharacter &lastFolderDelimiter = 0);
  void readValue(CFile *file);
  void includeFile(CFolder *folder);
};

}
}
}

#endif // CCONFIGURATIONPARCER_H
