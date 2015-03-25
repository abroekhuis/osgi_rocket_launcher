//
// Created by Alexander Broekhuis on 17/03/2015.
//
#include <stdlib.h>
#include <unistd.h>

#include "rocket_launcher_component.h"

#define CMD_FILL 0x5f
#define CMD_FILL_POST 0xe0, 0xff, 0xfe

static unsigned char STOP[] = {CMD_FILL, 0x0, CMD_FILL_POST};
static unsigned char LEFT[] = {CMD_FILL, 0x8, CMD_FILL_POST};
static unsigned char RIGHT[] = {CMD_FILL, 0x4, CMD_FILL_POST};
static unsigned char UP[] = {CMD_FILL, 0x2, CMD_FILL_POST};
static unsigned char DOWN[] = {CMD_FILL, 0x1, CMD_FILL_POST};
static unsigned char FIRE[] = {CMD_FILL, 0x10, CMD_FILL_POST};

static uint16_t VENDOR_ID = 0x0416;
static uint16_t PRODUCT_ID = 0x9391;
static uint8_t BM_REQUEST_TYPE = 0x21;
static uint8_t B_REQUEST = 0x09;
static uint8_t W_VALUE = 0x0300;
static uint8_t W_INDEX = 0x00;
static uint8_t TIMEOUT = 255;

celix_status_t rocketLauncher_create(rocket_launcher_component_pt *rocket_launcher_component_ptr) {
    celix_status_t status = CELIX_SUCCESS;

    *rocket_launcher_component_ptr = calloc(1, sizeof(**rocket_launcher_component_ptr));
    if (!*rocket_launcher_component_ptr) {
        status = CELIX_ENOMEM;
    }

    if (status == CELIX_SUCCESS) {
    }

    return status;
}

celix_status_t rocketLauncher_destroy(rocket_launcher_component_pt *rocket_launcher_component_ptr) {
    celix_status_t status = CELIX_SUCCESS;

    free(*rocket_launcher_component_ptr);

    return status;
}

celix_status_t rocketLauncher_componentInit(void *_ptr) {
    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_componentStart(void *_ptr) {
        rocket_launcher_component_pt self = _ptr;
        libusb_init(&self->context);
        if (self->context != NULL) {
            self->devHandle = libusb_open_device_with_vid_pid(self->context, VENDOR_ID, PRODUCT_ID);     
            if (self->devHandle == NULL) {
                    perror("Error finding usb device");
            }
        } else {
                perror("Error initializing libusb");
        }
    return CELIX_SUCCESS;
}
celix_status_t rocketLauncher_componentStop(void *_ptr) {
        rocket_launcher_component_pt self = _ptr;
        libusb_(&self->context);
        libusb_close(self->devHandle);
    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_componentExit(void *_ptr) {
    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_stop(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (component->devHandle != NULL) {
        libusb_control_transfer(component->devHandle,  BM_REQUEST_TYPE, B_REQUEST, W_VALUE, W_INDEX, STOP, 5, TIMEOUT);
    }

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Stop");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_up(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (component->devHandle != NULL) {
        libusb_control_transfer(component->devHandle,  BM_REQUEST_TYPE, B_REQUEST, W_VALUE, W_INDEX, UP, 5, TIMEOUT);
    }

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Up");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_down(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (component->devHandle != NULL) {
        libusb_control_transfer(component->devHandle,  BM_REQUEST_TYPE, B_REQUEST, W_VALUE, W_INDEX, DOWN, 5, TIMEOUT);
    }

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Down");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_left(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (component->devHandle != NULL) {
        libusb_control_transfer(component->devHandle,  BM_REQUEST_TYPE, B_REQUEST, W_VALUE, W_INDEX, LEFT, 5, TIMEOUT);
    }
    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Left");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_right(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (component->devHandle != NULL) {
        libusb_control_transfer(component->devHandle,  BM_REQUEST_TYPE, B_REQUEST, W_VALUE, W_INDEX, RIGHT, 5, TIMEOUT);
    }

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Right");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_fire(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    if (component->devHandle != NULL) {
        libusb_control_transfer(component->devHandle,  BM_REQUEST_TYPE, B_REQUEST, W_VALUE, W_INDEX, FIRE, 5, TIMEOUT);
    }

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Fire");
    }

    return CELIX_SUCCESS;
}

celix_status_t rocketLauncher_reset(rocket_launcher_component_pt component) {
    log_service_pt log_service = component->log_service_ptr;

    //ignore

    if (log_service) {
        log_service->log(log_service->logger, OSGI_LOGSERVICE_INFO, "Reset");
    }

    return CELIX_SUCCESS;
}
