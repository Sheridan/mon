#ifndef PATHINTERFACE_H_INCLUDED
#define PATHINTERFACE_H_INCLUDED
#include "cfile.h"
namespace mon
{
namespace lib
{
namespace config
{

class CFolder;

class IPathInterface
{
public:

  virtual bool        containsFolder(const std::string & name) = 0;
  virtual CFolder   * folder        (const std::string & name) = 0;
  virtual int         foldersCount  ()                         = 0;
  virtual TStringList folders       ()                         = 0;

  virtual bool        containsFile(const std::string & name) = 0;
  virtual CFile     * file        (const std::string & name) = 0;
  virtual int         filesCount  ()                         = 0;
  virtual TStringList files       ()                         = 0;

};
}
}
}
#endif // PATHINTERFACE_H_INCLUDED
