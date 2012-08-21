#ifndef MON_GLOBAL_H
#define MON_GLOBAL_H

#define MON_DEFAULT_LISTEN_PORT     4848
#define MON_DEFAULT_CONNECT_TIMEOUT 30
#define MON_DEFAULT_PASSWORD        std::string()

#ifdef MON_DEBUG
#define MON_CONF_FILE "/tmp/mon/debug." MON_MODULE_NAME ".conf"
#define MON_RUN_FILE  "/tmp/mon/debug." MON_MODULE_NAME ".run.conf"
#define MON_LOG_FILE  "/tmp/mon/debug." MON_MODULE_NAME ".log"
#else
#define MON_CONF_FILE "/etc/mon/"     MON_MODULE_NAME ".conf"
#define MON_RUN_FILE  "/var/run/mon/" MON_MODULE_NAME ".conf"
#define MON_LOG_FILE  "/var/log/mon/" MON_MODULE_NAME ".log"
#endif



#endif // MON_GLOBAL_H
