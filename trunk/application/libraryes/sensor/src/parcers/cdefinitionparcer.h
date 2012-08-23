/* %Id% */
#ifndef CDEFINITIONPARCER_H
#define CDEFINITIONPARCER_H
#include <string>
#include "cdefinition.h"
#include "class-helper.h"

namespace mon
{
namespace lib
{
namespace sensor
{

class CDefinitionParcer
{
    CDefinitionParcer();
    ~CDefinitionParcer();
    CDefinition * parce(const std::string &definition);

  private:
    std::string m_definitionText;
    int         m_currentIndex;

//    TCFChar readChar();
//    void stepBack();
//    void skipComment();
//    std::string readString(const TCFChar &stringOpenChar);
//    void readValue();
};

}
}
}
#endif // CDEFINITIONPARCER_H
