/* %Id% */
#include "cmessage.h"
#include "cvariant.h"

namespace mon
{
namespace lib
{
namespace protocol
{

CMessage::CMessage(const unsigned int &i_type) : mon::lib::base::CStringBuilder(),  m_type(i_type)
{}

CMessage::CMessage(const std::string  &i_incoming) : mon::lib::base::CStringBuilder()
{
  int t_index = i_incoming.find(MON_PROTO_TYPE_DELIMITER);
  m_type = mon::lib::base::toUInt(i_incoming.substr(0, t_index));
  append(i_incoming.substr(t_index+1, i_incoming.length()));
}

CMessage::~CMessage()
{}

const std::string &CMessage::prepared_msg()
{
  preface(MON_PROTO_TYPE_DELIMITER);
  preface(m_type);
  return msg();
}

}
}
}
