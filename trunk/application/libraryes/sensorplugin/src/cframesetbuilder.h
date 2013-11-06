#ifndef CFRAMESETBUILDER_H
#define CFRAMESETBUILDER_H
#include "cstringbuilder.h"

namespace mon
{
namespace lib
{
namespace sensorplugin
{

class CFramesetBuilder : public mon::lib::base::CStringBuilder
{
public:
  CFramesetBuilder(const std::string &sensor, const std::string &frame, const int &totalFrames);
  ~CFramesetBuilder();

  CFramesetBuilder &newFrame(const int &number);

  void append(const int           &val);
  void append(const unsigned int  &val);
  void append(const double        &val);
  void append(const float         &val);
  void append(const bool          &val);
  void append(const std::string   &val);
  void append(const char          *val);
  void append(const char          &val);
  void append(const unsigned char &val);

  const std::string &msg();

private:
  int  m_totalFrames;
  int  m_framesCount;
};


}
}
}
#endif // CFRAMESETBUILDER_H
