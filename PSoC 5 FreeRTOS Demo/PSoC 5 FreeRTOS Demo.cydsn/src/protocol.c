/* ========================================
 *
 * Copyright SISTEMAS INSEPET, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF SISTEMAS INSEPET.
 *
 * ========================================
*/
#include <device.h>
#include <variables.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* RTOS includes. */
#include <FreeRTOS.h>
#include <semphr.h>
#include "os_resource.h"
#include "os_mutex.h"


/* Pregunta si el surtidor tiene un estado valido */
bool PumpIsInValidState(state)
{
    bool retval = false;  
    
    switch(state)
    {
        case PUMP_IDLE:
            retval = true;
        break;
        case PUMP_CALLING:
            retval = true;
        break;
        case PUMP_AUTHORIZED:
            retval = true;
        break;
        case PUMP_BUSY:
            retval = true;
        break;
        case PUMP_PEOT:
            retval = true;
        break;
        case PUMP_FEOT:
            retval = true;
        break;
        case PUMP_STOPPED:
            retval = true;
        break;
        case PUMP_FAIL:
            retval = false;
        break;
        default:
            retval = false;
        break;
    }
    return retval;
}

uint8_t GetLRC(char8 *_pbuffer);
/*
*********************************************************************************************************
*                                    uint8 get_state(uint8 pos)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/

/* Obtiene el estado del surtidor */
uint8 get_state(uint8 pos){
    uint8 state = 0;
    
    Pump_PutChar(pos);
    Pump_ClearRxBuffer();
    if(OSonline){
        vTaskDelay( 70 / portTICK_PERIOD_MS );
    }else{
        CyDelay(60);
    }        
    if(Pump_GetRxBufferSize() > 0)
    {
        state = (Pump_ReadRxData() & 0xF0) >> 4;
        
        if(!PumpIsInValidState(state))
        {
            Pump_ClearRxBuffer();
            return 0;
        }else
        {
            Pump_ClearRxBuffer();
            return state;
        }
    }
    else
    {
        Pump_ClearRxBuffer();
        return 0;
    }
}

