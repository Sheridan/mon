#ifndef qwerwqefsfgdsbd
#define qwerwqefsfgdsbd

#ifdef MON_DEBUG
#define MON_CONF_FILE "/tmp/mon/conf." MON_MODULE_NAME ".conf"
#define MON_RUN_FILE  "/tmp/mon/run."  MON_MODULE_NAME ".conf"
#define MON_LOG_FILE  "/tmp/mon/log."  MON_MODULE_NAME ".log"
#else
#define MON_CONF_FILE "/etc/mon/"     MON_MODULE_NAME ".conf"
#define MON_RUN_FILE  "/var/run/mon/" MON_MODULE_NAME ".conf"
#define MON_LOG_FILE  "/var/log/mon/" MON_MODULE_NAME ".log"
#endif

#ifdef MON_DEBUG
  #define MON_MAX_LOG_PRI mon::lib::logger::pDebug
#else
  #define MON_MAX_LOG_PRI mon::lib::logger::pInfo
#endif
#define MON_DEFAULT_APPLICATION_INIT int dd=0; MON_LOG_DBG(dd++); \
  MON_ST_CONFIG->load(MON_CONF_FILE); MON_LOG_DBG(dd++); \
  MON_CFOLDER *init_fldr = MON_ST_CONFIG->folder(MON_MODULE_NAME); MON_LOG_DBG(dd++); \
  init_fldr->folder("a")->folder("b")->file("f_1")->set(init_fldr->name()); \
  MON_ST_CONFIG->cd(init_fldr); MON_LOG_DBG(dd++); \
  init_fldr = MON_ST_CONFIG->folder("logger"); MON_LOG_DBG(dd++); \
  init_fldr->folder("a")->folder("b")->file("f_1")->set(init_fldr->name()); \
  MON_ST_LOGGER->setMaxLogPriority (static_cast<mon::lib::logger::EPriority>(init_fldr->file("max_priority")->get(static_cast<int>(MON_MAX_LOG_PRI)))); MON_LOG_DBG(dd++); \
  MON_ST_LOGGER->setLogFilename    (init_fldr->file("filename")->get(std::string(MON_LOG_FILE))); MON_LOG_DBG(dd++); \
  init_fldr = init_fldr->folder("destination"); MON_LOG_DBG(dd++); \
  init_fldr->folder("a")->folder("b")->file("f_1")->set(init_fldr->name()); \
  MON_ST_LOGGER->enableOutToFile   (init_fldr->file("file")   ->get(true)); MON_LOG_DBG(dd++); \
  MON_ST_LOGGER->enableOutToConsole(init_fldr->file("console")->get(true)); MON_LOG_DBG(dd++); \
  MON_ST_LOGGER->enableOutToSyslog (init_fldr->file("syslog") ->get(true)); MON_LOG_DBG(dd++);  MON_LOG_DBG("---");

//

#endif // qwerwqefsfgdsbd
