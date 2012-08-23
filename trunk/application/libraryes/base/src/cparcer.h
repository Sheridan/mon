#ifndef CPARCER_H
#define CPARCER_H
#include <string>
#include "class-helper.h"
#include "parcer-helper.h"

namespace mon
{
namespace lib
{
namespace base
{

typedef std::string::value_type TStdStringCharacter;

struct SExtractedCharacter
{
    TStdStringCharacter character;
    bool valid;
    SExtractedCharacter(const TStdStringCharacter &c, const bool &v) { character = c; valid = v    ; }
    SExtractedCharacter(const TStdStringCharacter &c               ) { character = c; valid = true ; }
    SExtractedCharacter(                                           ) { character = 0; valid = false; }
    SExtractedCharacter(const SExtractedCharacter &c               ) { character = c.character; valid = c.valid; }
};

class CParcer
{
  public:
    CParcer();
    virtual ~CParcer();
  protected:

    static const int   boolKeywordsCount = 4;
    static const char *keywordsTrue [boolKeywordsCount];
    static const char *keywordsFalse[boolKeywordsCount];

    virtual SExtractedCharacter goOneCharacterForward() = 0;
    virtual SExtractedCharacter goOneCharacterBack   () = 0;
    SExtractedCharacter readCharacter();
    SExtractedCharacter stepBack();

//    void readValue();

    void skipComment();
    std::string readString(const SExtractedCharacter &stringOpenChar);

    bool isAlpha     (const SExtractedCharacter &character);
    bool isNumeric   (const SExtractedCharacter &character);
    bool isWhiteSpace(const SExtractedCharacter &character);

    void parcerError(const std::string& object, const std::string& message);

    // statistic
    int m_linesCount;
    int m_charactersCount;
    int m_currentLineCharactersCount;
};

}
}
}
#endif // CPARCER_H