/*
*********************************************************************************************************
*                                         uint8 get_position(void)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
uint8 get_position(void){
    uint8 x;            
    side.a.dir=0xff;
    side.b.dir=0xff;
    side.c.dir=0xff;
    side.d.dir=0xff;
    InitState[0] = 0x00;
    InitState[1] = 0x00;
    InitState[2] = 0x00;
    InitState[3] = 0x00;
    
    // Detecta las posiciones del surtidor
    for(x = 1; x <= 16; x++)
    {
        Pump_PutChar(x);
          
        CyDelay(100);           
      
        if((Pump_GetRxBufferSize() >= 1) && (side.a.dir == 0xff))
        {
           side.a.dir = x;
           InitState[0] = (Pump_ReadRxData() & 0xF0) >> 4;
           Pump_ClearRxBuffer();
        }
        if((Pump_GetRxBufferSize() >= 1) && (x != side.a.dir) && (side.b.dir == 0xff))
        {
           side.b.dir = x;
           InitState[1] = (Pump_ReadRxData() & 0xF0) >> 4;
           Pump_ClearRxBuffer();
        }
        if((Pump_GetRxBufferSize() >= 1) && (x != side.a.dir) && (x != side.b.dir) && (side.c.dir == 0xff))
        {
           side.c.dir = x;
           InitState[2] = (Pump_ReadRxData() & 0xF0) >> 4;
           Pump_ClearRxBuffer();
        }
        if((Pump_GetRxBufferSize() >= 1) && (x != side.a.dir) && (x != side.b.dir) && (x != side.c.dir) && (side.d.dir == 0xff))
        {
           side.d.dir = x;
           InitState[3] = (Pump_ReadRxData() & 0xF0) >> 4;
           Pump_ClearRxBuffer();
        }  

    }
    
    // Retorna el numero de posiciones   
    if(PumpIsInValidState(InitState[0]) && PumpIsInValidState(InitState[1]))
    {
        if(PumpIsInValidState(InitState[2]) && PumpIsInValidState(InitState[3]))
        {
            return 4;            
        }
        else
        {    
            return 2;
        }
    }
    else
    {
        return 0;
    }
    
}

/*
*********************************************************************************************************
*                                    uint8 get_totals(uint8 pos)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
uint8 getTotals(uint8 pos){
    uint8 x,y,z,w,gradeHandle;
    
    Pump_ClearRxBuffer();
    Pump_PutChar(0x50|pos);
    CyWdtClear();
    //CyDelay(900);
    vTaskDelay( 900 / portTICK_PERIOD_MS );
    CyWdtClear();
    
    x = Pump_GetRxBufferSize();
    
    if((x == 34) || (x == 64) || (x == 94) || (x == 124))  // Version 5 ó 6 digitos
    {           
        if((Pump_rxBuffer[0] == 0xFF) && (Pump_rxBuffer[1] == 0xF6) && (Pump_rxBuffer[3] == 0xF9))
        {
            gradeHandle = (x / 30) & 0x07;                    //Identificando cantidad de mangueras en el surtidor
            if(pos == side.a.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.a.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 8; z++)
                        {
                            side.a.totalsHandle[x][y][9-z] = (Pump_rxBuffer[w+4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2) && (z == 4))
                            {
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 7;
                    for(z = 4; z >= 1; z--)
                    {
                        side.a.totalsHandle[x][2][z] = side.a.totalsHandle[x][2][z+4];
                    }
                    side.a.totalsHandle[x][0][0] = 8;
                    side.a.totalsHandle[x][1][0] = 8;
                    side.a.totalsHandle[x][2][0] = 4;
                    if(ppux10 == 1)
                    {
                        side.a.totalsHandle[x][2][0] = 5;
                        side.a.totalsHandle[x][2][5] = 0;
                    }
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
            if(pos == side.b.dir){
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.b.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 8; z++)
                        {
                            side.b.totalsHandle[x][y][9-z] = (Pump_rxBuffer[w+4]&0x0F) + 0x30;
                            w++;
                            if((y == 2)&&(z == 4))
                            {
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 7;
                    for(z = 4; z >= 1; z--)
                    {
                        side.b.totalsHandle[x][2][z] = side.b.totalsHandle[x][2][z+4];
                    }
                    side.b.totalsHandle[x][0][0] = 8;
                    side.b.totalsHandle[x][1][0] = 8;
                    side.b.totalsHandle[x][2][0] = 4;
                    if(ppux10 == 1)
                    {
                        side.b.totalsHandle[x][2][0] = 5;
                        side.b.totalsHandle[x][2][5] = 0;
                    }
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
            
            if(pos == side.c.dir){
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.c.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 8; z++)
                        {
                            side.c.totalsHandle[x][y][9-z] = (Pump_rxBuffer[w+4]&0x0F) + 0x30;
                            w++;
                            if((y == 2)&&(z == 4))
                            {
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 7;
                    for(z = 4; z >= 1; z--)
                    {
                        side.c.totalsHandle[x][2][z] = side.c.totalsHandle[x][2][z+4];
                    }
                    side.c.totalsHandle[x][0][0] = 8;
                    side.c.totalsHandle[x][1][0] = 8;
                    side.c.totalsHandle[x][2][0] = 4;
                    if(ppux10 == 1)
                    {
                        side.c.totalsHandle[x][2][0] = 5;
                        side.c.totalsHandle[x][2][5] = 0;
                    }
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
            
            if(pos == side.d.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.d.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 8; z++)
                        {
                            side.d.totalsHandle[x][y][9-z] = (Pump_rxBuffer[w+4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2) && (z == 4))
                            {
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 7;
                    for(z = 4; z >= 1; z--)
                    {
                        side.d.totalsHandle[x][2][z] = side.d.totalsHandle[x][2][z+4];
                    }
                    side.d.totalsHandle[x][0][0] = 8;
                    side.d.totalsHandle[x][1][0] = 8;
                    side.d.totalsHandle[x][2][0] = 4;
                    if(ppux10 == 1)
                    {
                        side.d.totalsHandle[x][2][0] = 5;
                        side.d.totalsHandle[x][2][5] = 0;
                    }
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
            
        }else{
            Pump_ClearRxBuffer();
            return 0;
        }
    }else if((x == 46)||(x == 88)||(x == 130)||(x == 172))
    {     // Version 7 digitos
        if((Pump_rxBuffer[0] == 0xFF) && (Pump_rxBuffer[1] == 0xF6) && (Pump_rxBuffer[3] == 0xF9))
        {
            gradeHandle = (x/40) & 0x07;                        // Identificando cantidad de mangueras en el surtidor
            if(pos == side.a.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.a.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 12; z++)
                        {
                            side.a.totalsHandle[x][y][13 - z] = (Pump_rxBuffer[w + 4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2)&&(z == 6)){
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 9;
                    for(z = 6; z >= 1; z--)
                    {
                        side.a.totalsHandle[x][2][z] = side.a.totalsHandle[x][2][z + 6];
                    }
                    side.a.totalsHandle[x][0][0] = 12;
                    side.a.totalsHandle[x][1][0] = 12;
                    side.a.totalsHandle[x][2][0] = 6;
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
            if(pos == side.b.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.b.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 12; z++)
                        {
                            side.b.totalsHandle[x][y][13-z] = (Pump_rxBuffer[w+4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2)&&(z == 6))
                            {
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 9;
                    for(z = 6;z >= 1; z--)
                    {
                        side.b.totalsHandle[x][2][z] = side.b.totalsHandle[x][2][z+6];
                    }
                    side.b.totalsHandle[x][0][0] = 12;
                    side.b.totalsHandle[x][1][0] = 12;
                    side.b.totalsHandle[x][2][0] = 6;
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
            if(pos == side.c.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.c.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 12; z++)
                        {
                            side.c.totalsHandle[x][y][13 - z] = (Pump_rxBuffer[w + 4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2)&&(z == 6)){
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 9;
                    for(z = 6; z >= 1; z--)
                    {
                        side.c.totalsHandle[x][2][z] = side.c.totalsHandle[x][2][z + 6];
                    }
                    side.c.totalsHandle[x][0][0] = 12;
                    side.c.totalsHandle[x][1][0] = 12;
                    side.c.totalsHandle[x][2][0] = 6;
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
            if(pos == side.d.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.d.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 12; z++)
                        {
                            side.d.totalsHandle[x][y][13 - z] = (Pump_rxBuffer[w + 4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2)&&(z == 6)){
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 9;
                    for(z = 6; z >= 1; z--)
                    {
                        side.d.totalsHandle[x][2][z] = side.d.totalsHandle[x][2][z + 6];
                    }
                    side.d.totalsHandle[x][0][0] = 12;
                    side.d.totalsHandle[x][1][0] = 12;
                    side.d.totalsHandle[x][2][0] = 6;
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
        }else{
            Pump_ClearRxBuffer();
            return 0;
        }
    }else{
        Pump_ClearRxBuffer();
        return 0;
    }
    Pump_ClearRxBuffer();
    return 0;
}

/*
*********************************************************************************************************
*                                         uint8 price_change(uint8 pos)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
uint8 priceChange(uint8 pos,uint8 handle,uint8 *value){
	uint8 buffer[15] = {0xFF,0,0xF4,0xF6,0,0xF7,0,0,0,0,0,0,0,0,0},size,x,y;
    for(x = 1; x <= 6; x++)
    {
        if(value[x] == ',')
        {
            for(y = x; y >= 2; y--)
            {
                value[y] = value[y - 1];
            }
            value[1] = '0';
            break;
        }
    }
	if(digits != 7)
    {
		buffer[1] = 0xE5;
		buffer[4] = (0xE0 | ((handle & 0x0f)));
		if(ppux10 == 0)
        {
			for(x = 0; x < 4; x++)
            {
				buffer[6 + x]=(0xE0 | (value[x] & 0x0F));
			}
		}else{
            for(x = 0; x < 4; x++){
				buffer[6 + x]=(0xE0 | (value[x+1]&0x0F));  //Verificar ppux10
			}	
		}
		buffer[10] = 0xFB;
		for(x = 0; x <= 10; x++)
        {
			buffer[11] += (buffer[x] & 0x0F);	
		}
		buffer[11] = (((~buffer[11]) + 1) & 0x0F) | 0xE0;
		buffer[12] = 0xF0;
		size = 12;
	}
	if(digits == 7)
    {
		buffer[1] = 0xE3;
		buffer[4] = (0xE0 | ((handle & 0x0f)));	
        for(x = 0; x < 6; x++)
        {
            buffer[6 + x] = (0xE0 | (value[x] & 0x0F));
        }	
        buffer[11] = 0xE0;
		buffer[12] = 0xFB;
		for(x = 0; x <= 12; x++)
        {
			buffer[13] += (buffer[x] & 0x0F);	
		}
		buffer[13] = (((~buffer[13]) + 1) & 0x0F) | 0xE0;
		buffer[14] = 0xF0;
		size = 14;
	}	
    Pump_ClearRxBuffer();
	Pump_PutChar(0x20|pos);	
    
    //CyDelay(100);
    vTaskDelay( 100 / portTICK_PERIOD_MS );
    
    if(Pump_GetRxBufferSize() >= 1)
    {
		if(Pump_ReadRxData() == (0xD0 | pos))
        {
            Pump_ClearRxBuffer();
            
            for(x = 0; x <= size; x++)
            {
               	Pump_PutChar(buffer[x]); 	
            }
            
            Pump_ClearRxBuffer();
            
            vTaskDelay( 50 / portTICK_PERIOD_MS );
            
//			if(get_state(pos) == 0)
//            {
//				return 0;
//			}
//			else
//            {
//				return 1;
//			}
            return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;	
	}
}

/*
*********************************************************************************************************
*                  uint8 PresetData(uint8 pos, uint8 grade, uint8 *value, uint8 preset)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
uint8 PresetData(uint8 sideR, char8 grade, uint8 *value, uint8 preset){
    char8 SendComand[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint8 state,x,y,z,decimal,w,v;    
    char8 PumpDataReceive =0;
    x = 0;
    z = 0;
    decimal = 0;
    decimal=0;
    for(x = 1; x <= value[0]; x++)
    {
        if(value[x] == ',')
        {
            if((decimal = value[0] - x) > 3)
            {
                return 0;
            }
            for(y = x; y >= 2; y--)
            {
                value[y] = value[y - 1];
            }
            value[1]='0';
            break;
        }
    }
    if(digits != value[0])
    {
        for(x = 0; x < value[0]; x++)
        {
            value[digits - x] = value[value[0] - x];
        }
        for(x = (digits - value[0]); x > 0; x--)
        {
            value[x]='0';
        }
        value[0] = digits;
    }
    
    state = get_state(sideR);
    while(state == 0)
    {
        state = get_state(sideR);
    }
    if(state == 0x06 || state == 0x07)
    {
        Pump_PutChar(0x20 | sideR);
        //CyDelay(50);
        vTaskDelay( 50 / portTICK_PERIOD_MS );
        PumpDataReceive = Pump_ReadRxData();
    }
    Pump_ClearRxBuffer();
    Pump_ClearRxBuffer();
    x = 0;    
    if(PumpDataReceive == (0xd0|sideR))
    {
        SendComand[x] = SOM; x++;
        
        if(digits != 7) 
        {
            if(preset == 0x01)
            {
                SendComand[x] = 0xE3; x++; // Producto especificado en formato estandar volumen
            }
            else
            {
                SendComand[x] = 0xE2; x++; // Producto especificado en formato estandar dinero
            }
        }
        else
        {
            SendComand[x] = 0xE1; x++; // Producto especificado en formato extendido
        }
        
        // Lado A
        if(sideR == side.a.dir)
        {
            // Tipo de preset: 1 dinero 2 volumen
            if(preset == 0x03) //Full
            {
                SendComand[x] = 0xF0 | (0x02 & 0x0F); x++; //Full se hace en dinero
            }
            else
            {
                SendComand[x] = 0xF0 | (preset & 0x0F); x++;
            }
            if(digits != 7)
            {
                SendComand[x] = 0xF4; x++;
            }
            SendComand[x] = 0xF6; x++;
            SendComand[x] = 0xE0 | ((grade - 1) & 0x0F); x++;  // Producto
            SendComand[x] = PRDn; x++;
            
            if(preset == 0x03)   //Full
            {
                for(y = x; y < digits + x; y++ )
                {
                    SendComand[y] = 0xE9;                    
                }                
                x = y;
                if(digits != 7)
                {
                    for(y = x; y < 11; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }
                else
                {
                    if(digits != 7)
                    {
                        for(y = x; y < 11; y ++ )
                        {
                            SendComand[y] = 0xE0;
                            x++;
                        }
                    }
                    else
                    {
                        for(y = x; y < 14; y ++ )
                        {
                            SendComand[y] = 0xE0;
                            x++;
                        }
                    }
                    
                }
            }
            if(preset == 0x02)  //Dinero
            {
                z = value[0];
                for(y = x; y < value[0] + x; y++)
                {
                    SendComand[y] = 0xE0|(value[z] & 0x0F); z--;                    
                }                
                x = y;
                
                if(digits != 7)
                {
                    for(y = x; y < 11; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }
                else
                {
                    for(y = x; y < 14; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }
                
            }
            if(preset == 0x01)  // Volumen
            {
                if(digits != 7)
                {
                    if(decimal > (VolDec - 1))
                    {
                        for(w = value[0]; w > 1; w--)
                        {
                            value[w] = value[w - 1];
                        }
                        value[1] = '0';
                    }else if(decimal < (VolDec - 1))
                    {
                        v = (VolDec - 1) - (decimal);
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v]= '0';
                                }
                                break;
                            }
                        }
                    }
                }
                else{
                    if(decimal > 1)
                    {
                        v = VolDec - decimal;
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v] = '0';
                                }
                                break;
                            }
                        }
                    }else{
                        v = VolDec - decimal;
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v] = '0';
                                }
                                break;
                            }
                        }
                    }
                }                    
                
                z = value[0];
                
                if(digits != 7)
                {
                    for(y = x; y < value[0] - 1 + x; y++)
                    {
                        SendComand[y] = 0xE0 |(value[z] & 0x0F); z--;                    
                    }
                    x = y;
                }
                else
                {
                    for(y = x; y < value[0] + x; y++)
                    {
                        SendComand[y] = 0xE0 |(value[z] & 0x0F); z--;                    
                    }
                    x = y;   
                }
                
                
                if(digits >= 7)
                {
                    for(y = x; y < 14; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }
                
            }
            
            SendComand[x] = 0xFB;  x++;
            SendComand[x] = GetLRC(SendComand);  x++;
            SendComand[x] = (EOM);
            for(y = 0; y <= x; y++)
            {
                Pump_PutChar(SendComand[y]);
            } 
            //CyDelay(50);
            vTaskDelay( 50 / portTICK_PERIOD_MS );
            return 1;
        }       
        // Lado B
        if(sideR == side.b.dir)
        {
            if(preset == 0x03)
            {
                SendComand[x] = 0xF0 | (0x02 & 0x0F); x++;
            }
            else
            {
                SendComand[x] = 0xF0 | (preset & 0x0F); x++;
            }
            if(digits != 7)
            {
                SendComand[x] = 0xF4; x++;
            }
            SendComand[x] = 0xF6; x++;
            SendComand[x] = 0xE0 | ((grade - 1) & 0x0F); x++;
            SendComand[x] = PRDn; x++;
            if(preset == 0x03)
            {
                for(y = x; y < digits + x; y++ )
                {
                    SendComand[y] = 0xE9;                    
                }                
                x = y;
                for(y = x; y < 14; y ++ )
                {
                    SendComand[y] = 0xE0;
                    x++;
                }                
            }
            if(preset == 0x02)
            {
                z = value[0];
                for(y = x; y < value[0] + x; y++)
                {
                    SendComand[y] = 0xE0|(value[z] & 0x0F); z--;                    
                }                
                x = y;
                if(digits != 7)
                {
                    for(y = x; y < 11; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }
                else
                {
                    for(y = x; y < 14; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }               
            }
            if(preset == 0x01)
            {
                if(digits != 7)
                {
                    if(decimal > (VolDec - 1))
                    {
                        for(w = value[0]; w > 1; w--)
                        {
                            value[w] = value[w - 1];
                        }
                        value[1] = '0';
                    }else if(decimal < (VolDec - 1))
                    {
                        v = (VolDec - 1) - (decimal);
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v]= '0';
                                }
                                break;
                            }
                        }
                    }
                }
                else{
                    if(decimal > 1)
                    {
                        v = VolDec - decimal;
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v] = '0';
                                }
                                break;
                            }
                        }
                    }else{
                        v = VolDec - decimal;
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v] = '0';
                                }
                                break;
                            }
                        }
                    }
                }                    
                z = value[0];
                
                if(digits != 7)
                {
                    for(y = x; y < value[0] - 1 + x; y++)
                    {
                        SendComand[y] = 0xE0 |(value[z] & 0x0F); z--;                    
                    }
                    x = y;
                }
                else
                {
                    for(y = x; y < value[0] + x; y++)
                    {
                        SendComand[y] = 0xE0 |(value[z] & 0x0F); z--;                    
                    }
                    x = y;   
                }
                
                if(digits >= 7)
                {
                    for(y = x; y < 14; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }               
            }
            SendComand[x] = 0xFB;  x++;
            SendComand[x] = GetLRC(SendComand);  x++;
            SendComand[x] = (EOM);
            for(y = 0; y <= x; y++)
            {
                Pump_PutChar(SendComand[y]);
            } 
            //CyDelay(50);
            vTaskDelay( 50 / portTICK_PERIOD_MS );
            return 1;
        }
        // Lado C
        if(sideR == side.c.dir)
        {
            if(preset == 0x03)
            {
                SendComand[x] = 0xF0 | (0x02 & 0x0F); x++;
            }
            else
            {
                SendComand[x] = 0xF0 | (preset & 0x0F); x++;
            }
            if(digits != 7)
            {
                SendComand[x] = 0xF4; x++;
            }
            SendComand[x] = 0xF6; x++;
            SendComand[x] = 0xE0 | ((grade - 1) & 0x0F); x++;
            SendComand[x] = PRDn; x++;
            if(preset == 0x03)
            {
                for(y = x; y < digits + x; y++ )
                {
                    SendComand[y] = 0xE9;                    
                }                
                x = y;
                for(y = x; y < 14; y ++ )
                {
                    SendComand[y] = 0xE0;
                    x++;
                }                
            }
            if(preset == 0x02)
            {
                z = value[0];
                for(y = x; y < value[0] + x; y++)
                {
                    SendComand[y] = 0xE0|(value[z] & 0x0F); z--;                    
                }                
                x = y;
                if(digits != 7)
                {
                    for(y = x; y < 11; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }
                else
                {
                    for(y = x; y < 14; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }                
            }
            if(preset == 0x01)
            {
                if(digits != 7)
                {
                    if(decimal > (VolDec - 1))
                    {
                        for(w = value[0]; w > 1; w--)
                        {
                            value[w] = value[w - 1];
                        }
                        value[1] = '0';
                    }else if(decimal < (VolDec - 1))
                    {
                        v = (VolDec - 1) - (decimal);
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v]= '0';
                                }
                                break;
                            }
                        }
                    }
                }
                else{
                    if(decimal > 1)
                    {
                        v = VolDec - decimal;
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v] = '0';
                                }
                                break;
                            }
                        }
                    }else{
                        v = VolDec - decimal;
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v] = '0';
                                }
                                break;
                            }
                        }
                    }
                }                    
                z = value[0];
                
                if(digits != 7)
                {
                    for(y = x; y < value[0] - 1 + x; y++)
                    {
                        SendComand[y] = 0xE0 |(value[z] & 0x0F); z--;                    
                    }
                    x = y;
                }
                else
                {
                    for(y = x; y < value[0] + x; y++)
                    {
                        SendComand[y] = 0xE0 |(value[z] & 0x0F); z--;                    
                    }
                    x = y;   
                }
                if(digits >= 7)
                {
                    for(y = x; y < 14; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }               
            }
            SendComand[x] = 0xFB;  x++;
            SendComand[x] = GetLRC(SendComand);  x++;
            SendComand[x] = (EOM);
            for(y = 0; y <= x; y++)
            {
                Pump_PutChar(SendComand[y]);
            } 
            //CyDelay(50);
            vTaskDelay( 50 / portTICK_PERIOD_MS );
            return 1;
        }
        // Lado D
        if(sideR == side.d.dir)
        {
            if(preset == 0x03)
            {
                SendComand[x] = 0xF0 | (0x02 & 0x0F); x++;
            }
            else
            {
                SendComand[x] = 0xF0 | (preset & 0x0F); x++;
            }
            
            if(digits != 7)
            {
                SendComand[x] = 0xF4; x++;
            }
            SendComand[x] = 0xF6; x++;
            SendComand[x] = 0xE0 | ((grade - 1) & 0x0F); x++;
            SendComand[x] = PRDn; x++;
            if(preset == 0x03)
            {
                for(y = x; y < digits + x; y++ )
                {
                    SendComand[y] = 0xE9;                    
                }                
                x = y;
                for(y = x; y < 14; y ++ )
                {
                    SendComand[y] = 0xE0;
                    x++;
                }                
            }
            if(preset == 0x02)
            {
                z = value[0];
                for(y = x; y < value[0] + x; y++)
                {
                    SendComand[y] = 0xE0|(value[z] & 0x0F); z--;                    
                }                
                x = y;
                if(digits != 7)
                {
                    for(y = x; y < 11; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }
                else
                {
                    for(y = x; y < 14; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }                
            }
            if(preset == 0x01)
            {
                if(digits != 7)
                {
                    if(decimal > (VolDec - 1))
                    {
                        for(w = value[0]; w > 1; w--)
                        {
                            value[w] = value[w - 1];
                        }
                        value[1] = '0';
                    }else if(decimal < (VolDec - 1))
                    {
                        v = (VolDec - 1) - (decimal);
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v]= '0';
                                }
                                break;
                            }
                        }
                    }
                }
                else{
                    if(decimal > 1)
                    {
                        v = VolDec - decimal;
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v] = '0';
                                }
                                break;
                            }
                        }
                    }else{
                        v = VolDec - decimal;
                        for(w = 1; w <= value[0]; w++)
                        {
                            value[w] = value[v + w];
                            if((w + v) == value[0])
                            {
                                for(v = 1; v <= (value[0] - w); v++)
                                {
                                    value[w + v] = '0';
                                }
                                break;
                            }
                        }
                    }
                }                    
                z = value[0];
                
                if(digits != 7)
                {
                    for(y = x; y < value[0] - 1 + x; y++)
                    {
                        SendComand[y] = 0xE0 |(value[z] & 0x0F); z--;                    
                    }
                    x = y;
                }
                else
                {
                    for(y = x; y < value[0] + x; y++)
                    {
                        SendComand[y] = 0xE0 |(value[z] & 0x0F); z--;                    
                    }
                    x = y;   
                }
                
                if(digits >= 7)
                {
                    for(y = x; y < 14; y ++ )
                    {
                        SendComand[y] = 0xE0;
                        x++;
                    }
                }                
            }
            SendComand[x] = 0xFB;  x++;
            SendComand[x] = GetLRC(SendComand);  x++;
            SendComand[x] = (EOM);
            for(y = 0; y <= x; y++)
            {
                Pump_PutChar(SendComand[y]);
            } 
            //CyDelay(50);
            vTaskDelay( 50 / portTICK_PERIOD_MS );
            return 1;
        }
    }
    return 0;
}

/*
*********************************************************************************************************
*                  uint8 PumpCompleteConfiguration(uint8 pos, uint8 grade, uint8 *value, uint8 preset)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : 0 if Success
*
* Caller(s)   : 
*
* Note(s)     : Set config register.
*********************************************************************************************************
*/
uint8 PumpCompleteConfiguration(uint8 side){   
    uint8 state,x;
    char8 SendComand[9];
    char8 PumpDataReceive =0;    
    uint8 BufferSize = 0;
    
    // Obtiene el estado del sutidor 
    state = get_state(side);
    ppux10 = 0;
    //Envia comando 2X y espera respuesta DX
    if(state == 0x06)
    {
        Pump_PutChar(0x20 | side);
        CyDelay(50);
        PumpDataReceive = Pump_ReadRxData();
    }  
    Pump_ClearRxBuffer();
    
 ////////  Envia comando de funciones especial 00E para solicitar configuracion   /////////
    if(PumpDataReceive == (0xd0|side))
    {    
        SendComand[0] = SOM;        //Start Of Message    
        SendComand[1] = (0xE9);     //Data Length
        SendComand[2] = (0xFE);     //Special Functions Next (0xB0 0xB0 0xBE)
        SendComand[3] = (0xEE);     //Complete Pump Configuration Request (sf1)
        SendComand[4] = (0xE0);     //Complete Pump Configuration Request (sf2)
        SendComand[5] = (0xE0);     //Complete Pump Configuration Request (sf3)
        SendComand[6] = (0xFB);
        SendComand[7] = GetLRC(SendComand);
        SendComand[8] = (EOM);
        
        for(x = 0; x <= 8; x++)
        {
            Pump_PutChar(SendComand[x]);
        } 
        CyDelay(200);
    }
    
    BufferSize = Pump_GetRxBufferSize();
    
    char8 buffer[BufferSize];
    
    for(x = 0; x <= BufferSize; x++)
    {
       buffer[x] = Pump_ReadRxData(); 
    }
    
    Pump_ClearRxBuffer();

 // Almacena las configuraciones obtenidas
    UnitType            =  buffer [10] & 0x0F;
    ConversionFactor    =  buffer [12] & 0x0F;
    
    if(ConversionFactor == 1)
    {
        VolUnit[0] = 0x47;
        VolUnit[1] = 0x61;
        VolUnit[2] = 0x6C;
        VolUnit[3] = 0x20;
        VolUnit[4] = 0x20;
        VolUnit[5] = 0x20;
    }
    
    if(ConversionFactor == 2)
    {
        VolUnit[0] = 0x55;
        VolUnit[1] = 0x6B;
        VolUnit[2] = 0x20;
        VolUnit[3] = 0x47;
        VolUnit[4] = 0x61;
        VolUnit[5] = 0x6C;        
    }
    
    MoneyDec            = (buffer [14] & 0x0F) - 1;
    
    if( (buffer [16] & 0x0F) == 1 || (buffer [16] & 0x0F) == 4)
    {
        VolDec              = 3;
    }
    if( (buffer [16] & 0x0F) == 3 || (buffer [16] & 0x0F) == 0){
        VolDec              = 2;
    }
    if( (buffer [16]&0x0F) == 2)
    {
        VolDec              = 1;
    }
    PPUDec              = (buffer [18] & 0x0F) - 1;
    DDMode              =  buffer [20] & 0x0F;
    if(MoneyDec == 0x03 && PPUDec == 0x02)
        ppux10 = 1;
    return 0;
} 

