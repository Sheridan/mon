/* %Id% */
#ifndef THREADSHELPER_H_INCLUDED
#define THREADSHELPER_H_INCLUDED
#include <pthread.h>
#include "st.h"
#include "signals-helper.h"

#define MON_THREADED_FUNCTION_DECLARE(_name) \
  public: \
    void _name(); \
    void run_thread##_name(); \
  private: \
    bool thread_is_active##_name; \
    pthread_t thread_id_##_name; \
    void abort_thread_##_name();

#define MON_THREADED_FUNCTION_INIT(_name) thread_is_active##_name = false

#define MON_THREADED_FUNCTION_IMPLEMENT(_class,_name) \
void * thread_##_name(void *data) \
{ \
  MON_LOG_DBG("Thread " #_name " started..."); \
  (reinterpret_cast<_class *>(data))->run_thread##_name(); \
  return NULL; \
} \
void _class::_name() \
{ \
  MON_LOG_DBG("Thread " #_name " starting..."); \
  errno = pthread_create(&thread_id_##_name, NULL, thread_##_name, reinterpret_cast<void *>(this)); \
  thread_is_active##_name = errno == 0; \
  if(thread_is_active##_name) \
  { \
    MON_LOG_DBG("Thread " #_name " starting done..."); \
  } \
  else \
  { \
    MON_PRINT_ERRNO("Thread " #_name " starting failed.") \
    MON_ABORT; \
  } \
} \
void _class::abort_thread_##_name() \
{ \
  if(thread_is_active##_name) \
  { \
    MON_LOG_DBG("Thread " #_name " terminating..."); \
    errno = pthread_cancel(thread_id_##_name); pthread_join(thread_id_##_name, NULL); \
    if(errno) { MON_PRINT_ERRNO("Thread " #_name " terminating failed."); } \
    else { MON_LOG_DBG("Thread " #_name " terminated..."); } \
    return; \
  } \
  MON_LOG_DBG("Thread " #_name " not active, no need termination"); \
} \
void _class::run_thread##_name()

#define MON_THREADED_FUNCTION_ABORT(_name) abort_thread_##_name();

#endif // THREADSHELPER_H_INCLUDED
