#ifndef _LUMINIS_DEVCON_COMMAND_LEFT_H_
#define _LUMINIS_DEVCON_COMMAND_LEFT_H_

#include <shell/command_impl.h>

celix_status_t commandLeft_create(bundle_context_pt bundle_context_ptr, command_pt *command_ptr);
celix_status_t commandLeft_destroy(command_pt *command_ptr);

void commandLeft_left(command_pt command, char *line, void (*out)(char *), void (*err)(char *));

#endif //_LUMINIS_DEVCON_COMMAND_LEFT_H_
