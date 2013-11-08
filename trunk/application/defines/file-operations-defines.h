#ifndef FILEOPERATIONSDEFINES_H
#define FILEOPERATIONSDEFINES_H
#include <stdio.h>
#include <stdlib.h>

//! Открытие файла
#define MON_FILE_OPEN(_filename,_name) \
    { \
    FILE *_name; \
    if   ((_name=fopen(_filename, "r")) == NULL) \
         { MON_PRINT_FILEOP_ERRNO(_filename, "File open failed"); } \
    else {
//! Закрытие файла
#define MON_FILE_CLOSE(_filename, _name) } if(fclose(_name)) { MON_PRINT_FILEOP_ERRNO(_filename, "File close failed"); }; }
//! Единичный fscanf
#define MON_FILE_FSCANF(_name,_template,...) fscanf(_name, _template, __VA_ARGS__);
//! fscanf по всему файлу в цикле
#define MON_FILE_FSCANF_ALL(_name,_template,...) while(fscanf(_name, _template, __VA_ARGS__) != EOF)

#endif // FILEOPERATIONSDEFINES_H
