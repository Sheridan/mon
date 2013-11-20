/* %Id% */
#ifndef CMESSAGE_H
#define CMESSAGE_H
#include "libraryes/base/string/cstringbuilder.h"
#include "defines/class-helper.h"
#include "defines/protocol-control.h"
#include "libraryes/network/csocket.h"

namespace mon
{
namespace lib
{
namespace protocol
{

class CProtocol;

//! Форматтер сетевого сообщения
class CNetworkMessage : public mon::lib::base::CStringBuilderBase
{
    MON_STRING_BUILDER(CNetworkMessage)
    MON_READONLY_PROPERTY(EProtocolMessageType, type)
    MON_READONLY_PROPERTY(MON_PROTOCOL_MESSAGE_ID_TYPE, id)

  friend class CProtocol;
  public:
    //! Конструктор нового сообщения, предназначен для дальнейшей сборки самого сообщения
    CNetworkMessage(const MON_PROTOCOL_MESSAGE_ID_TYPE &id, const EProtocolMessageType &i_type);
    //! Конструктор нового сообщения, сразу вместе с текстом сообщения. Можно сразу отправлять
    CNetworkMessage(const MON_PROTOCOL_MESSAGE_ID_TYPE &id, const EProtocolMessageType &i_type, const std::string  &i_text);
    //! Конструктор нового сообщения. Это уже для пришедших сообщений. Сразу парсит
    CNetworkMessage(const std::string  &i_incoming);
    virtual ~CNetworkMessage();

  protected:
    const std::string &preparedText();
};


}
}
}
#endif // CMESSAGE_H
