//
// Created by Alexander Broekhuis on 19/03/2015.
//

#include <stdlib.h>

#include <celix_errno.h>
#include <dm_activator_base.h>

#include <shell/command.h>
#include <rocket_launcher_console.h>

#include "command_stop.h"
#include "command_up.h"
#include "command_down.h"
#include "command_left.h"
#include "command_right.h"
#include "command_fire.h"
#include "command_reset.h"

typedef struct cmd {
    command_pt command_ptr;
    command_service_pt service_ptr;
    dm_component_pt component_ptr;
    dm_service_dependency_pt rocket_launcher_dependency_ptr;
} cmd_t;

typedef struct dactivator {
    bundle_context_pt bundle_context_ptr;

    cmd_t stop;
    cmd_t up;
    cmd_t down;
    cmd_t left;
    cmd_t right;
    cmd_t fire;
    cmd_t reset;

} *dactivator_pt;

static celix_status_t dm_registerCommand(dactivator_pt activator_ptr, dm_dependency_manager_pt dependency_manager_ptr,
        command_pt command_ptr, dm_component_pt *component_ptr, command_service_pt *command_service_ptr,
        dm_service_dependency_pt *dependency_ptr);
static celix_status_t dm_unregisterCommand(dactivator_pt activator_ptr, dm_dependency_manager_pt manager_ptr,
        dm_component_pt component_ptr, dm_service_dependency_pt dependency_ptr);

celix_status_t dm_create(bundle_context_pt context, void **user_data_pptr) {
    celix_status_t status = CELIX_SUCCESS;

    dactivator_pt activator = calloc(1, sizeof(*activator));

    activator->bundle_context_ptr = context;

    *user_data_pptr = activator;

    return status;
}

celix_status_t dm_init(void * user_data_ptr, bundle_context_pt context, dm_dependency_manager_pt manager) {
    celix_status_t status = CELIX_SUCCESS;

    dactivator_pt activator_ptr = user_data_ptr;

    commandStop_create(context, &activator_ptr->stop.command_ptr);
    dm_registerCommand(activator_ptr, manager, activator_ptr->stop.command_ptr,
            &activator_ptr->stop.component_ptr, &activator_ptr->stop.service_ptr,
            &activator_ptr->stop.rocket_launcher_dependency_ptr);
    dependencyManager_add(manager, activator_ptr->stop.component_ptr);

    commandUp_create(context, &activator_ptr->up.command_ptr);
    dm_registerCommand(activator_ptr, manager, activator_ptr->up.command_ptr,
            &activator_ptr->up.component_ptr, &activator_ptr->up.service_ptr,
            &activator_ptr->up.rocket_launcher_dependency_ptr);
    dependencyManager_add(manager, activator_ptr->up.component_ptr);

    commandDown_create(context, &activator_ptr->down.command_ptr);
    dm_registerCommand(activator_ptr, manager, activator_ptr->down.command_ptr,
            &activator_ptr->down.component_ptr, &activator_ptr->down.service_ptr,
            &activator_ptr->down.rocket_launcher_dependency_ptr);
    dependencyManager_add(manager, activator_ptr->down.component_ptr);

    commandLeft_create(context, &activator_ptr->left.command_ptr);
    dm_registerCommand(activator_ptr, manager, activator_ptr->left.command_ptr,
            &activator_ptr->left.component_ptr, &activator_ptr->left.service_ptr,
            &activator_ptr->left.rocket_launcher_dependency_ptr);
    dependencyManager_add(manager, activator_ptr->left.component_ptr);

    commandRight_create(context, &activator_ptr->right.command_ptr);
    dm_registerCommand(activator_ptr, manager, activator_ptr->right.command_ptr,
            &activator_ptr->right.component_ptr, &activator_ptr->right.service_ptr,
            &activator_ptr->right.rocket_launcher_dependency_ptr);
    dependencyManager_add(manager, activator_ptr->right.component_ptr);

    commandFire_create(context, &activator_ptr->fire.command_ptr);
    dm_registerCommand(activator_ptr, manager, activator_ptr->fire.command_ptr,
            &activator_ptr->fire.component_ptr, &activator_ptr->fire.service_ptr,
            &activator_ptr->fire.rocket_launcher_dependency_ptr);
    dependencyManager_add(manager, activator_ptr->fire.component_ptr);

    commandReset_create(context, &activator_ptr->reset.command_ptr);
    dm_registerCommand(activator_ptr, manager, activator_ptr->reset.command_ptr,
            &activator_ptr->reset.component_ptr, &activator_ptr->reset.service_ptr,
            &activator_ptr->reset.rocket_launcher_dependency_ptr);
    dependencyManager_add(manager, activator_ptr->reset.component_ptr);

    return status;
}

