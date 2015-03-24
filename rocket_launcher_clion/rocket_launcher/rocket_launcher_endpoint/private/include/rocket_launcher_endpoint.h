//
// Created by Alexander Broekhuis on 19/03/2015.
//

#ifndef _LUMINIS_DEVCON_ROCKET_LAUNCHER_ENDPOINT_H_
#define _LUMINIS_DEVCON_ROCKET_LAUNCHER_ENDPOINT_H_

#include <celix_errno.h>
#include <remote_service_admin/remote_endpoint_impl.h>

celix_status_t rocketLauncherEndpoint_create(remote_endpoint_pt *endpoint);
celix_status_t rocketLauncherEndpoint_destroy(remote_endpoint_pt *endpoint);

celix_status_t rocketLauncherEndpoint_setService(remote_endpoint_pt endpoint, void *service);
celix_status_t rocketLauncherEndpoint_handleRequest(remote_endpoint_pt endpoint, char *data, char **reply);

#endif //_LUMINIS_DEVCON_ROCKET_LAUNCHER_ENDPOINT_H_
