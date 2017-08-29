/* ========================================
 *
 * Copyright CLS LED, 2015
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF CLS LED.
 *
 * ========================================
*/
/**
 * @file main.c
 * @brief Entry point and RTOS resources
 * @author Ingmar Delsink
 */

/*  INCLUDES  */
/* Project and default includes */
#include <project.h>
#include <protocol.h>
#include <variables.h>
#include <keyboard.h>
#include <ibutton.h>
#include <RFPoll.h>
#include <LCD.h>
#include <I2C.h>
#include <Printing.h>

/* RTOS includes. */
#include <FreeRTOS.h>
#include "os_mutex.h"
#include "os_resource.h"

/* Task includes */
#include "RFtask.h"
#include "PumpTask.h"
#include "PrinterTask.h"

xSemaphoreHandle g_pUARTSemaphore;
      

/*
 * Inicializa los perifiericos del sistema
 */
void GlobalInitializer(){
    EEPROM_1_Start();
    Pump_Start(); 
    Display1_Start();
    Display2_Start();    
    Tag_Start();   
    I2C_Bus_Start();
    RF_Connection_Start();
   
}

/* 
 * Almacena la configuracion de puntos decimales y posiciones detectadas 
*/
void StoreConfiguration(){
    EEPROM_1_WriteByte(UnitType,0);
    EEPROM_1_WriteByte(ConversionFactor,1);
    EEPROM_1_WriteByte(MoneyDec,2);
    EEPROM_1_WriteByte(VolDec,3);
    EEPROM_1_WriteByte(PPUDec,4);
    EEPROM_1_WriteByte(DDMode,5);
    EEPROM_1_WriteByte(digits,6); 
    EEPROM_1_WriteByte(side.a.dir,12);
    EEPROM_1_WriteByte(side.b.dir,13);
    EEPROM_1_WriteByte(side.c.dir,14);
    EEPROM_1_WriteByte(side.d.dir,15);
}

