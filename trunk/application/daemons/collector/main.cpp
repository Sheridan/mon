/* %Id% */
#include "defines/signals-helper.h"
#include "defines/default-application.h"
#include "daemons/collector/collector_st.h"
#include "daemons/collector/node/cnodes.h"

void mon_exit(int returnValue)
{
  if(returnValue == EXIT_SUCCESS) { MON_ST_CONFIG->save(MON_RUN_FILE); }
  MON_ST_DESTRUCT;
  exit(returnValue);
}

MON_SIGNAL_HANDLER(SIGINT) { mon_exit(EXIT_SUCCESS); }
MON_SIGNAL_HANDLER(SIGTERM){ mon_exit(EXIT_FAILURE); }
MON_SIGNAL_HANDLER(SIGABRT){ mon_exit(EXIT_FAILURE); }

int main (int argc, char* argv[])
{
  MON_HANDLE_SIGNAL(SIGINT );
  MON_HANDLE_SIGNAL(SIGTERM);
  MON_HANDLE_SIGNAL(SIGABRT);
  MON_ST_CNSTRUCT;

  MON_CMD_LINE_INIT;
  MON_DEFAULT_APPLICATION_INIT;

  MON_ST_APPEND_MEMBER(mon::daemons::collector::CNodes);
  MON_COLLECTOR_ST_NODES_MANAGER->load();

  MON_SIGNAL_LOOP;
  mon_exit(EXIT_SUCCESS);
}
