/* %Id% */
#ifndef COBJECT_H
#define COBJECT_H
#include <string>
#include <set>
#include <list>
#include <map>
#include "cfrequency.h"
#include "cfield.h"
#include "class-helper.h"
namespace mon
{
namespace lib
{
namespace sensordata
{

//! Флаги фрейма
enum EFrameFlags
{
  ffAggregated,    //!< Данные полей статистики представляют собой часть целого. То есть например 10%, 70%, 20%
  ffCalculateTotal //!< Необходимо суммировать значения полей в отдельное, генерируемое поле
};

//! Типы фрейма
enum EFrameType
{
  ftInformation, //!< Информационный фрейм, предназначен для сбора нестатистической инфрмации сенсором. Например имя процессора
  ftStatistic    //!< Статистический фрейм
};

typedef std::set<EFrameFlags>  TFlags;
typedef std::set<std::string>  TTags;

//! Класс, описывающий фрейм сенсора
class CFrame
{
    MON_PROPERTY(std::string            , label      ) //!< Метка фрейма
    MON_PROPERTY(EFrameType             , frameType  ) //!< Тип фрейма
    MON_READONLY_PROPERTY(TFlags        , flags      ) //!< Флаги фрейма
    MON_READONLY_PROPERTY(TTags         , tags       ) //!< Тэги фрейма
    MON_READONLY_PROPERTY(TFields       , fields     ) //!< Поля фрейма

  public:
    CFrame();
    ~CFrame();
    std::string generateText();
    void setFrequency(const EFrequencyPurpose &purpose, const EFrequencyMeasurment &measurment, const float &value);
    void addField    (const std::string &name, const std::string &label, const EFieldDataType &type, const std::string &description);
    void addFlag     (const EFrameFlags &flag);
    bool hasFlag     (const EFrameFlags &flag);
    void addTag      (const std::string &tag);
    bool hasTag      (const std::string &tag);

  private:
    CFrequency *m_frequences[3]; //!< Частоты взятия данных с фрейма

};

typedef std::map<std::string, CFrame *> TFrames;

}
}
}
#endif // COBJECT_H