/*Pump handle selection grade */
uint8 PumpHoseActiveState(uint8 side){       
    uint8 state, x;
    char8 SendComand[9];
    char8 PumpDataReceive = 0;       
    uint8 BufferSize = 0;
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state = get_state(side);
    if(state == PUMP_IDLE || state == PUMP_CALLING)
    {
        Pump_PutChar(0x20 | side);
        //CyDelay(50);
        vTaskDelay( 50 / portTICK_PERIOD_MS );
        PumpDataReceive = Pump_ReadRxData();
    }
    
    Pump_ClearRxBuffer();
    
    // Send special command 010 (extended pump status) 
    if(PumpDataReceive == (0xd0 | side))
    {
        SendComand[0] = SOM;            //Start Of Message
        SendComand[1] = 0xE9;           //Data Length
        SendComand[2] = 0xFE;           //Special Functions Next (0xB0 0xB0 0xB6)
        SendComand[3] = 0xE0;           //Complete Pump Configuration Request (sf1)
        SendComand[4] = 0xE1;           //Complete Pump Configuration Request (sf2)
        SendComand[5] = 0xE0;           //Complete Pump Configuration Request (sf3)
        SendComand[6] = 0xFB;           
        SendComand[7] = GetLRC(SendComand);
        SendComand[8] = EOM;
        
        for(x = 0; x <= 8; x++)
        {
            Pump_PutChar(SendComand[x]);
        } 
        //if(UnitType > 0){
          //  CyDelay(300);
        //}else{
            //CyDelay(150);
         vTaskDelay( 150 / portTICK_PERIOD_MS );
        //}
    }    
////////////////////////////////////////////////////////////////////////////////////////////////////////////
    BufferSize = Pump_GetRxBufferSize();
    char8 buffer[BufferSize];
    
    // Receive extended pump status
    for(x = 0; x <= BufferSize; x++)
    {
       buffer[x] = Pump_ReadRxData(); 
    }
    
    Pump_ClearRxBuffer();
    
    // Return the grade handle
    if((buffer[0x0C] & 0x0F) == 0x01)
    {
        return (buffer[0x0E] & 0x0F);
    }
    
    return 0;
    
}

