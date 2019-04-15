//
// Created by ganesh on 12/4/19.
//

#ifndef _UDPSERVICE_H
#define _UDPSERVICE_H


typedef enum UDP_SERVICE_TYPE {

    UDP_SERVICE_CLIENT_UNICAST ,
    UDP_SERVICE_CLIENT_MULTICAST,
    UDP_SERVICE_SERVER_UNICAST,
    UDP_SERVICE_SERVER_MULTICAST

} e_udpService_t;


typedef void udp_msg_notifier(void* msg);


typedef struct udpServiceHandlerTag{

    udp_msg_notifier    *msgNotifier;
    e_udpService_t      e_type;
    int                 msg_count;
    char                ip[32];
    int                 port;
    int                 sockId;

} udpService_t;


typedef enum udpServiceErrorCodeTag{

    E_UDP_SERVICE_ERROR_NONE    = 0,

    E_UDP_SERVICE_INVALID_PARAM     = -100,
    E_UDP_SERVICE_ERR_SOCK_CREATE,
    E_UDP_SERVICE_ERR_SEND_FAILED,
    E_UDP_SERVICE_ERR_MEM_ALLOC,

} udpServiceErrorCode_t;


udpServiceErrorCode_t udp_service_init();

udpServiceErrorCode_t udp_service_deInit();

udpServiceErrorCode_t udp_service_create(udpService_t **udpService, e_udpService_t type,
                                         char *ip, int port, udp_msg_notifier notifier_t);

udpServiceErrorCode_t udp_service_destroy(udpService_t *udpService);

udpServiceErrorCode_t udp_service_send_msg(udpService_t *p_udpService, void* msg, int len, char *ip);


#endif //_UDPSERVICE_H
