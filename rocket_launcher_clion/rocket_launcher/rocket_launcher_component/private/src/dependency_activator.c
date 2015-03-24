//
// Created by Alexander Broekhuis on 17/03/2015.
//

#include <stdlib.h>

#include <celix_errno.h>
#include <dm_activator_base.h>

#include <log_service/log_service.h>
#include <remote_constants.h>

#include "rocket_launcher_component.h"

typedef struct dactivator {
    dm_component_pt service_ptr;
    dm_service_dependency_pt log_service_dependency_ptr;

    rocket_launcher_component_pt rocket_launcher_component_ptr;
    rocket_launcher_service_pt rocket_launcher_service_ptr;
    properties_pt properties_ptr;
} *dactivator_pt;

celix_status_t dm_create(bundle_context_pt context, void **user_data_pptr) {
    celix_status_t status = CELIX_SUCCESS;

    dactivator_pt activator = calloc(1, sizeof(*activator));

    *user_data_pptr = activator;

    return status;
}

celix_status_t dm_init(void * user_data_ptr, bundle_context_pt context, dm_dependency_manager_pt manager) {
    celix_status_t status = CELIX_SUCCESS;

    dactivator_pt activator_ptr = user_data_ptr;

    rocketLauncher_create(&activator_ptr->rocket_launcher_component_ptr);

    component_create(context, manager, &activator_ptr->service_ptr);
    component_setImplementation(activator_ptr->service_ptr, activator_ptr->rocket_launcher_component_ptr);
//    component_setCallbacks(activator_ptr->service_ptr, rocketLauncher_componentInit, rocketLauncher_componentStart,
//            rocketLauncher_componentStop, rocketLauncher_componentExit);

    activator_ptr->rocket_launcher_service_ptr = calloc(1, sizeof(*activator_ptr->rocket_launcher_service_ptr));
    activator_ptr->rocket_launcher_service_ptr->rocket_launcher_component_ptr = activator_ptr->rocket_launcher_component_ptr;
    activator_ptr->rocket_launcher_service_ptr->stop = rocketLauncher_stop;
    activator_ptr->rocket_launcher_service_ptr->up = rocketLauncher_up;
    activator_ptr->rocket_launcher_service_ptr->down = rocketLauncher_down;
    activator_ptr->rocket_launcher_service_ptr->left = rocketLauncher_left;
    activator_ptr->rocket_launcher_service_ptr->right = rocketLauncher_right;
    activator_ptr->rocket_launcher_service_ptr->fire = rocketLauncher_fire;
    activator_ptr->rocket_launcher_service_ptr->reset = rocketLauncher_reset;

    activator_ptr->properties_ptr = properties_create();
    properties_set(activator_ptr->properties_ptr, (char *) OSGI_RSA_SERVICE_EXPORTED_INTERFACES, (char *) ROCKET_LAUNCHER);

    component_setInterface(activator_ptr->service_ptr, ROCKET_LAUNCHER, activator_ptr->rocket_launcher_service_ptr, activator_ptr->properties_ptr);

    serviceDependency_create(&activator_ptr->log_service_dependency_ptr);
    serviceDependency_setRequired(activator_ptr->log_service_dependency_ptr, true);
    serviceDependency_setService(activator_ptr->log_service_dependency_ptr, (char *) OSGI_LOGSERVICE_NAME, NULL);
    serviceDependency_setAutoConfigure(activator_ptr->log_service_dependency_ptr,
            &activator_ptr->rocket_launcher_component_ptr->log_service_lock,
            (void **) &activator_ptr->rocket_launcher_component_ptr->log_service_ptr);

    component_addServiceDependency(activator_ptr->service_ptr, activator_ptr->log_service_dependency_ptr, NULL);

    dependencyManager_add(manager, activator_ptr->service_ptr);

    return status;
}

celix_status_t dm_destroy(void * user_data_ptr, bundle_context_pt context, dm_dependency_manager_pt manager) {
    dactivator_pt activator_ptr = user_data_ptr;

    dependencyManager_remove(manager, activator_ptr->service_ptr);

    component_removeServiceDependency(activator_ptr->service_ptr, activator_ptr->log_service_dependency_ptr);
    serviceDependency_destroy(&activator_ptr->log_service_dependency_ptr);

    component_destroy(&activator_ptr->service_ptr);

    rocketLauncher_destroy(&activator_ptr->rocket_launcher_component_ptr);

    return CELIX_SUCCESS;
}

