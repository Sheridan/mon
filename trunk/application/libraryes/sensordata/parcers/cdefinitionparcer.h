/* %Id% */
#ifndef CDEFINITIONPARCER_H
#define CDEFINITIONPARCER_H
#include <string>
#include "defines/class-helper.h"
#include "libraryes/sensordata/data/cdefinition.h"
#include "libraryes/base/parcer/cparcerstring.h"
#include "libraryes/sensordata/data/cfrequency.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

//! Шаги чтения частоты обновления
enum EFrequencyCurrentReading
{
  fcrKeyword,   //!< Чтение ключевого слова
  fcrValue,     //!< Чтение значения
  fcrMeasurment //!< Чтение типа значения
};

//! Парсер описания сенсора
class CDefinitionParcer : public mon::lib::base::CParcerString
{
  public:
    CDefinitionParcer(CDefinition *target, const std::string &definition);
    ~CDefinitionParcer();
    void parce();

  private:
    std::string  m_definitionText;
    //int          m_currentIndex;
    CDefinition *m_definition;

    CFrame *parceFrame();

    void readFrequences(CFrame *frame);
    void readFlags     (CFrame *frame);
    void readTags      (CFrame *frame);
    void readFields    (CFrame *frame);
    void readFrameType (CFrame *frame);
    void readField     (CFrame *frame, const std::string &name);

    void skipToSemicolon();
    std::string readStringValue();
    EFieldDataType readFieldType ();

};

}
}
}
#endif // CDEFINITIONPARCER_H
