/* %Id% */

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

int main(int argc, char *argv[])
{
  MON_HANDLE_SIGNAL(SIGINT );
  MON_HANDLE_SIGNAL(SIGTERM);
  MON_HANDLE_SIGNAL(SIGABRT);
  MON_ST_CNSTRUCT;

  MON_ST_CONFIG->load(argc, argv);
  MON_ST_CONFIG->load(CONFGEN_CONF_FILE);
  MON_ST_LOGGER->setMaxLogPriority (MON_MAX_LOG_PRI);
  MON_ST_LOGGER->enableOutToFile   (false);
  MON_ST_LOGGER->enableOutToConsole(true);
  MON_ST_LOGGER->enableOutToSyslog (false);

  return 0;
}
