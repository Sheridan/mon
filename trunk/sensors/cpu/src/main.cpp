/* %Id% */
#include "mon-sensor-cpu.h"

MON_SENSOR_BEGIN

#include <unistd.h>
#include <map>
#include <iostream>
#include <sstream>

#define MON_SENSOR_STAT_FILE "/proc/stat"
#define MON_FILE_FSCANF_ALL_CPU_START(_name,_struct,_template) \
  char * cpu_##_name; \
  MON_FILE_OPEN(MON_SENSOR_STAT_FILE, _name); \
  MON_FILE_FSCANF_ALL(_name, "%s "_template" "_template" "_template" "_template" "_template" "_template" "_template" "_template" "_template" "_template, \
                      cpu_##_name, \
                      &_struct.user, &_struct.nice,    &_struct.system, &_struct.idle,  &_struct.iowait, \
                      &_struct.irq,  &_struct.softirq, &_struct.steal,  &_struct.guest, &_struct.guest_nice) \
{ if(!(cpu_##_name && strstr(cpu_##_name, "cpu"))) { break; } if(strlen(cpu_##_name) > 3) {

#define MON_FILE_FSCANF_ALL_CPU_STOP(_name,_struct) _struct.cpu_number++; } } MON_FILE_CLOSE(MON_SENSOR_STAT_FILE, _name);

#define MON_SENSOR_CPU_STAT_STRUCT(_name,_type) \
struct _name \
{ \
  _type user; \
  _type nice; \
  _type system; \
  _type idle; \
  _type iowait; \
  _type irq; \
  _type softirq; \
  _type steal; \
  _type guest; \
  _type guest_nice; \
  int cpu_number; \
  _name() { user = nice = system = idle = iowait = irq = softirq = steal = guest = guest_nice = cpu_number = 0; } \
};

MON_SENSOR_CPU_STAT_STRUCT(SCPUStat, int)
MON_SENSOR_CPU_STAT_STRUCT(SCPUPercentStat, float)

typedef std::map<int,SCPUStat> TCPUsStat;
TCPUsStat prevstat;

unsigned int cpu_count = 1;

MON_SENSOR_INITIALIZE
{
  SCPUStat stat;
  MON_FILE_FSCANF_ALL_CPU_START(file_cpu_count, stat, "%d")
      /*MON_LOG_DBG("fscanf: " <<
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
      cpu_count++;
      prevstat[stat.cpu_number] = stat;
  MON_FILE_FSCANF_ALL_CPU_STOP(file_cpu_count, stat)
}

MON_SENSOR_IMPLEMENT_STATISTICS_FUNCTION
{
  if(MON_SENSOR_REQUESTED_OBJECT_IS_NOT_SET)
  {
    return "";
  }
  if(MON_SENSOR_REQUESTED_OBJECT_IS(utilisation))
  {
    SCPUStat stat, delta;
    SCPUPercentStat pcStat;
    int totalDelta = 0;
    float onePercent = 0;
    std::ostringstream result;
    result << "cpu:utilisation!";
    MON_FILE_FSCANF_ALL_CPU_START(read_stat, stat, "%d")
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
        totalDelta = delta.user + delta.nice    + delta.system + delta.idle  + delta.iowait +
                     delta.irq  + delta.softirq + delta.steal  + delta.guest + delta.guest_nice;
        onePercent = totalDelta / 100;
        result << stat.cpu_number << "#" << ((float)delta.user   *onePercent) << ":" << ((float)delta.nice      *onePercent) << ":"
                                         << ((float)delta.system *onePercent) << ":" << ((float)delta.idle      *onePercent) << ":"
                                         << ((float)delta.iowait *onePercent) << ":" << ((float)delta.irq       *onePercent) << ":"
                                         << ((float)delta.softirq*onePercent) << ":" << ((float)delta.steal     *onePercent) << ":"
                                         << ((float)delta.guest  *onePercent) << ":" << ((float)delta.guest_nice*onePercent) << "|";
        prevstat[stat.cpu_number] = stat;
    MON_FILE_FSCANF_ALL_CPU_STOP(read_stat, stat)
    std::string r = result.str();
    return r.substr(0, r.length()-1).c_str();
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
