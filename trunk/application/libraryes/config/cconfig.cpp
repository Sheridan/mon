/* %Id% */
#include "defines/st.h"
#include "libraryes/config/cconfig.h"
#include "libraryes/config/rw/cconfigurationparcer.h"
#include "libraryes/config/rw/cconfigurationgenerator.h"


namespace mon
{
namespace lib
{
namespace config
{

CConfig::CConfig()
{
    m_root = new CFolder();
    cdRoot();
}

CConfig::~CConfig()
{
    delete m_root;
    m_pwd = nullptr;
}

void CConfig::load(const std::string &filename)
{
  m_base_filename = filename;
  CConfigurationParcer p = {m_base_filename, m_root};
  p.parce();
}

void CConfig::save(const std::string &filename)
{
  m_run_filename = filename;
  CConfigurationGenerator g = {m_run_filename, m_root};
  g.generate();
}

void CConfig::cd    (CFolder *val) { m_pwd = val   ; }
void CConfig::cdRoot(            ) { m_pwd = m_root; }

bool          CConfig::containsFolder(const std::string & name) { return m_pwd->containsFolder(name); }
int           CConfig::foldersCount  (                        ) { return m_pwd->foldersCount  (    ); }
TFoldersList  CConfig::folders       (                        ) { return m_pwd->folders       (    ); }
CFolder     * CConfig::folder        (const std::string & name) { return m_pwd->folder        (name); }

bool          CConfig::containsFile  (const std::string & name) { return m_pwd->containsFile  (name); }
int           CConfig::filesCount    (                        ) { return m_pwd->filesCount    (    ); }
TFilesList    CConfig::files         (                        ) { return m_pwd->files         (    ); }
CFile       * CConfig::file          (const std::string & name) { return m_pwd->file          (name); }

CFolder     * CConfig::root          (                        ) { return m_root                     ; }
}
}
}
