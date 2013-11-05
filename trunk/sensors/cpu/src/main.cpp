/* %Id% */
#include "mon-sensor-cpu.h"
#include <stdio.h>
#include <stdlib.h>

#define MON_FILE_OPEN(_filename,_name) \
    FILE *_name; \
    if   ((_name=fopen(_filename, "r")) == NULL) \
         { MON_PRINT_FILEOP_ERRNO(_filename, "File open failed"); } \
    else {
#define MON_FILE_CLOSE(_filename, _name) } if(fclose(_name)) { MON_PRINT_FILEOP_ERRNO(_filename, "File close failed"); };
#define MON_FILE_FSCANF(_name,_template,...) fscanf(_name, _template, __VA_ARGS__);


MON_SENSOR_BEGIN

#include <unistd.h>

#define MON_SENSOR_STAT_FILE "/proc/stat"

unsigned int cpu_count = 0;

MON_SENSOR_INITIALIZE
{
    MON_FILE_OPEN(MON_SENSOR_STAT_FILE, file_cpu_count);
    MON_FILE_CLOSE(MON_SENSOR_STAT_FILE, file_cpu_count);
}

MON_SENSOR_IMPLEMENT_STATISTICS_FUNCTION
{
  if(MON_SENSOR_REQUESTED_OBJECT_IS_NOT_SET)
  {
    return "";
  }
  return "";
}

MON_SENSOR_IMPLEMENT_EXEMPLARS_COUNT_FUNCTION
{
  return cpu_count;
}


MON_SENSOR_IMPLEMENT_AVIALABILITY_FUNCTION
{
  bool avialable = (access(MON_SENSOR_STAT_FILE, R_OK ) != -1);
  if(!avialable)
  {
    MON_PRINT_FILEOP_ERRNO(MON_SENSOR_STAT_FILE, "Access failed");
  }
  return avialable;
}

MON_SENSOR_END
