/*
*********************************************************************************************************
*                                         MUX ADVANCE CODE
*
*                             (c) Copyright 2016; Sistemas Insepet LTDA
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            MUX ADVANCE CODE
*
*                                             CYPRESS PSoC5LP
*                                                with the
*                                            CY8C5969AXI-LP035
*
* Filename      : LCD.c
* Version       : V1.00
* Programmer(s) : 
                  
*********************************************************************************************************
*/

#ifndef LCD_H
#define LCD_H
#include <device.h>
	
void SetPicture(uint8 lcd, uint16 picture);
void WriteMessage(uint8_t lcd,uint8_t data, uint16_t posy, uint16_t posx,uint8_t size, uint16_t fgcolor ,uint8_t bottomless);
void WriteLCD(uint8_t lcd,uint8_t data, uint16_t posy, uint16_t posx,uint8_t size, uint16_t fgcolor, uint8_t bottomless);
void write_button(uint8 lcd, uint8 screen);
void ShowRectangle(uint8 lcd,uint8 coordinate);
void SetColor(uint8 lcd);
void show_info(uint8 lcd, uint8 *version);
void ShowMessage(uint8 lcd,uint8 *msg, uint8 posx);
void show_market(uint8 lcd);
char8 UnmapCode(uint8 code);
typedef struct
{
    uint8 _refchar;
    uint8 _mappedto;
} DisplayCharacterMap;

#endif

//[] END OF FILE
