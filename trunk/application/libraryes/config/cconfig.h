/* %Id% */
#ifndef CCONFIG_H
#define CCONFIG_H
#include <queue>
#include "libraryes/config/model/cfolder.h"

namespace mon
{
namespace lib
{
namespace config
{

//! Конфиг, объект верхнего уровня
class CConfig : public IPathInterface
{
public:
  CConfig();
  virtual ~CConfig();
  void load(const std::string &filename);
  void save(const std::string &filename);

  bool         containsFolder(const std::string & name) final;
  CFolder    * folder        (const std::string & name) final;
  int          foldersCount  () final;
  TFoldersList folders       () final;

  bool       containsFile(const std::string & name) final;
  CFile    * file        (const std::string & name) final;
  int        filesCount  () final;
  TFilesList files       () final;

  CFolder  * root        ();

  // `fs` operations :)
  void cd(CFolder *val);
  void cdRoot();
//  void rm(CFolder *val);
//  void rm(CFile *val);
//  void mv(CFolder *from, CFolder *to);
//  void mv(CFile   *from, CFolder *to);

private:
  std::string  m_base_filename;
  std::string  m_run_filename;
  CFolder * m_root;
  CFolder * m_pwd;
};

}
}
}
#endif // CCONFIG_H
