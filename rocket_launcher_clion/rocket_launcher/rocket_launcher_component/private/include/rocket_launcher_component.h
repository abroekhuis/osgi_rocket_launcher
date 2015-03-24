//
// Created by Alexander Broekhuis on 17/03/2015.
//

#ifndef _LUMINIS_DEVCON_ROCKET_LAUNCHER_COMPONENT_H_
#define _LUMINIS_DEVCON_ROCKET_LAUNCHER_COMPONENT_H_

#include <log_service/log_service.h>

#include "rocket_launcher.h"

struct rocket_launcher_component {
    log_service_pt log_service_ptr;
    celix_thread_mutex_t log_service_lock;
};

celix_status_t rocketLauncher_create(rocket_launcher_component_pt *rocket_launcher_component_ptr);
celix_status_t rocketLauncher_destroy(rocket_launcher_component_pt *rocket_launcher_component_ptr);

celix_status_t rocketLauncher_componentInit(void *_ptr);
celix_status_t rocketLauncher_componentStart(void *_ptr);
celix_status_t rocketLauncher_componentStop(void *_ptr);
celix_status_t rocketLauncher_componentExit(void *_ptr);

celix_status_t rocketLauncher_stop(rocket_launcher_component_pt component);
celix_status_t rocketLauncher_up(rocket_launcher_component_pt component);
celix_status_t rocketLauncher_down(rocket_launcher_component_pt component);
celix_status_t rocketLauncher_left(rocket_launcher_component_pt component);
celix_status_t rocketLauncher_right(rocket_launcher_component_pt component);
celix_status_t rocketLauncher_fire(rocket_launcher_component_pt component);
celix_status_t rocketLauncher_reset(rocket_launcher_component_pt component);

#endif //_LUMINIS_DEVCON_ROCKET_LAUNCHER_COMPONENT_H_
