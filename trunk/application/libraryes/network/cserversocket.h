/* %Id% */
#ifndef CSERVERSOCKET_H
#define CSERVERSOCKET_H
#include "defines/threads-helper.h"
#include "libraryes/network/csocket.h"
#include "libraryes/network/cclientsocket.h"

namespace mon
{
namespace lib
{
namespace network
{

//! Серверный сокет
class CSocketServer : public CSocket
{
  MON_THREADED_FUNCTION_DECLARE(listen)
public:
  CSocketServer();
  virtual ~CSocketServer();
  void listen(const unsigned short &port);
  void close();

protected:
  TClientSockets m_clients;
  virtual CSocketClient * incommingConnection(const int &clientDescriptor, const std::string &addr_from, const int & port_from) = 0;

};

}
}
}
#endif // CSERVERSOCKET_H
