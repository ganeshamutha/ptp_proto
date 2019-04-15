
#include <stdio.h>
#include <string.h>

#include "udpService/udpService.h"

#define TEST_SERVER_IP      "10.90.228.16"
#define TEST_SERVER_PORT    10030

int main() {

    char *testMsg = "This is Test message";

    udpService_t *uClient = NULL;

    udp_service_init();

    //udp_service_create(&uClient, UDP_SERVICE_CLIENT_UNICAST, );

    udp_service_create(&uClient, UDP_SERVICE_CLIENT_UNICAST, NULL, 10030, NULL);

    udp_service_send_msg(uClient, (void*)testMsg, strlen(testMsg), TEST_SERVER_IP);

    udp_service_destroy(uClient);

    udp_service_deInit();

    return 0;
}