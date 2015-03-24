#include <stdlib.h>

#include "command_fire.h"
#include "rocket_launcher_console.h"

celix_status_t commandFire_create(bundle_context_pt bundle_context_ptr, command_pt *command_ptr) {
    celix_status_t status = CELIX_SUCCESS;

    *command_ptr = calloc(1, sizeof(**command_ptr));
    if (!*command_ptr) {
        status = CELIX_ENOMEM;
    }

    if (status == CELIX_SUCCESS) {
        (*command_ptr)->bundleContext = bundle_context_ptr;
        (*command_ptr)->name = "rocketLauncher_fire";
        (*command_ptr)->shortDescription = "Fire the rocketlauncher";
        (*command_ptr)->usage = "rocketLauncher_fire";
        (*command_ptr)->executeCommand = commandFire_fire;
        (*command_ptr)->handle = calloc(1, sizeof(struct cmd_handle));
    }

    return status;
}

celix_status_t commandFire_destroy(command_pt *command_ptr) {
    free(*command_ptr);
    return CELIX_SUCCESS;
}

void commandFire_fire(command_pt command, char *line, void (*out)(char *), void (*err)(char *)) {
    cmd_handle_pt handle = command->handle;
    printf("SRV %p\n", handle->rocket_launcher_service_ptr->fire);
    celixThreadMutex_lock(&handle->lock);
    handle->rocket_launcher_service_ptr->fire(handle->rocket_launcher_service_ptr->rocket_launcher_component_ptr);
    celixThreadMutex_unlock(&handle->lock);
    printf("SRV %p\n", handle->rocket_launcher_service_ptr);
}