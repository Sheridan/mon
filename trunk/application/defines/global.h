/* %Id% */
#ifndef MON_GLOBAL_H
#define MON_GLOBAL_H

//! Сетевой порт по умолчанию
#define MON_DEFAULT_LISTEN_PORT     4848
//! Таймаут неудачного соединения по умолчанию
#define MON_DEFAULT_CONNECT_TIMEOUT 30
//! Пароль по умолчанию
#define MON_DEFAULT_PASSWORD        std::string()

#ifdef MON_DEBUG
  #define MON_DEBUG_PATH_PREFIX "/tmp/mon/root"
#else
  #define MON_DEBUG_PATH_PREFIX
#endif

#define MON_CONF_FILE MON_DEBUG_PATH_PREFIX "/etc/mon/"     MON_MODULE_NAME ".conf"
#define MON_RUN_FILE  MON_DEBUG_PATH_PREFIX "/var/lib/mon/" MON_MODULE_NAME ".conf"
#define MON_LOG_FILE  MON_DEBUG_PATH_PREFIX "/var/log/mon/" MON_MODULE_NAME ".log"



#endif // MON_GLOBAL_H
