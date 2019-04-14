#include <stdio.h>
#include "udpService/udpService.h"

int main() {

    udpService_t *uClient = NULL;

    udp_service_init();

    //udp_service_create(&uClient, UDP_SERVICE_CLIENT_UNICAST, );




    udp_service_deInit();

    printf("Hello, World!\n");
    return 0;
}