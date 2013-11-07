/* %Id% */
#ifndef CPROTOCOL_H
#define CPROTOCOL_H
#include "csocket.h"
#include "cnetworkmessage.h"
#include "protocol-control.h"
#include <map>

namespace mon
{
namespace lib
{
namespace protocol
{

typedef void (*TFIncommingMsgCallback) (mon::lib::protocol::CNetworkMessage &);
typedef std::map<int,TFIncommingMsgCallback> TCallMap;

class CProtocol
{
public:
  CProtocol(mon::lib::network::CSocket *socket);
  virtual ~CProtocol();
  void incommingMessage(const std::string &i_incoming);

protected:
  void sendMessage(const unsigned int &i_type, const std::string &i_text = "");

private:
  mon::lib::network::CSocket *m_socket;
  unsigned long long m_currentID; //!< Текущий идентификатор сообщения. При достижении максимума - сбрасывается в ноль

  unsigned long long getID();
};



}
}
}
#endif // CPROTOCOL_H
