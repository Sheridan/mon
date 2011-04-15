#ifndef CCLIENTSOCKET_H
#define CCLIENTSOCKET_H
#include "csocket.h"
#include <map>

namespace mon
{

namespace lib
{
namespace network
{

class CSocketClient : public CSocket
{
public:
  CSocketClient();
  CSocketClient(const int &descriptor);
  void connect(const std::string &addr, const unsigned short &port);
  void connect();
};

typedef std::map<int, CSocketClient *> TClientSockets;

}
}
}
#endif // CCLIENTSOCKET_H
