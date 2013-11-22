#include "daemons/storage/cstorage.h"

namespace mon
{
namespace daemons
{
namespace storage
{


CStorage::CStorage()
  : mon::lib::model::CCollectors(),
    mon::lib::network::CSocketServer(),
    mon::lib::base::CSingletonMember(MON_STORAGE_MANAGER_ST_MEMBER_ID)
{
}

CStorage::~CStorage()
{
  close();
}

void CStorage::listen()
{
  mon::lib::network::CSocketServer::listen(MON_ST_CONFIG->folder("network")->folder("listen")->file("port")->get(MON_DEFAULT_STORAGE_LISTEN_PORT));
}

lib::network::CSocketClient *CStorage::incommingConnection(const int &clientDescriptor, const std::string &addr_from, const int &port_from)
{

}

}
}
}
