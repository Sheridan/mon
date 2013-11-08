/* %Id% */
#ifndef CMONNODESMANAGER_H
#define CMONNODESMANAGER_H
#include "csingletonmember.h"
#include "cremotenode.h"

namespace mon
{
namespace daemons
{
namespace collector
{

//! Менеджер нод коллектора
class CNodesManager : public mon::lib::base::CSingletonMember
{
public:
  CNodesManager();
  virtual ~CNodesManager();
  //! Ориентируясь на конфиг загружает список нод и инициализирует подключение
  void load();
  //! Удаляет ноды из списка, рарывая подключение
  void unload();
private:
  TRemoteNodes m_nodes;
};

}
}
}
#endif // CMONNODESMANAGER_H
