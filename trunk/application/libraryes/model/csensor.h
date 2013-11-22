#ifndef CSENSOR_H
#define CSENSOR_H
#include <string>
#include <list>
#include "defines/class-helper.h"
#include "libraryes/sensordata/data/cdefinition.h"

namespace mon
{
namespace lib
{
namespace model
{

class CNode;

class CSensor
{
    MON_READONLY_PROPERTY(std::string, name)
    MON_READONLY_PROPERTY(CNode *, parentNode)
    MON_READONLY_PROPERTY(mon::lib::sensordata::CDefinition *, definition)
    MON_READONLY_PROPERTY(std::string, definitionText)
  public:
    CSensor(CNode *parent, const std::string &sensorName, const std::string &definitionText);
    virtual ~CSensor();
    mon::lib::sensordata::TFramesNames &frames();

};

typedef std::list<CSensor *> TSensors;

}
}
}
#endif // CSENSOR_H
