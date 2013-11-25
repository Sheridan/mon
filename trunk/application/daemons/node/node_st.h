/* %Id% */
#ifndef NODE_ST_H_INCLUDED
#define NODE_ST_H_INCLUDED

#define MON_MODULE_NAME "node"

#include "defines/st.h"
#include "daemons/node/sensor/csensorsmanager.h"
#include "daemons/node/collector/ccollectors.h"

#define MON_ST_NODE_COLLECTOR_SOCKET MON_ST_MEMBER(mon::daemons::node::CCollectors,MON_COLLECTORS_MANAGER_ST_MEMBER_ID)
#define MON_ST_SENSORS_MANAGER MON_ST_MEMBER(mon::daemons::node::CSensors,MON_SENSORS_MANAGER_ST_MEMBER_ID)


#endif // NODE_ST_H_INCLUDED
