/* %Id% */
#include "cprotocol.h"
#include "cvariant.h"
#include "st.h"
#include <climits>

namespace mon
{
namespace lib
{
namespace protocol
{

CProtocol::CProtocol(network::CSocket *socket) : m_socket(socket)
{
  m_currentID = 1;
}

CProtocol::~CProtocol()
{}

void CProtocol::incommingMessage(const std::string &i_incoming)
{
  CNetworkMessage t_msg(m_socket, i_incoming);
  MON_LOG_WRN("Uncknown incoming message type: " << t_msg.type() << " (" << t_msg.msg() << ")")
}

void CProtocol::sendMessage(const unsigned int &i_type, const std::string &i_text)
{
   CNetworkMessage(m_socket, i_type, i_text).send();
}

unsigned long long CProtocol::getID()
{
  if(m_currentID == ULLONG_MAX) { m_currentID = 1; }
  return m_currentID++;
}

}
}
}
