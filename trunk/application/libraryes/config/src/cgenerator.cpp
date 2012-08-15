#include "cgenerator.h"
#include "st.h"
#include <stdlib.h>
namespace mon
{
namespace lib
{
namespace config
{

CGenerator::CGenerator(const std::string &filename, CFolder *root) : m_filename(filename), m_root(root)
{
  m_error = false;
  m_file = fopen(m_filename.c_str(), "w");
  if(m_file == NULL)
  {
    m_error = true;
    MON_PRINT_FILEOP_ERRNO(m_filename, "Open");
  }
}

CGenerator::~CGenerator()
{
  fclose(m_file);
}

void CGenerator::generate()
{
  if(m_error) { return; }

  MON_LOG_NFO("Writing config to " << m_filename);
  writeFolder(m_root);
  fprintf(m_file, "\n");
  MON_LOG_DBG("Writing config to " << m_filename << " done");
}

void CGenerator::writeFolder(CFolder *folder)
{
  MON_LOG_DBG("Enter folder: " << folder->name())
  int childsCount = folder->filesCount() + folder->foldersCount();
  if(childsCount == 0) { return; }

  bool hasOneChild = childsCount == 1;
  if(!folder->name().empty())
  {
    if(folder->parent() && (folder->parent()->filesCount()+folder->parent()->foldersCount()) > 1)
    {
      writeIndent(folder->level());
    }
    if(hasOneChild)
    {
      fprintf(m_file, "%s.", folder->name().c_str());
    }
    else
    {
      fprintf(m_file, "%s", folder->name().c_str());
      fprintf(m_file, "\n");
      writeIndent(folder->level());
      fprintf(m_file, "{");
      fprintf(m_file, "\n");
    }

  }

  MON_OPTION_FOREACH_FOLDER(child_folder, folder)
  {
    writeFolder(*child_folder);
  }

  MON_OPTION_FOREACH_FILE(child_file, folder)
  {
    writeFile(*child_file);
  }

  if(!folder->name().empty() && !hasOneChild)
  {
    writeIndent(folder->level());
    fprintf(m_file, "}");
    fprintf(m_file, "\n");
  }
  MON_LOG_DBG("Leave folder: " << folder->name())
}

void CGenerator::writeFile(CFile *file)
{
  MON_LOG_DBG("Enter file: " << file->name())
  writeIndent(file->level());
  fprintf(m_file, "%s=", file->name().c_str());
  switch(file->contentType())
  {
    case ctString: fprintf(m_file, "\"%s\";", replaceSpetial(file->toString()).c_str()); break;
    default: fprintf(m_file, "%s;", file->toString().c_str()); break;
  }
  fprintf(m_file, "\n");
  MON_LOG_DBG("Leave file: " << file->name())
}

std::string CGenerator::replaceSpetial(const std::string &source)
{
//  return source;
  std::string result = "";
  for(std::string::const_iterator si = source.begin(); si != source.end(); ++si)
  {
    switch(*si)
    {
      case '\\': result+="\\\\"; break;
      case '\n': result+="\\n" ; break;
      case '\t': result+="\\t" ; break;
      case '\a': result+="\\a" ; break;
      case '\b': result+="\\b" ; break;
      case '\r': result+="\\r" ; break;
      case  '"': result+="\\\""; break;
      default: result += *si;
    }
  }
  return result;
}

#define MON_INDENT_CHARACTER " "
#define MON_INDENT_COUNT      2

void CGenerator::writeIndent(const int &indent)
{
  for (int i = 0; i < indent*MON_INDENT_COUNT; i++)
  {
    fprintf(m_file, MON_INDENT_CHARACTER);
  }
}

}
}
}
