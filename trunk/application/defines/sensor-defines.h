/* %Id% */
#ifndef SENSORDEFINES_H_%sensor_name%
#define SENSORDEFINES_H_%sensor_name%

#include "definition.h"
#include "clogger.h"
#include "cconfig.h"
#include "logger-helper.h"
#include "file-operations-defines.h"
#include <string>
#include <iostream>
#include <sstream>

#define MON_ST_LOGGER logger
#define MON_ST_CONFIG config

#define MON_SENSOR_NAME %sensor_name%

#ifdef MON_DEBUG
  #define MON_SENSOR_IMPLEMENT_FUNCTION(_return_type,_function_name,_debug_text) \
                _return_type internal_%sensor_name%_##_function_name(const char *object); \
     extern "C" _return_type _function_name                         (const char *object) { MON_LOG_DBG(_debug_text); return internal_%sensor_name%_##_function_name(object); } \
                _return_type internal_%sensor_name%_##_function_name(const char *object)
#else
  #define MON_SENSOR_IMPLEMENT_FUNCTION(_return_type,_function_name,_debug_text) extern "C" _return_type _function_name(const char *object )
#endif

#define MON_SENSOR_BEGIN \
  mon::lib::logger::CLogger * logger ; \
  mon::lib::config::CFolder * config ; \
  const char * sensor_name = { "%sensor_name%\0" }; \
  void initialize(); \
  extern "C" void initSensor(mon::lib::logger::CLogger * l, mon::lib::config::CFolder * c) \
                                     { logger = l; config = c; MON_LOG_DBG("%sensor_name% sensor initialization"     ); initialize(); } \
  MON_SENSOR_IMPLEMENT_FUNCTION(const char *      , getName            , "Request %sensor_name% sensor name"       ) { return sensor_name      ; } \
  MON_SENSOR_IMPLEMENT_FUNCTION(const char *      , getDefinition      , "Request %sensor_name% definition"        ) { return definition       ; } \
  MON_SENSOR_IMPLEMENT_FUNCTION(const unsigned int, getDefinitionLength, "Request %sensor_name% definition length" ) { return definition_length; }

#define MON_SENSOR_END int main (int argc, char* argv[]) { return 0; }

#define MON_SENSOR_IMPLEMENT_STATISTICS_FUNCTION      MON_SENSOR_IMPLEMENT_FUNCTION(const char *      , getStatistics     , "Request %sensor_name% statistics"    )
#define MON_SENSOR_IMPLEMENT_EXEMPLARS_COUNT_FUNCTION MON_SENSOR_IMPLEMENT_FUNCTION(const unsigned int, getExemplarsCount , "Request %sensor_name% information"   )
#define MON_SENSOR_IMPLEMENT_AVIALABILITY_FUNCTION    MON_SENSOR_IMPLEMENT_FUNCTION(const bool        , getSensorAvialable, "Request %sensor_name% avialability"  )

#define MON_SENSOR_AVIALABLE_ALWAYS MON_SENSOR_IMPLEMENT_AVIALABILITY_FUNCTION {return true;}

#define MON_SENSOR_NO_STATISTICS                      MON_SENSOR_IMPLEMENT_STATISTICS_FUNCTION      { return NULL      ; }
#define MON_SENSOR_NO_INFORMATION                     MON_SENSOR_IMPLEMENT_INFORMATION_FUNCTION     { return NULL      ; }
#define MON_SENSOR_STATIC_EXEMPLARS_COUNT(_exemplars) MON_SENSOR_IMPLEMENT_EXEMPLARS_COUNT_FUNCTION { return _exemplars; }

#define MON_SENSOR_REQUESTED_OBJECT_IS(_name)  (strcmp(object,#_name) == 0)
#define MON_SENSOR_REQUESTED_OBJECT_IS_NOT_SET (object == NULL)

#define MON_SENSOR_INITIALIZE    void initialize()
#define MON_SENSOR_NO_INITIALIZE void initialize() {}

#define MON_SENSOR_DATA_DECLARE std::stringstream result; result << "%sensor_name%:" << object << "!";
#define MON_SENSOR_DATA_START_EXEMPLAR(_exemplar) result << _exemplar << "#";
#define MON_SENSOR_DATA_ADD_LAST_POINT(_point) result << _point;
#define MON_SENSOR_DATA_ADD_POINT(_point) result << _point << ":";
#define MON_SENSOR_DATA_STOP_EXEMPLAR result << "|";
#define MON_SENSOR_DATA_RETURN std::string r = result.str(); return r.substr(0, r.length()-1).c_str();

#endif // SENSORDEFINES_H_%sensor_name%
