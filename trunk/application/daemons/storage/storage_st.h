/* %Id% */
#ifndef STORAGE_ST_H_INCLUDED
#define STORAGE_ST_H_INCLUDED

#define MON_MODULE_NAME "storage"

#include "st.h"
#include "cstorage.h"

//#define MON_ST_NODE_COLLECTOR_SOCKET MON_ST_MEMBER(mon::daemons::node::CCollectorsManager,MON_COLLECTORS_MANAGER_ST_MEMBER_ID)
#define MON_ST_STORAGE_MANAGER MON_ST_MEMBER(mon::daemons::storage::CStorage,MON_STORAGE_MANAGER_ST_MEMBER_ID)


#endif // STORAGE_ST_H_INCLUDED
