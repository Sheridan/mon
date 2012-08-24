/* %Id% */
#ifndef CNODE_H
#define CNODE_H
#include <map>
#include <list>
#include <string>

namespace mon
{
namespace lib
{
namespace config
{

class CFolder;
typedef std::pair<std::string, CFolder *> TFolderPair;
typedef std::map <std::string, CFolder *> TFoldersMap;
typedef std::list<             CFolder *> TFoldersList;

class CFile;
typedef std::pair<std::string, CFile   *> TFilePair;
typedef std::map <std::string, CFile   *> TFilesMap;
typedef std::list<             CFile   *> TFilesList;

class CNode
{
public:
  CNode(const std::string &nodeName, CNode *parentNode);
  virtual ~CNode();

  const std::string &name();
  int level();

protected:
  CNode *parent();

private:
  std::string m_name;
  CNode *m_parent;
};

}
}
}
#endif // CNODE_H
