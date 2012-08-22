/* %Id% */
#ifndef INFINITYCYCLEHELPER_H
#define INFINITYCYCLEHELPER_H

#define MON_INFINITY_LOOP_BEGIN_LABEL_NAME(_name) label_##_name##_infinity_loop_begin
#define MON_INFINITY_LOOP_END_LABEL_NAME(_name)   label_##_name##_infinity_loop_end

#define MON_INFINITY_LOOP_RESTART(_name) goto MON_INFINITY_LOOP_BEGIN_LABEL_NAME(_name);
#define MON_INFINITY_LOOP_BREAK(_name)   goto MON_INFINITY_LOOP_END_LABEL_NAME(_name);

#define MON_INFINITY_LOOP_BEGIN(_name) \
  MON_INFINITY_LOOP_RESTART(_name) \
  MON_INFINITY_LOOP_BEGIN_LABEL_NAME(_name): ; \
  for(;;) \
    {
#define MON_INFINITY_LOOP_END(_name) \
    } \
  MON_INFINITY_LOOP_BREAK(_name) \
  MON_INFINITY_LOOP_END_LABEL_NAME(_name): ;

#endif // INFINITYCYCLEHELPER_H
