/* %Id% */
#include "mon-sensor-cpu.h"
#include <unistd.h>

MON_SENSOR_BEGIN

MON_SENSOR_INITIALIZE
{

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
  if(MON_SENSOR_REQUESTED_OBJECT_IS_NOT_SET)
  {
    return 0;
  }
  return 1;
}

#define MON_SENSOR_STAT_FILE "/proc/stat"
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
