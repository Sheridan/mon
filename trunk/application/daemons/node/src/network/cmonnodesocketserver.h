#ifndef CMONNODESOCKETSERVER_H
#define CMONNODESOCKETSERVER_H
#include "cserversocket.h"
#include "csingletonmember.h"

namespace mon
{
namespace daemons
{
namespace node
{

class CMonNodeSocketServer : public mon::lib::network::CSocketServer, public mon::lib::base::CSingletonMember
{
public:
  CMonNodeSocketServer();
  ~CMonNodeSocketServer();
  void listen();
protected:
private:
  bool incommingConnection(mon::lib::network::CSocketClient *client);
  bool checkConnection(mon::lib::network::CSocketClient *client);
};

}
}
}
#endif // CMONNODESOCKETSERVER_H
