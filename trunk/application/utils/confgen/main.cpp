/* %Id% */

#include "libraryes/config/rw/ccmdlineparcer.h"
#include "defines/st.h"
#include "defines/default-application.h"
#include "defines/signals-helper.h"
#include "libraryes/config/config.h"

#define CONFGEN_CONF_FILE  MON_DEBUG_PATH_PREFIX "/etc/confgen/confgen.conf"

void mon_exit(int returnValue)
{
  MON_ST_DESTRUCT;
  exit(returnValue);
}

MON_SIGNAL_HANDLER(SIGINT) { mon_exit(EXIT_SUCCESS); }
MON_SIGNAL_HANDLER(SIGTERM){ mon_exit(EXIT_FAILURE); }
MON_SIGNAL_HANDLER(SIGABRT){ mon_exit(EXIT_FAILURE); }

int main(int argc, char **argv)
{
  MON_HANDLE_SIGNAL(SIGINT );
  MON_HANDLE_SIGNAL(SIGTERM);
  MON_HANDLE_SIGNAL(SIGABRT);
  MON_ST_CNSTRUCT;

  MON_ST_LOGGER->setMaxLogPriority (MON_MAX_LOG_PRI);
  MON_ST_LOGGER->enableOutToFile   (false);
  MON_ST_LOGGER->enableOutToConsole(true);
  MON_ST_LOGGER->enableOutToSyslog (false);

  MON_CMD_LINE_INIT;
  MON_CMD_LINE_ADD_OPTION("c", "config", "Load config from file", CONFGEN_CONF_FILE);
  MON_CMD_LINE_PARCE;

//  MON_ST_CONFIG->load(pcmdl, argc, argv);
  MON_ST_CONFIG->load(MON_CMD_LINE_OPTION_VALUE("c").toString());


  return 0;
}
