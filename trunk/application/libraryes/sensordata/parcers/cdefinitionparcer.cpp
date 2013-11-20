/* %Id% */
#include "libraryes/sensordata/parcers/cdefinitionparcer.h"
#include "libraryes/base/parcer/parcer-helper.h"
#include "libraryes/base/string/cvariant.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

CDefinitionParcer::CDefinitionParcer(CDefinition *target, const std::string &definition)
  : mon::lib::base::CParcerString(definition),
    m_definition(target)
{}

CDefinitionParcer::~CDefinitionParcer()
{}

void CDefinitionParcer::parce()
{
  MON_PARCER_LOOP_BEGIN(read_frame_name)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_frame_name)
    {
      MON_PARCER_BUFFER_APPEND(read_frame_name);
      MON_PARCER_LOOP_RESTART(read_frame_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_frame_name)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frame_name, "frame name must begin only with alpha symbols");
      MON_PARCER_BUFFER_APPEND(read_frame_name);
      MON_PARCER_LOOP_RESTART(read_frame_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_frame_name)
    {
      MON_PARCER_LOOP_RESTART(read_frame_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frame_name, '#')
    {
      skipComment();
      MON_PARCER_LOOP_RESTART(read_frame_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frame_name, '{')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frame_name, "Missed frame name");
      m_definition->addFrame(MON_PARCER_BUFFER(read_frame_name), parceFrame());
      MON_PARCER_BUFFER_RESET(read_frame_name);
      MON_PARCER_LOOP_RESTART(read_frame_name);
    }
    MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_frame_name, "Misplaced character");
  }
  MON_PARCER_LOOP_END(read_frame_name);
}

CFrame * CDefinitionParcer::parceFrame()
{
  CFrame *frame = new CFrame();
  MON_PARCER_LOOP_BEGIN(read_frame)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_frame)
    {
      MON_PARCER_BUFFER_APPEND(read_frame);
      MON_PARCER_LOOP_RESTART(read_frame);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_frame)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frame, "frame keyword must begin only with alpha symbols");
      MON_PARCER_BUFFER_APPEND(read_frame);
      MON_PARCER_LOOP_RESTART(read_frame);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_frame)
    {
      MON_PARCER_LOOP_RESTART(read_frame);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frame, '#')
    {
      skipComment();
      MON_PARCER_LOOP_RESTART(read_frame);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frame, ':')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frame, "Missed frame keyword");
      MON_PARCER_IS_KEYWORD(read_frame, "label")
      {
        frame->setlabel(readStringValue());
        MON_PARCER_BUFFER_RESET(read_frame);
        MON_PARCER_LOOP_RESTART(read_frame);
      }
      MON_PARCER_IS_KEYWORD(read_frame, "frequency")
      {
        readFrequences(frame);
        MON_PARCER_BUFFER_RESET(read_frame);
        MON_PARCER_LOOP_RESTART(read_frame);
      }
      MON_PARCER_IS_KEYWORD(read_frame, "type")
      {
        readFrameType(frame);
        MON_PARCER_BUFFER_RESET(read_frame);
        MON_PARCER_LOOP_RESTART(read_frame);
      }
      MON_PARCER_IS_KEYWORD(read_frame, "flags")
      {
        readFlags(frame);
        MON_PARCER_BUFFER_RESET(read_frame);
        MON_PARCER_LOOP_RESTART(read_frame);
      }
      MON_PARCER_IS_KEYWORD(read_frame, "tags")
      {
        readTags(frame);
        MON_PARCER_BUFFER_RESET(read_frame);
        MON_PARCER_LOOP_RESTART(read_frame);
      }
      MON_PARCER_IS_KEYWORD(read_frame, "fields")
      {
        readFields(frame);
        MON_PARCER_BUFFER_RESET(read_frame);
        MON_PARCER_LOOP_RESTART(read_frame);
      }
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frame, '}')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_frame, "Misplaced character");
      MON_PARCER_LOOP_BREAK(read_frame)
    }
    MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_frame, "Misplaced character");
  }
  MON_PARCER_LOOP_END(read_frame);
  return frame;
}

void CDefinitionParcer::readFields(CFrame *frame)
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
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_fields, '#')
    {
      skipComment();
      MON_PARCER_LOOP_RESTART(read_fields);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_fields, ':')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_fields, "Missed field name");
      readField(frame, MON_PARCER_BUFFER(read_fields));
      MON_PARCER_BUFFER_RESET(read_fields);
      MON_PARCER_LOOP_RESTART(read_fields);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_fields, '}')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_fields, "Misplaced character");
      MON_PARCER_LOOP_BREAK(read_fields)
    }
    MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_fields, "Misplaced character");
  }
  MON_PARCER_LOOP_END(read_fields);
}

void CDefinitionParcer::readField(CFrame *frame, const std::string &name)
{
  std::string    label       = "";
  EFieldDataType type        = EFieldDataType::Int;
  std::string    description = "";
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
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_field, '#')
    {
      skipComment();
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
        type = readFieldType();
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
  frame->addField(name, label, type, description);
}

