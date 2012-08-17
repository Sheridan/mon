/* %Id% */
#ifndef CMESSAGE_H
#define CMESSAGE_H
#include "cstringbuilder.h"
#include "class-helper.h"

#define MON_PROTO_TYPE_DELIMITER '!'

namespace mon
{
namespace lib
{
namespace protocol
{


class CMessage : public mon::lib::base::CStringBuilder
{
    MON_STRING_BUILDER(CMessage)
    MON_READONLY_PROPERTY(unsigned int, type)
  public:
    CMessage(const unsigned int &i_type = 0);
    CMessage(const std::string  &i_incoming);
    ~CMessage();
    const std::string &prepared_msg();
};

}
}
}
#endif // CMESSAGE_H
