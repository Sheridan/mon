#include "cserversocket.h"
#include "signals-helper.h"
#include "st.h"


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
  MON_THREADED_FUNCTION_ABORT(listen);
}

MON_THREADED_FUNCTION_IMPLEMENT(CSocketServer, listen)
{
  sockaddr_in stSockAddr;
  m_socketDescriptor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(m_socketDescriptor == -1)
  {
    MON_PRINT_ERRNO("Cannot create socket");
    MON_ABORT;
  }

  memset(&stSockAddr, 0, sizeof(stSockAddr));
  stSockAddr.sin_family      = PF_INET;
  stSockAddr.sin_port        = htons(portLocal());
  stSockAddr.sin_addr.s_addr = INADDR_ANY;

  m_isOpen = true;

  if(bind(m_socketDescriptor, (const sockaddr *)(&stSockAddr), sizeof(stSockAddr)) == -1)
  {
    MON_PRINT_ERRNO("Socket bind error");
    close();
    MON_ABORT;
  }

  if(::listen(m_socketDescriptor, 10) == -1)
  {
    MON_PRINT_ERRNO("Socket listen error");
    close();
    MON_ABORT;
  }

  MON_LOG_NFO("Node listen on " << stSockAddr.sin_addr.s_addr << ":" << portLocal());

  for(;;)
  {
    sockaddr clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    int clientDescriptor = accept(m_socketDescriptor, &clientAddr, NULL);

    if(clientDescriptor < 0)
    {
      MON_PRINT_ERRNO("Incoming connection error");
      ::close(clientDescriptor);
    }
    else
    {
      MON_LOG_DBG("Incoming connection.");
      CSocketClient *client = new CSocketClient(clientDescriptor);
      if(checkConnection(client))
      {
        m_clients[client->descriptor()] = client;
      }
      else
      {
        MON_LOG_WRN("Incoming connection check failed");
        delete client;
      }
    }
  }
}

void CSocketServer::listen(const unsigned short &port)
{
  setPortLocal(port);
  listen();
}


}
}
}
