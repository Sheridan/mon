/* %Id% */
#include "mon-sensor-memory.h"
#include <unistd.h>

MON_SENSOR_BEGIN

MON_SENSOR_INITIALIZE
{

}

MON_SENSOR_IMPLEMENT_STATISTICS_FUNCTION
{
  if(MON_SENSOR_REQUESTED_FRAME_IS_NOT_SET)
  {
    return "";
  }
  return "";
}

#define MON_SENSOR_STAT_FILE "/proc/meminfo"
MON_SENSOR_IMPLEMENT_AVIALABILITY_FUNCTION
{
  bool avialable = (access(MON_SENSOR_STAT_FILE, R_OK ) != -1);
  if(!avialable)
  {
    MON_PRINT_FILEOP_ERRNO(MON_SENSOR_STAT_FILE, "Access failed");
  }
  return avialable;
}

MON_SENSOR_STATIC_EXEMPLARS_COUNT(1)

MON_SENSOR_END
