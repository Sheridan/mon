/* %Id% */
#include "cdefinitionparcer.h"
#include "parcer-helper.h"
#include "cvariant.h"

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
      MON_PARCER_IS_KEYWORD(read_object, "frequency")
      {
        readFrequences(obj);
        MON_PARCER_BUFFER_RESET(read_object);
        MON_PARCER_LOOP_RESTART(read_object);
      }
      MON_PARCER_IS_KEYWORD(read_object, "type")
      {
        readType(obj);
        MON_PARCER_BUFFER_RESET(read_object);
        MON_PARCER_LOOP_RESTART(read_object);
      }
      MON_PARCER_IS_KEYWORD(read_object, "flags")
      {
        readFlags(obj);
        MON_PARCER_BUFFER_RESET(read_object);
        MON_PARCER_LOOP_RESTART(read_object);
      }
      MON_PARCER_IS_KEYWORD(read_object, "tags")
      {
        readTags(obj);
        MON_PARCER_BUFFER_RESET(read_object);
        MON_PARCER_LOOP_RESTART(read_object);
      }
      MON_PARCER_IS_KEYWORD(read_object, "fields")
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

void CDefinitionParcer::readFields(CObject *obj)
{
  MON_PARCER_LOOP_BEGIN(read_fields)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_fields)
    {
      MON_PARCER_BUFFER_APPEND(read_fields);
      MON_PARCER_LOOP_RESTART(read_fields);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_fields)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_fields, "Field named must begin only with alpha symbols");
      MON_PARCER_BUFFER_APPEND(read_fields);
      MON_PARCER_LOOP_RESTART(read_fields);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_fields)
    {
      MON_PARCER_LOOP_RESTART(read_fields);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_fields, ':')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_fields, "Missed field name");
      readField(obj, MON_PARCER_BUFFER(read_fields));
      MON_PARCER_BUFFER_RESET(read_fields);
      MON_PARCER_LOOP_RESTART(read_fields);
    }
    MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_fields, "Misplaced character");
  }
  MON_PARCER_LOOP_END(read_fields);
}

void CDefinitionParcer::readField(CObject *obj, const std::string &name)
{
  std::string label = "";
  EDataType type = dtInteger;
  std::string str_type = "";
  std::string description = "";
  MON_PARCER_LOOP_BEGIN(read_field)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_field)
    {
      MON_PARCER_BUFFER_APPEND(read_field);
      MON_PARCER_LOOP_RESTART(read_field);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_field)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_field, "Field named must begin only with alpha symbols");
      MON_PARCER_BUFFER_APPEND(read_field);
      MON_PARCER_LOOP_RESTART(read_field);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_field)
    {
      MON_PARCER_LOOP_RESTART(read_field);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_field, ':')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_field, "Missed field parameter name");
      MON_PARCER_IS_KEYWORD(read_field, "label")
      {
        label = readStringValue();
        MON_PARCER_BUFFER_RESET(read_field);
        MON_PARCER_LOOP_RESTART(read_field);
      }
      MON_PARCER_IS_KEYWORD(read_field, "type")
      {
        str_type = readValue();
               if (str_type == "%"       ) { type = dtPercent         ; }
        else { if (str_type == "bool"    ) { type = dtBool            ; }
        else { if (str_type == "short"   ) { type = dtShort           ; }
        else { if (str_type == "ushort"  ) { type = dtUnsignedShort   ; }
        else { if (str_type == "integer" ) { type = dtInteger         ; }
        else { if (str_type == "uinteger") { type = dtUnsignedIinteger; }
        else { if (str_type == "long"    ) { type = dtLong            ; }
        else { if (str_type == "ulong"   ) { type = dtUnsignedLong    ; }
        else { if (str_type == "float"   ) { type = dtFloat           ; }
        else { if (str_type == "string"  ) { type = dtString          ; }
                                                        } } } } } } } } }
        MON_PARCER_BUFFER_RESET(read_field);
        MON_PARCER_LOOP_RESTART(read_field);
      }
      MON_PARCER_IS_KEYWORD(read_field, "description")
      {
        description = readStringValue();
        MON_PARCER_BUFFER_RESET(read_field);
        MON_PARCER_LOOP_RESTART(read_field);
      }
      MON_PARCER_BUFFER_RESET(read_field);
      MON_PARCER_LOOP_RESTART(read_field);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_field, '{')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_field, "Misplaced character");
      MON_PARCER_LOOP_RESTART(read_field)
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_field, '}')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_field, "Misplaced character");
      MON_PARCER_LOOP_BREAK(read_field)
    }
  }
  MON_PARCER_LOOP_END(read_field);
  obj->addField(name, label, type, description);
}

