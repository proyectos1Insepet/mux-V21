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

/*  INCLUDES  */
/* Project and default includes */
#include <project.h>
#include <stdio.h>
/* RTOS includes. */
#include <FreeRTOS.h>
#include <semphr.h>
#include <protocol.h>
#include <variables.h>
#include <keyboard.h>
#include <ibutton.h>
#include <RFPoll.h>
#include <LCD.h>
#include <I2C.h>
#include <Printing.h>
#include "os_resource.h"
/* Drivers */
#include "RFtask.h"



/** @brief RF Task */
void RF_Task(void *arg)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 10;
    xLastWakeTime = xTaskGetTickCount();
    uint16 i = 0; 
    uint8 x;
    static uint16 cnt = 0;  
    uint8 FlagRF = 0;
    //uint8 FlagRecv = 0;
    uint8 buffer_rfTMP;
    uint8 GeneralConfig;

    // Inicializa variables
    if(NumPositions <= 2)
    {
        // Obtiene la posicion RF con umbral
        side.a.RF = EEPROM_1_ReadByte(200);
        side.b.RF = EEPROM_1_ReadByte(201);
        
        // Pone flag de totales en Cero
        side.a.FlagTotal = 0;
        side.b.FlagTotal = 0;
        
        
        bufferDisplay1.VarActual = 1;
        bufferDisplay2.VarActual = 1;
    }
    else
    {
        // Obtiene la posicion RF con umbral
        side.a.RF = EEPROM_1_ReadByte(200);
        side.b.RF = EEPROM_1_ReadByte(201);
        side.c.RF = EEPROM_1_ReadByte(202);
        side.d.RF = EEPROM_1_ReadByte(203);
        
        // Pone flag de totales en Cero
        side.a.FlagTotal = 0;
        side.b.FlagTotal = 0;
        side.c.FlagTotal = 0;
        side.d.FlagTotal = 0; 
        
        bufferDisplay1.VarActual = 1;
        bufferDisplay2.VarActual = 1;
        bufferDisplay3.VarActual = 1;
        bufferDisplay4.VarActual = 1;
    }
    LongEsperada = 0;
    while(1) 
    {       
        while(RF_Connection_GetRxBufferSize() > 0)  
        {
            
            buffer_rfTMP  = RF_Connection_ReadRxData();
            GeneralConfig = 0;
            FlagRF = 1;
            
//            if (buffer_rfTMP == 0xBC && HeaderRF == 1)
//            { 
//                i = 0;
//                HeaderRF = 0;
//                //LongEsperada = 0;
//            }
            if (buffer_rfTMP == 0xBC)
            { 
                i = 0;                
                LongEsperada = 0;
            }
                                 
            // Status
            if( buffer_rf[6] == 0xA1)
            {
                LongEsperada = 8;              
            }
            else if ( buffer_rf[6] == 0xA3)
            {
                LongEsperada = 25;
            }
            // Fin venta ACK
            else if ( buffer_rf[6] == 0xA4)
            {
                LongEsperada = 9;
            }
            
            // Totals request
            else if ( buffer_rf[6] == 0xA5)
            {
                LongEsperada = 8;
            }
            
            // PPU Setting
            else if ( buffer_rf[6] == 0xA6)
            {
                LongEsperada = 15;
            }
            
            // Impresion general   
            else if ( buffer_rf[6] == 0xA7)
            {
                if(buffer_rf[8] != 0x00)
                {
                    if(buffer_rf[8] + 0x09 < 234)
                    {
                        LongEsperada = buffer_rf[8] + 0x09;
                        vTaskDelay( 1 / portTICK_PERIOD_MS );
                    }
                    else
                    {
                        LongEsperada = 234;
                    }
                }
            } 
            
            else if ( buffer_rf[6] == 0xA9)
            {
                LongEsperada = 19;
            }
            
            else if ( buffer_rf[6] == 0xB3)
            {
                if(buffer_rf[7]== 0x01)
                {                    
					if(buffer_rf[8] != 0x00)
					{
						LongEsperada = buffer_rf[8] + 9;
					}
                }else{
					if(buffer_rf[8] != 0x00)
					{
						LongEsperada = buffer_rf[8] + 9;
					}
                }
            }
            else if ( buffer_rf[6] == 0xB4)
            {
                LongEsperada   = 42;                
            }
            else if ( buffer_rf[6] == 0xB6)
            {
                LongEsperada   = 102;                
            }
            else if ( buffer_rf[6] == 0xB7)
            {
                LongEsperada = 9;
            }
            else if ( buffer_rf[6] == 0xB8)
            {
                LongEsperada = 35;
            }
            else if ( buffer_rf[6] == 0xB9)
            {
                LongEsperada = 107;
            }
            else if ( buffer_rf[6] == 0xBB)
            {
                LongEsperada = 8;
            }
            else if ( buffer_rf[6] == 0xBF)
            {
                LongEsperada = 8;
            }
            else if ( buffer_rf[6] == 0xC3)
            {
                LongEsperada = 15;
            }
            // big config
            else if ( buffer_rf[6] == 0xE1)
            {
                LongEsperada   = 337;
                GeneralConfig  = 1;
            }
            
            else if ( buffer_rf[6] == 0xE2)
            {
                LongEsperada = 14;
            }
   
            // Turno
            else if ( buffer_rf[6] == 0xE4)
            {
                LongEsperada = 9;
            }
            else if ( buffer_rf[6] == 0xA8)
            {
                LongEsperada = 117;
            }
             
            buffer_rf[i] = buffer_rfTMP;         
            
            if (i == LongEsperada - 1)
            {                
                RF_Connection_ClearRxBuffer();
                
                if(NumPositions <= 2)
                {
                    if(buffer_rf[5] == side.a.RF || buffer_rf[5] == side.b.RF || GeneralConfig == 1)
                    {
                       pollingRF_Rx(buffer_rf);
                       RFOnline = 1; 
					   for(x = 0; x < 100; x++)
					   {
						   buffer_rf[x] = 0x00;
					   }
                    }
                    else
                    {
                       RFOnline = 0;                       
                    }  
                }
                else
                {
                    if(buffer_rf[5] == side.a.RF || buffer_rf[5] == side.b.RF || buffer_rf[5] == side.c.RF|| buffer_rf[5] == side.d.RF || GeneralConfig == 1)
                    {
                        
                       pollingRF_Rx(buffer_rf);
                       RFOnline = 1;                        
                       for(x = 0; x < 100; x++)
					   {
						   buffer_rf[x] = 0x00;
					   }
                    }
                    else
                    {
                       RFOnline = 0;                       
                    }
                }
                buffer_rf[6] = 0xFF;
                RF_Connection_ClearRxBuffer();            
                break;
            }  
            i++;
            
            
        }               
         
        if(RFOnline == 1)
        {
            pollingRFA_Tx();           
            pollingRFB_Tx();
            if(NumPositions > 2)
            {
                pollingRFC_Tx();
                pollingRFD_Tx();
            }
            RFOnline = 0;
        }
        
        /* detecta perdida de comunicacion RF */
        if(FlagRF == 1)
        {
            FlagRF = 0; 
            RfActive = 1;
            cnt = 0;           
        }
        else
        {
            if(cnt < 1000)
            {
                cnt = cnt + 1;
               
            }
            else
            {
                RfActive = 0;
                bufferDisplay1.PrintEnd = 0;
                bufferDisplay2.PrintEnd = 0;
                bufferDisplay3.PrintEnd = 0;
                bufferDisplay4.PrintEnd = 0;
            }
          
        }
        
        
    
        vTaskDelayUntil(&xLastWakeTime, xFrequency);       
    }
}







/* [] END OF FILE */
