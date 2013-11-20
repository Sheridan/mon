#include "libraryes/sensordata/parcers/cdefinitiongenerator.h"
#include "defines/st.h"

//#define MON_DEFINITION_GENERATOR_DEBUG_ENABLE
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
  for(auto &frames_names : framesNames)
  {
    generateFrame(m_definition->frame(frames_names));
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
  for(auto &tags : t_tags)
  {
    (*m_result) << tags << ";";
  }
  (*m_result) << "}";
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' tags done");
}

void CDefinitionGenerator::generateFields(CFrame *frame)
{
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "' fields start");
  TFields t_fields = frame->fields();
  (*m_result) << "fields:{";
  for(auto &field : t_fields)
  {
    generateField(field);
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
    case EFieldDataType::Percent: (*m_result) << "%"       ; break;
    case EFieldDataType::Bool:    (*m_result) << "bool"    ; break;
    case EFieldDataType::Short:   (*m_result) << "short"   ; break;
    case EFieldDataType::UShort:  (*m_result) << "ushort"  ; break;
    case EFieldDataType::Int:     (*m_result) << "integer" ; break;
    case EFieldDataType::UInt:    (*m_result) << "uinteger"; break;
    case EFieldDataType::Long:    (*m_result) << "long"    ; break;
    case EFieldDataType::ULong:   (*m_result) << "ulong"   ; break;
    case EFieldDataType::Float:   (*m_result) << "float"   ; break;
    case EFieldDataType::String:  (*m_result) << "string"  ; break;
  }
  (*m_result) << ";description:\"" << field->description() << "\";"
              << "}";
  MON_DEFINITION_GENERATOR_DEBUG("Field '" << field->name() << "' done");
}

}
}
}
