/* %Id% */
#ifndef CCONFIGURATIONPARCER_H
#define CCONFIGURATIONPARCER_H
#include <string>
#include "cfolder.h"
#include "cparcerfile.h"

namespace mon
{
namespace lib
{
namespace config
{

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
};

}
}
}

#endif // CCONFIGURATIONPARCER_H
