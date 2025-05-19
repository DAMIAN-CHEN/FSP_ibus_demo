/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_dmac.h"
#include "r_transfer_api.h"
#include "r_sci_uart.h"
            #include "r_uart_api.h"
FSP_HEADER
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_transfer_dmac_sci2_rx;

/** Access the DMAC instance using these structures when calling API functions directly (::p_api is not used). */
extern dmac_instance_ctrl_t g_transfer_dmac_sci2_rx_ctrl;
extern const transfer_cfg_t g_transfer_dmac_sci2_rx_cfg;

#ifndef dmac_sci2_rx_callback
void dmac_sci2_rx_callback(transfer_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart2_ibus;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     g_uart2_ibus_ctrl;
            extern const uart_cfg_t g_uart2_ibus_cfg;
            extern const sci_uart_extended_cfg_t g_uart2_ibus_cfg_extend;

            #ifndef NULL
            void NULL(uart_callback_args_t * p_args);
            #endif
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart0_debug;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_uart_instance_ctrl_t     g_uart0_debug_ctrl;
            extern const uart_cfg_t g_uart0_debug_cfg;
            extern const sci_uart_extended_cfg_t g_uart0_debug_cfg_extend;

            #ifndef uart0_debug_callback
            void uart0_debug_callback(uart_callback_args_t * p_args);
            #endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
