#ifndef CFOLDER_H
#define CFOLDER_H
#include "cnode.h"
#include "cfile.h"
#include "pathinterface.h"

namespace mon
{
namespace lib
{
namespace config
{

class CFolder;
typedef std::pair<std::string, CFolder *> TFolder;
typedef std::map <std::string, CFolder *> TFolders;

class CFolder : public CNode, public IPathInterface
{
public:
  CFolder();
  CFolder(const std::string &nodeName, CNode *parentNode);
  ~CFolder();

  bool        containsFolder(const std::string & name);
  CFolder   * folder        (const std::string & name);
  int         foldersCount  ();
  TStringList folders       ();

  bool        containsFile(const std::string & name);
  CFile     * file        (const std::string & name);
  int         filesCount  ();
  TStringList files       ();

  CFolder   * parent();

private:
  TFolders m_folders;
  TFiles   m_files;
};

}
}
}
#endif // CFOLDER_H
