/* %Id% */
#include "mon-sensor-cpu.h"

MON_SENSOR_BEGIN

#include <unistd.h>
#include <map>


#define MON_SENSOR_STAT_FILE "/proc/stat"
#define MON_FILE_FSCANF_ALL_CPUSTAT_START(_name,_struct) \
  char cpu_##_name[32]; \
  MON_FILE_OPEN(MON_SENSOR_STAT_FILE, _name); \
  MON_FILE_FSCANF_ALL(_name, "%s %d %d %d %d %d %d %d %d %d %d", \
                      cpu_##_name, \
                      &_struct.user, &_struct.nice,    &_struct.system, &_struct.idle,  &_struct.iowait, \
                      &_struct.irq,  &_struct.softirq, &_struct.steal,  &_struct.guest, &_struct.guest_nice) \
{ if(!(strstr(cpu_##_name, "cpu"))) { break; } if(strlen(cpu_##_name) > 3) {
#define MON_FILE_FSCANF_ALL_CPUSTAT_STOP(_name,_struct) _struct.cpu_number++; } } MON_FILE_CLOSE(MON_SENSOR_STAT_FILE, _name);

#define MON_SENSOR_INFO_FILE "/proc/cpuinfo"
#define MON_FILE_FSCANF_ALL_CPUINFO_START(_name,_struct) \
  char * cpuinfo_##_name = nullptr; \
  MON_FILE_OPEN(MON_SENSOR_INFO_FILE, _name); \
  MON_FILE_FSCANF_ALL(_name, "%s %d %d %d %d %d %d %d %d %d %d", \
                      cpu_##_name, \
                      &_struct.user, &_struct.nice,    &_struct.system, &_struct.idle,  &_struct.iowait, \
                      &_struct.irq,  &_struct.softirq, &_struct.steal,  &_struct.guest, &_struct.guest_nice) \
{ if(!(cpu_##_name && strstr(cpu_##_name, "cpu"))) { break; } if(strlen(cpu_##_name) > 3) {
#define MON_FILE_FSCANF_ALL_CPUINFO_STOP(_name,_struct) _struct.cpu_number++; } } MON_FILE_CLOSE(MON_SENSOR_INFO_FILE, _name);

/*! Struct for store cpu statistics */
struct SCPUStat
{
  int user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice, cpu_number;
  SCPUStat() { user = nice = system = idle = iowait =
               irq = softirq = steal = guest = guest_nice = cpu_number = 0; }
};
typedef std::map<int, SCPUStat> TCPUsStat;
TCPUsStat prevstat;

/*! Struct for store cpu information */
struct SCPUInfo
{
  char vendor[64], modelName[128];
  int family, model, stepping;
  int cpu_number;
  SCPUInfo() { memset(vendor, '\0', 64); memset(modelName, '\0', 128);
               family = model = stepping = cpu_number = 0; }
};

unsigned int cpu_count = 1;

MON_SENSOR_INITIALIZE
{
  SCPUStat stat;
  MON_FILE_FSCANF_ALL_CPUSTAT_START(file_cpu_count, stat)
      cpu_count++;
      prevstat[stat.cpu_number] = stat;
  MON_FILE_FSCANF_ALL_CPUSTAT_STOP(file_cpu_count, stat)
}

MON_SENSOR_IMPLEMENT_EXEMPLARS_COUNT_FUNCTION
{
  return cpu_count;
}

MON_SENSOR_IMPLEMENT_STATISTICS_FUNCTION
{
  if(MON_SENSOR_REQUESTED_FRAME_IS_NOT_SET)
  {
    return nullptr;
  }
  if(MON_SENSOR_REQUESTED_FRAME_IS(utilisation))
  {
    SCPUStat stat, delta;
    float totalDelta = 0;
    float onePercent = 0;
    MON_SENSOR_DATA_DECLARE(cpuframeset);
    MON_FILE_FSCANF_ALL_CPUSTAT_START(read_stat, stat)
        delta.user       = stat.user       - prevstat[stat.cpu_number].user;
        delta.nice       = stat.nice       - prevstat[stat.cpu_number].nice;
        delta.system     = stat.system     - prevstat[stat.cpu_number].system;
        delta.idle       = stat.idle       - prevstat[stat.cpu_number].idle;
        delta.iowait     = stat.iowait     - prevstat[stat.cpu_number].iowait;
        delta.irq        = stat.irq        - prevstat[stat.cpu_number].irq;
        delta.softirq    = stat.softirq    - prevstat[stat.cpu_number].softirq;
        delta.steal      = stat.steal      - prevstat[stat.cpu_number].steal;
        delta.guest      = stat.guest      - prevstat[stat.cpu_number].guest;
        delta.guest_nice = stat.guest_nice - prevstat[stat.cpu_number].guest_nice;
        totalDelta = delta.user + delta.nice    + delta.system + delta.idle  + delta.iowait    +
                     delta.irq  + delta.softirq + delta.steal  + delta.guest + delta.guest_nice;
        onePercent = totalDelta / 100;
        cpuframeset.newFrame(stat.cpu_number)
              << ((float)delta.user      *onePercent)
              << ((float)delta.nice      *onePercent)
              << ((float)delta.system    *onePercent)
              << ((float)delta.idle      *onePercent)
              << ((float)delta.iowait    *onePercent)
              << ((float)delta.irq       *onePercent)
              << ((float)delta.softirq   *onePercent)
              << ((float)delta.steal     *onePercent)
              << ((float)delta.guest     *onePercent)
              << ((float)delta.guest_nice*onePercent);
        prevstat[stat.cpu_number] = stat;
    MON_FILE_FSCANF_ALL_CPUSTAT_STOP(read_stat, stat)
    return cpuframeset.string().c_str();
  }
  if(MON_SENSOR_REQUESTED_FRAME_IS(info))
  {
    return MON_SENSORS_EMPTY_RESULT;
  }
  return MON_SENSORS_EMPTY_RESULT;
}

MON_SENSOR_IMPLEMENT_AVIALABILITY_FUNCTION
{
  if(MON_SENSOR_REQUESTED_FRAME_IS_NOT_SET)
  {
    return MON_SENSOR_CALL_AVIALABILITY_FUNCTION(utilisation) &&
           MON_SENSOR_CALL_AVIALABILITY_FUNCTION(info);
  }
  if(MON_SENSOR_REQUESTED_FRAME_IS(utilisation))
  {
    if(access(MON_SENSOR_STAT_FILE, R_OK ) != -1) return true;
    MON_PRINT_FILEOP_ERRNO(MON_SENSOR_STAT_FILE, "Access failed");
    return false;
  }
  if(MON_SENSOR_REQUESTED_FRAME_IS(info))
  {
    if(access(MON_SENSOR_INFO_FILE, R_OK ) != -1) return true;
    MON_PRINT_FILEOP_ERRNO(MON_SENSOR_INFO_FILE, "Access failed");
    return false;
  }
  return false;
}

MON_SENSOR_END

/* MON_LOG_DBG("fscanf: " <<
             "cpu"           << stat.cpu_number << " -> " <<
             "  user:"       << stat.user       <<
             ", nice:"       << stat.nice       <<
             ", system:"     << stat.system     <<
             ", idle:"       << stat.idle       <<
             ", iowait:"     << stat.iowait     <<
             ", irq:"        << stat.irq        <<
             ", softirq:"    << stat.softirq    <<
             ", steal:"      << stat.steal      <<
             ", guest:"      << stat.guest      <<
             ", guest_nice:" << stat.guest_nice);*/
