#ifndef CREMOTENODESENSOR_H
#define CREMOTENODESENSOR_H
#include <list>
#include <string>
#include "defines/class-helper.h"
#include "libraryes/sensordata/data/cdefinition.h"
#include "libraryes/model/csensor.h"

namespace mon
{
namespace daemons
{
namespace collector
{

class CNode;

//! Сенсор удаленной ноды
class CSensor : public mon::lib::model::CSensor
{
  public:
    CSensor(CNode *parentNode, const std::string &name, const std::string &definition);
    ~CSensor();

};

}
}
}
#endif // CREMOTENODESENSOR_H
