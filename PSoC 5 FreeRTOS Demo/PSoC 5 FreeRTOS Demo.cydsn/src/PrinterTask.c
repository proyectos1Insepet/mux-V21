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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "os_resource.h"

#include "PrinterTask.h"



void PrinterTask(void *arg)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 10;
    xLastWakeTime = xTaskGetTickCount();
    uint8 x; 
 
    
    while(1) 
    {                                               
        if(bufferDisplay1.flagPrint == 1 && bufferDisplay1.PrintFlagEOT == 1)
        {    
                
            //Impresion
            imprimir(printPortA, side.a.RF);
            bufferDisplay1.flagPrint = 0;            
            bufferDisplay1.PrintFlagEOT = 0;
            for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
            {   										    							
		        side.a.saleNumber[x] = 0x00;
	        }           
            bufferDisplay1.flagActiveSale = false; 
            bufferDisplay1.PrintEnd = 0;
                
        }      
        if(bufferDisplay2.flagPrint == 1 && bufferDisplay2.PrintFlagEOT == 1)
        {    
            //Impresion
            imprimir(printPortB, side.b.RF);
            bufferDisplay2.flagPrint = 0;             
            bufferDisplay2.PrintFlagEOT = 0;            
            for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
            {   										    							
		        side.b.saleNumber[x] = 0x00;
	        }
            bufferDisplay2.flagActiveSale = false;
            bufferDisplay2.PrintEnd = 0;
          
        }       
        if(bufferDisplay3.flagPrint == 1 && bufferDisplay3.PrintFlagEOT == 1)
        {    
                
            //Impresion
            imprimir(printPortA, side.c.RF);
            bufferDisplay3.flagPrint = 0;            
            bufferDisplay3.PrintFlagEOT = 0;
            for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
            {   										    							
		        side.c.saleNumber[x] = 0x00;
	        }               
            bufferDisplay3.flagActiveSale = false;
            bufferDisplay3.PrintEnd = 0;

        }
        if(bufferDisplay4.flagPrint == 1 && bufferDisplay4.PrintFlagEOT == 1 )
        {                    
            //Impresion
            imprimir(printPortB, side.d.RF);
            bufferDisplay4.flagPrint = 0;
            bufferDisplay4.PrintFlagEOT = 0;                            
            for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
            {   										    							
		        side.d.saleNumber[x] = 0x00;
	        }
            bufferDisplay4.flagActiveSale = false;
            bufferDisplay4.PrintEnd = 0;
        }                   
        vTaskDelayUntil(&xLastWakeTime, xFrequency);            
    }
        
}

/* [] END OF FILE */