void CDefinitionParcer::readTags(CObject *obj)
{
  MON_PARCER_LOOP_BEGIN(read_tags)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_tags)
    {
      MON_PARCER_BUFFER_APPEND(read_tags);
      MON_PARCER_LOOP_RESTART(read_tags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_tags)
    {
      MON_PARCER_BUFFER_APPEND(read_tags);
      MON_PARCER_LOOP_RESTART(read_tags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_tags)
    {
      MON_PARCER_LOOP_RESTART(read_tags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_tags, ',')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_tags, "Missed tag");
      obj->addTag(MON_PARCER_BUFFER(read_tags));
      MON_PARCER_BUFFER_RESET(read_tags);
      MON_PARCER_LOOP_RESTART(read_tags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_tags, '{')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_tags, "Misplaced character");
      MON_PARCER_LOOP_RESTART(read_tags)
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_tags, '}')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_tags, "Misplaced character");
      MON_PARCER_LOOP_BREAK(read_tags)
    }
  }
  MON_PARCER_LOOP_END(read_tags);
}

void CDefinitionParcer::readFlags(CObject *obj)
{
  MON_PARCER_LOOP_BEGIN(read_flags)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_flags)
    {
      MON_PARCER_BUFFER_APPEND(read_flags);
      MON_PARCER_LOOP_RESTART(read_flags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_flags)
    {
      MON_PARCER_BUFFER_APPEND(read_flags);
      MON_PARCER_LOOP_RESTART(read_flags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_flags)
    {
      MON_PARCER_LOOP_RESTART(read_flags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_flags, ',')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_flags, "Missed flag");
      MON_PARCER_IS_KEYWORD(read_flags, "aggregated")
      {
        obj->addFlag(fAggregated);
      }
      MON_PARCER_IS_KEYWORD(read_flags, "calculateTotal")
      {
        obj->addFlag(fCalculateTotal);
      }
      MON_PARCER_BUFFER_RESET(read_flags);
      MON_PARCER_LOOP_RESTART(read_flags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_flags, '{')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_flags, "Misplaced character");
      MON_PARCER_LOOP_RESTART(read_flags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_flags, '}')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_flags, "Misplaced character");
      MON_PARCER_LOOP_BREAK(read_flags);
    }
  }
  MON_PARCER_LOOP_END(read_flags);
}

void CDefinitionParcer::readType(CObject *obj)
{
  MON_PARCER_LOOP_BEGIN(read_type)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_type)
    {
      MON_PARCER_BUFFER_APPEND(read_type);
      MON_PARCER_LOOP_RESTART(read_type);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_type)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_type, "Type keyword must begin only with alpha symbols");
      MON_PARCER_BUFFER_APPEND(read_type);
      MON_PARCER_LOOP_RESTART(read_type);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_type)
    {
      MON_PARCER_LOOP_RESTART(read_type);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_type, ';')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_type, "Missed type");
      MON_PARCER_IS_KEYWORD(read_type, "information")
      {
        obj->settype(tInformation);
        MON_PARCER_LOOP_BREAK(read_type)
      }
      MON_PARCER_IS_KEYWORD(read_type, "statistic")
      {
        obj->settype(tStatistic);
        MON_PARCER_LOOP_BREAK(read_type)
      }
      parcerError("Unknown type", MON_PARCER_CURRENT_CHARACTER(read_type));
      MON_PARCER_LOOP_BREAK(read_type)
    }
  }
  MON_PARCER_LOOP_END(read_type);
}

