/* %Id% */
#ifndef PATHINTERFACE_H_INCLUDED
#define PATHINTERFACE_H_INCLUDED
#include "libraryes/config/model/cnode.h"

namespace mon
{
namespace lib
{
namespace config
{

//! Интерфейс навигации по ветвям конфига
class IPathInterface
{
public:

  virtual bool         containsFolder(const std::string & name) = 0;
  virtual CFolder    * folder        (const std::string & name) = 0;
  virtual int          foldersCount  ()                         = 0;
  virtual TFoldersList folders       ()                         = 0;

  virtual bool        containsFile(const std::string & name) = 0;
  virtual CFile     * file        (const std::string & name) = 0;
  virtual int         filesCount  ()                         = 0;
  virtual TFilesList  files       ()                         = 0;
};

}
}
}
#endif // PATHINTERFACE_H_INCLUDED
