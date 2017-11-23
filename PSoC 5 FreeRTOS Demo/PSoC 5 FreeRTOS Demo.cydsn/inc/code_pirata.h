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

#ifndef CODE_PIRATA_H
#define CODE_PIRATA_H
#include <device.h>
    
void send_pirata(uint8_t data_tx[],uint8_t tamano);
uint8_t cs(uint8_t data_tx[],uint8_t tamano);
uint16_t tamano_buffer(uint8_t data_buffer[]);
void borrar(void);
uint8_t code_pirata(char pos, char tipo);

#endif

/* [] END OF FILE */
