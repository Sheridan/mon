/* %Id% */
#ifndef LOGGERHELPER_H
#define LOGGERHELPER_H

#ifdef MON_SENSOR_NAME
  #define MON_LOG_PREFIX << "Sensor " MON_SENSOR_NAME ". "
#else
  #define MON_LOG_PREFIX
#endif
//#define MON_LOG_PREFIX
#ifdef MON_DEBUG
  //#define LOG_FL_ENABLED
  #ifdef LOG_FL_ENABLED
    #define LOG_FL << "File: " << __FILE__ << "; Line: " << __LINE__ << "; "
  #else
    #define LOG_FL
  #endif
  #define MON_LOG(_message,_type) \
    MON_ST_LOGGER->log(mon::lib::logger::CLogMessage(_type) MON_LOG_PREFIX LOG_FL \
                     << "Function: " << __PRETTY_FUNCTION__ \
                     << "; Message: " << _message);
#else
  #define MON_LOG(_message,_type) MON_ST_LOGGER->log(mon::lib::logger::CLogMessage(_type) MON_LOG_PREFIX << _message);
#endif

#define MON_LOG_NFO(_message) MON_LOG(_message, mon::lib::logger::pInfo);
#define MON_LOG_ERR(_message) MON_LOG(_message, mon::lib::logger::pError);
#define MON_LOG_WRN(_message) MON_LOG(_message, mon::lib::logger::pWarning);

#ifdef MON_DEBUG
  #define MON_LOG_DBG(_message) MON_LOG(_message, mon::lib::logger::pDebug);
#else
  #define MON_LOG_DBG(_message)
#endif

#define MON_PRINT_ERRNO(_message) MON_LOG_ERR(_message << ". (" << errno << "), " << strerror(errno));
#define MON_PRINT_FILEOP_ERRNO(_filename, _operation) MON_PRINT_ERRNO(_operation " file '" << _filename << "' failed");


#endif // LOGGERHELPER_H
