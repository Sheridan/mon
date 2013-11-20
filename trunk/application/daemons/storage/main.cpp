/* %Id% */
#include "defines/default-application.h"
#include "defines/signals-helper.h"
#include "daemons/storage/storage_st.h"
#include "daemons/storage/cstorage.h"

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

  MON_DEFAULT_APPLICATION_INIT;

  MON_ST_APPEND_MEMBER(mon::daemons::storage::CStorage);
  MON_ST_STORAGE_MANAGER->listen();
  //MON_ST_APPEND_MEMBER(mon::daemons::node::CSensorsManager);
  //MON_ST_SENSORS_MANAGER->load();

  MON_SIGNAL_LOOP;
  mon_exit(EXIT_SUCCESS);
}
