#include "hal_data.h"
#include "bsp_uart_debug.h"
#include "stdio.h"


/***********************************************************************************************************************
 * ��������жϻص�����
 **********************************************************************************************************************/
volatile bool uart_send_complete_flag = false;

 void uart0_debug_callback(uart_callback_args_t * p_args)
{
    if(p_args->event==UART_EVENT_TX_COMPLETE)
    {
        uart_send_complete_flag = true;
    }
}


/***********************************************************************************************************************
 * ���Դ��ڳ�ʼ��
 **********************************************************************************************************************/
void uart_debug_init(void)
{
    fsp_err_t err;
    err =R_SCI_UART_Open(g_uart0_debug.p_ctrl,g_uart0_debug.p_cfg);
    assert(FSP_SUCCESS == err);  
}


/***********************************************************************************************************************
 * �ض��� printf ���
 **********************************************************************************************************************/
#if defined __GNUC__ && !defined __clang__
int _write(int fd, char *pBuffer, int size); //��ֹ���뾯��
int _write(int fd, char *pBuffer, int size)
{
   (void)fd;
   R_SCI_UART_Write(&g_uart4_ctrl, (uint8_t *)pBuffer, (uint32_t)size);
   while(uart_send_complete_flag == false);
   uart_send_complete_flag = false;

   return size;
}
#else
int fputc(int ch, FILE *f)
{
    (void)f;
    R_SCI_UART_Write(&g_uart0_debug_ctrl, (uint8_t *)&ch, 1);
    while(uart_send_complete_flag == false);
    uart_send_complete_flag = false;

    return ch;
}
#endif