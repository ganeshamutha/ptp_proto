//
// Created by ganesh on 12/4/19.
//

#ifndef UDPMONITOR_H
#define UDPMONITOR_H

#include "udpService.h"

void udp_monitor_init();

void udp_add_monitor(udpService_t   *service);

void udp_del_monitor(udpService_t   *service);

void udp_monitor_deInit();


#endif //UDPMONITOR_H
