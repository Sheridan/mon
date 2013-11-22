/* %Id% */
#ifndef CMONNODESMANAGER_H
#define CMONNODESMANAGER_H
#include "daemons/collector/node/cnode.h"
#include "libraryes/model/cnodes.h"
#include "libraryes/base/singleton/csingletonmember.h"

namespace mon
{
namespace daemons
{
namespace collector
{

//! Менеджер нод коллектора
class CNodes :
    public mon::lib::model::CNodes,
    public mon::lib::base::CSingletonMember
{
public:
  CNodes();
  virtual ~CNodes();
  //! Ориентируясь на конфиг загружает список нод и инициализирует подключение
  void load();
};

}
}
}
#endif // CMONNODESMANAGER_H
