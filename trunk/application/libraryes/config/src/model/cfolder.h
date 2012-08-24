/* %Id% */
#ifndef CFOLDER_H
#define CFOLDER_H
#include "cnode.h"
#include "pathinterface.h"

namespace mon
{
namespace lib
{
namespace config
{

class CFolder : public CNode, public IPathInterface
{
public:
  CFolder();
  CFolder(const std::string &nodeName, CNode *parentNode);
  ~CFolder();

  bool         containsFolder(const std::string & name);
  CFolder    * folder        (const std::string & name);
  int          foldersCount  ();
  TFoldersList folders       ();

  bool         containsFile(const std::string & name);
  CFile      * file        (const std::string & name);
  int          filesCount  ();
  TFilesList   files       ();

  CFolder   * parent();

private:
  TFoldersMap m_folders;
  TFilesMap   m_files;
};

}
}
}
#endif // CFOLDER_H
