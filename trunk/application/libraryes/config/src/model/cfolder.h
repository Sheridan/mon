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

//! Ветвь конфига
class CFolder : public CNode, public IPathInterface
{
public:
  CFolder();
  CFolder(const std::string &nodeName, CNode *parentNode);
  ~CFolder();

  bool         containsFolder(const std::string & name) final;
  CFolder    * folder        (const std::string & name) final;
  int          foldersCount  () final;
  TFoldersList folders       () final;

  bool         containsFile(const std::string & name) final;
  CFile      * file        (const std::string & name) final;
  int          filesCount  () final;
  TFilesList   files       () final;

  CFolder   * parent();

private:
  TFoldersMap m_folders;
  TFilesMap   m_files;
};

}
}
}
#endif // CFOLDER_H
