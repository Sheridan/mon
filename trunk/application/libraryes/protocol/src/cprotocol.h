#ifndef CPROTOCOL_H
#define CPROTOCOL_H
#include "csocket.h"
#include "cmessage.h"

#define MON_PROTO_CONNECT_ID                 1
#define MON_PROTO_CONNECT_REQUESTED_ID       2
#define MON_PROTO_CONNECT_SEND_ANSWER_ID     3
#define MON_PROTO_CONNECT_ANSWER_RECEIVED_ID 4

namespace mon
{
namespace lib
{
namespace protocol
{

class CProtocol
{
  public:
    CProtocol(mon::lib::network::CSocket *socket);
   ~CProtocol();

    // connect
    void connect                 (const std::string &password);
    void connectionRequested     (const std::string &password);
    void connectionSendAnswer    (const bool &answer);
    void connectionAnswerReceived(const bool &answer);

    void incommingMessage(const std::string &i_incoming);

  private:
    mon::lib::network::CSocket *m_socket;
};

}
}
}
#endif // CPROTOCOL_H