void CDefinitionParcer::readTags(CFrame *frame)
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
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_tags, '#')
    {
      skipComment();
      MON_PARCER_LOOP_RESTART(read_tags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_tags, ';')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_tags, "Missed tag");
      frame->addTag(MON_PARCER_BUFFER(read_tags));
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

void CDefinitionParcer::readFlags(CFrame *frame)
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
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_flags, '#')
    {
      skipComment();
      MON_PARCER_LOOP_RESTART(read_flags);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_flags, ';')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_flags, "Missed flag");
      MON_PARCER_IS_KEYWORD(read_flags, "aggregated")
      {
        frame->addFlag(ffAggregated);
      }
      MON_PARCER_IS_KEYWORD(read_flags, "calculateTotal")
      {
        frame->addFlag(ffCalculateTotal);
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

void CDefinitionParcer::readFrameType(CFrame *frame)
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
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_type, '#')
    {
      skipComment();
      MON_PARCER_LOOP_RESTART(read_type);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_type, ';')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_type, "Missed type");
      MON_PARCER_IS_KEYWORD(read_type, "information")
      {
        frame->setframeType(ftInformation);
        MON_PARCER_LOOP_BREAK(read_type)
      }
      MON_PARCER_IS_KEYWORD(read_type, "statistic")
      {
        frame->setframeType(ftStatistic);
        MON_PARCER_LOOP_BREAK(read_type)
      }
      parcerError("Unknown type", MON_PARCER_CURRENT_CHARACTER(read_type));
      MON_PARCER_LOOP_BREAK(read_type)
    }
  }
  MON_PARCER_LOOP_END(read_type);
}

void CDefinitionParcer::readFrequences(CFrame *frame)
{
  float                    value      = 0;
  EFrequencyMeasurment     measurment = EFrequencyMeasurment::Hz;
  EFrequencyPurpose        purpose    = fpMax;
  EFrequencyCurrentReading fcr        = fcrKeyword;
  MON_PARCER_LOOP_BEGIN(read_frequency)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_frequency)
    {
      MON_PARCER_LOOP_RESTART(read_frequency);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frequency, '#')
    {
      skipComment();
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
        }
      }
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC_DOT(read_frequency)
    {
      MON_PARCER_BUFFER_APPEND(read_frequency);
      MON_PARCER_LOOP_RESTART(read_frequency);
    }

    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_frequency, ';')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_frequency, "Missed frequency");
      MON_PARCER_IS_KEYWORD(read_frequency, "Hz")
      {
        measurment = EFrequencyMeasurment::Hz;
      }
      MON_PARCER_IS_KEYWORD(read_frequency, "SPP")
      {
        measurment = EFrequencyMeasurment::SPP;
      }
      frame->setFrequency(purpose, measurment, value);
      value      = 0;
      measurment = EFrequencyMeasurment::Hz;
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

#define MON_PARCER_RETURN_FIELD_TYPE(_name,_keyword,_return_value) \
  MON_PARCER_IS_KEYWORD(_name,_keyword) { return _return_value; }
EFieldDataType CDefinitionParcer::readFieldType()
{
  MON_PARCER_LOOP_BEGIN(read_value)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(read_value)
    {
      MON_PARCER_BUFFER_APPEND(read_value);
      MON_PARCER_LOOP_RESTART(read_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_value, '%')
    {
      MON_PARCER_BUFFER_APPEND(read_value);
      MON_PARCER_LOOP_RESTART(read_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(read_value)
    {
      MON_PARCER_ERROR(read_value, "Field type keyword must contain only alpha");
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(read_value)
    {
      MON_PARCER_LOOP_RESTART(read_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_value, ';')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(read_value, "Missed field type");
      MON_PARCER_RETURN_FIELD_TYPE(read_value, "%"       , EFieldDataType::Percent);
      MON_PARCER_RETURN_FIELD_TYPE(read_value, "bool"    , EFieldDataType::Bool   );
      MON_PARCER_RETURN_FIELD_TYPE(read_value, "short"   , EFieldDataType::Short  );
      MON_PARCER_RETURN_FIELD_TYPE(read_value, "ushort"  , EFieldDataType::UShort );
      MON_PARCER_RETURN_FIELD_TYPE(read_value, "integer" , EFieldDataType::Int    );
      MON_PARCER_RETURN_FIELD_TYPE(read_value, "uinteger", EFieldDataType::UInt   );
      MON_PARCER_RETURN_FIELD_TYPE(read_value, "long"    , EFieldDataType::Long   );
      MON_PARCER_RETURN_FIELD_TYPE(read_value, "ulong"   , EFieldDataType::ULong  );
      MON_PARCER_RETURN_FIELD_TYPE(read_value, "float"   , EFieldDataType::Float  );
      MON_PARCER_RETURN_FIELD_TYPE(read_value, "string"  , EFieldDataType::String );
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(read_value, "Unknown field type");
      MON_PARCER_BUFFER_RESET(read_value);
      MON_PARCER_LOOP_BREAK(read_value);
    }
  }
  MON_PARCER_LOOP_END(read_value);
  return EFieldDataType::Int;
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
