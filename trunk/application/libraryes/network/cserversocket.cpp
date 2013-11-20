/* %Id% */
#include <arpa/inet.h>
#include "defines/st.h"
#include "defines/signals-helper.h"
#include "defines/infinity-cycle-helper.h"
#include "libraryes/network/cserversocket.h"

namespace mon
{
namespace lib
{
namespace network
{

CSocketServer::CSocketServer() : CSocket()
{
  MON_THREADED_FUNCTION_INIT(listen);
}

CSocketServer::~CSocketServer()
{
    close();
}

MON_THREADED_FUNCTION_IMPLEMENT(CSocketServer, listen)
{
  MON_LOG_NFO("Server listening... ");
  m_socketDescriptor = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(m_socketDescriptor < 0)
  {
    MON_PRINT_ERRNO("Cannot create socket");
    MON_ABORT;
  }

  sockaddr_in stSockAddr;
  memset(&stSockAddr, 0, sizeof(stSockAddr));
  stSockAddr.sin_family      = PF_INET;
  stSockAddr.sin_port        = htons(portLocal());
  stSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(::bind(m_socketDescriptor, (struct sockaddr *)(&stSockAddr), sizeof(stSockAddr)) < 0)
  {
    MON_PRINT_ERRNO("Socket bind error");
    MON_ABORT;
  }

  if(::listen(m_socketDescriptor, 10) == -1)
  {
    MON_PRINT_ERRNO("Socket listen error");
    close();
    MON_ABORT;
  }

  MON_LOG_NFO("Server listen on " << stSockAddr.sin_addr.s_addr << ":" << portLocal());

  m_isListen = true;

//  waitRecv();

  MON_INFINITY_LOOP_BEGIN(wait_for_connect);
    MON_THREADED_ABORT_IF_NEED(listen);
    sockaddr_in clientAddr;
    socklen_t addr_length = sizeof(clientAddr);
    memset(&clientAddr, 0, addr_length);
    int clientDescriptor = ::accept(m_socketDescriptor, (sockaddr *)&clientAddr, &addr_length);
    if(clientDescriptor < 0)
    {
      MON_PRINT_ERRNO("Incoming connection error");
      ::close(clientDescriptor);
    }
    else
    {
      MON_THREADED_FUNCTION_DISABLE_CANCEL
      MON_LOG_NFO("Incoming connection...");
      CSocketClient * client = incommingConnection(clientDescriptor, inet_ntoa(clientAddr.sin_addr), clientAddr.sin_port);
      MON_LOG_NFO("Incoming connection accepted from " << client->addrRemote() << ":" << client->portRemote());
      m_clients[clientDescriptor] = client;
      MON_THREADED_FUNCTION_ENABLE_CANCEL
    }
  MON_INFINITY_LOOP_END(wait_for_connect);
}

void CSocketServer::listen(const unsigned short &port)
{
  setPortLocal(port);
  listen();
}

void CSocketServer::close()
{
    MON_THREADED_FUNCTION_ABORT(listen);
    CSocket::close();
}

}
}
}
