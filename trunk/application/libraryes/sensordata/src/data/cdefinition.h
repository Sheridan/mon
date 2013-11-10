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

class CDefinition
{
  public:
    CDefinition();
    virtual ~CDefinition();
    void addFrame(const std::string &name, CFrame *frame);
    CFrame * frame(const std::string &name);
  private:
    TFrames m_frames;
};

}
}
}
#endif // CDEFINITION_H
