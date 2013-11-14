#ifndef PROTOCOLCONTROLCHARACTERS_H
#define PROTOCOLCONTROLCHARACTERS_H
#include <climits>

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
MON_DECLARE_PROTOCOL_DELIMITER(sensorname ,framename  ,'$' ); //!< Разделитель имени сенсора и имени фрейма
MON_DECLARE_PROTOCOL_DELIMITER(framename  ,frameset   ,'!' ); //!< Разделитель имени фрейма и фреймсета
MON_DECLARE_PROTOCOL_DELIMITER(framenumber,framefields,'#' ); //!< Разделитель номера фрейма в фремсете и полей фреймсета
MON_DECLARE_PROTOCOL_DELIMITER(frame      ,frame      ,'|' ); //!< Разделитель фреймов в фреймсете
MON_DECLARE_PROTOCOL_DELIMITER(field      ,field      ,':' ); //!< Разделитель полей фрейма
MON_DECLARE_PROTOCOL_DELIMITER(sensorname ,sensorname ,':' ); //!< Разделитель сенсоров в списке сенсоров
MON_DECLARE_PROTOCOL_DELIMITER(sensorname ,definition ,'#' ); //!< Разделитель имени сенсора и его описания

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
  mtRequestSensorDefinition
};

typedef unsigned long long TProtocolMessageID; //!< Тип идентификатора сообщений
#define MON_PROTOCOL_MESSAGE_ID_MAX ULLONG_MAX

}
}
}
#endif // PROTOCOLCONTROLCHARACTERS_H
