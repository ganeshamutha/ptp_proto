//
// Created by ganesh on 7/4/19.
//

#ifndef _PTP_HOST_MSG_H
#define _PTP_HOST_MSG_H


//Message of Header

typedef struct PTP_HOST_MESSAGE_HEADER_T
{

    unsigned char       sourceId;
    unsigned char       destId;
    unsigned short int  msgCode;
    unsigned char       msgCounter;

    unsigned char       headerSpace_;
    unsigned short int  msgLength;

}ptp_host_msg_header_t;


//General Message Format
typedef struct PTP_GEN_MSG_T
{
    ptp_host_msg_header_t   msgHeader;
    unsigned short int      param1;
    unsigned short int      param2;
    unsigned short int      param3;
    unsigned short int      param4;
    unsigned short int      param5;
    unsigned short int      param6;

} ptp_gen_msg_t;

//Software Version and DOR message format
typedef struct PTP_SWV_DOR_MSG_T
{

    ptp_host_msg_header_t   msgHeader;
    unsigned char           param1;
    unsigned char           param2;
    unsigned short int      param3;
    unsigned char           param4[50];

} ptp_swv_dor_msg_t;

typedef enum PTP_MSG_TYPE_TAG {

    E_PTP_MSG_GENERIC,
    E_PTP_MSG_SWV_DOR,

}e_ptp_msg_type_t;


typedef struct PTP_MSG_T {

    e_ptp_msg_type_t        msgType;
    union{

        ptp_gen_msg_t       genMsg;
        ptp_swv_dor_msg_t   swvDorMsg;
    };

}ptp_msg_t;


//Source Id
typedef enum PTP_SOURCE_ID_T
{

    E_MU        = 0x00,
    E_MUA       = 0x01,
    E_MUB       = 0x02,

    E_PTP_M1    = 0x61,
    E_PTP_M2    = 0x62,

    E_LCU1      = 0x30,
    E_LCU2      = 0x31,
    E_LCU3      = 0x32,
    E_LCU4      = 0x33,
    E_LCU5      = 0x34,
    E_LCU6      = 0x35,

    E_PTP_S     = 0x72


}e_ptp_source_id_t;


//Message Code
typedef enum PTP_MSG_CODE_T
{
    E_HEALTH_MSG_MAS_TO_MU      = 0x2201,
    E_SW_VER_MSG_MAS_TO_MU      = 0x2202,

    E_SHUTDOWN_MSG_MU_TO_MAS    = 0x2212,

    E_HEALTH_MSG_SLV_TO_LCU     = 0x3201,
    E_SW_VER_MSG_SLV_TO_LCU     = 0x3202,

    E_IP_CHG_MSG_LCU_TO_SLV     = 0x3211,
    E_LCU_IP_MSG_LCU_TO_SLV     = 0x3212,

    E_SHUTDOWN_MSG_LCU_TO_SLV   = 0x3213


}e_ptp_msg_code_t;


typedef struct PTP_IP_CONFIG_TAG{

    unsigned char *ptp_master_1_src_ip;
    unsigned char *ptp_master_2_src_ip;

    unsigned char *ptp_slave_1_src_ip;
    unsigned char *ptp_slave_2_src_ip;
    unsigned char *ptp_slave_3_src_ip;
    unsigned char *ptp_slave_4_src_ip;
    unsigned char *ptp_slave_5_src_ip;
    unsigned char *ptp_slave_6_src_ip;

    unsigned char *mu_A_dst_ip;
    unsigned char *mu_B_dst_ip;


    unsigned char *lcu_1_dst_ip;
    unsigned char *lcu_2_dst_ip;
    unsigned char *lcu_3_dst_ip;
    unsigned char *lcu_4_dst_ip;
    unsigned char *lcu_5_dst_ip;
    unsigned char *lcu_6_dst_ip;


    unsigned char *mcast_ip;

    unsigned char *ptp_card_master_1_ip;
    unsigned char *ptp_card_master_2_ip;


    unsigned char *ptp_card_slave_1_ip;
    unsigned char *ptp_card_slave_2_ip;
    unsigned char *ptp_card_slave_3_ip;
    unsigned char *ptp_card_slave_4_ip;
    unsigned char *ptp_card_slave_5_ip;
    unsigned char *ptp_card_slave_6_ip;


}ptp_ip_config_t;

//IP configurations.
int ptp_host_msg_init(ptp_ip_config_t *ipConfig);

int ptp_create_mu_comm( );

int ptp_create_mas_comm();

int ptp_create_slv_comm();

int ptp_create_lcu_comm();

int ptp_send_msg(int handle, unsigned char *dstIp, ptp_msg_t *msg);

int ptp_destroy_comm(int handle);

int ptp_host_msg_deInit();


#if 0
//PTP_Master and MU Communication.

int ptp_send_msg_mu_to_mas();

int ptp_send_msg_mas_to_mu();


//PTP_Slave and LCU Communication.

int ptp_send_msg_slv_to_lcu();

int ptp_send_msg_lcu_to_slv();


//ext:
int ptp_send_msg_unicast(unsigned char *srcIp, unsigned char *dstIp, void *msg);
#endif



#endif //_PTP_HOST_MSG_H
