//
// Created by Alexander Broekhuis on 19/03/2015.
//

#ifndef _LUMINIS_DEVCON_ROCKET_LAUNCHER_CONSOLE_H_
#define _LUMINIS_DEVCON_ROCKET_LAUNCHER_CONSOLE_H_

#include <celix_threads.h>
#include "rocket_launcher.h"

typedef struct cmd_handle {
    celix_thread_mutex_t lock;
    rocket_launcher_service_pt rocket_launcher_service_ptr;
} *cmd_handle_pt;

#endif //_LUMINIS_DEVCON_ROCKET_LAUNCHER_CONSOLE_H_
