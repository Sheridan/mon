#ifndef CITEMS_H_MODEL
#define CITEMS_H_MODEL
#include <list>
#include <string>
#include <assert.h>
#include "defines/st.h"
#include "defines/mutex-helper.h"
#include "defines/logger-helper.h"
#include "defines/signals-helper.h"

namespace mon
{
namespace lib
{
namespace model
{

template<typename T>
class CItems
{
    MON_MUTEX_DECLARE(items)
  public:
    typedef std::list<T *> TItems;
    typedef std::list<std::string> TNames;

    CItems()
    {
      MON_MUTEX_INITIALIZE(items)
    }

    virtual ~CItems()
    {
      MON_MUTEX_LOCK(items);
      for(T *i : m_items)
      {
        delete i;
      }
      m_items.clear();
      m_names.clear();
      MON_MUTEX_UNLOCK(items);
      MON_MUTEX_DESTROY(items)
    }

    T *item(const std::string &name)
    {
      T *result = nullptr;
      MON_MUTEX_LOCK(items);
      for(T *tmpItem : m_items)
      {
        MON_LOG_DBG("item get " << tmpItem->name())
        if(name.compare(tmpItem->name()) == 0)
        {
          result = tmpItem;
          break;
        }
      }
      MON_MUTEX_UNLOCK(items);
      #ifdef MON_DEBUG
      if(result == nullptr)
      {
        MON_LOG_ERR("Some troubles with items... Pointer to null.");
        MON_ABORT;
      }
      #endif
      return result;
    }

    TNames names()
    {
      return m_names;
    }

  protected:
    void add(T *incomingItem)
    {
      MON_MUTEX_LOCK(items);
      MON_LOG_DBG("item add " << incomingItem->name())
      m_items.push_back(incomingItem);
      m_names.push_back(incomingItem->name());
      MON_MUTEX_UNLOCK(items);
    }

  private:
    TItems m_items;
    TNames m_names;
};

}
}
}

#endif // CITEMS_H_MODEL
