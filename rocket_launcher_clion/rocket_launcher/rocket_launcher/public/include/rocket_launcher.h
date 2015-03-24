//
// Created by Alexander Broekhuis on 17/03/2015.
//

#ifndef _LUMINIS_DEVCON_ROCKET_LAUNCHER_H_
#define _LUMINIS_DEVCON_ROCKET_LAUNCHER_H_

#include <celix_errno.h>

#define ROCKET_LAUNCHER "eu.luminis.devcon.RocketLauncher"

#define ROCKET_LAUNCHER_STOP "stop()V"
#define ROCKET_LAUNCHER_UP "up()V"
#define ROCKET_LAUNCHER_DOWN "down()V"
#define ROCKET_LAUNCHER_LEFT "left()V"
#define ROCKET_LAUNCHER_RIGHT "right()V"
#define ROCKET_LAUNCHER_FIRE "fire()V"
#define ROCKET_LAUNCHER_RESET "reset()V"

typedef struct rocket_launcher_component *rocket_launcher_component_pt;

typedef struct rocket_launcher_service {
    rocket_launcher_component_pt rocket_launcher_component_ptr;
    celix_status_t (*stop)(rocket_launcher_component_pt component);
    celix_status_t (*up)(rocket_launcher_component_pt component);
    celix_status_t (*down)(rocket_launcher_component_pt component);
    celix_status_t (*left)(rocket_launcher_component_pt component);
    celix_status_t (*right)(rocket_launcher_component_pt component);
    celix_status_t (*fire)(rocket_launcher_component_pt component);
    celix_status_t (*reset)(rocket_launcher_component_pt component);
} *rocket_launcher_service_pt;

#endif //_LUMINIS_DEVCON_ROCKET_LAUNCHER_H_
