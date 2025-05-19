//
// Created by DAMIAN_CHEN on 25-3-30.
//

#include "drv_ibus.h"
#include <string.h>


static uint8_t  rx_buffer[32] = {0};
static uint8_t  rx_buffer_from_dma[64] = {0};
static uint8_t  rx_buffer_initial_find[64] = {0};
uint16_t channel[IBUS_USER_CHANNELS] = {0};         //最终解包后遥控器通道数据(此处用全局变量是为了debug使用监视点实时观察)
static uint16_t checksum_cal, checksum_ibus;

fs_ia6b_ibus_t rc_data;

/***********************************************************************************************************************
 * 数据接收buffer初步处理函数
 **********************************************************************************************************************/

static int ibus_initial_unpack(void)
{
    for (int i=0;i<64-32;++i)//确保检测到的字节数为32字节，防止copy溢出
    {
        if (rx_buffer_initial_find[i]==IBUS_start1&&rx_buffer_initial_find[i+1]==IBUS_start2)  //根据通信协议从buffer中找出数据帧
        {
            memcpy(rx_buffer,&rx_buffer_initial_find[i],32);
            return 0;
        }
    }
    return 1;
}

/***********************************************************************************************************************
 * ibus通信协议解包函数
 **********************************************************************************************************************/
void ibus_unpack()
{
    if (ibus_initial_unpack()==0)
    {

    uint16_t channel_buffer[IBUS_MAX_CHANNLES] = {0};

    if(rx_buffer[0] == IBUS_start1 && rx_buffer[1] == IBUS_start2)
    {
        checksum_cal = 0xffff - rx_buffer[0] - rx_buffer[1];

        for(int i = 0; i < IBUS_MAX_CHANNLES; i++)
        {
            channel_buffer[i] = (uint16_t)(rx_buffer[i * 2 + 3] << 8 | rx_buffer[i * 2 + 2]);
            checksum_cal = checksum_cal - rx_buffer[i * 2 + 3] - rx_buffer[i * 2 + 2];
        }

        checksum_ibus = (uint16_t)(rx_buffer[31] << 8 | rx_buffer[30]);

        if(checksum_cal == checksum_ibus)
        {
            for(int j = 0; j < IBUS_USER_CHANNELS; j++)
            {
                channel[j] = channel_buffer[j];
            }
            memcpy(&rc_data,channel,sizeof(fs_ia6b_ibus_t));
        }
    }

    }
}

/***********************************************************************************************************************
 * ibus接收串口初始化函数
 **********************************************************************************************************************/

void ibus_init(void)
{
		fsp_err_t err;
	
    /* 配置串口接收 DMA 源地址、目标地址、长度 */
	  
		err =R_DMAC_Reset (g_transfer_dmac_sci2_rx.p_ctrl,
                        (void const * volatile)(&R_SCI2->RDR),
                        rx_buffer_from_dma,
                        sizeof(rx_buffer_from_dma));
		assert(FSP_SUCCESS == err);
   
	  err =R_DMAC_Open (g_transfer_dmac_sci2_rx.p_ctrl, g_transfer_dmac_sci2_rx.p_cfg);
		assert(FSP_SUCCESS == err);
	  err =R_DMAC_Enable (g_transfer_dmac_sci2_rx.p_ctrl);
		assert(FSP_SUCCESS == err); 
		err =R_SCI_UART_Open(g_uart2_ibus.p_ctrl,g_uart2_ibus.p_cfg);
		assert(FSP_SUCCESS == err);
	  
}

/***********************************************************************************************************************
 * DMAC接收中断回调函数
 **********************************************************************************************************************/
void dmac_sci2_rx_callback(dmac_callback_args_t *p_args)
{
    (void)p_args;
	
    memcpy(&rx_buffer_initial_find,rx_buffer_from_dma,sizeof(rx_buffer_from_dma));  //复制接收buffer到数据处理buffer中
	 
    R_DMAC_Disable (g_transfer_dmac_sci2_rx.p_ctrl);                                //失能DMA
    R_DMAC_Reset (g_transfer_dmac_sci2_rx.p_ctrl,
                        (void const * volatile)(&R_SCI2->RDR),                      //重新配置DMA接收初始地址
                        rx_buffer_from_dma,
                        sizeof(rx_buffer_from_dma));
    R_DMAC_Enable (g_transfer_dmac_sci2_rx.p_ctrl);                                 //使能DMA
} 

/***********************************************************************************************************************
 * 打印解包结果
 **********************************************************************************************************************/

void channel_print(void)
{
    printf("channel_0: %d \n",channel[0]);
	  printf("channel_1: %d \n",channel[1]);
	  printf("channel_2: %d \n",channel[2]);
	  printf("channel_3: %d \n",channel[3]);
	  printf("channel_4: %d \n",channel[4]);
	  printf("channel_5: %d \n",channel[5]);
	//printf("\n");
}


