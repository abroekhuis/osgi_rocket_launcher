#ifndef _LUMINIS_DEVCON_COMMAND_FIRE_H_
#define _LUMINIS_DEVCON_COMMAND_FIRE_H_

#include <shell/command_impl.h>

celix_status_t commandFire_create(bundle_context_pt bundle_context_ptr, command_pt *command_ptr);
celix_status_t commandFire_destroy(command_pt *command_ptr);

void commandFire_fire(command_pt command, char *line, void (*out)(char *), void (*err)(char *));

#endif //_LUMINIS_DEVCON_COMMAND_FIRE_H_
