#include "bsp_led.h"
#include "hal_data.h"


void led_on(void)
{
    g_ioport.p_api->pinWrite(g_ioport.p_ctrl,BSP_IO_PORT_06_PIN_10,BSP_IO_LEVEL_LOW);
		g_ioport.p_api->pinWrite(g_ioport.p_ctrl,BSP_IO_PORT_06_PIN_09,BSP_IO_LEVEL_LOW);
		g_ioport.p_api->pinWrite(g_ioport.p_ctrl,BSP_IO_PORT_06_PIN_08,BSP_IO_LEVEL_LOW);
}

void led_off(void)
{
	  g_ioport.p_api->pinWrite(g_ioport.p_ctrl,BSP_IO_PORT_06_PIN_10,BSP_IO_LEVEL_HIGH);
		g_ioport.p_api->pinWrite(g_ioport.p_ctrl,BSP_IO_PORT_06_PIN_09,BSP_IO_LEVEL_HIGH);
		g_ioport.p_api->pinWrite(g_ioport.p_ctrl,BSP_IO_PORT_06_PIN_08,BSP_IO_LEVEL_HIGH);
}

void led_twinkling(void)
{
	  g_ioport.p_api->pinWrite(g_ioport.p_ctrl,BSP_IO_PORT_06_PIN_10,!R_BSP_PinRead(BSP_IO_PORT_06_PIN_10));
		g_ioport.p_api->pinWrite(g_ioport.p_ctrl,BSP_IO_PORT_06_PIN_09,!R_BSP_PinRead(BSP_IO_PORT_06_PIN_09));
		g_ioport.p_api->pinWrite(g_ioport.p_ctrl,BSP_IO_PORT_06_PIN_08,!R_BSP_PinRead(BSP_IO_PORT_06_PIN_08));
}