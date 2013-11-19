/* %Id% */
#ifndef NODE_ST_H_INCLUDED
#define NODE_ST_H_INCLUDED

#define MON_MODULE_NAME "node"

#include "st.h"
#include "csensorsmanager.h"
#include "cnodecollectorsmanager.h"

#define MON_ST_NODE_COLLECTOR_SOCKET MON_ST_MEMBER(mon::daemons::node::CNodeCollectorsManager,MON_COLLECTORS_MANAGER_ST_MEMBER_ID)
#define MON_ST_SENSORS_MANAGER MON_ST_MEMBER(mon::daemons::node::CSensorsManager,MON_SENSORS_MANAGER_ST_MEMBER_ID)


#endif // NODE_ST_H_INCLUDED
