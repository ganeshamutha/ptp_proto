cmake_minimum_required(VERSION 3.1)
project(ptp_proto C)

set(CMAKE_C_STANDARD 99)

add_library(udpService SHARED   udpService/udpService.h
                                udpService/udpService.c
                                udpService/udpMonitor.c
                                udpService/udpMonitor.h)

add_executable(udpClient.out udpClientTest.c)

add_executable(udpServer.out udpServerTest.c)


target_link_libraries(udpServer.out udpService)

target_link_libraries(udpClient.out udpService)
