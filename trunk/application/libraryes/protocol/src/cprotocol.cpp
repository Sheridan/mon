/* %Id% */
#include "cprotocol.h"
#include "cvariant.h"
#include "st.h"
namespace mon
{
namespace lib
{
namespace protocol
{

CProtocol::CProtocol(network::CSocket *socket) : m_socket(socket)
{}

CProtocol::~CProtocol()
{}

void CProtocol::incommingMessage(const std::string &i_incoming)
{
  CMessage t_msg(i_incoming);
  switch (t_msg.type())
  {
    case MON_PROTO_ID_COLLECTOR_TO_NODE_CONNECT:
    {
      sendMessage(
                   MON_PROTO_ID_CONNECT_ANSWER,
                   t_msg.msg().compare(MON_ST_CONFIG->folder("node")->file("password")->get(std::string(""))) == 0 ? "+" : "-"
                 );
      break;
    }
    case MON_PROTO_ID_CONNECT_ANSWER:
    {

      break;
    }
    default: MON_LOG_WRN("Uncknown incoming message type: " << t_msg.type() << " (" << t_msg.msg() << ")")
  }
}

void CProtocol::sendMessage(const unsigned int &i_type, const std::string &i_text)
{
   m_socket->write(CMessage(i_type, i_text).prepared_msg());
}

}
}
}
