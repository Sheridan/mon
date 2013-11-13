/* %Id% */
#include "cfolder.h"
#include "cfile.h"

namespace mon
{
namespace lib
{
namespace config
{

CFolder::CFolder() : CNode("", nullptr)
{}

CFolder::CFolder(const std::string &nodeName, CNode *parentNode) : CNode(nodeName, parentNode)
{}

CFolder::~CFolder()
{
  for(auto &folder : m_folders)
  {
    delete folder.second;
  }
  m_folders.clear();

  for(auto &file : m_files)
  {
    delete file.second;
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
  for(auto &folder : m_folders)
  {
    t_list.push_back(folder.second);
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
  for(auto &file : m_files)
  {
    t_list.push_back(file.second);
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
