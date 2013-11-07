#ifndef PROTOCOLCONTROLCHARACTERS_H
#define PROTOCOLCONTROLCHARACTERS_H

#define MON_PROTO_TYPE_I_MESSAGE_DELIMITER             '^'
#define MON_PROTO_ID_I_TYPE_DELIMITER                  '@'
#define MON_PROTO_ENDL                                 '\n'
#define MON_DATA_SENSORNAME_I_FRAMENAME_DELIMITER      ":"
#define MON_DATA_SENSOR_HEADER_I_FRAMESETS_DELIMITER   "!"
#define MON_DATA_SENSOR_FRAMENUMBER_I_FIELDS_DELIMITER "#"
#define MON_DATA_SENSOR_FRAME_I_FRAME_DELIMITER        "|"
#define MON_DATA_SENSOR_FIELD_I_FIELD_DELIMITER        ":"

/*
#define MON_PROTO_ID_COLLECTOR_TO_NODE_CONNECT  1
#define MON_PROTO_ID_CONNECT_ANSWER             2
#define MON_PROTO_ID_REQUEST_NODE_SENSORS_LIST  3
#define MON_PROTO_ID_ANSWER_NODE_SENSORS_LIST   4
#define MON_PROTO_ID_REQUEST_SENSOR_DEFINITION  5
#define MON_PROTO_ID_ANSWER_SENSOR_DEFINITION   6
*/

/// Ответ на запросы
#define MON_PROTO_ANSWER                        0

/// Запрос соединения, отправляется сразу с паролем.
/**
 * Запрос: 'id@1^qwerty'
 * Ответ:  'id@0^y' или 'id@n'
 */
#define MON_PROTO_ID_CONNECT                    1

/// Запрос списка сенсоров ноды.
/**
 * Запрос: 'id@2'
 * Ответ:  'id@0^cpu:memory'
 */
#define MON_PROTO_ID_REQUEST_NODE_SENSORS_LIST  2


/// Запрос определения сенсора.
/**
 * Запрос списка всех фреймов сенсора
 * Запрос: 'id@3^'
 * Ответ:  'id@0^one{f1{...},f2{...}}; two{...}'
 */
#define MON_PROTO_ID_REQUEST_SENSOR_DEFINITION   3

#endif // PROTOCOLCONTROLCHARACTERS_H
