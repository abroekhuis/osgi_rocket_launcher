//
// Created by Alexander Broekhuis on 19/03/2015.
//

#ifndef _LUMINIS_DEVCON_COMMAND_STOP_H_
#define _LUMINIS_DEVCON_COMMAND_STOP_H_

#include <shell/command_impl.h>

celix_status_t commandStop_create(bundle_context_pt bundle_context_ptr, command_pt *command_ptr);
celix_status_t commandStop_destroy(command_pt *command_ptr);

void commandStop_stop(command_pt command, char *line, void (*out)(char *), void (*err)(char *));

#endif //_LUMINIS_DEVCON_COMMAND_STOP_H_
