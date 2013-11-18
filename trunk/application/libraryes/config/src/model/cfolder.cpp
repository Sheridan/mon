/* %Id% */
#include "cfolder.h"
#include "cfile.h"

namespace mon
{
namespace lib
{
namespace config
{

CFolder::CFolder() : CFolder("", nullptr) {}
CFolder::CFolder(const std::string &nodeName, CNode *parentNode) : CNode(nodeName, parentNode)
{
  MON_MUTEX_INITIALIZE(folder)
  MON_MUTEX_INITIALIZE(file)
}

CFolder::~CFolder()
{
  MON_MUTEX_LOCK(folder)
  for(auto &folder : m_folders)
  {
    delete folder.second;
  }
  m_folders.clear();
  MON_MUTEX_UNLOCK(folder)
  MON_MUTEX_LOCK(file)
  for(auto &file : m_files)
  {
    delete file.second;
  }
  m_files.clear();
  MON_MUTEX_UNLOCK(file)
  MON_MUTEX_DESTROY(file)
  MON_MUTEX_DESTROY(folder)
}

bool CFolder::containsFolder(const std::string & name)
{
  MON_MUTEX_LOCK(folder)
  bool result = m_folders.find(name) != m_folders.end();
  MON_MUTEX_UNLOCK(folder)
  return result;
}

int CFolder::foldersCount()
{
  MON_MUTEX_LOCK(folder)
  int result = m_folders.size();
  MON_MUTEX_UNLOCK(folder)
  return result;
}

TFoldersList CFolder::folders()
{
  TFoldersList t_list;
  MON_MUTEX_LOCK(folder)
  for(auto &folder : m_folders)
  {
    t_list.push_back(folder.second);
  }
  MON_MUTEX_UNLOCK(folder)
  return t_list;
}

CFolder *CFolder::folder(const std::string & name)
{
  if(!containsFolder(name))
  {
    MON_MUTEX_LOCK(folder)
    m_folders[name] = new CFolder(name, this);
    MON_MUTEX_UNLOCK(folder)
  }
  MON_MUTEX_LOCK(folder)
  CFolder *f = m_folders[name];
  MON_MUTEX_UNLOCK(folder)
  return f;
}

bool CFolder::containsFile(const std::string & name)
{
  MON_MUTEX_LOCK(file)
  bool result = m_files.find(name) != m_files.end();
  MON_MUTEX_UNLOCK(file)
  return result;
}

int CFolder::filesCount()
{
  MON_MUTEX_LOCK(file)
  int result = m_files.size();
  MON_MUTEX_UNLOCK(file)
  return result;
}

TFilesList CFolder::files()
{
  TFilesList t_list;
  MON_MUTEX_LOCK(file)
  for(auto &file : m_files)
  {
    t_list.push_back(file.second);
  }
  MON_MUTEX_UNLOCK(file)
  return t_list;
}

CFile *CFolder::file(const std::string & name)
{
  if(!containsFile(name))
  {
    MON_MUTEX_LOCK(file)
    m_files[name] = new CFile(name, this);
    MON_MUTEX_UNLOCK(file)
  }
  MON_MUTEX_LOCK(file)
  CFile *f = m_files[name];
  MON_MUTEX_UNLOCK(file)
  return f;
}

CFolder * CFolder::parent()
{
  return static_cast<CFolder *>(CNode::parent());
}


}
}
}