static celix_status_t dm_registerCommand(dactivator_pt activator_ptr, dm_dependency_manager_pt dependency_manager_ptr,
        command_pt command_ptr, dm_component_pt *component_ptr, command_service_pt *command_service_ptr,
        dm_service_dependency_pt *dependency_ptr) {
    celix_status_t status = CELIX_SUCCESS;

    bundle_context_pt bundle_context_ptr = activator_ptr->bundle_context_ptr;

    cmd_handle_pt cmd_handle_ptr = command_ptr->handle;
    component_create(bundle_context_ptr, dependency_manager_ptr, component_ptr);
    component_setImplementation(*component_ptr, command_ptr);

    *command_service_ptr = calloc(1, sizeof(**command_service_ptr));
    if (*command_service_ptr) {
        (*command_service_ptr)->command = command_ptr;
        (*command_service_ptr)->executeCommand = command_ptr->executeCommand;
        (*command_service_ptr)->getName = command_getName;
        (*command_service_ptr)->getShortDescription = command_getShortDescription;
        (*command_service_ptr)->getUsage = command_getUsage;
    }

    component_setInterface(*component_ptr, (char *) OSGI_SHELL_COMMAND_SERVICE_NAME, *command_service_ptr, NULL);

    serviceDependency_create(dependency_ptr);
    serviceDependency_setRequired(*dependency_ptr, true);
    serviceDependency_setService(*dependency_ptr, (char *) ROCKET_LAUNCHER, NULL);
    serviceDependency_setAutoConfigure(*dependency_ptr,
            &cmd_handle_ptr->lock,
            (void **) &cmd_handle_ptr->rocket_launcher_service_ptr);

    component_addServiceDependency(*component_ptr, *dependency_ptr, NULL);

    return status;
}

celix_status_t dm_destroy(void * user_data_ptr, bundle_context_pt context, dm_dependency_manager_pt manager) {
    dactivator_pt activator_ptr = user_data_ptr;

    dm_unregisterCommand(activator_ptr, manager, activator_ptr->stop.component_ptr,
            activator_ptr->stop.rocket_launcher_dependency_ptr);
    commandStop_destroy(&activator_ptr->stop.command_ptr);
    
    dm_unregisterCommand(activator_ptr, manager, activator_ptr->up.component_ptr,
            activator_ptr->up.rocket_launcher_dependency_ptr);
    commandUp_destroy(&activator_ptr->up.command_ptr);
    
    dm_unregisterCommand(activator_ptr, manager, activator_ptr->down.component_ptr,
            activator_ptr->down.rocket_launcher_dependency_ptr);
    commandDown_destroy(&activator_ptr->down.command_ptr);

    dm_unregisterCommand(activator_ptr, manager, activator_ptr->left.component_ptr,
            activator_ptr->left.rocket_launcher_dependency_ptr);
    commandLeft_destroy(&activator_ptr->left.command_ptr);

    dm_unregisterCommand(activator_ptr, manager, activator_ptr->right.component_ptr,
            activator_ptr->right.rocket_launcher_dependency_ptr);
    commandRight_destroy(&activator_ptr->right.command_ptr);

    dm_unregisterCommand(activator_ptr, manager, activator_ptr->fire.component_ptr,
            activator_ptr->fire.rocket_launcher_dependency_ptr);
    commandFire_destroy(&activator_ptr->fire.command_ptr);

    dm_unregisterCommand(activator_ptr, manager, activator_ptr->reset.component_ptr,
            activator_ptr->reset.rocket_launcher_dependency_ptr);
    commandReset_destroy(&activator_ptr->reset.command_ptr);

    return CELIX_SUCCESS;
}

static celix_status_t dm_unregisterCommand(dactivator_pt activator_ptr, dm_dependency_manager_pt manager_ptr,
        dm_component_pt component_ptr, dm_service_dependency_pt dependency_ptr) {
    celix_status_t status = CELIX_SUCCESS;

    dependencyManager_remove(manager_ptr, component_ptr);

    component_removeServiceDependency(component_ptr, dependency_ptr);
    serviceDependency_destroy(&dependency_ptr);

    component_destroy(&component_ptr);

    return status;
}