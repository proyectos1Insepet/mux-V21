/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef RFPOLL_H
#define RFPOLL_H
#include <device.h>
#include <stdbool.h>
    
//void pollingRF_Rx(void);
void pollingRF_Rx(uint8 PRF_rxBuffer[]);
void pollingRFA_Tx(void);
void pollingRFB_Tx(void);
void pollingRFC_Tx(void);
void pollingRFD_Tx(void);
uint8 verificar_check(uint8 *datos, uint16 size);

#endif

/* [] END OF FILE */
