//
// Created by Alexander Broekhuis on 19/03/2015.
//

#include <stdlib.h>

#include <dm_activator_base.h>

#include "rocket_launcher.h"
#include "rocket_launcher_endpoint.h"

typedef struct dactivator {
    properties_pt properties_ptr;
    dm_component_pt rocket_launcher_endpoint_component_ptr;
    remote_endpoint_pt endpoint_ptr;
    remote_endpoint_service_pt endpoint_service_ptr;
} *dactivator_pt;

celix_status_t dm_create(bundle_context_pt context, void **user_data_pptr) {
    celix_status_t status = CELIX_SUCCESS;

    dactivator_pt activator = calloc(1, sizeof(*activator));
    activator->rocket_launcher_endpoint_component_ptr = NULL;
    activator->properties_ptr = NULL;
    activator->endpoint_ptr = NULL;
    activator->endpoint_service_ptr = NULL;

    *user_data_pptr = activator;

    return status;
}

celix_status_t dm_init(void * user_data_ptr, bundle_context_pt context, dm_dependency_manager_pt manager) {
    celix_status_t status = CELIX_SUCCESS;

    dactivator_pt activator_ptr = user_data_ptr;

    rocketLauncherEndpoint_create(&activator_ptr->endpoint_ptr);
    component_create(context, manager, &activator_ptr->rocket_launcher_endpoint_component_ptr);
    component_setImplementation(activator_ptr->rocket_launcher_endpoint_component_ptr, activator_ptr->endpoint_ptr);

    activator_ptr->endpoint_service_ptr = calloc(1, sizeof(*activator_ptr->endpoint_service_ptr));
    if (activator_ptr->endpoint_service_ptr) {
        activator_ptr->endpoint_service_ptr->endpoint = activator_ptr->endpoint_ptr;
        activator_ptr->endpoint_service_ptr->handleRequest = rocketLauncherEndpoint_handleRequest;
        activator_ptr->endpoint_service_ptr->setService = rocketLauncherEndpoint_setService;
    }

    activator_ptr->properties_ptr = properties_create();
    properties_set(activator_ptr->properties_ptr, (char *) "remote.interface", (char *) ROCKET_LAUNCHER);

    component_setInterface(activator_ptr->rocket_launcher_endpoint_component_ptr, (char *) OSGI_RSA_REMOTE_ENDPOINT,
            activator_ptr->endpoint_service_ptr, activator_ptr->properties_ptr);

    dependencyManager_add(manager, activator_ptr->rocket_launcher_endpoint_component_ptr);

    return status;
}

celix_status_t dm_destroy(void * user_data_ptr, bundle_context_pt context, dm_dependency_manager_pt manager) {
    dactivator_pt activator_ptr = user_data_ptr;

    dependencyManager_remove(manager, activator_ptr->rocket_launcher_endpoint_component_ptr);
//
//    component_removeServiceDependency(activator_ptr->service_ptr, activator_ptr->log_service_dependency_ptr);
//    serviceDependency_destroy(&activator_ptr->log_service_dependency_ptr);
//
    component_destroy(&activator_ptr->rocket_launcher_endpoint_component_ptr);

    rocketLauncherEndpoint_destroy(&activator_ptr->endpoint_ptr);

    return CELIX_SUCCESS;
}