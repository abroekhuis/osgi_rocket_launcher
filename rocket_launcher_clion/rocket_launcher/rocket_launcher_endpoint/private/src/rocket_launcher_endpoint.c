#include <stdlib.h>
#include <string.h>

#include <jansson.h>

#include <log_helper.h>

#include "rocket_launcher_endpoint.h"
#include "rocket_launcher.h"

static celix_status_t rocketLauncherEndpoint_command(remote_endpoint_pt endpoint_ptr, json_t *data_ptr, celix_status_t  (*_fptr)(rocket_launcher_component_pt), char **reply_pstr);

celix_status_t rocketLauncherEndpoint_create(remote_endpoint_pt *endpoint) {
    celix_status_t status = CELIX_SUCCESS;
    *endpoint = calloc(1, sizeof(**endpoint));
    if (!*endpoint) {
        status = CELIX_ENOMEM;
    } else {
        (*endpoint)->service = NULL;
    }

    return status;
}

celix_status_t rocketLauncherEndpoint_destroy(remote_endpoint_pt *endpoint) {
    celix_status_t status = CELIX_SUCCESS;

    if (*endpoint) {
        free(*endpoint);
        *endpoint = NULL;
    }

    return status;
}

celix_status_t rocketLauncherEndpoint_setService(remote_endpoint_pt endpoint_ptr, void * service_ptr)
{
    endpoint_ptr->service = service_ptr;
    return CELIX_SUCCESS;
}

celix_status_t rocketLauncherEndpoint_handleRequest(remote_endpoint_pt endpoint_ptr, char * data_str, char ** reply_pstr)
{
    celix_status_t status = CELIX_SUCCESS;

    json_t *      root_ptr = NULL;
    const char *  sig_str  = NULL;
    json_error_t error;

    memset(&error, 0, sizeof (error) );

    if (!endpoint_ptr || !endpoint_ptr->service || !data_str || (data_str[0] == '\0') || !reply_pstr)
    {
        status = CELIX_ILLEGAL_ARGUMENT;
    }

    if (status == CELIX_SUCCESS)
    {
        root_ptr = json_loads(data_str, 0, &error);
        if (!json_is_object(root_ptr) )
        {
            status = CELIX_BUNDLE_EXCEPTION;
        }
    }

    if (status == CELIX_SUCCESS)
    {
        if ( (json_unpack(root_ptr, "{s:s}", "m", &sig_str) != 0)
                || !sig_str || (sig_str[0] == '\0') )
        {
            status = CELIX_BUNDLE_EXCEPTION;
        }
    }

    if (status == CELIX_SUCCESS)
    {
        rocket_launcher_service_pt service_ptr = endpoint_ptr->service;

        if (strcmp(sig_str, ROCKET_LAUNCHER_STOP) == 0)
        {
            status = rocketLauncherEndpoint_command(endpoint_ptr, root_ptr, service_ptr->stop, reply_pstr);
        }
        else if (strcmp(sig_str, ROCKET_LAUNCHER_UP) == 0)
        {
            status = rocketLauncherEndpoint_command(endpoint_ptr, root_ptr, service_ptr->up, reply_pstr);
        }
        else if (strcmp(sig_str, ROCKET_LAUNCHER_DOWN) == 0)
        {
            status = rocketLauncherEndpoint_command(endpoint_ptr, root_ptr, service_ptr->down, reply_pstr);
        }
        else if (strcmp(sig_str, ROCKET_LAUNCHER_LEFT) == 0)
        {
            status = rocketLauncherEndpoint_command(endpoint_ptr, root_ptr, service_ptr->left, reply_pstr);
        }
        else if (strcmp(sig_str, ROCKET_LAUNCHER_RIGHT) == 0)
        {
            status = rocketLauncherEndpoint_command(endpoint_ptr, root_ptr, service_ptr->right, reply_pstr);
        }
        else if (strcmp(sig_str, ROCKET_LAUNCHER_FIRE) == 0)
        {
            status = rocketLauncherEndpoint_command(endpoint_ptr, root_ptr, service_ptr->fire, reply_pstr);
        }
        else if (strcmp(sig_str, ROCKET_LAUNCHER_RESET) == 0)
        {
            status = rocketLauncherEndpoint_command(endpoint_ptr, root_ptr, service_ptr->reset, reply_pstr);
        }
        else {
            status = CELIX_ILLEGAL_ARGUMENT;
        }
    }

    json_decref(root_ptr);

    return status;
}

static celix_status_t rocketLauncherEndpoint_command(remote_endpoint_pt endpoint_ptr, json_t *data_ptr, celix_status_t (*_fptr)(rocket_launcher_component_pt), char **reply_pstr)
{
    celix_status_t status = CELIX_SUCCESS;

    rocket_launcher_service_pt service_ptr    = (endpoint_ptr != NULL) ? endpoint_ptr->service       : NULL;

    json_t *root_ptr = NULL;
    char error[256];

    memset(&error, 0, sizeof (error) );

    if (!endpoint_ptr || !service_ptr || !_fptr || !json_is_object(data_ptr) || !reply_pstr)
    {
        status = CELIX_ILLEGAL_ARGUMENT;
    }

    if (status == CELIX_SUCCESS)
    {
        status = _fptr(service_ptr->rocket_launcher_component_ptr);
        if (status != CELIX_SUCCESS)
        {
            status = CELIX_BUNDLE_EXCEPTION;
        }
    }

    if (status == CELIX_SUCCESS)
    {
        root_ptr = json_pack("{}");
    }
    else
    {
        celix_strerror(status, error, 256);
        root_ptr = json_pack("{s:{s:s,s:s,s:[]}}", "e", "type", "org.osgi.framework.ServiceException", "msg",
                error, "stacktrace");
    }
    if (!json_is_object(root_ptr) )
    {
        *reply_pstr = NULL;
        status = CELIX_BUNDLE_EXCEPTION;
    }
    else
    {
        *reply_pstr = json_dumps(root_ptr, 0);
        if (!*reply_pstr || (*reply_pstr[0] == '\0') )
        {
            status = CELIX_BUNDLE_EXCEPTION;
        }
    }

    json_decref(root_ptr);

    return status;
}



