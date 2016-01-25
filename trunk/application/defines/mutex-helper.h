#ifndef MUTEXHELPER_H
#define MUTEXHELPER_H
#include <pthread.h>

#define MON_MUTEX_NAME(_name)       m_mutex_##_name
#define MON_MUTEX_DECLARE(_name)    private: mutable pthread_mutex_t MON_MUTEX_NAME(_name);
#define MON_MUTEX_INITIALIZE(_name) pthread_mutex_init(&MON_MUTEX_NAME(_name), NULL);
#define MON_MUTEX_DESTROY(_name)    pthread_mutex_destroy(&MON_MUTEX_NAME(_name));
#define MON_MUTEX_LOCK(_name)       pthread_mutex_lock  (&MON_MUTEX_NAME(_name));
#define MON_MUTEX_UNLOCK(_name)     pthread_mutex_unlock(&MON_MUTEX_NAME(_name));

#endif // MUTEXHELPER_H
