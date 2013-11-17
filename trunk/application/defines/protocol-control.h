#ifndef PROTOCOLCONTROLCHARACTERS_H
#define PROTOCOLCONTROLCHARACTERS_H
#include <limits>

namespace mon
{
namespace lib
{
namespace protocol
{

#define MON_PROTO_DELIMITER(_left,_right) PD##_left##_right
#define MON_PROTOCOL_DELIMITER(_left,_right) mon::lib::protocol::MON_PROTO_DELIMITER(_left,_right)
#define MON_DECLARE_PROTOCOL_DELIMITER(_left,_right,_delimiter) \
  static const char MON_PROTO_DELIMITER(_left,_right) = _delimiter

MON_DECLARE_PROTOCOL_DELIMITER(type       ,message    ,'^' ); //!< Разделитель между типом сообщения и самим сообщением
MON_DECLARE_PROTOCOL_DELIMITER(id         ,type       ,'@' ); //!< Резделитель идентификатора и типа сообщения
MON_DECLARE_PROTOCOL_DELIMITER(end        ,line       ,'\n'); //!< Конец сообщения
MON_DECLARE_PROTOCOL_DELIMITER(date       ,frameset   ,'*' ); //!< Разделитель между датой и фреймсетом
MON_DECLARE_PROTOCOL_DELIMITER(sensorname ,framename  ,'$' ); //!< Разделитель имени сенсора и имени фрейма
MON_DECLARE_PROTOCOL_DELIMITER(framename  ,frameset   ,'!' ); //!< Разделитель имени фрейма и фреймсета
MON_DECLARE_PROTOCOL_DELIMITER(framenumber,framefields,'#' ); //!< Разделитель номера фрейма в фремсете и полей фреймсета
MON_DECLARE_PROTOCOL_DELIMITER(frame      ,frame      ,'|' ); //!< Разделитель фреймов в фреймсете
MON_DECLARE_PROTOCOL_DELIMITER(field      ,field      ,':' ); //!< Разделитель полей фрейма
MON_DECLARE_PROTOCOL_DELIMITER(sensorname ,sensorname ,':' ); //!< Разделитель сенсоров в списке сенсоров
MON_DECLARE_PROTOCOL_DELIMITER(sensorname ,definition ,'#' ); //!< Разделитель имени сенсора и его описания
MON_DECLARE_PROTOCOL_DELIMITER(framename  ,statistic  ,'!' ); //!< Разделитель имени фрейма и списка статистических данных
MON_DECLARE_PROTOCOL_DELIMITER(statistic  ,statistic  ,'~' ); //!< Разделитель статистических данных в их списке
enum EProtocolMessageType
{
  /// Ответ на запросы
  /**
   * Формат: 'id@0^сообщение'
   */
  mtAnswer,
  /// Запрос соединения, отправляется сразу с паролем.
  /**
   * Запрос: 'id@1^пароль'@n
   * Ответ:  'id@0^y' или 'id\@n'
   */
  mtConnect,
  /// Запрос списка сенсоров ноды.
  /**
   * Запрос: 'id@2'@n
   * Ответ:  'id@0^сенсор:сенсор:сенсор'
   */
  mtRequestSensorsList,
  /// Запрос определения сенсора.
  /**
   * Запрос списка всех фреймов сенсора
   * Запрос: 'id@3^'@n
   * Ответ:  'id@0^описаниесенсора'
   */
  mtRequestSensorDefinition,
  /// Запрос статистики фрейма сенсора .
  /**
   * Запрос: 'id@4^сенсор$фрейм'@n
   * Ответ:  'id@0^статистика'
   */
  mtRequestSensorFrameStatistic
};

#define MON_PROTOCOL_MESSAGE_ID_TYPE unsigned long long //!< Тип идентификатора сообщений
#define MON_PROTOCOL_MESSAGE_ID_MAX (std::numeric_limits<MON_PROTOCOL_MESSAGE_ID_TYPE>::max())

}
}
}
#endif // PROTOCOLCONTROLCHARACTERS_H
