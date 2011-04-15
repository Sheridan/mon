#include "cfolder.h"
namespace mon
{
namespace lib
{
namespace config
{

CFolder::CFolder() : CNode("", NULL)
{
  //ctor
}

CFolder::CFolder(const std::string &nodeName, CNode *parentNode) : CNode(nodeName, parentNode)
{

}

CFolder::~CFolder()
{
  TFolders::iterator iFolder = m_folders.begin();
  while (iFolder != m_folders.end())
  {
    delete iFolder->second;
    iFolder++;
  }
  m_folders.clear();

  TFiles::iterator iFile = m_files.begin();
  while (iFile != m_files.end())
  {
    delete iFile->second;
    iFile++;
  }
  m_files.clear();
}

bool CFolder::containsFolder(const std::string & name)
{
  return m_folders.find(name) != m_folders.end();
}

int CFolder::foldersCount()
{
  return m_folders.size();
}

TStringList CFolder::folders()
{
  TStringList slist;
  TFolders::iterator iFolder = m_folders.begin();
  while (iFolder != m_folders.end())
  {
    slist.push_back(iFolder->first);
    iFolder++;
  }
  return slist;
}

CFolder *CFolder::folder(const std::string & name)
{
  if(!containsFolder(name))
  {
    m_folders[name] = new CFolder(name, this);
  }
  return m_folders[name];
}

bool CFolder::containsFile(const std::string & name)
{
  return m_files.find(name) != m_files.end();
}

int CFolder::filesCount()
{
  return m_files.size();
}

TStringList CFolder::files()
{
  TStringList slist;
  TFiles::iterator iFile = m_files.begin();
  while (iFile != m_files.end())
  {
    slist.push_back(iFile->first);
    iFile++;
  }
  return slist;
}

CFile *CFolder::file(const std::string & name)
{
  if(!containsFile(name))
  {
    m_files[name] = new CFile(name, this);
  }
  return m_files[name];
}

CFolder * CFolder::parent()
{
  return static_cast<CFolder *>(CNode::parent());
}


}
}
}
