/* %Id% */
#ifndef CNODECOLLECTORSSMANAGER_H
#define CNODECOLLECTORSSMANAGER_H
#include "cserversocket.h"
#include "csingletonmember.h"
#include "daemons/node/collector/ccollector.h"

namespace mon
{
namespace daemons
{
namespace node
{

//! Менеджер подключенных коллекторов
class CCollectors : public mon::lib::network::CSocketServer, public mon::lib::base::CSingletonMember
{
  public:
    CCollectors();
    ~CCollectors();
    void listen();
    void unlisten();

  private:
    TCollectors m_collectors;
    //! "Отщепление" сокета при успешном входящем подключении
    mon::lib::network::CSocketClient * incommingConnection(const int &clientDescriptor, const std::string &addr_from, const int & port_from) final;
    void incommingMessage(const std::string &message) final {}
};

}
}
}
#endif // CNODECOLLECTORSSMANAGER_H
