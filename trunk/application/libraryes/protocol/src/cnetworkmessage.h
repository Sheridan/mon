/* %Id% */
#ifndef CMESSAGE_H
#define CMESSAGE_H
#include "cstringbuilder.h"
#include "class-helper.h"
#include "protocol-control.h"
#include "csocket.h"

namespace mon
{
namespace lib
{
namespace protocol
{

class CProtocol;

//! Обработчик сетевых сообщений
class CNetworkMessage : public mon::lib::base::CStringBuilder
{
    MON_STRING_BUILDER(CNetworkMessage)
    MON_READONLY_PROPERTY(EProtocolMessageType, type)
    MON_READONLY_PROPERTY(TProtocolMessageID, id)

  friend class CProtocol;
  public:
    //! Конструктор нового сообщения, предназначен для дальнейшей сборки самого сообщения
    CNetworkMessage(const TProtocolMessageID &id, const EProtocolMessageType &i_type);
    //! Конструктор нового сообщения, сразу вместе с текстом сообщения. Можно сразу отправлять
    CNetworkMessage(const TProtocolMessageID &id, const EProtocolMessageType &i_type, const std::string  &i_text);
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
