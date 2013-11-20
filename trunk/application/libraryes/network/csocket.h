/* %Id% */
#ifndef CSOCKET_H
#define CSOCKET_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include "defines/threads-helper.h"
#include "defines/mutex-helper.h"

namespace mon
{
namespace lib
{
namespace network
{

//! Базовый сокет
class CSocket
{
    MON_THREADED_FUNCTION_DECLARE(waitRecv)
    MON_MUTEX_DECLARE(write)
  public:
    CSocket();
    virtual ~CSocket();
    void write(const std::string &data);

    void close();

    void setPortLocal (const unsigned short &port);
    void setPortRemote(const unsigned short &port);
    void setAddrLocal (const std::string    &addr);
    void setAddrRemote(const std::string    &addr);
    void setTimeout   (const int            &val );
    const unsigned short & portLocal () const;
    const unsigned short & portRemote() const;
    const std::string    & addrLocal () const;
    const std::string    & addrRemote() const;
    const int            & descriptor() const;
    const int            & timeout   () const;
    const bool &isConnected() const;
    const bool &isListen   () const;

  protected:
    int  m_socketDescriptor;
    int  m_timeout;
    bool m_isListen;
    bool m_isConnected;

    virtual void incommingMessage(const std::string &message) = 0;

  private:
    unsigned short m_portLocal;
    unsigned short m_portRemote;
    std::string    m_addrLocal;
    std::string    m_addrRemote;
};

}
}
}
#endif // CSOCKET_H
