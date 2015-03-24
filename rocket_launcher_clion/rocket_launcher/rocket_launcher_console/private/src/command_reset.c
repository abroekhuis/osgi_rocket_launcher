#include <stdlib.h>

#include "command_reset.h"
#include "rocket_launcher_console.h"

celix_status_t commandReset_create(bundle_context_pt bundle_context_ptr, command_pt *command_ptr) {
    celix_status_t status = CELIX_SUCCESS;

    *command_ptr = calloc(1, sizeof(**command_ptr));
    if (!*command_ptr) {
        status = CELIX_ENOMEM;
    }

    if (status == CELIX_SUCCESS) {
        (*command_ptr)->bundleContext = bundle_context_ptr;
        (*command_ptr)->name = "rocketLauncher_reset";
        (*command_ptr)->shortDescription = "Reset the rocketlauncher";
        (*command_ptr)->usage = "rocketLauncher_reset";
        (*command_ptr)->executeCommand = commandReset_reset;
        (*command_ptr)->handle = calloc(1, sizeof(struct cmd_handle));
    }

    return status;
}

celix_status_t commandReset_destroy(command_pt *command_ptr) {
    free(*command_ptr);
    return CELIX_SUCCESS;
}

void commandReset_reset(command_pt command, char *line, void (*out)(char *), void (*err)(char *)) {
    cmd_handle_pt handle = command->handle;
    printf("SRV %p\n", handle->rocket_launcher_service_ptr->reset);
    celixThreadMutex_lock(&handle->lock);
    handle->rocket_launcher_service_ptr->reset(handle->rocket_launcher_service_ptr->rocket_launcher_component_ptr);
    celixThreadMutex_unlock(&handle->lock);
    printf("SRV %p\n", handle->rocket_launcher_service_ptr);
}