/*
*********************************************************************************************************
*                                         uint8 get_sale(uint8 pos)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
uint8 getSale(uint8 pos){
	uint8 x;    
	Pump_ClearRxBuffer();
	Pump_PutChar(0x40 | pos);
    if(OSonline)
    {
        vTaskDelay(250 / portTICK_PERIOD_MS);
    }
    else
    {
        CyDelay(250);
    }
    
    
    //6 Digits
	if((digits != 7) && (Pump_GetRxBufferSize() == 33))
    {
		if((Pump_rxBuffer[0] == 0xFF) && (Pump_rxBuffer[2] == 0xF8) && (Pump_rxBuffer[32] == 0xF0))
        {
			if(pos == side.a.dir)
            {
				side.a.productSale = ((Pump_rxBuffer[9] & 0x0F) + 1) + 0x30;
				for(x = 1; x <= 4; x++)
                {
					side.a.ppuSale[5 - x]=((Pump_rxBuffer[x + 11] & 0x0F) + 0x30);
				}
                side.a.ppuSale[0] = 4;
                if(ppux10 == 1)
                {
                    side.a.ppuSale[0] = 5;
                    side.a.ppuSale[5] = '0';
                }
				for(x = 1; x <= 6; x++)
                {
					side.a.volumeSale[7 - x] = ((Pump_rxBuffer[x + 16] & 0x0F) + 0x30);
				}		
                side.a.volumeSale[0] = 6;                
				for(x = 1; x <= 6; x++)
                {
					side.a.moneySale[7 - x] = ((Pump_rxBuffer[x + 23] & 0x0F) + 0x30);
				}
                if(digits == 5)
                {
                    for(x = 6; x > 1; x--)
                    {
                        side.a.moneySale[x] = side.a.moneySale[x - 1];
                    }
                    side.a.moneySale[1] = '0';
                }
                side.a.moneySale[0] = 6;
			}
			if(pos == side.b.dir)
            {
				side.b.productSale = ((Pump_rxBuffer[9] & 0x0F) + 1) + 0x30;
				for(x = 1; x <= 4; x++)
                {
					side.b.ppuSale[5 - x] = ((Pump_rxBuffer[x + 11] & 0x0F) + 0x30);
				}
                side.b.ppuSale[0]=4;
                if(ppux10==1){
                    side.b.ppuSale[0]=5;
                    side.b.ppuSale[5]='0';
                }
				for(x=1;x<=6;x++){
					side.b.volumeSale[7-x]=((Pump_rxBuffer[x+16]&0x0F)+0x30);
				}
                side.b.volumeSale[0]=6;
				for(x=1;x<=6;x++){
					side.b.moneySale[7-x]=((Pump_rxBuffer[x+23]&0x0F)+0x30);
				}	
                if(digits==5){
                    for(x=6;x>1;x--){
                        side.b.moneySale[x]=side.b.moneySale[x-1];
                    }
                    side.b.moneySale[1]='0';
                }
                side.b.moneySale[0]=6;
			}
            if(pos == side.c.dir)
            {
				side.c.productSale = ((Pump_rxBuffer[9] & 0x0F) + 1) + 0x30;
				for(x = 1; x <= 4; x++)
                {
					side.c.ppuSale[5 - x]=((Pump_rxBuffer[x + 11] & 0x0F) + 0x30);
				}
                side.c.ppuSale[0] = 4;
                if(ppux10 == 1)
                {
                    side.a.ppuSale[0] = 5;
                    side.a.ppuSale[5] = '0';
                }
				for(x = 1; x <= 6; x++)
                {
					side.c.volumeSale[7 - x] = ((Pump_rxBuffer[x + 16] & 0x0F) + 0x30);
				}		
                side.c.volumeSale[0] = 6;                
				for(x = 1; x <= 6; x++)
                {
					side.c.moneySale[7 - x] = ((Pump_rxBuffer[x + 23] & 0x0F) + 0x30);
				}
                if(digits == 5)
                {
                    for(x = 6; x > 1; x--)
                    {
                        side.c.moneySale[x] = side.c.moneySale[x - 1];
                    }
                    side.c.moneySale[1] = '0';
                }
                side.c.moneySale[0] = 6;
			}
            if(pos == side.d.dir)
            {
				side.d.productSale = ((Pump_rxBuffer[9] & 0x0F) + 1) + 0x30;
				for(x = 1; x <= 4; x++)
                {
					side.d.ppuSale[5 - x]=((Pump_rxBuffer[x + 11] & 0x0F) + 0x30);
				}
                side.d.ppuSale[0] = 4;
                if(ppux10 == 1)
                {
                    side.d.ppuSale[0] = 5;
                    side.d.ppuSale[5] = '0';
                }
				for(x = 1; x <= 6; x++)
                {
					side.d.volumeSale[7 - x] = ((Pump_rxBuffer[x + 16] & 0x0F) + 0x30);
				}		
                side.d.volumeSale[0] = 6;                
				for(x = 1; x <= 6; x++)
                {
					side.d.moneySale[7 - x] = ((Pump_rxBuffer[x + 23] & 0x0F) + 0x30);
				}
                if(digits == 5)
                {
                    for(x = 6; x > 1; x--)
                    {
                        side.d.moneySale[x] = side.d.moneySale[x - 1];
                    }
                    side.d.moneySale[1] = '0';
                }
                side.d.moneySale[0] = 6;
			}
            
			return 1;
		}
		else{
			return 0;
		}
	}
    // 7 digits
	else if((digits == 7) && (Pump_GetRxBufferSize() == 39))
    {
		if((Pump_rxBuffer[0] == 0xFF) && (Pump_rxBuffer[2] == 0xF8) && (Pump_rxBuffer[38] == 0xF0))
        {
			if(pos == side.a.dir)
            {
				side.a.productSale = ((Pump_rxBuffer[9] & 0x0F) + 1) + 0x30;
				for(x = 1; x <= 6; x++)
                {
					side.a.ppuSale[7 - x] = ((Pump_rxBuffer[x + 11] & 0x0F) + 0x30);
				}
                side.a.ppuSale[0] = 6;
				for(x = 1; x <= 8; x++)
                {
					side.a.volumeSale[9 - x] = ((Pump_rxBuffer[x + 18] & 0x0F) + 0x30);
				}		
                side.a.volumeSale[0] = 8;
				for(x = 1; x <= 7; x++)
                {
					side.a.moneySale[9 - x] = ((Pump_rxBuffer[x + 28] & 0x0F) + 0x30);
				}
                side.a.moneySale[1] = '0';
                side.a.moneySale[0] = 8;
			}
			if(pos == side.b.dir)
            {
				side.b.productSale=((Pump_rxBuffer[9]&0x0F)+1)+0x30;
				for(x=1;x<=6;x++){
					side.b.ppuSale[7-x]=((Pump_rxBuffer[x+11]&0x0F)+0x30);
				}
                side.b.ppuSale[0]=6;
				for(x=1;x<=8;x++){
					side.b.volumeSale[9-x]=((Pump_rxBuffer[x+18]&0x0F)+0x30);
				}	
                side.b.volumeSale[0]=8;
				for(x=1;x<=7;x++){
					side.b.moneySale[9-x]=((Pump_rxBuffer[x+28]&0x0F)+0x30);
				}	
                side.b.moneySale[1]='0';
                side.b.moneySale[0]=8;
			}
            if(pos == side.c.dir)
            {
				side.c.productSale = ((Pump_rxBuffer[9] & 0x0F) + 1) + 0x30;
				for(x = 1; x <= 6; x++)
                {
					side.c.ppuSale[7 - x] = ((Pump_rxBuffer[x + 11] & 0x0F) + 0x30);
				}
                side.c.ppuSale[0] = 6;
				for(x = 1; x <= 8; x++)
                {
					side.c.volumeSale[9 - x] = ((Pump_rxBuffer[x + 18] & 0x0F) + 0x30);
				}		
                side.c.volumeSale[0] = 8;
				for(x = 1; x <= 7; x++)
                {
					side.c.moneySale[9 - x] = ((Pump_rxBuffer[x + 28] & 0x0F) + 0x30);
				}
                side.c.moneySale[1] = '0';
                side.c.moneySale[0] = 8;
			}
            
            if(pos == side.d.dir)
            {
				side.d.productSale = ((Pump_rxBuffer[9] & 0x0F) + 1) + 0x30;
				for(x = 1; x <= 6; x++)
                {
					side.d.ppuSale[7 - x] = ((Pump_rxBuffer[x + 11] & 0x0F) + 0x30);
				}
                side.d.ppuSale[0] = 6;
				for(x = 1; x <= 8; x++)
                {
					side.d.volumeSale[9 - x] = ((Pump_rxBuffer[x + 18] & 0x0F) + 0x30);
				}		
                side.d.volumeSale[0] = 8;
				for(x = 1; x <= 7; x++)
                {
					side.d.moneySale[9 - x] = ((Pump_rxBuffer[x + 28] & 0x0F) + 0x30);
				}
                side.d.moneySale[1] = '0';
                side.d.moneySale[0] = 8;
			}
			return 1;
		}
		else{
			return 0;
		}
	}
	return 0;
}

uint8_t GetLRC(char8 *_pbuffer){
    uint8_t lrc = 0;
    while(*_pbuffer != 0xFB)
    {
        lrc += (*_pbuffer & 0x0F);
        _pbuffer++;
    }
    lrc += (*_pbuffer & 0x0F);
    return (((~lrc + 1) & 0x0F) | 0xE0);
}

/*
*********************************************************************************************************
*                                         void Authorization(uint8 pos, uint8 Type)
*
* Description : Execute the authorization depend of type:
*               1 : Authorization from MUX
*               2 : Authorization from External Controller
*               3 : Authorization from Server (iButton, Tag, etc...)
*               4 : Authorization free (After Hose handle)
*
* Argument(s) : position (1 - 15), type (1 - 4)
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
void Authorization(uint8 pos){
         
    Pump_PutChar(0x10 | pos);
   
}

/*
*********************************************************************************************************
*                                    uint8 get_totals(uint8 pos)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
uint8 getTotalsInit(uint8 pos){
    uint8 x,y,z,w,gradeHandle;
    
    Pump_ClearRxBuffer();
    Pump_PutChar(0x50|pos);
    CyWdtClear();
    CyDelay(900);
    //vTaskDelay( 900 / portTICK_PERIOD_MS );
    CyWdtClear();
    
    x = Pump_GetRxBufferSize();
    
    if((x == 34) || (x == 64) || (x == 94) || (x == 124))  // Version 5 ó 6 digitos
    {           
        if((Pump_rxBuffer[0] == 0xFF) && (Pump_rxBuffer[1] == 0xF6) && (Pump_rxBuffer[3] == 0xF9))
        {
            gradeHandle = (x / 30) & 0x07;                    //Identificando cantidad de mangueras en el surtidor
            if(pos == side.a.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.a.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 8; z++)
                        {
                            side.a.totalsHandle[x][y][9-z] = (Pump_rxBuffer[w+4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2) && (z == 4))
                            {
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 7;
                    for(z = 4; z >= 1; z--)
                    {
                        side.a.totalsHandle[x][2][z] = side.a.totalsHandle[x][2][z+4];
                    }
                    side.a.totalsHandle[x][0][0] = 8;
                    side.a.totalsHandle[x][1][0] = 8;
                    side.a.totalsHandle[x][2][0] = 4;
                    if(ppux10 == 1)
                    {
                        side.a.totalsHandle[x][2][0] = 5;
                        side.a.totalsHandle[x][2][5] = 0;
                    }
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }else{
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.b.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 8; z++)
                        {
                            side.b.totalsHandle[x][y][9-z] = (Pump_rxBuffer[w+4]&0x0F) + 0x30;
                            w++;
                            if((y == 2)&&(z == 4))
                            {
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 7;
                    for(z = 4; z >= 1; z--)
                    {
                        side.b.totalsHandle[x][2][z] = side.b.totalsHandle[x][2][z+4];
                    }
                    side.b.totalsHandle[x][0][0] = 8;
                    side.b.totalsHandle[x][1][0] = 8;
                    side.b.totalsHandle[x][2][0] = 4;
                    if(ppux10 == 1)
                    {
                        side.b.totalsHandle[x][2][0] = 5;
                        side.b.totalsHandle[x][2][5] = 0;
                    }
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
        }else{
            Pump_ClearRxBuffer();
            return 0;
        }
    }else if((x == 46)||(x == 88)||(x == 130)||(x == 172))
    {     // Version 7 digitos
        if((Pump_rxBuffer[0] == 0xFF) && (Pump_rxBuffer[1] == 0xF6) && (Pump_rxBuffer[3] == 0xF9))
        {
            gradeHandle = (x/40) & 0x07;                        // Identificando cantidad de mangueras en el surtidor
            if(pos == side.a.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.a.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                for(y = 0; y < 3; y ++)
                {
                    for(z = 0; z < 6; z++)
                    {
                        side.a.ppuAuthorized[y][z] = Pump_rxBuffer[(30 + (42 * y)) + z] & 0x0F;
                        EEPROM_1_WriteByte(side.a.ppuAuthorized[y][z],(20 + (y * 5)) + z); //PPU to EEprom
                    }                   
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 12; z++)
                        {
                            side.a.totalsHandle[x][y][13 - z] = (Pump_rxBuffer[w + 4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2)&&(z == 6)){
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 9;
                    for(z = 6; z >= 1; z--)
                    {
                        side.a.totalsHandle[x][2][z] = side.a.totalsHandle[x][2][z + 6];
                    }
                    side.a.totalsHandle[x][0][0] = 12;
                    side.a.totalsHandle[x][1][0] = 12;
                    side.a.totalsHandle[x][2][0] = 6;
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
            if(pos == side.b.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.b.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                for(y = 0; y < 3; y ++)
                {
                    for(z = 0; z < 6; z++)
                    {
                        side.b.ppuAuthorized[y][z] = Pump_rxBuffer[(30 + (42 * y)) + z] & 0x0F;
                        EEPROM_1_WriteByte(side.b.ppuAuthorized[y][z],(40 + (y * 5)) + z); //PPU to EEprom
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 12; z++)
                        {
                            side.b.totalsHandle[x][y][13-z] = (Pump_rxBuffer[w+4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2)&&(z == 6))
                            {
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 9;
                    for(z = 6;z >= 1; z--)
                    {
                        side.b.totalsHandle[x][2][z] = side.b.totalsHandle[x][2][z+6];
                    }
                    side.b.totalsHandle[x][0][0] = 12;
                    side.b.totalsHandle[x][1][0] = 12;
                    side.b.totalsHandle[x][2][0] = 6;
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
            if(pos == side.c.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.c.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                for(y = 0; y < 3; y ++)
                {
                    for(z = 0; z < 6; z++)
                    {
                        side.c.ppuAuthorized[y][z] = Pump_rxBuffer[(30 + (42 * y)) + z] & 0x0F;
                        EEPROM_1_WriteByte(side.c.ppuAuthorized[y][z],(60 + (y * 5)) + z); //PPU to EEprom
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 12; z++)
                        {
                            side.c.totalsHandle[x][y][13 - z] = (Pump_rxBuffer[w + 4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2) && (z == 6))
                            {
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 9;
                    for(z = 6;z >= 1; z--)
                    {
                        side.c.totalsHandle[x][2][z] = side.c.totalsHandle[x][2][z+6];
                    }
                    side.c.totalsHandle[x][0][0] = 12;
                    side.c.totalsHandle[x][1][0] = 12;
                    side.c.totalsHandle[x][2][0] = 6;
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
            if(pos == side.d.dir)
            {
                for(x = 0; x < 4; x++)
                {
                    for(y = 0; y < 3; y++)
                    {
                        for(z = 0; z < 14; z++)
                        {
                            side.d.totalsHandle[x][y][z] = 0;
                        }
                    }
                }
                for(y = 0; y < 3; y ++)
                {
                    for(z = 0; z < 6; z++)
                    {
                        side.d.ppuAuthorized[y][z] = Pump_rxBuffer[(30 + (42 * y)) + z] & 0x0F;
                        EEPROM_1_WriteByte(side.d.ppuAuthorized[y][z],(80 + (y * 5)) + z); //PPU to EEprom
                    }
                }
                w = 0;
                for(x = 0; x < gradeHandle; x++)
                {
                    for(y = 0; y <= 2; y++)
                    {
                        for(z = 1; z <= 12; z++)
                        {
                            side.d.totalsHandle[x][y][13-z] = (Pump_rxBuffer[w+4] & 0x0F) + 0x30;
                            w++;
                            if((y == 2)&&(z == 6))
                            {
                                break;
                            }
                        }
                        w++;
                    }
                    w = w + 9;
                    for(z = 6;z >= 1; z--)
                    {
                        side.d.totalsHandle[x][2][z] = side.d.totalsHandle[x][2][z+6];
                    }
                    side.d.totalsHandle[x][0][0] = 12;
                    side.d.totalsHandle[x][1][0] = 12;
                    side.d.totalsHandle[x][2][0] = 6;
                }
                Pump_ClearRxBuffer();
                return gradeHandle;
            }
        }else{
            Pump_ClearRxBuffer();
            return 0;
        }
    }else{
        Pump_ClearRxBuffer();
        return 0;
    }
    Pump_ClearRxBuffer();
    return 0;
}