/*
 * Carga las configuraciones desde la memoria EEPROM
*/
void loadConfiguration(){
  
    uint16 x;          
    
    configAccess[0] = 0x04; 

    //PrinterType[1] = 1; // Tipo de impresora
    
    /// Leer desde eeprom externa ///
    LeerEeprom(0,2);
	for(x=0;x<=buffer_i2c[0];x++){
		logoPrint[x]=buffer_i2c[x];
	}
    LeerEeprom(2,2);
	for(x=0;x<=buffer_i2c[0];x++){
		PrinterType[x]=buffer_i2c[x];
	}
    LeerEeprom(4,5);
	for(x=0;x<=buffer_i2c[0];x++){
		side.a.GradesHose[x]=buffer_i2c[x];
	}
    LeerEeprom(9,5);
	for(x=0;x<=buffer_i2c[0];x++){
		side.b.GradesHose[x]=buffer_i2c[x];
	}
    LeerEeprom(14,5);
	for(x=0;x<=buffer_i2c[0];x++){
		side.c.GradesHose[x]=buffer_i2c[x];
	}
    LeerEeprom(19,5);
	for(x=0;x<=buffer_i2c[0];x++){
		side.d.GradesHose[x]=buffer_i2c[x];
	}    
    LeerEeprom(335,17);
	for(x=0;x<=buffer_i2c[0];x++){
		Product1[x]=buffer_i2c[x];
	}
    LeerEeprom(355,17);
	for(x=0;x<=buffer_i2c[0];x++){
		Product2[x]=buffer_i2c[x];
	}
    LeerEeprom(375,17);
	for(x=0;x<=buffer_i2c[0];x++){
		Product3[x]=buffer_i2c[x];
	}
    LeerEeprom(395,17);
	for(x=0;x<=buffer_i2c[0];x++){
		Product4[x]=buffer_i2c[x];
	}
    LeerEeprom(30,31);
	for(x=0;x<=buffer_i2c[0];x++){
		Encabezado1[x]=buffer_i2c[x];
	}
    LeerEeprom(65,31);
	for(x=0;x<=buffer_i2c[0];x++){
		Encabezado2[x]=buffer_i2c[x];
	}
    LeerEeprom(100,31);
	for(x=0;x<=buffer_i2c[0];x++){
		Encabezado3[x]=buffer_i2c[x];
	}
    LeerEeprom(135,31);
	for(x=0;x<=buffer_i2c[0];x++){
		Encabezado4[x]=buffer_i2c[x];
	}
    LeerEeprom(200,31);
	for(x=0;x<=buffer_i2c[0];x++){
		Encabezado5[x]=buffer_i2c[x];
	}
    LeerEeprom(4,5);
	for(x=0;x<=buffer_i2c[0];x++){
		side.a.GradesHose[x]=buffer_i2c[x];
	}
    LeerEeprom(9,5);
    for(x=0;x<=buffer_i2c[0];x++){
		side.b.GradesHose[x]=buffer_i2c[x];
	}
    LeerEeprom(14,5);
    for(x=0;x<=buffer_i2c[0];x++){
		side.c.GradesHose[x]=buffer_i2c[x];
	}
    LeerEeprom(19,5);
    for(x=0;x<=buffer_i2c[0];x++){
		side.d.GradesHose[x]=buffer_i2c[x];
	}
    
    //LeerEeprom(500,31);
	for(x=1;x<=30;x++){
		Pie1[x]=EEPROM_1_ReadByte(100+x);
	}
    LeerEeprom(600,31);
	for(x=0;x<=buffer_i2c[0];x++){
		Pie2[x]=buffer_i2c[x];
	}
    
	for(x=1;x<=30;x++){
		Pie3[x]=EEPROM_1_ReadByte(130+x);
	}
    logoPrint[1] = 11; //Fijo para pruebas
    //LeerEeprom(700,31);
    MoneyDec   = EEPROM_1_ReadByte(2);  //Punto decimal dinero
    VolDec     = EEPROM_1_ReadByte(3);  //Punto decimal volumen
    PPUDec     = EEPROM_1_ReadByte(4);  //Punto decimal PPU
    DDMode     = EEPROM_1_ReadByte(5);  //Punto decimal 
    digits     = EEPROM_1_ReadByte(6);  //Digitos
    lockTurn   = EEPROM_1_ReadByte(7);  
    //lockTurn   = 1;                   //Fijo turno abierto para pruebas
    printPortA = EEPROM_1_ReadByte(8);  //Puertos de impresion
    printPortB = EEPROM_1_ReadByte(9);  //Puertos de impresion
    IDCast[0]  = EEPROM_1_ReadByte(10); //ID Estacion1
    IDCast[1]  = EEPROM_1_ReadByte(11); //ID Estacion2  
    side.a.dir = EEPROM_1_ReadByte(12); //Primera posicion
    side.b.dir = EEPROM_1_ReadByte(13); //Segunda posicion
    side.c.dir = EEPROM_1_ReadByte(14); //Tercera posicion
    side.d.dir = EEPROM_1_ReadByte(15); //Cuarta posicion
}

/* 
 * Funcion que pone el surtidor en modo consola para configuracion
 * Esta funcion se debe habilitar solo cuando sea requerida
 */
