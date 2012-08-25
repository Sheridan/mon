/* %Id% */
#include "cdefinitionparcer.h"
#include "parcer-helper.h"

namespace mon
{
namespace lib
{
namespace sensor
{

CDefinitionParcer::CDefinitionParcer(CDefinition *target, const std::string &definition)
  : mon::lib::base::CParcerString(definition),
    m_definition(target)
{}

CDefinitionParcer::~CDefinitionParcer()
{}

void CDefinitionParcer::parce()
{
  MON_PARCER_LOOP_BEGIN(read_object_name)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_object_name)
    {
      MON_PARCER_BUFFER_APPEND(read_object_name);
      MON_PARCER_LOOP_RESTART(read_object_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_object_name)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_object_name, "Object name must begin only with alpha symbols");
      MON_PARCER_BUFFER_APPEND(read_object_name);
      MON_PARCER_LOOP_RESTART(read_object_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_object_name)
    {
      MON_PARCER_LOOP_RESTART(read_object_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_object_name, '{')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_object_name, "Missed object name");
      m_definition->addObject(MON_PARCER_BUFFER(read_object_name), parceObject());
      MON_PARCER_BUFFER_RESET(read_object_name);
      MON_PARCER_LOOP_RESTART(read_object_name);
    }
    MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_object_name, "Misplaced character");
  }
  MON_PARCER_LOOP_END(read_object_name);
}

CObject * CDefinitionParcer::parceObject()
{
  CObject *obj = new CObject();
  MON_PARCER_LOOP_BEGIN(read_object)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_object)
    {
      MON_PARCER_BUFFER_APPEND(read_object);
      MON_PARCER_LOOP_RESTART(read_object);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_object)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_object, "Object keyword must begin only with alpha symbols");
      MON_PARCER_BUFFER_APPEND(read_object);
      MON_PARCER_LOOP_RESTART(read_object);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_object)
    {
      MON_PARCER_LOOP_RESTART(read_object);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_object, ':')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_object, "Missed object keyword");
      MON_PARCER_IS_KEYWORD(read_object, "label")
      {
        obj->setlabel(readStringValue());
        MON_PARCER_BUFFER_RESET(read_object);
        MON_PARCER_LOOP_RESTART(read_object);
      }
      MON_PARCER_IS_KEYWORD(read_object, "frequence")
      {
        readFrequences(obj);
        MON_PARCER_BUFFER_RESET(read_object);
        MON_PARCER_LOOP_RESTART(read_object);
      }
      MON_PARCER_IS_KEYWORD(read_object, "flags")
      {}
      MON_PARCER_IS_KEYWORD(read_object, "tags")
      {}
      MON_PARCER_IS_KEYWORD(read_object, "statisticalFields")
      {}
      MON_PARCER_IS_KEYWORD(read_object, "informationFields")
      {}
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_object, '}')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_object, "Misplaced character");
      MON_PARCER_LOOP_BREAK(read_object)
    }
    MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_object, "Misplaced character");
  }
  MON_PARCER_LOOP_END(read_object);
  return obj;
}

void CDefinitionParcer::readFrequences(CObject *obj)
{
  MON_PARCER_LOOP_BEGIN(read_frequences)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_frequences)
    {
      MON_PARCER_BUFFER_APPEND(read_frequences);
      MON_PARCER_LOOP_RESTART(read_frequences);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_frequences)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frequences, "Frequency keyword must begin only with alpha symbols");
      MON_PARCER_BUFFER_APPEND(read_frequences);
      MON_PARCER_LOOP_RESTART(read_frequences);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_frequences)
    {
      MON_PARCER_LOOP_RESTART(read_frequences);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frequences, '}')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_frequences, "Misplaced character");
      MON_PARCER_LOOP_BREAK(read_frequences)
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frequences, ':')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frequences, "Missed frequency keyword");
      MON_PARCER_IS_KEYWORD(read_frequences, "statistical")
      {}
      MON_PARCER_IS_KEYWORD(read_frequences, "information")
      {}
    }
    MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_frequences, "Misplaced character");
  }
  MON_PARCER_LOOP_END(read_frequences);
}

void CDefinitionParcer::readFrequency(const EFrequencyClasses &ftype, CObject *obj)
{
  MON_PARCER_LOOP_BEGIN(read_frequency)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_frequency)
    {
      MON_PARCER_BUFFER_APPEND(read_frequency);
      MON_PARCER_LOOP_RESTART(read_frequency);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_frequency)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frequency, "Frequency keyword must begin only with alpha symbols");
      MON_PARCER_BUFFER_APPEND(read_frequency);
      MON_PARCER_LOOP_RESTART(read_frequency);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_frequency)
    {
      MON_PARCER_LOOP_RESTART(read_frequency);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frequency, '}')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_frequency, "Misplaced character");
      MON_PARCER_LOOP_BREAK(read_frequency)
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frequency, ':')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frequency, "Missed frequency keyword");
      MON_PARCER_IS_KEYWORD(read_frequency, "max")
      {}
      MON_PARCER_IS_KEYWORD(read_frequency, "default")
      {}
    }
  }
  MON_PARCER_LOOP_END(read_frequency);
}

void CDefinitionParcer::skipToSemicolon()
{
  MON_PARCER_LOOP_BEGIN(find_semicolon)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(find_semicolon)
    {
      MON_PARCER_LOOP_RESTART(find_semicolon);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(find_semicolon, ';')
    {
      MON_PARCER_LOOP_BREAK(find_semicolon)
    }
    parcerError("Misplaced character", MON_PARCER_CURRENT_CHARACTER(find_semicolon));
  }
  MON_PARCER_LOOP_END(find_semicolon);
}

std::string CDefinitionParcer::readStringValue()
{
  std::string result = readString(findString());
  skipToSemicolon();
  return result;
}

}
}
}
