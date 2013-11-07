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

CNetworkMessage::CNetworkMessage(const unsigned int &i_type)
  : mon::lib::base::CStringBuilder(),
    m_type(i_type)
{}

CNetworkMessage::CNetworkMessage(const std::string  &i_incoming)
  : mon::lib::base::CStringBuilder()
{
  int t_index = i_incoming.find(MON_PROTO_TYPE_DELIMITER);
  m_type = mon::lib::base::toUInt(i_incoming.substr(0, t_index));
  append(i_incoming.substr(t_index+1, i_incoming.length()));
}

CNetworkMessage::CNetworkMessage(const unsigned int &i_type, const std::string  &i_text)
  : mon::lib::base::CStringBuilder(),
    m_type(i_type)
{
  append(i_text);
}

CNetworkMessage::~CNetworkMessage()
{}

const std::string &CNetworkMessage::prepared_msg()
{
//  preface(MON_PROTO_TYPE_DELIMITER);
//  preface(m_id);
  append(MON_PROTO_ENDL);
  preface(MON_PROTO_TYPE_DELIMITER);
  preface(m_type);
  return msg();
}

}
}
}