void console(uint8 position)
{
    Pump_PutChar(0x10 | position);
    CyDelay(100);
    Pump_PutChar(0x30 | position);
    CyDelay(100);
    Pump_PutChar(0x10 | position);
    CyDelay(100);
    Pump_PutChar(0x30 | position);
    CyDelay(100);
    Pump_PutChar(0x10 | position);
    CyDelay(100);
    Pump_PutChar(0x30 | position);
    
}
/*
*********************************************************************************************************
*                                         void InitPump(void)
*
* Description : Pregunta configuraciones al dispensador 
*               
*
*********************************************************************************************************
*/
void InitPump(){   
    
    //Detecta las posiciones del surtidor
    NumPositions = get_position();
    //console();
    if(NumPositions > 0)
    {
              
            if(NumPositions <= 2)
            {
              if(get_state(side.a.dir) == PUMP_PEOT || 
                 get_state(side.a.dir) == PUMP_FEOT)
                {
                    getSale(side.a.dir);
                    CyDelay(100);
                }
                if(get_state(side.b.dir) == PUMP_PEOT || 
                   get_state(side.b.dir) == PUMP_FEOT)
                { 
                    getSale(side.b.dir);
                    CyDelay(100);
                }
            }
            
            if(NumPositions > 2)
            {
                if(get_state(side.a.dir) == PUMP_PEOT || 
                   get_state(side.a.dir) == PUMP_FEOT)
                {
                    getSale(side.a.dir);
                    CyDelay(100);
                }
                if(get_state(side.b.dir) == PUMP_PEOT || 
                   get_state(side.b.dir) == PUMP_FEOT)
                  {
                    getSale(side.b.dir);
                    CyDelay(100);
                  }
                if(get_state(side.c.dir) == PUMP_PEOT || 
                   get_state(side.c.dir) == PUMP_FEOT)
                  {
                    getSale(side.c.dir);
                    CyDelay(100);
                  }
                if(get_state(side.d.dir) == PUMP_PEOT || 
                   get_state(side.d.dir) == PUMP_FEOT)
                 {
                    getSale(side.d.dir);
                    CyDelay(100);
                 }
            }
                    
                
            if(get_state(side.a.dir) == PUMP_IDLE && get_state(side.b.dir) == PUMP_IDLE )
            {
                PumpCompleteConfiguration(side.a.dir);
                CyDelay(100);
                StoreConfiguration();
                CyDelay(100);
                return;
            }else
            {
                CyDelay(100);
                SetPicture(1,DISPLAY_BAJE_MANIJA);
                CyDelay(100);
                SetPicture(2,DISPLAY_BAJE_MANIJA);
                CyDelay(100);
                InitPump();                
            }
    }        
    else
    {
       CyDelay(100);
       SetPicture(1,DISPLAY_ERROR);
       CyDelay(100);
       SetPicture(2,DISPLAY_ERROR);
       CyDelay(100);
       NumPositions = 0;
       InitPump();   
    }
}



/*----------------------------------------------------------------------------
   Main: Initialize and start Kernel
*---------------------------------------------------------------------------*/
int main()
{	  

    /* Drivers                                                                          */
    CySysTickStart();
    
    /* ISR                                                                              */
    CyGlobalIntEnable;                          /* Init the interrupts                  */
    GlobalInitializer();
    
    //CyDelay(5000);
    
    /* Init Pump                                                                        */       
    InitPump(); 
    loadConfiguration();
    if(NumPositions == 2){
        getTotalsInit(side.a.dir);
        getTotalsInit(side.b.dir);
    }
    if(NumPositions == 4){
        getTotalsInit(side.a.dir);
        get_state(side.b.dir);        
        getTotalsInit(side.b.dir);
        get_state(side.c.dir);
        getTotalsInit(side.c.dir);
        get_state(side.d.dir);
        getTotalsInit(side.d.dir);
        
    }
    console(side.a.dir);
    OSonline = 0;
    CyDelay(100);
    
    /* OS Init                                                                          */
    osInit();                               /* Initialize all thread related tasks      */ 
    prvHardwareSetup();                     /* FreeRTOS setup                           */
	vTaskStartScheduler();                  /* Start the scheduler                      */

	return 1;
}

int osInit(void)
{
    /*  tasks  */    
    xTaskCreate(Display_Task, "DisplayTask", (configMINIMAL_STACK_SIZE), NULL, tskIDLE_PRIORITY + 2, NULL);  /* DISPLAY TASK    */
    xTaskCreate(Pump_Task, "PumpTask", (configMINIMAL_STACK_SIZE), NULL, tskIDLE_PRIORITY + 2, NULL);        /* PUMP TASK       */   
    xTaskCreate(PrinterTask, "PrinterTask", (configMINIMAL_STACK_SIZE), NULL, tskIDLE_PRIORITY + 2, NULL);   /* PRINTER TASK    */
    xTaskCreate(RF_Task, "RFTask", (configMINIMAL_STACK_SIZE), NULL, tskIDLE_PRIORITY + 2, NULL);            /* RF TASK         */
    return 1; // All went well
}

int osDeInit(void)
{
    return 1;
}

/* [] END OF FILE */
