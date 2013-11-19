/* %Id% */
#ifndef MON_GLOBAL_H
#define MON_GLOBAL_H

//! Сетевой порт сборщика по умолчанию
#define MON_DEFAULT_COLLECTOR_LISTEN_PORT     ((unsigned short)4848)
//! Сетевой порт хранилища по умолчанию
#define MON_DEFAULT_STORAGE_LISTEN_PORT       ((unsigned short)4949)
//! Таймаут неудачного соединения по умолчанию
#define MON_DEFAULT_CONNECT_TIMEOUT           ((unsigned short)30)
//! Таймаут запроса данных из удаленной ноды умолчанию (интервал, сек)
#define MON_DEFAULT_REMOTE_NODE_DATA_REQUEST_TIMEOUT ((float)10)
//! Пароль по умолчанию
#define MON_DEFAULT_PASSWORD        std::string("password")

#ifdef MON_DEBUG
  #define MON_DEBUG_PATH_PREFIX "/tmp/mon/root"
#else
  #define MON_DEBUG_PATH_PREFIX
#endif

#define MON_CONF_FILE MON_DEBUG_PATH_PREFIX "/etc/mon/"     MON_MODULE_NAME ".conf"
#define MON_RUN_FILE  MON_DEBUG_PATH_PREFIX "/var/lib/mon/" MON_MODULE_NAME ".conf"
#define MON_LOG_FILE  MON_DEBUG_PATH_PREFIX "/var/log/mon/" MON_MODULE_NAME ".log"



#endif // MON_GLOBAL_H
