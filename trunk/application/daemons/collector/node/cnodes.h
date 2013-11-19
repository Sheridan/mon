/* %Id% */
#ifndef CMONNODESMANAGER_H
#define CMONNODESMANAGER_H
#include "csingletonmember.h"
#include "daemons/collector/node/cnode.h"

namespace mon
{
namespace daemons
{
namespace collector
{

//! Менеджер нод коллектора
class CNodes : public mon::lib::base::CSingletonMember
{
public:
  CNodes();
  virtual ~CNodes();
  //! Ориентируясь на конфиг загружает список нод и инициализирует подключение
  void load();
  //! Удаляет ноды из списка, рарывая подключение
  void unload();
private:
  TNodes m_nodes;
};

}
}
}
#endif // CMONNODESMANAGER_H
