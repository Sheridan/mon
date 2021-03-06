/* %Id% */
#include "defines/protocol-control.h"
#include "libraryes/protocol/cnetworkmessage.h"
#include "libraryes/base/string/cvariant.h"

namespace mon
{
namespace lib
{
namespace protocol
{

CNetworkMessage::CNetworkMessage(const MON_PROTOCOL_MESSAGE_ID_TYPE &id, const EProtocolMessageType &i_type)
  : mon::lib::base::CStringBuilderBase(),
    m_type(i_type),
    m_id(id)
{}

CNetworkMessage::CNetworkMessage(const MON_PROTOCOL_MESSAGE_ID_TYPE & id, const EProtocolMessageType &i_type, const std::string  &i_text)
  : mon::lib::base::CStringBuilderBase(),
    m_type(i_type),
    m_id(id)
{
  append(i_text);
}

CNetworkMessage::CNetworkMessage(const std::string  &i_incoming)
  : mon::lib::base::CStringBuilderBase()
{
  int id_index   = i_incoming.find(MON_PROTOCOL_DELIMITER(id  , type   ));
  int type_index = i_incoming.find(MON_PROTOCOL_DELIMITER(type, message));

  m_id   = mon::lib::base::toULLong(i_incoming.substr(0, id_index));
  m_type = static_cast<EProtocolMessageType>(mon::lib::base::toInt(i_incoming.substr(id_index+1, type_index)));

  append(i_incoming.substr(type_index+1, i_incoming.length()));
}

CNetworkMessage::~CNetworkMessage()
{}

const std::string &CNetworkMessage::preparedText()
{
  append(MON_PROTOCOL_DELIMITER(end,line));
  preface(MON_PROTOCOL_DELIMITER(type, message));
  preface(m_type);
  preface(MON_PROTOCOL_DELIMITER(id, type));
  preface(m_id);
  return string();
}


}
}
}
