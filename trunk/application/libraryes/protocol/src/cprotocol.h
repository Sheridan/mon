/* %Id% */
#ifndef CPROTOCOL_H
#define CPROTOCOL_H
#include "csocket.h"
#include "cmessage.h"

#define MON_PROTO_ID_COLLECTOR_TO_NODE_CONNECT  1
#define MON_PROTO_ID_CONNECT_ANSWER             2

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
   virtual ~CProtocol();

    // initialize messaging


    void incommingMessage(const std::string &i_incoming);

  protected:
    void sendMessage(const unsigned int &i_type, const std::string &i_text);

  private:
    mon::lib::network::CSocket *m_socket;
};

}
}
}
#endif // CPROTOCOL_H
