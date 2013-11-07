/* %Id% */
#include "cnetworkmessage.h"
#include "cvariant.h"
#include "protocol-control.h"

namespace mon
{
namespace lib
{
namespace protocol
{

CNetworkMessage::CNetworkMessage(const unsigned long long &id, mon::lib::network::CSocket * socket, const unsigned int &i_type)
  : mon::lib::base::CStringBuilder(),
    m_type(i_type), m_socket(socket), m_id(id)
{}

CNetworkMessage::CNetworkMessage(const unsigned long long & id, mon::lib::network::CSocket * socket, const unsigned int &i_type, const std::string  &i_text)
  : mon::lib::base::CStringBuilder(),
    m_type(i_type), m_socket(socket), m_id(id)
{
  append(i_text);
}

CNetworkMessage::CNetworkMessage(mon::lib::network::CSocket * socket, const std::string  &i_incoming)
  : mon::lib::base::CStringBuilder(), m_socket(socket)
{
  int id_index   = i_incoming.find(MON_PROTO_ID_I_TYPE_DELIMITER     );
  int type_index = i_incoming.find(MON_PROTO_TYPE_I_MESSAGE_DELIMITER);

  m_id   = mon::lib::base::toULLong(i_incoming.substr(0, id_index));
  m_type = mon::lib::base::toULLong(i_incoming.substr(id_index+1, type_index));

  append(i_incoming.substr(type_index+1, i_incoming.length()));
}

CNetworkMessage::~CNetworkMessage()
{}

void CNetworkMessage::send()
{
  append(MON_PROTO_ENDL);
  preface(MON_PROTO_TYPE_I_MESSAGE_DELIMITER);
  preface(m_type);
  preface(MON_PROTO_ID_I_TYPE_DELIMITER);
  preface(m_id);
  m_socket->write(msg());
  delete this;
}

}
}
}
