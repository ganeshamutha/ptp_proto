cmake_minimum_required(VERSION 3.13)
project(ptp_proto C)

set(CMAKE_C_STANDARD 99)

add_library(udpService SHARED   udpService/udpService.h
                                udpService/udpService.c
                                udpService/udpMonitor.c
                                udpService/udpMonitor.h)

add_executable(ptp_proto udpService udpClientTest.c)