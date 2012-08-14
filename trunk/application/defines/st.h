#ifndef MON_ST_H
#define MON_ST_H
#include "csingleton.h"
#include <errno.h>
#include <string.h>
// main
#define MON_ST        mon::lib::base::CSingleton::instance()
#define MON_ST_LOGGER MON_ST->logger()
#define MON_ST_CONFIG MON_ST->config()

// creating and destroy
#define MON_ST_CNSTRUCT MON_ST; MON_LOG_DBG("App started");
#define MON_ST_DESTRUCT MON_LOG_DBG("App destroying"); mon::lib::base::CSingleton::destroy();

// logger --------------------------------------------------------------------------------------------------------
//#ifdef MON_MODULE_NAME
//  #define MON_LOG_PREFIX << "Module " MON_MODULE_NAME ". "
//#else
//  #define MON_LOG_PREFIX
//#endif
#define MON_LOG_PREFIX
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

// config --------------------------------------------------------------------------------------------------------
#define MON_CFOLDER mon::lib::config::CFolder
#define MON_CFILE mon::lib::config::CFile
#define MON_OPTION_FOREACH_OPTION(_name,_list,_type) \
   mon::lib::config::_type h_list_##_name = _list; \
   for(mon::lib::config::_type::iterator _name = h_list_##_name.begin(); \
    _name != h_list_##_name.end(); \
    ++_name)
#define MON_OPTION_FOREACH_FOLDER(_name,_folder) MON_OPTION_FOREACH_OPTION(_name, _folder->folders(), TFoldersList)
#define MON_OPTION_FOREACH_FILE(_name,_folder)   MON_OPTION_FOREACH_OPTION(_name, _folder->files()  , TFilesList)


// singleton members id ---------------------------------------------------------------------------------------------
#define MON_NODE_SOCKET_SERVER_ST_MEMBER_ID   1
#define MON_SERVER_NODES_MANAGER_ST_MEMBER_ID 2

#define MON_ST_APPEND_MEMBER(_type) MON_ST->appendMember(new _type())
#define MON_ST_MEMBER(_type,_id) (static_cast<_type *>(MON_ST->member(_id)))

#endif // MON_ST_H
