/* %Id% */
#ifndef CDEFINITION_H
#define CDEFINITION_H
#include "libraryes/sensordata/data/cframe.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

//! Описание сенсора
class CDefinition
{
  public:
    CDefinition();
    virtual ~CDefinition();
    void addFrame(const std::string &name, CFrame *frame);
    CFrame * frame(const std::string &name);
    TFramesNames &frames();

  private:
    TFramesMap m_frames;  //!< Фреймы сенсора
    TFramesNames m_names; //!< Имена фреймов
};

}
}
}
#endif // CDEFINITION_H
