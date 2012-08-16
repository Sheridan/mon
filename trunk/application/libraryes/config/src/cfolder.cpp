/* %Id% */
#include "cfolder.h"
#include "cfile.h"
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
  TFoldersMap::iterator iFolder = m_folders.begin();
  while (iFolder != m_folders.end())
  {
    delete iFolder->second;
    iFolder++;
  }
  m_folders.clear();

  TFilesMap::iterator iFile = m_files.begin();
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

TFoldersList CFolder::folders()
{
  TFoldersList t_list;
  TFoldersMap::iterator t_folder = m_folders.begin();
  while (t_folder != m_folders.end())
  {
    t_list.push_back(t_folder->second);
    t_folder++;
  }
  return t_list;
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

TFilesList CFolder::files()
{
  TFilesList t_list;
  TFilesMap::iterator t_file = m_files.begin();
  while (t_file != m_files.end())
  {
    t_list.push_back(t_file->second);
    t_file++;
  }
  return t_list;
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
