#ifndef SIGHELP_H
#define SIGHELP_H
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define MON_SIGNAL_HANDLER_NAME(_signal) sig_hand_##_signal
#define MON_SIGNAL_HANDLER(_signal) void MON_SIGNAL_HANDLER_NAME(_signal)(int signal)
#define MON_HANDLE_SIGNAL(_signal) (void) signal(_signal, MON_SIGNAL_HANDLER_NAME(_signal));
#define MON_SIGNAL_LOOP for(;;) { pause(); }
#define MON_ABORT { if(raise(SIGTERM)) { abort(); } }

#endif // SIGHELP_H
