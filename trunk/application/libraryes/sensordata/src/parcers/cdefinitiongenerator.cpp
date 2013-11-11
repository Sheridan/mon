#include "cdefinitiongenerator.h"
#include "stl-helper.h"
#include "st.h"

#define MON_DEFINITION_GENERATOR_DEBUG_ENABLE
#ifdef MON_DEFINITION_GENERATOR_DEBUG_ENABLE
  #define MON_DEFINITION_GENERATOR_DEBUG(_msg) MON_LOG_DBG(_msg)
#else
  #define MON_DEFINITION_GENERATOR_DEBUG(_msg)
#endif

namespace mon
{
namespace lib
{
namespace sensordata
{

CDefinitionGenerator::CDefinitionGenerator(CDefinition *definition)
  : m_definition(definition)
{
  m_result = new mon::lib::base::CStringBuilder();
}


CDefinitionGenerator::~CDefinitionGenerator()
{
  delete m_result;
}

const std::string &CDefinitionGenerator::generate()
{
  MON_DEFINITION_GENERATOR_DEBUG("Generating definition start");
  TFramesNames framesNames = m_definition->frames();
  MON_STL_LIST_FOREACH(frames_names, TFramesNames, framesNames)
  {
    generateFrame(m_definition->frame(MON_STL_LIST_VALUE(frames_names)));
  }
  MON_DEFINITION_GENERATOR_DEBUG("Generating definition done");
  return m_result->string();
}

void CDefinitionGenerator::generateFrame(CFrame *frame)
{
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "'' start");
  (*m_result) << frame->name() << "{"
              "label:\"" << frame->label() << "\";"
              "type:";
  switch(frame->frameType())
  {
    case ftInformation: (*m_result) << "information"; break;
    case ftStatistic  : (*m_result) << "statistic"  ; break;
  }
  (*m_result) << ";";
  generateFrequencyes(frame);
  generateFlags(frame);
  generateTags(frame);
  generateFields(frame);
  (*m_result) << "}";
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' done");
}

void CDefinitionGenerator::generateFrequencyes(CFrame *frame)
{
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' frequency start");
  (*m_result) << "frequency:{"
              << "max:"     << frame->frequency(fpMax    )->asHz() << "Hz;"
              << "default:" << frame->frequency(fpDefault)->asHz() << "Hz;"
              << "}";
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' frequency done");
}

void CDefinitionGenerator::generateFlags(CFrame *frame)
{
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' flags start");
  (*m_result) << "flags:{"
              << (frame->hasFlag(ffAggregated)     ?  "aggregated;" : "")
              << (frame->hasFlag(ffCalculateTotal) ?  "calculateTotal;" : "")
              << "}";
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' flags done");
}

void CDefinitionGenerator::generateTags(CFrame *frame)
{
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' tags start");
  TTags t_tags = frame->tags();
  (*m_result) << "tags:{";
  MON_STL_SET_FOREACH(tags, TTags, t_tags)
  {
    (*m_result) << MON_STL_SET_VALUE(tags) << ";";
  }
  (*m_result) << "}";
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' tags done");
}

void CDefinitionGenerator::generateFields(CFrame *frame)
{
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' fields start");
  TFields t_fields = frame->fields();
  (*m_result) << "fields:{";
  MON_STL_LIST_FOREACH(field, TFields, t_fields)
  {
    generateField(MON_STL_LIST_VALUE(field));
  }
  (*m_result) << "}";
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' fields done");
}

void CDefinitionGenerator::generateField(CField *field)
{
  MON_DEFINITION_GENERATOR_DEBUG("Field '" << field->name() << "' start");
  (*m_result) << field->name() << ":{"
              << "label:\"" << field->label() << "\";"
              << "type:";
  switch (field->type())
  {
    case dtPercent:         (*m_result) << "%"       ; break;
    case dtBool:            (*m_result) << "bool"    ; break;
    case dtShort:           (*m_result) << "short"   ; break;
    case dtUnsignedShort:   (*m_result) << "ushort"  ; break;
    case dtInteger:         (*m_result) << "integer" ; break;
    case dtUnsignedIinteger:(*m_result) << "uinteger"; break;
    case dtLong:            (*m_result) << "long"    ; break;
    case dtUnsignedLong:    (*m_result) << "ulong"   ; break;
    case dtFloat:           (*m_result) << "float"   ; break;
    case dtString:          (*m_result) << "string"   ; break;
  }
  (*m_result) << ";description:\"" << field->description() << "\";"
              << "}";
  MON_DEFINITION_GENERATOR_DEBUG("Field '" << field->name() << "' done");
}

}
}
}
