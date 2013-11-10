/* %Id% */
#ifndef CDEFINITION_H
#define CDEFINITION_H
#include "cframe.h"
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
    TFramesNames frames();

  private:
    TFramesMap m_frames; //!< Фреймы сенсора
};

}
}
}
#endif // CDEFINITION_H
