/* %Id% */
#ifndef CCOLLECTORSSMANAGER_H
#define CCOLLECTORSSMANAGER_H
#include "cserversocket.h"
#include "csingletonmember.h"
#include "cremotecollector.h"

namespace mon
{
namespace daemons
{
namespace node
{

//! Менеджер подключенных коллекторов
class CCollectorsManager : public mon::lib::network::CSocketServer, public mon::lib::base::CSingletonMember
{
public:
  CCollectorsManager();
  ~CCollectorsManager();
  void listen();
  void unlisten();
protected:
private:
  TRemoteCollectors m_collectors;

  //! "Отщепление" сокета при успешном входящем подключении
  mon::lib::network::CSocketClient * incommingConnection(const int &clientDescriptor, const std::string &addr_from, const int & port_from) final;
  void incommingMessage(const std::string &message) final;
};

}
}
}
#endif // CCOLLECTORSSMANAGER_H
