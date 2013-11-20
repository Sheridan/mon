#ifndef CREMOTENODESENSOR_H
#define CREMOTENODESENSOR_H
#include <list>
#include <string>
#include "defines/class-helper.h"
#include "libraryes/sensordata/data/cdefinition.h"

namespace mon
{
namespace daemons
{
namespace collector
{

class CNode;

//! Сенсор удаленной ноды
class CSensor
{
    MON_READONLY_PROPERTY(std::string, name)
  public:
    CSensor(const std::string &name, const std::string &definition, CNode *parentNode);
    ~CSensor();
    mon::lib::sensordata::TFramesNames &frames();
  private:
    CNode *m_parentNode;
    mon::lib::sensordata::CDefinition *m_definition;
};

//! Список сенсоров удаленной ноды
typedef std::list<CSensor *> TSensors;

}
}
}
#endif // CREMOTENODESENSOR_H
