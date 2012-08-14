#ifndef CSERVERSOCKET_H
#define CSERVERSOCKET_H
#include "csocket.h"
#include "cclientsocket.h"
#include "threads-helper.h"

namespace mon
{
namespace lib
{
namespace network
{

class CSocketServer : public CSocket
{
  MON_THREADED_FUNCTION_DECLARE(listen)
public:
  CSocketServer();
  ~CSocketServer();
  void listen(const unsigned short &port);
  void close();

protected:
  TClientSockets m_clients;
  virtual bool incommingConnection(CSocketClient *client) = 0;
  virtual bool checkConnection(CSocketClient *client) = 0;

};

}
}
}
#endif // CSERVERSOCKET_H
