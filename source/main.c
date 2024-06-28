/******************************************************************************
* File Name: main.c
*
* Description:
*   This code example demonstrates the TCP Keepalive Offload functionality
*   offered by Cypress Wi-Fi devices using PSoC® 6 MCU. It employs Low Power
*   Assistant (LPA) middleware library which helps in developing low power
*   applications for the Cypress devices.
*
* Related Document:
*   README.md
*   AN227910 Low-Power System Design with CYW43012 and PSoC 6
*
* Supported Kits (Target Names):
*   CY8CKIT-062S2-43012 PSoC 6 Wi-Fi BT Pioneer Kit
*   CY8CPROTO-062-4343W PSoC 6 Wi-Fi BT Prototyping Kit
*
********************************************************************************
* Copyright 2020-2024, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/* Header file includes */

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

/* User settings related to Wi-Fi and network stack */
#include "app_config.h"

/* Provides function prototypes for Wi-Fi connection,
 * Socket connection, and for the task that suspends
 * the network stack.
 */
#include "tcp_keepalive_offload.h"

/* Include serial flash library and QSPI memory configurations only for the
 * kits that require the Wi-Fi firmware to be loaded in external QSPI NOR flash.
 */
#if defined(CY_ENABLE_XIP_PROGRAM)
#include "cy_serial_flash_qspi.h"
#include "cycfg_qspi_memslot.h"
#endif

/*******************************************************************************
* Macros
********************************************************************************/
/* Configure task stack size and priority */
#define NETWORK_ACTIVITY_TASK_STACK_SIZE            (256)
#define NETWORK_ACTIVITY_TASK_PRIORITY              (1)

/*******************************************************************************
* Global Variables
********************************************************************************/

/*******************************************************************************
 * Function Name: main
 *******************************************************************************
 * Summary:
 *  Entry function for the application.
 *  This function initializes the BSP, UART port for debugging, and starts the
 *  RTOS scheduler.
 *
 * Parameters:
 *  void
 *
 * Return:
 *  int: Should never return.
 *
 *******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the Board Support Package (BSP) */
    result = cybsp_init();

    CHECK_RESULT(result);

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                        CY_RETARGET_IO_BAUDRATE);

    #if defined(CY_ENABLE_XIP_PROGRAM)
    const uint32_t bus_frequency = 50000000lu;

    cy_serial_flash_qspi_init(smifMemConfigs[0], CYBSP_QSPI_D0, CYBSP_QSPI_D1,
                                  CYBSP_QSPI_D2, CYBSP_QSPI_D3, NC, NC, NC, NC,
                                  CYBSP_QSPI_SCK, CYBSP_QSPI_SS, bus_frequency);

    cy_serial_flash_qspi_enable_xip(true);
    #endif

    /* \x1b[2J\x1b[;H - ANSI ESC sequence to clear screen */
    APP_INFO(("\x1b[2J\x1b[;H"));
    APP_INFO(("=====================================\n"));
    APP_INFO(("CE229926 - WLAN Offloads\n"));
    APP_INFO(("=====================================\n\n"));

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    /* Should never get here */
    CY_ASSERT(0);
}

/********************************************************************************
 * Function Name: vApplicationDaemonTaskStartupHook
 ********************************************************************************
 * Summary:
 *  This is a RTOS daemon task used for initialization purposes. This function
 *  initializes the Wi-Fi. It joins with Access Point with the given SSID and
 *  PASSWORD. After connection, it establishes TCP socket connection with the
 *  remote TCP server. It then starts a low power task which is responsible for
 *  suspending the network stack to achieve host MCU low power.
 *
 * Parameters:
 *  None
 *
 * Return:
 *  void
 *
 *******************************************************************************/
void vApplicationDaemonTaskStartupHook()
{
    BaseType_t xReturned;
    cy_rslt_t  result;

    /*
     * Connect to Wi-Fi Access Point.
     */
    result = wifi_connect();

    PRINT_AND_ASSERT(result, "Wi-Fi connection failed.\n");

    /*
     * Establish TCP socket connection with the configured TCP server.
     * Ensure the remote TCP server has already started before running this application.
     */
    result = tcp_socket_connection_start();

    if (CY_RSLT_SUCCESS != result)
    {
        ERR_INFO(("One or more TCP socket connections failed.\n"));
        /*
         * Wait for few seconds to let the user notice about the socket
         * connection failure before the network stats start to print
         * on the serial terminal that would cause the user to miss seeing
         * the error message.
         */
        vTaskDelay(pdMS_TO_TICKS(TCP_SOCKET_ERROR_DELAY_MS));
    }

    /*
     * Suspend/Resume network stack.
     * This task will cause PSoC 6 MCU to go into deep-sleep power mode. The PSoC 6 MCU
     * wakes up only when the network stack resumes due to Tx/Rx activity detected
     * by the Offload Manager (OLM).
     */
    xReturned = xTaskCreate(network_idle_task,
                            "NetAct",
                            NETWORK_ACTIVITY_TASK_STACK_SIZE,
                            NULL,
                            NETWORK_ACTIVITY_TASK_PRIORITY,
                            NULL);

    if (pdPASS != xReturned)
    {
        APP_INFO(("Failed to create low power task.\n"));
        CY_ASSERT(0);
    }
}


/* [] END OF FILE */
