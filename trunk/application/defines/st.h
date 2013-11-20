/* %Id% */
#ifndef MON_ST_H
#define MON_ST_H
#include "defines/global.h"
#include "libraryes/base/singleton/csingleton.h"
#include "generated.h"
#include <errno.h>
#include <string.h>
// main

#define MON_ST          mon::lib::base::CSingleton::instance()
#ifndef MON_ST_LOGGER
  #define MON_ST_LOGGER MON_ST->logger()
#endif
#ifndef MON_ST_CONFIG
  #define MON_ST_CONFIG MON_ST->config()
#endif

// creating and destroy
#define MON_ST_CNSTRUCT MON_ST; MON_LOG_DBG("App started");
#define MON_ST_DESTRUCT MON_LOG_DBG("App destroying"); mon::lib::base::CSingleton::destroy();

// logger --------------------------------------------------------------------------------------------------------
#include "logger-helper.h"

// config --------------------------------------------------------------------------------------------------------
#define MON_CFOLDER mon::lib::config::CFolder
#define MON_CFILE mon::lib::config::CFile
#define MON_OPTION_FOREACH_OPTION(_name,_list,_type) \
  mon::lib::config::_type list##_name = _list; \
  for (auto &_name : list##_name)
#define MON_OPTION_FOREACH_FOLDER(_name,_folder) MON_OPTION_FOREACH_OPTION(_name, _folder->folders(), TFoldersList)
#define MON_OPTION_FOREACH_FILE(_name,_folder)   MON_OPTION_FOREACH_OPTION(_name, _folder->files()  , TFilesList)


// singleton members id ---------------------------------------------------------------------------------------------
#define MON_COLLECTORS_MANAGER_ST_MEMBER_ID   1
#define MON_NODES_MANAGER_ST_MEMBER_ID        2
#define MON_SENSORS_MANAGER_ST_MEMBER_ID      3
#define MON_STORAGE_MANAGER_ST_MEMBER_ID      4

#define MON_ST_APPEND_MEMBER(_type) MON_ST->appendMember(new _type())
#define MON_ST_MEMBER(_type,_id) (static_cast<_type *>(MON_ST->member(_id)))

#endif // MON_ST_H
