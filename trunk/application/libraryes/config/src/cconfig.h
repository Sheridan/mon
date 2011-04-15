#ifndef CCONFIG_H
#define CCONFIG_H
#include "cfolder.h"
#include <queue>
namespace mon
{
namespace lib
{
namespace config
{

class CConfig : public IPathInterface
{
public:
  CConfig();
  virtual ~CConfig();
  void load(const std::string &filename);
  void save(const std::string &filename);

  bool        containsFolder(const std::string & name);
  CFolder   * folder        (const std::string & name);
  int         foldersCount  ();
  TStringList folders       ();

  bool        containsFile(const std::string & name);
  CFile     * file        (const std::string & name);
  int         filesCount  ();
  TStringList files       ();

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
