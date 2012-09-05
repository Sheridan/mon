/* %Id% */
#ifndef CSENSOR_H
#define CSENSOR_H
#include <string>
#include "class-helper.h"
#include <list>
#include "logger.h"
#include "config.h"
namespace mon
{
namespace daemons
{
namespace node
{

typedef void              (*TFInitSensor)(mon::lib::logger::CLogger *, mon::lib::config::CFolder *);
typedef const char *      (*TFGetName)            (const char *);
typedef const char *      (*TFGetDefinition)      (const char *);
typedef unsigned int      (*TFGetDefinitionLength)(const char *);
typedef const std::string (*TFGetStatistics)      (const char *);

class CSensor
{
    MON_READONLY_PROPERTY(std::string, name)
  public:
    CSensor(const std::string &i_name);
    ~CSensor();
    void load();
    TFInitSensor          initSensor;
    TFGetName             getName;
    TFGetDefinition       getDefinition;
    TFGetDefinitionLength getDefinitionLength;
    TFGetStatistics       getStatistics;

  private:
    void * m_handle;
};

typedef std::list<CSensor *> TSensors;

}
}
}
#endif // CSENSOR_H
