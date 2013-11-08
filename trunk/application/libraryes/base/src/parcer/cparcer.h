#ifndef CPARCER_H
#define CPARCER_H
#include <string>
#include "class-helper.h"

namespace mon
{
namespace lib
{
namespace base
{

typedef std::string::value_type TStdStringCharacter;

//! Базовый класс парсера
class CParcer
{
  public:
    CParcer();
    virtual ~CParcer();

  protected:

    bool m_eof;
    bool m_error;

    static const int   boolKeywordsCount = 4;
    static const char *keywordsTrue [boolKeywordsCount];
    static const char *keywordsFalse[boolKeywordsCount];

    virtual TStdStringCharacter goOneCharacterForward() = 0;
    virtual TStdStringCharacter goOneCharacterBack   () = 0;
    TStdStringCharacter readCharacter();
    TStdStringCharacter stepBack();

    void skipComment();
    std::string readString(const TStdStringCharacter &stringOpenChar);
    TStdStringCharacter findString();
    bool convertBool(const std::string &string);

    bool isAlpha     (const TStdStringCharacter &character);
    bool isNumeric   (const TStdStringCharacter &character);
    bool isNumericDot(const TStdStringCharacter &character);
    bool isWhiteSpace(const TStdStringCharacter &character);
    bool isQuotation (const TStdStringCharacter &character);
    bool isMarker    (const TStdStringCharacter &character);

    void parcerError(const std::string& message, const TStdStringCharacter &character);
    void parcerError(const std::string& message);

    // statistic
    int m_linesCount;
    int m_charactersCount;
    int m_currentLineCharactersCount;
};

}
}
}
#endif // CPARCER_H
