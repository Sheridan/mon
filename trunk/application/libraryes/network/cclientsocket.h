/* %Id% */
#ifndef CCLIENTSOCKET_H
#define CCLIENTSOCKET_H
#include "libraryes/network/csocket.h"
#include <map>

namespace mon
{

namespace lib
{
namespace network
{

//! Клиентский сокет
class CSocketClient : public CSocket
{
  public:
    CSocketClient();
    CSocketClient(const int &descriptor, const std::string &addr_from, const int & port_from);
    virtual ~CSocketClient();
    void connect(const std::string &addr, const unsigned short &port);
    void connect();

  protected:
    virtual void connected(const std::string &to_addr, const unsigned short &to_port) = 0;

};

typedef std::map<int, CSocketClient *> TClientSockets;

}
}
}
#endif // CCLIENTSOCKET_H
