#include "cdefinitiongenerator.h"
#include "stl-helper.h"
#include "st.h"

#define MON_CONFIG_GENERATOR_DEBUG_ENABLE
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
  return m_result->msg();
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

  (*m_result) << "}";
  MON_DEFINITION_GENERATOR_DEBUG("Frame '" << frame->name() << "'' done");
}


}
}
}
