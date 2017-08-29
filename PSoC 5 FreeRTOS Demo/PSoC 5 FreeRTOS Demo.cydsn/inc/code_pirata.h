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
    
static int8_t bandera_entrada;
static int16_t bandera_numero_entrada = 0;
static int8_t byte_ibutto = 16;
static int8_t byte_tag = 16;
static int8_t byte_RFID = 16;
static int8_t byte_QR = 40;
static int8_t byte_MAG = 40;
static int8_t byte_data;
static int8_t bandera_posicion;
static int8_t bandera_posicion1;
static int8_t bandera_posicion2;

void send_pirata(uint8_t data_tx[],uint8_t tamano);
uint8_t cs(uint8_t data_tx[],uint8_t tamano);
uint16_t tamano_buffer(uint8_t data_buffer[]);
void borrar(void);
uint8_t code_pirata(char pos, char tipo);

#endif

/* [] END OF FILE */
