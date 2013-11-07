/* %Id% */
#ifndef CMESSAGE_H
#define CMESSAGE_H
#include "cstringbuilder.h"
#include "class-helper.h"
#include "csocket.h"

namespace mon
{
namespace lib
{
namespace protocol
{

//! Обработчик сетевых сообщений
class CNetworkMessage : public mon::lib::base::CStringBuilder
{
    MON_STRING_BUILDER(CNetworkMessage)
    MON_READONLY_PROPERTY(unsigned int, type)
    MON_READONLY_PROPERTY(unsigned long long, id)

  public:
    //! Конструктор нового сообщения, предназначен для дальнейшей сборки самого сообщения
    CNetworkMessage(const unsigned long long & id, mon::lib::network::CSocket * socket, const unsigned int &i_type);
    //! Конструктор нового сообщения, сразу вместе с текстом сообщения. Можно сразу отправлять
    CNetworkMessage(const unsigned long long & id, mon::lib::network::CSocket * socket, const unsigned int &i_type, const std::string  &i_text);
    //! Конструктор нового сообщения. Это уже для пришедших сообщений. Сразу парсит
    CNetworkMessage(mon::lib::network::CSocket * socket, const std::string  &i_incoming);
    ~CNetworkMessage();
    void send(); //!< Отправляет сообщение и удаляет себя (!!!)

  private:
    mon::lib::network::CSocket *m_socket; //!< "Родительский" сокет, из которого вывалилось данное сообщение
};

}
}
}
#endif // CMESSAGE_H
