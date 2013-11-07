/* %Id% */
#ifndef CMESSAGE_H
#define CMESSAGE_H
#include "cstringbuilder.h"
#include "class-helper.h"

namespace mon
{
namespace lib
{
namespace protocol
{


class CNetworkMessage : public mon::lib::base::CStringBuilder
{
    MON_STRING_BUILDER(CNetworkMessage)
    MON_READONLY_PROPERTY(unsigned int, type)
  public:
    CNetworkMessage(const unsigned int &i_type);
    CNetworkMessage(const unsigned int &i_type, const std::string  &i_text);
    CNetworkMessage(const std::string  &i_incoming);
    ~CNetworkMessage();
    const std::string &prepared_msg();
};

}
}
}
#endif // CMESSAGE_H
