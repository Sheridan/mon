#ifndef CSENSOR_H_LIB
#define CSENSOR_H_LIB
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

//! Модель сенсора
class CSensor
{
    MON_READONLY_PROPERTY(std::string, name)
    MON_READONLY_PROPERTY(CNode *, parentNode)
    MON_READONLY_PROPERTY(mon::lib::sensordata::CDefinition *, definition)
    MON_READONLY_PROPERTY(std::string, definitionText)
  public:
    CSensor(CNode *parent, const std::string &sensorName, const std::string &definitionText);
    CSensor(CNode *parent, const std::string &sensorName);
    virtual ~CSensor();
    mon::lib::sensordata::TFramesNames &frames();

  protected:
    void setDefinition(const std::string &def);

};

}
}
}
#endif // CSENSOR_H_LIB
