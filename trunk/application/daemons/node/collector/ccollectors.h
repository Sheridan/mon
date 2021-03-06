/* %Id% */
#ifndef CNODECOLLECTORSSMANAGER_H
#define CNODECOLLECTORSSMANAGER_H
#include "libraryes/network/cserversocket.h"
#include "libraryes/base/singleton/csingletonmember.h"
#include "daemons/node/collector/ccollector.h"
#include "libraryes/model/ccollectors.h"

namespace mon
{
namespace daemons
{
namespace node
{

//! Менеджер подключенных коллекторов
class CCollectors :
    public mon::lib::model::CCollectors,
    public mon::lib::network::CSocketServer,
    public mon::lib::base::CSingletonMember
{
  public:
    CCollectors();
    ~CCollectors();
    void listen();

  private:
    //! "Отщепление" сокета при успешном входящем подключении
    mon::lib::network::CSocketClient * incommingConnection(const int &clientDescriptor, const std::string &addr_from, const int & port_from) final;
    void incommingMessage(const std::string &message) final {}
};

}
}
}
#endif // CNODECOLLECTORSSMANAGER_H
