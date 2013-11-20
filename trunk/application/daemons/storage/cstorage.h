#ifndef CSTORAGE_H
#define CSTORAGE_H
#include "libraryes/base/singleton/csingletonmember.h"
#include "libraryes/network/cserversocket.h"

namespace mon
{
namespace daemons
{
namespace storage
{
//! Менеджер хранилища
class CStorage : public mon::lib::network::CSocketServer, public mon::lib::base::CSingletonMember
{
  public:
    CStorage();
    ~CStorage();
    void listen();
    void unlisten();
  private:
    //! "Отщепление" сокета при успешном входящем подключении
    mon::lib::network::CSocketClient * incommingConnection(const int &clientDescriptor, const std::string &addr_from, const int & port_from) final;
    void incommingMessage(const std::string &message) final {}
};
}
}
}
#endif // CSTORAGE_H
