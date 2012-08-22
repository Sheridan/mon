/* %Id% */
#ifndef NODE_ST_H_INCLUDED
#define NODE_ST_H_INCLUDED

#define MON_MODULE_NAME "node"

#include "st.h"

#define MON_ST_NODE_COLLECTOR_SOCKET MON_ST_MEMBER(mon::daemons::node::CCollectorsManager,MON_COLLECTORS_MANAGER_ST_MEMBER_ID)
#define MON_ST_SENSORS_MANAGER MON_ST_MEMBER(mon::daemons::node::CSensorsManager,MON_SENSORS_MANAGER_ST_MEMBER_ID)


#endif // NODE_ST_H_INCLUDED
