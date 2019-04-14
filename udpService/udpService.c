//
// Created by ganesh on 12/4/19.
//

#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

#include "udpService.h"


static int server_unicast(int sockId, int port){

     struct sockaddr_in address;
     int    retValue  = 0;

     memset(&address, 0, sizeof(struct sockaddr_in));

     address.sin_family = AF_INET;
     address.sin_addr.s_addr = htonl(INADDR_ANY);
     address.sin_port    = htons(port);

     retValue = bind(sockId, (struct sockaddr*) &address, sizeof(address));
     if(retValue == -1) {

         perror("Bind error ");
         printf("Bind Error : %d \n", errno);

         return retValue;
     }

    return  retValue;
}

static int server_multicast(int sockId, int port, char *groupIp){

    int retValue  = 0;
    struct in_addr localInterface;

    server_unicast(sockId, port);

    localInterface.s_addr = inet_addr(groupIp);

    if(setsockopt(sockId, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)
    {
        perror("Setting local interface error");
        retValue = -1;
    }

    return retValue;
}


static int register_event_notifier(udpService_t *udpService){

    unsigned char   buf[512] = {0};
    int             retValue = 0;
    pthread_t       threadId = -1;

    retValue = recvfrom(udpService->sockId, buf, sizeof(buf), 0, NULL, NULL);

    if(retValue > 0){
        udpService->msgNotifier(buf);
    }

    //TODO Async
    //if(retValue > 0) {
    //    pthread_create(&threadId, NULL, )
    //}

}



udpServiceErrorCode_t udp_service_init() {

    udpServiceErrorCode_t errorCode = E_UDP_SERVICE_ERROR_NONE;

    //TODO N/w or Sys init or Global stuff.

    return errorCode;
}


udpServiceErrorCode_t udp_service_deInit(){

    udpServiceErrorCode_t errorCode = E_UDP_SERVICE_ERROR_NONE;

    //TODO N/w or Sys or Global stuff.

    return errorCode;

}

udpServiceErrorCode_t udp_service_create(udpService_t **udpService, e_udpService_t type, char *ip, int port, udp_msg_notifier notifier_t) {

    int sockId = 0;

    udpServiceErrorCode_t   errorCode = E_UDP_SERVICE_ERROR_NONE;
    udpService_t            *p_udpService = NULL;

    p_udpService = malloc(sizeof(udpService_t));
    if(udpService == NULL){

        errorCode = E_UDP_SERVICE_ERR_MEM_ALLOC;
        return  errorCode;
    }

    //copy port and IP.
    p_udpService->port = port;
    strcpy(p_udpService->ip , ip);

    //Create Socket as per type.
    sockId = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockId == -1){
        perror("Socket Create Error ");
        //printf("Error Number %d \n", errno);

        errorCode = E_UDP_SERVICE_ERR_SOCK_CREATE;

        free(p_udpService);
        p_udpService = NULL;

        //Update
        *udpService = p_udpService;

        return errorCode;
    }

    p_udpService->sockId = sockId;

    //type.
    switch (type) {

        case UDP_SERVICE_SERVER_UNICAST :

            p_udpService->msgNotifier = notifier_t;
            server_unicast(p_udpService->sockId, p_udpService->port);
            break;

        case UDP_SERVICE_CLIENT_UNICAST:
            //Just socket Creation enough.
            //Nothing TODO here.

            p_udpService->msgNotifier = NULL;
            break;

        case UDP_SERVICE_SERVER_MULTICAST:
        case UDP_SERVICE_CLIENT_MULTICAST:

            p_udpService->msgNotifier = notifier_t;

            server_multicast(p_udpService->sockId, p_udpService->port, p_udpService->ip);
            break;

        default:
            errorCode = E_UDP_SERVICE_INVALID_PARAM;
            free(p_udpService);
            p_udpService = NULL;


            //Update
            *udpService = p_udpService;
            return errorCode;

    }



    //Update
    *udpService = p_udpService;


    return errorCode;

}


udpServiceErrorCode_t udp_service_destroy(udpService_t *udpService);

udpServiceErrorCode_t udp_service_send_msg(void* msg, char *ip);