void CDefinitionParcer::readFrequences(CObject *obj)
{
  float                    value      = 0;
  EFrequencyMeasurment     measurment = ftHz;
  EFrequencyPurpose        purpose    = fpMax;
  EFrequencyCurrentReading fcr        = fcrKeyword;
  MON_PARCER_LOOP_BEGIN(read_frequency)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_frequency)
    {
      MON_PARCER_LOOP_RESTART(read_frequency);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_frequency)
    {
      switch(fcr)
      {
        case fcrKeyword:
        case fcrMeasurment:
        {
          MON_PARCER_BUFFER_APPEND(read_frequency);
          MON_PARCER_LOOP_RESTART(read_frequency);
          break;
        }
        case fcrValue:
        {
          fcr = fcrMeasurment;
          value = mon::lib::base::toFloat(MON_PARCER_BUFFER(read_frequency));
          MON_PARCER_BUFFER_RESET(read_frequency);
          MON_PARCER_BUFFER_APPEND(read_frequency);
          MON_PARCER_LOOP_RESTART(read_frequency);
        }
      }
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_frequency)
    {
      switch(fcr)
      {
        case fcrKeyword:
        case fcrMeasurment:
        {
          parcerError("Frequency keyword or type must contain only alpha", MON_PARCER_CURRENT_CHARACTER(read_frequency));
        }
        case fcrValue:
        {
          MON_PARCER_BUFFER_APPEND(read_frequency);
          MON_PARCER_LOOP_RESTART(read_frequency);
          break;
        }
      }
    }

    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frequency, ';')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frequency, "Missed frequency");
      MON_PARCER_IS_KEYWORD(read_frequency, "Hz")
      {
        measurment = ftHz;
      }
      MON_PARCER_IS_KEYWORD(read_frequency, "SPP")
      {
        measurment = ftSPP;
      }
      obj->setFrequency(purpose, measurment, value);
      value      = 0;
      measurment = ftHz;
      purpose    = fpMax;
      fcr        = fcrKeyword;
      MON_PARCER_BUFFER_RESET(read_frequency);
      MON_PARCER_LOOP_RESTART(read_frequency)
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frequency, ':')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frequency, "Missed frequency keyword");
      MON_PARCER_IS_KEYWORD(read_frequency, "max")
      {
        purpose = fpMax;
        fcr = fcrValue;
        MON_PARCER_BUFFER_RESET(read_frequency);
        MON_PARCER_LOOP_RESTART(read_frequency);
      }
      MON_PARCER_IS_KEYWORD(read_frequency, "default")
      {
        purpose = fpDefault;
        fcr = fcrValue;
        MON_PARCER_BUFFER_RESET(read_frequency);
        MON_PARCER_LOOP_RESTART(read_frequency);
      }
      parcerError("Unknown frequency type", MON_PARCER_CURRENT_CHARACTER(read_frequency));
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frequency, '{')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_frequency, "Misplaced character");
      MON_PARCER_LOOP_RESTART(read_frequency)
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frequency, '}')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_frequency, "Misplaced character");
      MON_PARCER_LOOP_BREAK(read_frequency)
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

std::string CDefinitionParcer::readValue()
{
  std::string result = "";
  MON_PARCER_LOOP_BEGIN(read_value)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_value)
    {
      MON_PARCER_BUFFER_APPEND(read_value);
      MON_PARCER_LOOP_RESTART(read_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_value)
    {
      MON_PARCER_BUFFER_APPEND(read_value);
      MON_PARCER_LOOP_RESTART(read_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_value)
    {
      MON_PARCER_LOOP_RESTART(read_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_value, ';')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_value, "Missed value");
      result = MON_PARCER_BUFFER(read_value);
      MON_PARCER_LOOP_BREAK(read_value)
    }
  }
  MON_PARCER_LOOP_END(read_value);
  return result;
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
