#include "cclientsocket.h"
#include "st.h"
#include "signals-helper.h"
#include <arpa/inet.h>
#include <netdb.h>
namespace mon
{
namespace lib
{
namespace network
{

CSocketClient::CSocketClient() : CSocket()
{
}

CSocketClient::CSocketClient(const int &descriptor)
{
  m_socketDescriptor = descriptor;
  m_isOpen = true;
  m_isConnected = true;
}
void CSocketClient::connect(const std::string &addr, const unsigned short &port)
{
  setPortRemote(port);
  setAddrRemote(addr);
  connect();
}

#define MON_TO_STRING(_str,_tmpl,_data) \
{ \
  char *s = NULL; \
  int l = snprintf(s, 0, _tmpl, _data); \
  if(l > 0) \
  { \
    s = static_cast<char *>(malloc(sizeof(char) * l)); \
    snprintf(s, l + 1, "%d", _data); \
  } \
  _str = s; \
  free (s); \
}
//MON_LOG_DBG("Data: " << _data << "; Result string: " << _str);

void CSocketClient::connect()
{
  MON_LOG_DBG("Connecting to " << addrRemote() << ":" << portRemote());
  addrinfo hints, *result, *rp;
//  size_t len;
//  char buf[1024];

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
  hints.ai_flags = 0;
  hints.ai_protocol = 0;          /* Any protocol */


  std::string strPort = "";
  MON_TO_STRING(strPort,"%d",portRemote());

  int gai_err = getaddrinfo(addrRemote().c_str(), strPort.c_str(), &hints, &result);
  if (gai_err != 0)
  {
    MON_LOG_ERR("Error get address info for " << addrRemote() << ":" << portRemote() << " - " << gai_strerror(gai_err));
    MON_ABORT;
  }

  /* getaddrinfo() returns a list of address structures.
              Try each address until we successfully connect(2).
              If socket(2) (or connect(2)) fails, we (close the socket
              and) try the next address. */

  for (rp = result; rp != NULL; rp = rp->ai_next)
  {
    m_socketDescriptor = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (m_socketDescriptor == -1) { continue; }
    if (::connect(m_socketDescriptor, rp->ai_addr, rp->ai_addrlen) != -1) { break; } /* Success */
    ::close(m_socketDescriptor);
  }

  if (rp == NULL) /* No address succeeded */
  {
    fprintf(stderr, "Could not connect\n");
    exit(EXIT_FAILURE);
  }

  freeaddrinfo(result);           /* No longer needed */


  //---------------------------------------------------------------------------------------------------
//  struct sockaddr_in stSockAddr;
//
//  m_socketDescriptor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//  if(m_socketDescriptor == -1)
//  {
//    MON_PRINT_ERRNO("Can not create a socket");
//    MON_ABORT;
//  }
//  m_isOpen = true;
//
//  memset(&stSockAddr, 0, sizeof(stSockAddr));
//  stSockAddr.sin_family = PF_INET;
//  stSockAddr.sin_port = htons(portLocal());
//  int i32Res = inet_pton(PF_INET, addrRemote().c_str(), &stSockAddr.sin_addr);
//  if(i32Res < 0)
//  {
//    MON_PRINT_ERRNO(addrLocal() << " - uncorrect address category");
//    close();
//    MON_ABORT;
//  }
//  else if(i32Res == 0)
//  {
//    MON_PRINT_ERRNO(addrLocal() << " - uncorrect IP address");
//    close();
//    MON_ABORT;
//  }
//
//  if(::connect(m_socketDescriptor, (const sockaddr *)&stSockAddr, sizeof(stSockAddr)) < 0)
//  {
//    MON_PRINT_ERRNO("Connection error");
//    close();
//  }
  m_isOpen = true;
  m_isConnected = true;
}

}
}
}
