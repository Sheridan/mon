/* %Id% */
#ifndef CMONNODESMANAGER_H
#define CMONNODESMANAGER_H
#include "csingletonmember.h"
#include "ccollectorremotenode.h"

namespace mon
{
namespace daemons
{
namespace collector
{

//! Менеджер нод коллектора
class CCollectorNodesManager : public mon::lib::base::CSingletonMember
{
public:
  CCollectorNodesManager();
  virtual ~CCollectorNodesManager();
  //! Ориентируясь на конфиг загружает список нод и инициализирует подключение
  void load();
  //! Удаляет ноды из списка, рарывая подключение
  void unload();
private:
  TCollectorRemoteNodes m_nodes;
};

}
}
}
#endif // CMONNODESMANAGER_H
