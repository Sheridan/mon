/* %Id% */
#ifndef CDEFINITIONPARCER_H
#define CDEFINITIONPARCER_H
#include <string>
#include "cdefinition.h"
#include "class-helper.h"
#include "cparcerstring.h"

namespace mon
{
namespace lib
{
namespace sensor
{

class CDefinitionParcer : public mon::lib::base::CParcerString
{
    CDefinitionParcer(const std::string &definition);
    ~CDefinitionParcer();
    CDefinition * parce();

  private:
    std::string m_definitionText;
    int         m_currentIndex;

};

}
}
}
#endif // CDEFINITIONPARCER_H
