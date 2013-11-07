/* %Id% */
#ifndef CPROTOCOL_H
#define CPROTOCOL_H
#include "csocket.h"
#include "cnetworkmessage.h"
#include "protocol-control.h"


namespace mon
{
namespace lib
{
namespace protocol
{

typedef void (*TFIncommingMsgCallback) (const std::string &);

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
};

}
}
}
#endif // CPROTOCOL_H
