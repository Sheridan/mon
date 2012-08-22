#ifndef SENSORDEFINES_H_%sensor_name%
#define SENSORDEFINES_H_%sensor_name%

#include "definition.h"
#include "clogger.h"
#include "cfolder.h"
#include "logger-helper.h"

#define MON_ST_LOGGER logger
#define MON_ST_CONFIG config

#define MON_SENSOR_NAME %sensor_name%

#ifdef MON_DEBUG
  #define MON_SENSOR_IMPLEMENT_FUNCTION(_return_type,_function_name,_debug_text) \
     _return_type internal_%sensor_name%_##_function_name(); \
     _return_type _function_name() { MON_LOG_DBG(_debug_text); return internal_%sensor_name%_##_function_name(); } \
     _return_type internal_%sensor_name%_##_function_name()
#else
  #define MON_SENSOR_IMPLEMENT_FUNCTION(_return_type,_function_name,_debug_text) _return_type _function_name()
#endif

#define MON_SENSOR_PREPARE \
  mon::lib::logger::CLogger * logger = NULL; \
  mon::lib::config::CFolder * config = NULL; \
  const char * sensor_name = { "%sensor_name%\0" }; \
  MON_SENSOR_IMPLEMENT_FUNCTION(const char *,getName, "Request %sensor_name% sensor name" ) { return sensor_name; }

#define MON_SENSOR_BEGIN \
  MON_SENSOR_PREPARE \
  void init_sensor(mon::lib::logger::CLogger * l, mon::lib::config::CFolder * c) \
                                     { logger = l; config = c; MON_LOG_DBG("%sensor_name% sensor initialization"     ); } \
  MON_SENSOR_IMPLEMENT_FUNCTION(const unsigned char *,getDefinition      , "Request %sensor_name% definition"        ) { return definition       ; } \
  MON_SENSOR_IMPLEMENT_FUNCTION(const unsigned int   ,getDefinitionLength, "Request %sensor_name% definition length" ) { return definition_length; }

#define MON_SENSOR_IMPLEMENT_STATISTICS_FUNCTION  MON_SENSOR_IMPLEMENT_FUNCTION(const char *, getStatistics , "Request %sensor_name% statistics"  )
#define MON_SENSOR_IMPLEMENT_INFORMATION_FUNCTION MON_SENSOR_IMPLEMENT_FUNCTION(const char *, getInformation, "Request %sensor_name% information" )

#define MON_SENSOR_END int main (int argc, char* argv[]) { return 0; }

#endif // SENSORDEFINES_H_%sensor_name%
