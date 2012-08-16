#ifndef SENSORDEFINES_H
#define SENSORDEFINES_H

#include "generated.h"

#define MON_SENSOR_BEGIN \
  const unsigned char * getDefinition()       { return definition       ; } \
  const unsigned int    getDefinitionLength() { return definition_length; }

#define MON_SENSOR_IMPLEMENT_STATISTICS_FUNCTION \
  const char * getStatistics()

#define MON_SENSOR_IMPLEMENT_INFORMATION_FUNCTION \
  const char * getInformation()

#define MON_SENSOR_END \
  int main (int argc, char* argv[]) { return 0; }

#endif // SENSORDEFINES_H
