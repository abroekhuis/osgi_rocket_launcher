//
// Created by Alexander Broekhuis on 17/03/2015.
//
#include <stdlib.h>

#include "rocket_launcher_component.h"

celix_status_t rocketLauncher_create(rocket_launcher_component_pt *rocket_launcher_component_ptr) {
    celix_status_t status = CELIX_SUCCESS;

    *rocket_launcher_component_ptr = calloc(1, sizeof(**rocket_launcher_component_ptr));
    if (!*rocket_launcher_component_ptr) {
        status = CELIX_ENOMEM;
    }

    if (status == CELIX_SUCCESS) {
    }

    return status;
}

celix_status_t rocketLauncher_destroy(rocket_launcher_component_pt *rocket_launcher_component_ptr) {
    celix_status_t status = CELIX_SUCCESS;

    free(*rocket_launcher_component_ptr);

    return status;
}

celix_status_t rocketLauncher_componentInit(void *_ptr) {
    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_componentStart(void *_ptr) {
    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_componentStop(void *_ptr) {
    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_componentExit(void *_ptr) {
    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_stop(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Stop");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_up(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Up");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_down(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Down");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_left(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Left");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_right(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Right");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_fire(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Fire");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_reset(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Reset");
    }

    return CELIX_SUCCESS;
}