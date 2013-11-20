#ifndef CFRAMESETBUILDER_H
#define CFRAMESETBUILDER_H
#include <string>
#include "defines/class-helper.h"
#include "libraryes/base/string/cstringbuilder.h"

namespace mon
{
namespace lib
{
namespace sensorplugin
{
//! Сборщик фреймов.
/**
 * Позволяет удобно собирать сообщение с статистическими данными, подготавливает для отправки
 */
class CFramesetBuilder : public mon::lib::base::CStringBuilder
{
    MON_READONLY_PROPERTY(std::string, sensor)
    MON_READONLY_PROPERTY(std::string, frame)
public:
  CFramesetBuilder(const std::string &sensor, const std::string &frame, const int &totalFrames);
  ~CFramesetBuilder();

  CFramesetBuilder &newFrame(const int &number);

  void append(const bool               &val);
  void append(const int                &val);
  void append(const unsigned int       &val);
  void append(const short              &val);
  void append(const unsigned short     &val);
  void append(const long               &val);
  void append(const unsigned long      &val);
  void append(const long long          &val);
  void append(const unsigned long long &val);
  void append(const std::string        &val);
  void append(const char               *val);
  void append(const char               &val);
  void append(const unsigned char      &val);


  void append(const float              &val);
  void append(const double             &val);

  const std::string &string();

private:
  int  m_totalFrames; //!< Общий счетчик фреймов в фреймсете.
  int  m_framesCount; //!< Текущий фрейм фреймсета
};


}
}
}
#endif // CFRAMESETBUILDER_H
