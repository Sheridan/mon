#include "cprotocol.h"
#include "cvariant.h"
namespace mon
{
namespace lib
{
namespace protocol
{

CProtocol::CProtocol(network::CSocket *socket) : m_socket(socket)
{
}

CProtocol::~CProtocol()
{
}

void CProtocol::connect(const std::string &password)
{
  CMessage t_msg(MON_PROTO_CONNECT_ID);
  t_msg << password;
  m_socket->write(t_msg.prepared_msg());
}

void CProtocol::incommingMessage(const std::string &i_incoming)
{
  CMessage t_msg(i_incoming);
  switch (t_msg.type())
  {
    case MON_PROTO_CONNECT_ID:
    {
      break;
    }
  }
}

void CProtocol::connectionRequested(const std::string &password)
{

}

void CProtocol::connectionSendAnswer(const bool &answer)
{

}

void CProtocol::connectionAnswerReceived(const bool &answer)
{

}

}
}
}
