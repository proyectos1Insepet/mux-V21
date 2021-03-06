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
#include <codetag.h>
#include <keyboard.h>
#include <ibutton.h>
#include <RFPoll.h>
#include <LCD.h>
#include <I2C.h>
#include <Printing.h>
#include <string.h>
#include <stdio.h>

#include <stdlib.h>
#include <code_pirata.h>
#include "os_resource.h"

/* Drivers */
#include "PumpTask.h"

char mensaje[]  = {"OPERACION"};
char mensaje2[] = {"RECHAZADA"};
char mensaje3[] = {"MANGUERA"};
char mensaje4[] = {"INCORRECTA"};
char mensaje5[] = {"TERMINE "};
char mensaje6[] = {"TRANSACCION"};
char mensaje7[] = {"EN TODAS"};
char mensaje8[] = {"LAS CARAS"};

uint8 nombre[8]   = {"NOMBRE: "};
uint8 placa[8]    = {"PLACA:  "};
uint8 tarjeta[8]  = {"TARJETA:"};
uint8 saldo_d[8]  = {"SALDO D."};
uint8 saldo_a[8]  = {"SALDO A."};
uint8 NumSale[14] = {"No. de venta: "};
uint8 VolSale[9]  = {"Volumen: "};
uint8 MonSale[8]  = {"Dinero: "};
uint8 MilageSale[8]    = {"Millas: "};
uint8 NameCustomer[17] = {"Datos del cliente"};
uint8 MonSalePayed[21] = {"Dinero discriminado: "};
uint32 counter;
uint32 counter2;
uint32 counter3;
uint32 counter4;
uint8  upcount[2] = {0,0};
uint8  upcount2[2] = {0,0};
uint8  upcount3 [2] = {0,0};
uint8  upcount4 [2] = {0,0};
int writevalue,writevalueB, res,resB;

uint8 precios = 0;

/* Drivers */
#include "PumpTask.h"

/* Configuration Password */
uint8 passwordPump[5] = "00204";

/*
*********************************************************************************************************
*                                         void InitDisplay1(void)
*
* Description : Pregunta configuraciones al dispensador 
*               
*
*********************************************************************************************************
*/
void InitDisplay1(){ 
    if(NumPositions == 2)
    {
        SetPicture(1, DISPLAY_INICIO0);                 
        vTaskDelay( 300 / portTICK_PERIOD_MS );              //Freertos delay
        if(EEPROM_1_ReadByte(0) == 0)
        {
            side.a.hoseNumber = EEPROM_1_ReadByte(0) + 1;
            side.b.hoseNumber = EEPROM_1_ReadByte(0) + 1;   //UnitType     
        }
        if(EEPROM_1_ReadByte(0) == 1)
        {
            side.a.hoseNumber = EEPROM_1_ReadByte(0) + 1;
            side.b.hoseNumber = EEPROM_1_ReadByte(0) + 1;
        }
        if(EEPROM_1_ReadByte(0) == 2)
        {
            side.a.hoseNumber = EEPROM_1_ReadByte(0) + 1;
            side.b.hoseNumber = EEPROM_1_ReadByte(0) + 1;
        }
        if(EEPROM_1_ReadByte(0) == 3)
        {
            side.a.hoseNumber = EEPROM_1_ReadByte(0) + 1;
            side.b.hoseNumber = EEPROM_1_ReadByte(0) + 1;
        } 
        if(EEPROM_1_ReadByte(5) == 0) //DDMode
        {
            digits = 5;
        }
        if(EEPROM_1_ReadByte(5) == 1) //DDMode
        {                            
            digits = 6; //Mostrar modo de display
        }
        if(EEPROM_1_ReadByte(5) == 2) //DDMode
        {
           //ShowMessage(1,DisplayMode2,22);
            digits = 7;
        }
        if(EEPROM_1_ReadByte(5) == 3) //DDMode
        {
            //ShowMessage(1,DisplayMode3,22);
            digits = 8;
        }
    }
    if(NumPositions == 4)
    {
        SetPicture(1,DISPLAY_SELECCIONE_POSICION);        
        //ShowMessage(1, iniText, 0);    
        vTaskDelay( 300 / portTICK_PERIOD_MS );              //Freertos delay
        if(EEPROM_1_ReadByte(0) == 0) //UnitType
        {
            side.a.hoseNumber = EEPROM_1_ReadByte(0) + 1;
            side.b.hoseNumber = EEPROM_1_ReadByte(0) + 1;
            side.c.hoseNumber = EEPROM_1_ReadByte(0) + 1;
            side.d.hoseNumber = EEPROM_1_ReadByte(0) + 1;
            //ShowMessage(1,Unit,0);                          //Mostrar tipo de dispensador      
        }
        if(EEPROM_1_ReadByte(0) == 1)
        {
            side.a.hoseNumber = EEPROM_1_ReadByte(0) ;
            side.b.hoseNumber = EEPROM_1_ReadByte(0) ;
            side.c.hoseNumber = EEPROM_1_ReadByte(0) ;
            side.d.hoseNumber = EEPROM_1_ReadByte(0) ;
            //ShowMessage(1,Unit2,0);
        }
        if(EEPROM_1_ReadByte(0) == 2)
        {
            side.a.hoseNumber = EEPROM_1_ReadByte(0);
            side.b.hoseNumber = EEPROM_1_ReadByte(0);
            side.c.hoseNumber = EEPROM_1_ReadByte(0) - 1;
            side.d.hoseNumber = EEPROM_1_ReadByte(0) - 1;
            //ShowMessage(1,Unit3,0);
        }
        if(EEPROM_1_ReadByte(0) == 3)
        {
            side.a.hoseNumber = EEPROM_1_ReadByte(0) - 1;
            side.b.hoseNumber = EEPROM_1_ReadByte(0) - 1;
            side.c.hoseNumber = EEPROM_1_ReadByte(0) - 1;
            side.d.hoseNumber = EEPROM_1_ReadByte(0) - 1;
            //ShowMessage(1,Unit4,0);
        }    
        if(EEPROM_1_ReadByte(5) == 1) //DDMode
        {
            //ShowMessage(1,DisplayMode,22);                  //Mostrar modo de display
            digits = 6;
        }
        if(EEPROM_1_ReadByte(5) == 2) //DDMode
        {
            //ShowMessage(1,DisplayMode2,22);
            digits = 7;
        } 
    }        
    if(NumPositions < 2)
    {
        SetPicture(1,DISPLAY_ERROR);        
    }      
   
}

/*
*********************************************************************************************************
*                                         void InitDisplay2(void)
*
* Description : Pregunta configuraciones al dispensador 
*               
*
*********************************************************************************************************
*/
void InitDisplay2(){ 
    if(NumPositions == 2){        
        SetPicture(2,DISPLAY_INICIO0);  
        flowDisplay2 = 0;
        Display2_ClearRxBuffer();
    }
    if(NumPositions == 4){
        flowDisplay2 = 0;
        SetPicture(2,DISPLAY_SELECCIONE_POSICION);         
    }        
    if(NumPositions < 2){        
        SetPicture(2,DISPLAY_ERROR);
    }     
}

/*
*********************************************************************************************************
*                                         void PrintTest(void)
*
* Description : Pregunta configuraciones al dispensador 
*               
*
*********************************************************************************************************
*/
void PrintTest(){
    uint8 datoA[26] = "Test de Impresion Puerto 1";
    uint8 datoB[26] = "Test de Impresion Puerto 2";
    uint8 x;
    for(x = 0; x < 26;x++)
    {
        write_psoc1(1,datoA[x]);
    }
    write_psoc1(1,10);
    write_psoc1(1,10);
    write_psoc1(1,10);
    write_psoc1(1,10);
    write_psoc1(1,10);
    write_psoc1(1,10);
    for(x = 0; x < 26; x++)
    {
        write_psoc1(2,datoB[x]);
    }
    write_psoc1(2,10);
    write_psoc1(2,10);
    write_psoc1(2,10);
    write_psoc1(2,10);
    write_psoc1(2,10);
    write_psoc1(2,10);
}

/*
*********************************************************************************************************
*                                         void PollingDisplay1(void)
*
* Description : Pregunta estado al surtidor 
*               
*
*********************************************************************************************************
*/
void PollingDisplay1(void){    
    uint8 x, y;    
    tempcont = EEPROM_1_ReadByte(225);
    if(counter >= tempcont*100 && tempcont > 0){ //70 segs aprox
        bufferDisplay1.flagPrint =  0;
        flowDisplay1 = 's'; 
        flowPos      = 0;                           
        PresetFlag   = 0;
        iButtonFlag  = 0;
        counter      = 0;
        SetPicture(1, DISPLAY_TIEMPO_EXPIRADO);
    }
    switch(flowDisplay1){
        case 's':
        if(Display1_GetRxBufferSize() == 8)
        {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Return to initial screen                                                                                    
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            AuthType = 0;
                            counter  = 0;
                            Display1_ClearRxBuffer();
                        break;
                        case 0x94:  //Return to initial screen                                                                                    
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            AuthType = 0;
                            counter  = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }               
                Display1_ClearRxBuffer();
            }
        break;
        case 0:            
            InitDisplay1();             
            if(NumPositions == 2){
                SetPicture(1, DISPLAY_INICIO0);
            }else{
                SetPicture(1, DISPLAY_SELECCIONE_POSICION);
            }            
            // Impresion de tiquete 
            bufferDisplay1.flagActiveSale = false;
            flowDisplay1 = 1;            
            Display1_ClearRxBuffer();             
        break;
        case 1: //Menu              
            if(NumPositions > 2){
                if(bufferDisplay1.flagActiveSale){
                    flowDisplay1 = flowPos;            
                }
                if(bufferDisplay3.flagActiveSale){
                    flowDisplay3 = flowPosC;
                    selectPos = 2;
                }
            }            
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {     
                    if(NumPositions == 2 && bufferDisplay1.PrintEnd == 0){
                        flowDisplay1 = 2;                         //Pantalla forma de pago                      
                        if(EEPROM_1_ReadByte(215)!= 11){
                            SetPicture(1, DISPLAY_FORMA_PAGO_DESEADA);                                                
							Display1_ClearRxBuffer();
                        }else{
                            SetPicture(1,DISPLAY_FORMA_PAGO_DESEADA_TERPEL);
                        }                                                
                    }else{
                        switch(Display1_rxBuffer[3]){
				        case 0x56:						         //POS A                                                                                                                       
                            if(bufferDisplay1.flagActiveSale || bufferDisplay1.PrintEnd == 1){
                                flowDisplay1 = flowPos;      //Si está vendiendo en esta posición regresa a su flujo
                            }else{
                                if(EEPROM_1_ReadByte(215)!= 11){
                                    SetPicture(1, DISPLAY_FORMA_PAGO_DESEADA);                                                
                                }else{
                                    SetPicture(1,DISPLAY_FORMA_PAGO_DESEADA_TERPEL);
                                }
                                selectPos     = 1;
                                flowDisplay1  = 2;
								Display1_ClearRxBuffer();
                            }
                            if (bufferDisplay3.flagActiveSale){
                                flowDisplay3 = flowPosC;     //Si la venta está activa en POS B regresa a su flujo
                            }
                            else{
                                flowDisplay3 = 0; 
                                flowPosC     = 0;
                            }
					    break;
                            		       
					    case 0x57:  				             //POS B                                                                 
                            if(bufferDisplay1.flagActiveSale){
                                flowDisplay1 = flowPos;      //Si está vendiendo en esta posición regresa a su flujo
                            }
                            else{
                                flowDisplay1 = 0;
                                flowPos      = 0;
                            } 
                            if (bufferDisplay3.flagActiveSale || bufferDisplay3.PrintEnd == 1){                                    
                                flowDisplay3 = flowPosC;     //Si la venta está activa en POS B regresa a su flujo
                            }else{
                                if(EEPROM_1_ReadByte(215)!= 11){
                                    SetPicture(1, DISPLAY_FORMA_PAGO_DESEADA);                                                
                                }else{
                                    SetPicture(1,DISPLAY_FORMA_PAGO_DESEADA_TERPEL);
                                }
						        selectPos     = 2;
                                flowDisplay3  = 2;                            
                            }                           
					    break;                                                   
				    }                      
                    }                    
                } 
                Display1_ClearRxBuffer();
            }         
        break;
        case 2:  //Pantalla forma de pago
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C)){
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x0D:  //Pantalla efectivo   
                            if(EEPROM_1_ReadByte(220) == 1)
                            {
                                bufferDisplay1.saleType = 1;
                                AuthType = 2;
                                if(EEPROM_1_ReadByte(215)!= 11){
                                    flowDisplay1 = 3;                                                                                                            
                                    SetPicture(1, DISPLAY_FORMA_PROGRAMACION);                                      
                                }else{
                                    flowDisplay1 = 37;                                                                          
                                    SetPicture(1, DISPLAY_FIDELIZACION);  
                                }
                            }else
                            {
                                SetPicture(1, DISPLAY_CANCELADO_X_PC);
                                vTaskDelay( 900 / portTICK_PERIOD_MS );
                                flowDisplay1 = 0;  
                                Display1_ClearRxBuffer();
                            }
                        break;
                        case 0x0E:  //Pantalla credito                           
                            for(x = 0; x < 10; x++)
                            {                                
                                bufferDisplay1.CreditpresetValue[0][x] = 0x00;
                                bufferDisplay1.CreditpresetValue[1][x] = 0x00;
                                
                            }
                            if(EEPROM_1_ReadByte(220) == 1)
                            {                                
                                bufferDisplay1.saleType = 2;
                                AuthType = 1;
                                if(EEPROM_1_ReadByte(215)!= 11){
                                    flowDisplay1 = 10;
                                    SetPicture(1, DISPLAY_ID_DIGITAL);
                                }else{
                                    flowDisplay1 = 37;
                                    SetPicture(1, DISPLAY_FIDELIZACION);                                    
                                }                                
                                Display1_ClearRxBuffer();
                            }else
                            {
                                SetPicture(1, DISPLAY_CANCELADO_X_PC);
                                vTaskDelay( 900 / portTICK_PERIOD_MS );
                                flowDisplay1 = 0;    
                                counter = 0;
                                Display1_ClearRxBuffer();
                            }
                        break;
                        
                        case 0x0F: //Forma de pago
                            if(EEPROM_1_ReadByte(220) == 1)
                            {
                                flowDisplay1 = 38;                            
                                SetPicture(1, DISPLAY_SELECCION_VENTA);
                            }
                        break;
                            
                        case 0x45:  //Pantalla otras opciones 
                            flowDisplay1 = 12;                            
                            SetPicture(1,DISPLAY_OPERACIONES);
                            AuthType = 0;
                            Display1_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay1.flagPrint =  0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0;
                            SetPicture(1, DISPLAY_INICIO0);                               
                            vTaskDelay( 10 / portTICK_PERIOD_MS );
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay1.flagPrint =  0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0;
                            SetPicture(1, DISPLAY_INICIO0);                            
                            vTaskDelay( 10 / portTICK_PERIOD_MS );
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            }            
        break;
        
        case 37: // Desea fidelizar            
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    side.a.ActivoFideliza = 0;
                    side.a.ActivoRedencion = 0;
                    switch(Display1_rxBuffer[3])
                    {                         
                        case 0x0A: //Si                                                                                   
                            flowDisplay1 = 33;
                            SetPicture(1, DISPLAY_IDEN_FIDELIZACION);                              
                        break;
                        case 0x0B:  //No 
                            if(AuthType == 1){
                                flowDisplay1 =10;                                
                                SetPicture(1, DISPLAY_ID_TERPEL);
                            }else{
                                flowDisplay1 =3;                               
                                SetPicture(1, DISPLAY_FORMA_PROGRAMACION); 
                            }                                                                                     
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            counter      = 0;
                        break;
                    }                    
                }                                
                Display1_ClearRxBuffer();
            }             
        break;
                    
            
        case 3: //Pantalla ingreso de valores
            for(x = 0; x < 10; x++)
            {
                bufferDisplay1.presetValue[0][x] = 0x00;
                bufferDisplay1.presetValue[1][x] = 0x00;
            }
            Credit_Auth_OK = 0;            
            counter ++;
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {                    
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x0F:  //Preset dinero                
                            flowDisplay1 = 4;                              
                            bufferDisplay1.presetType[0] = 2;
                            bufferDisplay1.presetType[1] = '$';
                            numberKeys1 = 0;
                            SetPicture(1, DISPLAY_INTRODUZCA_VALOR);   
                            WriteLCD(1, '$', 3, 2, 1, 0x0000, 'N');                            
                            if(EEPROM_1_ReadByte(2) > 0)
                            {
                                flagPoint1 = 0;
                            }else
                            {
                                flagPoint1 = 1;
                            } 
                            counter = 0;
                            Display1_ClearRxBuffer();
                        break; 
                        case 0x10:  //Preset volumen                 
                            flowDisplay1 = 4;                            
                            bufferDisplay1.presetType[0] = 1;
                            bufferDisplay1.presetType[1] = 'G';
                            numberKeys1 = 0;                            
                            SetPicture(1, DISPLAY_INTRODUZCA_VOLUMEN);                            
                            WriteLCD(1, 'G', 3, 2, 1, 0x0000, 'N');                            
                            if(EEPROM_1_ReadByte(3) > 0) //VolDec
                            {
                                flagPoint1 = 0;
                            }else
                            {
                                flagPoint1 = 1;
                            }  
                            counter = 0;
                            Display1_ClearRxBuffer();
                        break;
                        case 0x43:     //Preset full 
                            bufferDisplay1.presetType[0] = 3;
                            bufferDisplay1.presetType[1] = 'F';
                            
                            for(x = 1; x <(digits - 1); x++)
                            {
                                bufferDisplay1.presetValue[0][x] = '9';
                            }
                            
                            bufferDisplay1.presetValue[0][x] = '0';
                            bufferDisplay1.presetValue[0][x + 1] = '0';
                            bufferDisplay1.presetValue[0][0] = digits;
                            
                            for(x = 0; x <= bufferDisplay1.presetValue[0][0]; x++)
                            {
                                bufferDisplay1.presetValue[1][x] = bufferDisplay1.presetValue[0][x];
                            }                            
                            flowDisplay1 = 5;                            
                            SetPicture(1,DISPLAY_SELECCIONE_PRODUCTO4);
                            counter = 0;
                            Display1_ClearRxBuffer();
                        break;
                        case 0x94:  //Retroceso
                            bufferDisplay1.flagPrint =  0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            Display1_ClearRxBuffer();
                        break;
                        case 0x3B:  //Pantalla Inicial  
                            AuthType = 0;                        
                            flowDisplay1 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            Display1_ClearRxBuffer();
                        break;
                        case 0x7E:  //Pantalla Inicial                              
                            bufferDisplay1.flagPrint =  0;
                            AuthType     = 0;
                            flowDisplay1 = 0;
                            counter      = 0;
                            SetPicture(1,DISPLAY_INICIO0); 
                            Display1_ClearRxBuffer();
                        break;
                    }
                }  
                Display1_ClearRxBuffer();
            }
        break;
        
        case 4: 
            counter ++;
            switch (alphanumeric_keyboard(digits + 1, 0))
            {
                case 0:  //Pantalla Inicial    
                    flowDisplay1 = 0;
                    SetPicture(1,DISPLAY_INICIO0); 
                    Display1_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    counter = 0;
                    for(x = 0; x <= bufferDisplay1.valueKeys[0]; x++)
                    {
                        bufferDisplay1.presetValue[0][x] = bufferDisplay1.valueKeys[x];
                        bufferDisplay1.presetValue[1][x] = bufferDisplay1.valueKeys[x];
                    }                      
                    IntValueA = 0;
                    for(x = 0; x < 10; x++)
                    {                            
                        bufferDisplay1.PresetTemp[x] = 0x00;                          
                    }
                    // Convierte valor del preset en entero
                    for(x = 1; x < 10; x++)
                    {
                        if(bufferDisplay1.presetValue[0][x] != '.' && bufferDisplay1.presetValue[0][x] != ',' && bufferDisplay1.presetValue[0][x] != 0x00)
                        {
                           bufferDisplay1.PresetTemp[x - 1] = bufferDisplay1.presetValue[0][x] - 48;
                        }                      
                    }                    
                    // Convierte valor del preset en entero
                    for(x = 0; x < bufferDisplay1.presetValue[0][0]; x++)
                    {                                
                        IntValueA = 10 * IntValueA + bufferDisplay1.PresetTemp[x];                            
                    }                      
                    // Rechaza transaccion si el Preset es menor a COP$1000
                    if(bufferDisplay1.presetType[0] == 2)
                    {
                    	if(IntValueA < 1000)
                    	{
                        	AuthType = 0;
                        	bufferDisplay1.flagPrint =  0;
                        	flowDisplay1 = 0;
                        	SetPicture(1,DISPLAY_INICIO0); 
                    	}
                    	else
                    	{
                        	flowDisplay1 = 5;   //caso para seleccion de producto
                        	SetPicture(1, DISPLAY_SELECCIONE_PRODUCTO4);
                    	}
                    }
                    else
                    {                        
                        if((bufferDisplay1.presetValue[0][0] > 0 && IntValueA != 0) && (bufferDisplay1.presetValue[0][0] < 7 && IntValueA >= 1))
                        {
                            flowDisplay1 = 5;   //caso para seleccion de producto
                        	SetPicture(1, DISPLAY_SELECCIONE_PRODUCTO4);  
                        }
                        else
                        {
                            AuthType = 0;
                        	bufferDisplay1.flagPrint =  0;
                        	flowDisplay1 = 0;
                        	SetPicture(1,DISPLAY_INICIO0);
                        }                   	
                    }
                    Display1_ClearRxBuffer();
                break;
            }
        break;
            
        case 5: //Seleccion de producto  
            counter = counter + 3;
            if(counter > ((tempcont*100)/2) ){
                upcount[0] = 1;
            }else{
                 upcount[0] = 0;
            }
            if(side.a.GradesHose[1] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(1, producto[side.a.GradesHose[1]-1][x],9+x,11); //FontSpace(LCD, caracter,posx,posy)
                //WriteMessage(1, producto[side.a.GradesHose[1]-1][x],11,6+x,2,0x0000,'Y'); //WriteMessage(1, producto1[x],11,7+x,2,0x0000,'Y');
                }
            }
            if(side.a.GradesHose[2] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(1, producto[side.a.GradesHose[2]-1][x],10+x,17); //FontSpace(LCD, caracter,posx,posy)
                //WriteMessage(1, producto[side.a.GradesHose[2]-1][x],17,7+x,2,0x0000,'Y');//WriteMessage(1, producto2[x],17,8+x,2,0x0000,'Y');
                }
            }
            if(side.a.GradesHose[3] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(1, producto[side.a.GradesHose[3]-1][x],11+x,23);
                //WriteMessage(1, producto[side.a.GradesHose[3]-1][x],23,8+x,2,0x0000,'Y');
                }
            }
            if(side.a.GradesHose[4] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(1, producto[side.a.GradesHose[4]-1][x],12+x,29);
                //WriteMessage(1, producto[side.a.GradesHose[4]-1][x],29,9+x,2,0x0000,'Y');
                }
            }             
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                               
                            case 0x80:  //Grado 1 
                                if(side.a.hoseNumber > 0)
                                {
                                    numberKeys1 = 0; 
                                    flowDisplay1 = 9;
                                    side.a.hose = 1;                         
                                    //Cash
                                    if(AuthType == 2)
                                    {
                                        if(KmCash[1] == 0x01)
                                        {
                                            bufferDisplay1.flagKeyboard = 2; 
                                            SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                        }else{
                                            bufferDisplay1.flagKeyboard = 1; 
                                            SetPicture(1, DISPLAY_DIGITE_PLACA);
                                        }                                        

                                    }                            
                                    //Credit
                                    if(AuthType == 1)
                                    {   
                                        bufferDisplay1.flagKeyboard = 2;
                                        SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                    }
                                }
                                counter = 0;
                                Display1_ClearRxBuffer();
                            break;                            
                            case 0x81:  //Grado 2
                                if(side.a.hoseNumber > 1)
                                {
                                    numberKeys1=0; 
                                    flowDisplay1 = 9;
                                    side.a.hose = 2;
                                    //Cash
                                    if(AuthType == 2)
                                    {
                                        if(KmCash[1] == 0x01)
                                        {
                                            bufferDisplay1.flagKeyboard = 2; 
                                            SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                        }else{
                                            bufferDisplay1.flagKeyboard = 1; 
                                            SetPicture(1, DISPLAY_DIGITE_PLACA);
                                        }                                        
                                    }                            
                                    //Credit
                                    if(AuthType == 1)
                                    { 
                                        bufferDisplay1.flagKeyboard = 2;
                                        SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                    }
                                }
                                counter = 0;
                                Display1_ClearRxBuffer(); 
                            break;
                                
                            case 0x7F:  //Grado 3
                                if(side.a.hoseNumber > 2)
                                {
                                    numberKeys1=0; 
                                    flowDisplay1 = 9;
                                    side.a.hose = 3;
                                   //Credit
                                    if(AuthType == 2)
                                    {
                                        if(KmCash[1] == 0x01)
                                        {
                                            bufferDisplay1.flagKeyboard = 2; 
                                            SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                        }else{
                                            bufferDisplay1.flagKeyboard = 1; 
                                            SetPicture(1, DISPLAY_DIGITE_PLACA);
                                        }                                        
                                    }                            
                                    //Cash
                                    if(AuthType == 1)
                                    {
                                        bufferDisplay1.flagKeyboard = 2;
                                        SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                    }
                                }
                                counter = 0;
                                Display1_ClearRxBuffer();
                            break;   
                            
                            case 0xB8:  //Grado 4 
                                if(side.a.hoseNumber > 3)
                                {
                                    numberKeys1 = 0; 
                                    flowDisplay1 = 9;
                                    side.a.hose = 4;
                                    //Credit
                                    if(AuthType == 2)
                                    {
                                        if(KmCash[1] == 0x01)
                                        {
                                            bufferDisplay1.flagKeyboard = 2; 
                                            SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                        }else{
                                            bufferDisplay1.flagKeyboard = 1; 
                                            SetPicture(1, DISPLAY_DIGITE_PLACA);
                                        }                                        
                                    }                            
                                    //Cash
                                    if(AuthType == 1)
                                    {
                                        bufferDisplay1.flagKeyboard = 2;
                                        SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                    } 
                                }
                                counter = 0;
                                Display1_ClearRxBuffer();
                            break;
                                
                            case 0x94:  //Retroceso
                                bufferDisplay1.flagPrint =  0;
                                flowDisplay1 = 0;
                                AuthType     = 0;
                                counter      = 0;
                                SetPicture(1,DISPLAY_INICIO0);
                                Display1_ClearRxBuffer();
                            break;
                                
                            case 0x7E:  //Pantalla Inicial
                                bufferDisplay1.flagPrint =  0;
                                SetPicture(1,DISPLAY_INICIO0);
                                flowDisplay1 = 0;
                                AuthType     = 0;
                                counter      = 0;
                                Display1_ClearRxBuffer();
                            break;
                    }                    
                }
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
                Display1_ClearRxBuffer();
            }
        break;
                    
        case 6: // Print Screen
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x39:  //Print 
                            flowDisplay1 = 7;
                            numberKeys1 = 0;
                            bufferDisplay1.flagPrint =  1;                                                
							bufferDisplay1.PrintFlagEOT = 0;
                            SetPicture(1, DISPLAY_SUBA_MANIJA);  
                            Display1_ClearRxBuffer();
                        break; 
                        case 0x38:  //No Print 
                                flowDisplay1 = 7; // Wait of handle up
                                bufferDisplay1.flagPrint =  0;                                                               
								bufferDisplay1.PrintFlagEOT = 0;
                                SetPicture(1, DISPLAY_SUBA_MANIJA);
                                Display1_ClearRxBuffer();
                        break;
                        case 0x7E:  //Return to initial screen                                                                                    
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            AuthType = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }
               
                Display1_ClearRxBuffer();
            }
        break;
                                        
            // PRESET flag ON and wait to handle up
        case 7:                       
            PresetFlag = 1;
            counter = counter + 4;
            vTaskDelay( 40 / portTICK_PERIOD_MS );
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            AuthType = 0;     
                            bufferDisplay1.zeroSend = 1;                            
                            vTaskDelay( 50 / portTICK_PERIOD_MS );                      
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            AuthType = 0;
                            bufferDisplay1.zeroSend = 1;
                            vTaskDelay( 50 / portTICK_PERIOD_MS );
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            }           
        break;            
          
        case 8:           
           //Pump Busy...
           vTaskDelay( 10 / portTICK_PERIOD_MS ); 
           if(NumPositions > 2)
		   {
				flowDisplay1 = 1;
		   }
           counter = 0;
        break;
            
        case 9: //Keyboard    
            if(upcount[0] == 1){
                if(upcount[1] == 1){
                    counter ++;
                    upcount[1] = 0;
                }else{
                    upcount[1] = 1;
                }
            }else{
                counter++;
            }
            switch (alphanumeric_keyboard(11,0))
            {
                case 0: //Cancel
                    switch(bufferDisplay1.flagKeyboard)
                    {
                        case 1://License plate
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay1.licenceSale[x] = 0;
                            }
                            flowDisplay1 = 0; 
                            counter = 0;
                            SetPicture(1, DISPLAY_INICIO0);
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 2://Mileage
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay1.mileageSale[x] = 0;
                            }        
                            counter = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 3://CC/NIT
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay1.identySale[x] = 0;
                            }
                            counter = 0;
                            Display1_ClearRxBuffer();
                        break;
                            
                        case 4://ID
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay1.shiftId[x] = 0;
                            }
                            counter = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                    Display1_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay1.flagKeyboard)
                    {
                        case 1://License plate
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay1.licenceSale[x] = 0x00;
                            }
                            
                            for(x = 0; x <= bufferDisplay1.valueKeys[0]; x++)
                            {
                                bufferDisplay1.licenceSale[x] = bufferDisplay1.valueKeys[x];
                            }

                            flowDisplay1 = 6;
                            SetPicture(1, DISPLAY_DESEA_IMPRIMIR_RECIBO);  
                            counter = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 2:// mileage
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay1.mileageSale[x] = 0;
                            }                         
                            for(x = 0; x <= bufferDisplay1.valueKeys[0]; x++)
                            {
                                bufferDisplay1.mileageSale[x] = bufferDisplay1.valueKeys[x];
                            }
                            
                            //Credit Sale
                            if(AuthType == 1)
                            {
                                flowDisplay1 = 7;                               
                                SetPicture(1, DISPLAY_SUBA_MANIJA);
                            }
                            if(AuthType == 2)
                            {
                                if(KmCash[1] == 0x01)
                                {   
                                    numberKeys1 = 0; 
                                    flowDisplay1 = 9;
                                    bufferDisplay1.flagKeyboard = 1; 
                                    SetPicture(1, DISPLAY_DIGITE_PLACA);
                                }                                         
                            }
                            counter = 0;
                            Display1_ClearRxBuffer();                           
                        break;
                        
                        case 3:     //CC/NIT                            
                            for(x = 0; x <= bufferDisplay1.valueKeys[0]; x++)
                            {
                                bufferDisplay1.identySale[x] = bufferDisplay1.valueKeys[x];
                            }
                            counter = 0;
                            Display1_ClearRxBuffer();
                        break;
                        case 4:     //ID                            
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay1.shiftId[x] = bufferDisplay1.valueKeys[x];
                            }                            
                            flowDisplay1 = 14;          //password request                    
                            numberKeys1 = 0;
                            hiddenKeys = 10;
                            controlChar = '*';
                            bufferDisplay1.flagKeyboard = 3;
                            SetPicture(1,DISPLAY_INGRESE_PASSWORD);
                            counter = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                    //Display1_ClearRxBuffer();
                break;
            }  
            Display1_ClearRxBuffer();
        break;    
    
    ////////////////// CASOS PARA CRÉDITO  /////////////////////
        case 10:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0xB6:  //ibutton Request   
                            flowDisplay1 = 11;
                            numberKeys1 = 0;                            
                            //bufferDisplay1.flagPrint =  1;
                            bufferDisplay1.idType = 1;
                            counter = 0;
                            SetPicture(1, DISPLAY_ESPERANDO_ID);                            
                        break; 
                        case 0xB7:  //ID Number
                            if(EEPROM_1_ReadByte(215)!= 11){
                            	flowDisplay1 = 24;
                            	numberKeys1 = 0;   
                                bufferDisplay1.idType = 1;                            	
                            	Tag_ClearRxBuffer();
                            	Tag_ClearTxBuffer();
                            	Tag_PutChar('O');
                            	Tag_PutChar('K');
                            	Tag_PutChar(0x01);
                            	vTaskDelay( 100 / portTICK_PERIOD_MS );
                            	SetPicture(1, DISPLAY_ESPERANDO_ID);                           
                            }else{
                            	flowDisplay1 = 25;
                                numberKeys1 = 0;
                                bufferDisplay1.idType = 3;
                            	vTaskDelay( 100 / portTICK_PERIOD_MS );
                            	SetPicture(1, DISPLAY_SELECCIONE_OP_TERPEL);
                            }     
                            counter = 0;
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay1.flagPrint =  0;
                            bufferDisplay1.idType = 0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0;
                            SetPicture(1, DISPLAY_INICIO0);                            
                        break;
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay1.flagPrint =  0;
                            bufferDisplay1.idType = 0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0;
                            SetPicture(1, DISPLAY_INICIO0);                            
                        break;
                    }                    
                }             
                Display1_ClearRxBuffer();
            }                        
        break;
        
        case 11:
            // iButton read
            counter ++;
            for(x = 0; x < 30; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 25; x++)
            {
                bufferDisplay1.idSerial[x] = 0x00;
            }
            if(touch_present(1) == 1)
            {                
				if(touch_write(1,0x33))
                {
					for(x = 1; x <= 8; x++)
                    {
						temporal[x] = touch_read_byte(1);  // Id
					}
					y = 0;
					for(x = 1; x < 8; x++)
                    {
                        y = crc_check(y,temporal[x]);      // Checksum
                    }					
                    if(y == temporal[8])
                    {
						bufferDisplay1.idSerial[0] = 16;
						y = 16;						
                        for(x = 1; x <= 8; x++)
                        {
							if((temporal[x] & 0x0F) >= 10)
                            {
								bufferDisplay1.idSerial[y] = (temporal[x] & 0x0F) + 55;
							}else{
								bufferDisplay1.idSerial[y] = (temporal[x] & 0x0F) + 48;				
							}
                            y--;
							if(((temporal[x] >> 4) & 0x0F) >= 10)
                            {
								bufferDisplay1.idSerial[y] = ((temporal[x] >> 4) & 0x0F) + 55;
							}else{
								bufferDisplay1.idSerial[y] = ((temporal[x] >> 4) & 0x0F) + 48;				
							}
                            y--;
						}
                        
                        // Authorization request
                        SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                        vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                        iButtonFlag = 1;
                        SetPicture(1, DISPLAY_FORMA_PROGRAMACION);
                        flowDisplay1 = 3;  
                        counter      = 0;
					}
				}else
                    {   // iButton Error
                        SetPicture(1,DISPLAY_ID_NO_RECONOCIDO);                                           
                        Display1_ClearRxBuffer();
                        vTaskDelay( 700 / portTICK_PERIOD_MS );    
                        SetPicture(1, DISPLAY_INICIO0);
                        flowDisplay1 = 0;
                        bufferDisplay1.flagPrint =  0;
                        PresetFlag = 0;
                        iButtonFlag = 0;
                        AuthType = 0;                        
                    }
			}                     
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag   = 0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            }                                                          
        break;
        case 24:
            counter ++;
            for(x=0;x<=150;x++){
                temporal[x]=0x00;
            }
            for(x=0;x<=24;x++){
                bufferDisplay1.idSerial[x]=0x00;
            }
            if(serial_codetag(1)==1){
                for(x=0;x<=temporal[0];x++){
                    bufferDisplay1.idSerial[x]=temporal[x];
                }
                bufferDisplay1.idSerial[0]=16;
				y=16;
				for(x=1;x<=8;x++){
					if((temporal[x]&0x0F)>=10){
						bufferDisplay1.idSerial[y]=(temporal[x]&0x0F)+55;
					}else{
						bufferDisplay1.idSerial[y]=(temporal[x]&0x0F)+48;				
					}
                    y--;
					if(((temporal[x]>>4)&0x0F)>=10){
						bufferDisplay1.idSerial[y]=((temporal[x]>>4)&0x0F)+55;
					}else{
						bufferDisplay1.idSerial[y]=((temporal[x]>>4)&0x0F)+48;				
					}
                    y--;
				}                
                // Authorization request
                SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag = 1;
                SetPicture(1, DISPLAY_FORMA_PROGRAMACION);
                flowDisplay1 = 3;
                counter = 0;
            }
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            //SetPicture(1, DISPLAY_INICIO0);                            
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0;                           
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            //SetPicture(1, DISPLAY_INICIO0);
                            flowPos = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0;                            
                        break;
                    }                    
                }                
                Display1_ClearRxBuffer();
            } 
        break;
            
        case 25:
            counter ++;
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0xB6:  //Autorizacion con tarjeta   
                            flowDisplay1 = 26;
                            numberKeys1 = 0;                            
                            bufferDisplay1.flagPrint =  1;
                            counter = 0;
                            SetPicture(1, DISPLAY_ESPERANDO_ID_TERPEL);                            
                        break; 
                        case 0xB7:  //Saldo                           
                        	flowDisplay1 = 27;
                        	numberKeys1 = 0;  
                            side.a.ActivoFideliza = 3;   
                            side.a.RFstateReport = 3;
                            bufferDisplay1.FidelConf = 0; 
                            counter = 0;
                        	SetPicture(1, DISPLAY_ESPERANDO_ID_TERPEL);                                                                                  
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay1.flagPrint =  0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0; 
                            SetPicture(1, DISPLAY_INICIO0);                            
                        break;
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay1.flagPrint =  0;
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0; 
                        break;
                    }                    
                }             
                Display1_ClearRxBuffer();
            }                        
        break;
            
        case 26:
            counter ++;
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay1.idSerial[x] = 0x00;
            }
            if(code_pirata(magneticReader[1],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){                    
				    bufferDisplay1.idSerial[x-1] = temporal[x];                    
                }
                bufferDisplay1.idSerial[0] = x-2;
                // Authorization request
                SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag = 2;
                flowDisplay1 = 14;
                bufferDisplay1.flagKeyboard = 4;
                numberKeys1 = 0;
                hiddenKeys  = 5;
                controlChar ='*';
                counter     = 0;
                SetPicture(1,DISPLAY_INGRESE_PASSWORD);  
                Display1_ClearRxBuffer();                                                                        
									                                       
			}                     
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0; 
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0; 
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display1_ClearRxBuffer();
            } 
        break;
        
        case 27:
            counter ++;
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay1.idSerial[x] = 0x00;
            }
            if(code_pirata(magneticReader[1],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){                    
				    bufferDisplay1.idSerial[x-1] = temporal[x];                    
                }
                bufferDisplay1.idSerial[0] = x-2;
                // Authorization request
                SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag = 2;
                flowDisplay1 = 14;
                bufferDisplay1.flagKeyboard = 7;
                numberKeys1 = 0;
                hiddenKeys  = 5;
                controlChar ='*';
                counter     = 0;
                SetPicture(1,DISPLAY_INGRESE_PASSWORD);  
                Display1_ClearRxBuffer();                                                                        
									                                       
			}                     
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);                           
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0; 
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);                            
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            flowDisplay1 = 0;
                            AuthType     = 0;
                            counter      = 0; 
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display1_ClearRxBuffer();
            }
        break;
        case 28:            
            side.a.rfState = RF_ASK_BALANCE;
            counter ++;
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            counter      = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            ShiftState   = 0;
                            counter      = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer();             
        break;
        
        case 29:
            if(cardmessagedisplay == 1){
            for(x = 1; x < 31; x++)
            {
                WriteMessage(1, Encabezado1[x],4,x-1,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 4; x < 31; x++)
            {
                WriteMessage(1, Encabezado2[x],6,x-4,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 8; x++) //nombre
            {
                WriteMessage(1, nombre[x],8,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 20; x++)
            {
                WriteMessage(1, Company[x],8,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 8; x++) //placa
            {
                WriteMessage(1, placa[x],10,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 8; x++)
            {
                WriteMessage(1, LicensePlate[x],10,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 8; x++)//tarjeta
            {
                WriteMessage(1,tarjeta[x],12,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 5; x++)
            {
                WriteMessage(1,'*',12,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 3; x++)
            {
                WriteMessage(1,cardNumberA[x],12,x+13,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 8; x++)//saldo
            {
                WriteMessage(1,saldo_d[x],14,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 18; x++)
            {
                WriteMessage(1,BalanceA[x],14,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 8; x++)//saldo aprobado
            {
                WriteMessage(1,saldo_a[x],16,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            for(x = 0; x < 18; x++)
            {
                WriteMessage(1,BalanceB[x],16,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
            }
            }
            if(cardmessagedisplay == 2)
            {
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage[x],6,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage1[x],8,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage2[x],10,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage3[x],12,x,1,0x0000,'Y');
                }
            }
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:
                            printBalance(EEPROM_1_ReadByte(8),side.a.dir); //PrintPortA
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            ShiftState   = 0; 
                            SetPicture(1, DISPLAY_INICIO0);
                        break;
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            ShiftState   = 0;
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer(); 
            
        break;
    ///////////////FIN CASOS PARA CRÉDITO  /////////////////////  
    
    //////////// CASOS PARA CONFIGURACIONES  ///////////////////
        case 12:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x46:  //Turnos                                             
                            flowDisplay1 = 13;                             
                            if(EEPROM_1_ReadByte(220) == 1)
                            {
                                SetPicture(1,DISPLAY_CERRAR_TURNO);
                            }else
                            {
                                SetPicture(1,DISPLAY_ABRIR_TURNO);
                            }                                                                              
                            counter = 0;                        
                        break;
                        case 0x55:  //Configurar módulo 
                            flowDisplay1 = 14;
                            bufferDisplay1.flagKeyboard = 6;
                            numberKeys1 = 0;
                            hiddenKeys = 5;
                            controlChar ='*';
                            counter     = 0;
                            SetPicture(1,DISPLAY_INGRESE_PASSWORD);  
                            Display1_ClearRxBuffer();
                        break;
                        case 0xB5:  //Copia de recibo                             
                            side.a.RFstateReport = 1;
                            side.a.rfStateCopy = RF_COPY_RECEIPT;
                            SetPicture(1,DISPLAY_IMPRIMIENDO_RECIBO);                                
                            flowDisplay1  = 23;
                            bufferDisplay1.PrintCopy = 1;  
                            counter = 0;
                            Display1_ClearRxBuffer();                           
                        break;
                        
                        case 0x3B:  //Pantalla Inicial    
                            flowDisplay1 = 0;
                            counter = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            Display1_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay1.flagPrint =  0;
                            flowDisplay1 = 0;
                            counter = 0;
                            SetPicture(1,DISPLAY_INICIO0); 
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay1.flagPrint =  0;
                            flowDisplay1 = 0;
                            counter = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            Display1_ClearRxBuffer();
                        break;
                    }
                }                  
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }
        break;

        case 13:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x47:  //Open Shift  
                            flowDisplay1 = 9;
                            numberKeys1 = 0;    
                            bufferDisplay1.flagKeyboard = 4;
                            SetPicture(1,DISPLAY_INTRODUZCA_CEDULA);                            
                        break;
                        case 0x48:  //Close shift 
                            flowDisplay1 = 9;
                            numberKeys1 = 0;   
                            bufferDisplay1.flagKeyboard = 4;
                            SetPicture(1,DISPLAY_INTRODUZCA_CEDULA);                           
                        break;                         
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay1.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay1.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break; 
            
        case 14: //Teclado general      
            switch (alphanumeric_keyboard(hiddenKeys,controlChar))
            {
                case 0: //Cancelar
                    switch(bufferDisplay1.flagKeyboard)
                    {
                        case 1://ID Estacion
                            for(x = 0; x <= 4; x++)
                            {
                                idStation[x] = 0;
                            }
                            flowDisplay1 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 2://Umbral
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                pumpGap[x] = 0;
                            }
                            flowDisplay1 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 3://Pass turno
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.shiftPassword[x] = 0;
                            }
                            flowDisplay1 = 0;
                            ShiftState = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        
                        break;
                        case 4://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.passCard[x] = 0;
                            }
                            flowDisplay1 = 0;
                        break;
                        case 5://Pass
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.shiftPassword[x] = 0;
                            }
                            flowDisplay1 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                            
                        case 6://Pass MUX
                            for(x = 1; x <= configAccess[0]; x++)
                            {
                                configAccess[x] = 0;
                            }
                            flowDisplay1 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        
                        case 7://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.passCard[x] = 0;
                            }
                            flowDisplay1 = 0;
                        break;
                            
                        case 8://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.passCard[x] = 0;
                            }
                            flowDisplay1 = 0;
                        break;
                        case 9://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.valueKeys[x] = 0;
                            }
                            flowDisplay1 = 0;
                        break;
                    }                    
                    Display1_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay1.flagKeyboard)
                    {   
                        case 1://ID Estacion
                            for(x = 0; x <= 4; x++)
                            {
                                idStation[x] = bufferDisplay1.valueKeys[x+1];                                
                            }
                            idStation[4] = 0x00;
                            intIDStation = atoi(idStation);
                            IDCast[0] = intIDStation;
                            IDCast[1] = intIDStation>>8;
                            EEPROM_1_WriteByte(IDCast[0],10);
                            EEPROM_1_WriteByte(IDCast[1],11);
                            flowDisplay1 = 15;
                            SetPicture(1,DISPLAY_CONFIGURACIONES);
                        break;
                        case 2://Umbral
                            
                            for(x = 1; x <= bufferDisplay1.valueKeys[0]; x++)
                            {
                                pumpGap[x] = bufferDisplay1.valueKeys[x] - 48;
                            }
                            PositionGAP = 0;
                            
                            for(x = 1; x <= bufferDisplay1.valueKeys[0]; x++)
                            {
                                PositionGAP = pumpGap[x] + PositionGAP * 10;
                            }  
                            
                            side.a.RF = side.a.dir + PositionGAP;
                            side.b.RF = side.b.dir + PositionGAP;
                            side.c.RF = side.c.dir + PositionGAP;
                            side.d.RF = side.d.dir + PositionGAP;
                            
                            // Almacena posicion RF
                            EEPROM_1_WriteByte(side.a.RF,200);
                            EEPROM_1_WriteByte(side.b.RF,201);
                            EEPROM_1_WriteByte(side.c.RF,202);
                            EEPROM_1_WriteByte(side.d.RF,203);
                            
                            flowDisplay1 = 15;
                            SetPicture(1,DISPLAY_CONFIGURACIONES);
                        break;
                        case 3://Pass turno
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.shiftPassword[x] = bufferDisplay1.valueKeys[x];
                            }
                            flowDisplay1 = 19;
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            side.a.RFstateReport = 1;
                            ShiftState = 1;
                        break;
                        case 4://Pass Card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.passCard[x] = bufferDisplay1.valueKeys[x];
                            }
                            vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                            iButtonFlag = 2;
                            SetPicture(1, DISPLAY_FORMA_PROGRAMACION);
                            flowDisplay1 = 3;
                        break;
                        case 5://Pass
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.shiftPassword[x] = bufferDisplay1.valueKeys[x];
                            }
                            flowDisplay1 = 15;
                            SetPicture(1,DISPLAY_CONFIGURACIONES);
                        break; 
                        case 6://Pass
                            for(x = 1; x <= configAccess[0]; x++)
                            {
                                configAccess[x] = bufferDisplay1.valueKeys[x];
                            }
                            if(configAccess[1] == passwordPump[1] && configAccess[2] == passwordPump[2] && configAccess[3] == passwordPump[3] && configAccess[4] == passwordPump[4])
                            {                                
                                SetPicture(1,DISPLAY_PASSWORD_VALIDO);
                                //CyDelay(700);
                                vTaskDelay( 700 / portTICK_PERIOD_MS );
                                flowDisplay1 = 15;
                                SetPicture(1,DISPLAY_CONFIGURACIONES);
                            }else{
                                SetPicture(1,DISPLAY_PASSWORD_INVALIDO);
                                //CyDelay(700);
                                vTaskDelay( 700 / portTICK_PERIOD_MS );
                                flowDisplay1 = 0;
                                SetPicture(1,DISPLAY_INICIO0);
                            }
                        break;
                        case 7://Pass Card
                            for(x = 0; x < 20; x++)
                            {
                                bufferDisplay1.passCard[x] = 0x00;
                            }
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.passCard[x] = bufferDisplay1.valueKeys[x];
                            }
                            side.a.RFstateReport = 2;
                            vTaskDelay( 500 / portTICK_PERIOD_MS );  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);
                            flowDisplay1 = 28;
                        break;
                            
                        case 8://Pass Card forma pago                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay1.passCard[x] = bufferDisplay1.valueKeys[x];
                            }
                            side.a.RFstateReport = 5;
                            vTaskDelay( 100 / portTICK_PERIOD_MS );  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);
                            flowDisplay1 = 35;
                        break;
                        case 9://tiempo contador                            
                            for(x = 1; x < hiddenKeys + 1; x++)
                            {
                                TimeValue[x-1] = bufferDisplay1.valueKeys[x];
                            } 
                            TimeValue[2] = 0x00;
                            EEPROM_1_WriteByte(atoi(TimeValue),225); 
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);
                            vTaskDelay( 500 / portTICK_PERIOD_MS );   
                            flowDisplay1 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                    }                    
                    Display1_ClearRxBuffer();
                break;
            }            
        break;
            
        case 15: //Menu de configuraciones
            counter++;
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x82:  //ID Estacion  
                            flowDisplay1 = 14;
                            numberKeys1 = 0; 
                            controlChar = 0;
                            hiddenKeys  = 5;
                            counter     = 0;
                            bufferDisplay1.flagKeyboard = 1;
                            SetPicture(1,DISPLAY_INTRODUZCA_VALOR);                            
                        break;

						case 0x83:  //KM efectivo 
                            flowDisplay1 = 30;
                            counter      = 0;
                            SetPicture(1,DISPLAY_KM_EFECTIVO);                            
                        break;
                        case 0x65:  //Test Impresoras 
                            flowDisplay1 = 16; 
                            counter      = 0;
                            PrintTest();
                            SetPicture(1,DISPLAY_AMBAS_IMPRESORAS_FUNCIONANDO);                           
                        break;        
                        case 0x5A:  //Umbral 
                            flowDisplay1 = 14;
                            numberKeys1 = 0;
                            controlChar = 0;
                            hiddenKeys  = 3;
                            for(x = 0; x < 3; x++)
                            {
                                pumpGap[x]  = 0x00;
                            }
                            pumpGap[0]  = 2;
                            bufferDisplay1.flagKeyboard = 2;
                            counter     = 0;
                            SetPicture(1,DISPLAY_INTRODUZCA_VALOR);                            
                        break;
                        case 0x5B:  //Lectores banda 
                            flowDisplay1 = 31;
                            counter     = 0;
                            SetPicture(1,DISPLAY_LECTORES_BANDA);                            
                        break;
                        case 0x58:  //Hora y Fecha //Configuracion de tiempo                            
                            flowDisplay1 = 14;                            
                            numberKeys1 = 0;  
                            controlChar = 0;
                            hiddenKeys  = 3;
                            counter     = 0;
                            TimeValue[0]= 0x00;
                            TimeValue[1]= 0x00;
                            TimeValue[2]= 0x00;
                            for(x = 0; x < hiddenKeys + 1; x++)
                            {
                                bufferDisplay1.valueKeys[x] = 0x00;
                            }
                            bufferDisplay1.flagKeyboard = 9;
                            SetPicture(1,DISPLAY_INTRODUZCA_VALOR);                           
                        break;
                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay1.flagPrint =  0;
                            counter     = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay1.flagPrint =  0;
                            counter     = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                        break;
                    }                    
                }                     
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break; 
            
        case 16: //Menu de configuraciones de impresoras 1
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x38:  //No funcionan  
                            flowDisplay1 = 17;
                            SetPicture(1,DISPLAY_IMPRESORA_NO_FUNCIONANDO);                            
                        break;
                        case 0x39:  //Si funcionan
                            flowDisplay1 = 15;                           
                            EEPROM_1_WriteByte(1,8);
                            EEPROM_1_WriteByte(2,9);
                            SetPicture(1,DISPLAY_CONFIGURACIONES);
                        break;                                            
                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay1.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay1.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break;
            
        case 17: //Menu de configuraciones de impresoras 2
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x8C:  //1 no funciona  
                            flowDisplay1 = 15; 
                            EEPROM_1_WriteByte(2,8);
                            EEPROM_1_WriteByte(2,9);
                            SetPicture(1,DISPLAY_CONFIGURACIONES);                            
                        break;
                        case 0x8D:  //2 no funciona
                            flowDisplay1 = 15; 
                            EEPROM_1_WriteByte(1,8);
                            EEPROM_1_WriteByte(1,9);
                            SetPicture(1,DISPLAY_CONFIGURACIONES); 
                        break;
                            
                        case 0x8E:  //ninguna funciona
                            flowDisplay1 = 15; 
                            EEPROM_1_WriteByte(0,8);
                            EEPROM_1_WriteByte(0,9);
                            SetPicture(1,DISPLAY_CONFIGURACIONES); 
                        break;
                                               
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay1.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                        break;
                            
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay1.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                        break;
                    }                    
                }
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break;
            
        case 18: //Menu configuracion manual de fecha y hora
            if(leer_hora() == 1)
            {
                WriteLCD(1,(((timeDownHandle[1] & 0x30) >> 4) + 48),13,8,1,0x0000,'N'); //WriteLCD(1,(((timeDownHandle[1] & 0x10) >> 4) + 48),13,8,1,0x0000,'N');
                WriteLCD(1,((timeDownHandle[1] & 0x0F) + 48),13,9,1,0x0000,'N');
                WriteLCD(1,':',13,10,1,0x0000,'N');
                WriteLCD(1,(((timeDownHandle[0] & 0xF0)>>4)+48),13,11,1,0x0000,'N');
                WriteLCD(1,((timeDownHandle[0] & 0x0F)+48),13,12,1,0x0000,'N');               
            }
            if(leer_fecha() == 1)
            {                
                WriteLCD(1,(((dateDownHandle[0] & 0x30) >> 4) + 48),21,8,1,0x0000,'N');
                WriteLCD(1,((dateDownHandle[0] & 0x0F) + 48),21,9,1,0x0000,'N');
                WriteLCD(1,'/',21,10,1,0x0000,'N');
                WriteLCD(1,(((dateDownHandle[1] & 0x10) >> 4) + 48),21,11,1,0x0000,'N');
                WriteLCD(1,((dateDownHandle[1] & 0x0F) + 48),21,12,1,0x0000,'N');
                WriteLCD(1,'/',21,13,1,0x0000,'N');
                WriteLCD(1,(((dateDownHandle[2] & 0xF0) >> 4) + 48),21,14,1,0x0000,'N');
                WriteLCD(1,((dateDownHandle[2] & 0x0F) + 48),21,15,1,0x0000,'N');
            }
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                       
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay1.flagPrint =  0;
                            flowDisplay1 = 0;
                            SetPicture(1,DISPLAY_INICIO0);                            
                        break;
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay1.flagPrint =  0;
                            flowDisplay1 = 0;
                            SetPicture(1,DISPLAY_INICIO0);                            
                        break;
                    }                    
                }
                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break;
            
        case 19:             
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                        break;
                    }                    
                }
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer();
            
        break;
            
        case 20: //pantalla de espera de autorizacion
            SetPicture(1, DISPLAY_ESPERANDO_AUTORIZACION);
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            ShiftState   = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer();            
        break;
            
            
        case 21: //Pantalla de credito no autorizado            
            SetPicture(1, DISPLAY_AUTORIZACION_RECHAZADA);
            bufferDisplay1.flagPrint = 0;
            PresetFlag   = 0;
            flowDisplay1 = 0;
            AuthType     = 0;
            counter      = 0; 
            for(x = 0; x < 9; x++)
            {
                FontSpace(1, mensaje[x],1+x,17);
                FontSpace(1, mensaje[x],1+x,21);                  
            }
            side.a.ActivoFideliza = 3;                                        
            side.a.RFstateReport = 3;
            bufferDisplay1.FidelConf = 0;
            side.a.rfState = RF_IDLE;
            vTaskDelay( 2000 / portTICK_PERIOD_MS );
            flowDisplay1 = 0;
            SetPicture(1, DISPLAY_INICIO0);
        break;
                    
        case 22: // Pantalla de Manguera incorrecta            
            SetPicture(1, DISPLAY_AUTORIZACION_RECHAZADA);
            bufferDisplay1.flagPrint = 0;
            for(x = 0; x < 8; x++)
            {                
                FontSpace(1, mensaje3[x],1+x,17);                                   
            }
            for(x = 0; x < 10; x++)
            {                
                FontSpace(1, mensaje4[x],1+x,21);                    
            }
            side.a.ActivoFideliza = 3;                                        
            side.a.RFstateReport  = 3;
            bufferDisplay1.FidelConf = 0;
            vTaskDelay( 2000 / portTICK_PERIOD_MS );
            flowDisplay1 = 0;
            AuthType     = 0;
            counter      = 0; 
            SetPicture(1, DISPLAY_INICIO0);
        break;

        case 23: //Pantalla imprimiendo durante copia de recibo
            if(bufferDisplay1.PrintCopy == 0)
            {        
                CounterA = 0;
                Display1_ClearRxBuffer();
            }
            else  //Espera la impresion si no recibe nada se va a la pantalla inicial 
            {
                if(CounterA < 100)  // 10 segundos de espera aprox.
                {
                    vTaskDelay( 100 / portTICK_PERIOD_MS );
                    CounterA++; 
                }
                else
                {
                    CounterA = 0;
                    flowDisplay1 = 0;               
                    Display1_ClearRxBuffer();
                }          
            }            
        break;
        
        //////////////////CASOS ADICIONALES CONFIGURACIÓN ///////
        case 30://KM efectivo
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {  
                        case 0x0A:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                            KmCash[0] = 0x01;
                            KmCash[1] = 0x01;
                            WriteEeprom(500,KmCash);
                        break;
                        
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                            KmCash[0] = 0x01;
                            KmCash[1] = 0x00;
                            WriteEeprom(500,KmCash);
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer();            
        break;
            
        case 31://Lectores
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {  
                        case 0x0A:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                            magneticReader[0] = 0x02;
                            magneticReader[1] = 'A';
                            magneticReader[2] = 'A';
                            WriteEeprom(503,magneticReader);
                        break;
                        
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                            magneticReader[0] = 0x02;
                            magneticReader[1] = 'A';
                            magneticReader[2] = 'B';
                            WriteEeprom(503,magneticReader);
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                        break;
                    }                    
                }                   
				vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer();            
        break;
        
        ///////////////// CASOS FIDELIZACIÓN TERPEL /////////////        
        case 32: //Teclado general      
            counter++;
            switch (alphanumeric_keyboard(keysTerpel,0))
            {
                case 0: //Cancelar
                    switch(bufferDisplay1.flagKeyboard)
                    {                        
                        case 1://Cedula
                            
                            for(x = 0; x < keysTerpel; x++)
                            {
                                bufferDisplay1.idTerpelFideliza[x] = 0;
                            }                            
                            flowDisplay1 = 0;
                            ShiftState = 0;
                            counter = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;   
                        case 2://Tarjeta para forma pago                            
                            for(x = 0; x < keysTerpel; x++)
                            {
                                bufferDisplay1.idFormaPago[x] = 0;
                            }                            
                            flowDisplay1 = 0;
                            ShiftState = 0;
                            counter = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 3://Tarjeta para forma pago
                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay1.saleNumber[x] = 0;
                            }                            
                            flowDisplay1 = 0;
                            ShiftState = 0;
                            counter = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 4://Tarjeta para forma pago
                            
                            for(x = 0; x < 8; x++)
                            {
                                bufferDisplay1.MoneyPay[x] = 0;
                            }                            
                            flowDisplay1 = 0;
                            ShiftState = 0;
                            counter = 0;
							side.a.RFstateReport = 7;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 5://Tarjeta para forma pago
                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay1.idFormaPago[x] = 0;
                            }                            
                            flowDisplay1 = 0;
                            ShiftState = 0;
                            counter = 0;
							if(bufferDisplay1.idType == 6)
                                side.a.RFstateReport = 7;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                            
                        case 6://Tarjeta para forma pago                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay1.PaymentNumber[x] = 0;
                            }                            
                            flowDisplay1 = 0;
                            ShiftState = 0;
                            counter = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                    }                    
                    Display1_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay1.flagKeyboard)
                    {                           
                        case 1://Datos fidelización                            
                            for(x = 0; x < keysTerpel; x++)
                            {
                                bufferDisplay1.idTerpelFideliza[x] = bufferDisplay1.valueKeys[x];
                            }                            
                            flowDisplay1 = 35;
                            if(side.a.ActivoRedencion == 1){
                                side.a.RFstateReport = 4;                                
                            }else{
                                side.a.RFstateReport = 2;                        
                                side.a.ActivoFideliza = 2;
                            }
                            counter = 0;
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                            
                        case 2://LFM Forma de pago                            
                            for(x = 0; x < keysTerpel; x++)
                            {
                                bufferDisplay1.idFormaPago[x] = bufferDisplay1.valueKeys[x];
                            }
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            for(x = 0; x < 21; x++)
                            {
                                bufferDisplay1.valueKeys[x] = 0x00;
                            }
                            flowDisplay1 = 14;    
                            hiddenKeys = 20;
                            controlChar ='*';
                            numberKeys1 = 0;
                            counter = 0;
                            bufferDisplay1.flagKeyboard = 8;
                            SetPicture(1,DISPLAY_PASS_ALFNUM);
                        break;
                            
                        case 3://numero de venta FP                            
                            for(x = 0; x < keysTerpel; x++)
                            {
                                bufferDisplay1.saleNumber[x] = bufferDisplay1.valueKeys[x];
                            }                            
                            flowDisplay1 = 39;
                            counter = 0;
                            SetPicture(1, DISPLAY_FORMA_DE_PAGO_TERPEL);
                        break;
                            
                        case 4://valor voucher                             
                            for(x = 0; x < keysTerpel + 1; x++)
                            {
                                bufferDisplay1.MoneyPay[x] = 0x00;
                            }
                            for(x = 1; x <= bufferDisplay1.valueKeys[0]; x++)
                            {
                                bufferDisplay1.MoneyPay[x-1] = bufferDisplay1.valueKeys[x];
                            }
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            writevalue = atoi(bufferDisplay1.MoneyPay);
                            res =(atoi(bufferDisplay1.saleValue)-atoi(bufferDisplay1.MoneyPayed));
                            if( abs(res) >= writevalue && writevalue > 0 )
                            {
                                for(x = 0; x < keysTerpel + 1; x++)
                                {
                                    bufferDisplay1.valueKeys[x] = 0x00;
                                }
                                flowDisplay1 = 32;
                                numberKeys1 = 0;
                                keysTerpel = 20;
                                if(bufferDisplay1.idType == 6){
                                    bufferDisplay1.flagKeyboard = 5;
                                }else{
                                    for(x = 0; x < keysTerpel; x++)
                                    {
                                        bufferDisplay1.idFormaPago[x] = 0x00;
                                    }
                                    bufferDisplay1.flagKeyboard = 6;
                                }
                                SetPicture(1, DISPLAY_PASAPORTE);
                            }else{                            
                                flowDisplay1 = 32;
                                numberKeys1 = 0;
                                keysTerpel = 10;                            
                                bufferDisplay1.flagKeyboard = 4;                                
                                SetPicture(1, DISPLAY_INTRODUZCA_VALOR); 
                                WriteLCD(1,'$',3,2,1,0x0000,'N');
                            }
                            counter = 0;
                        break;
                            
                        case 5://pin voucher                           
                            for(x = 0; x < keysTerpel; x++)
                            {
                                bufferDisplay1.idFormaPago[x] = bufferDisplay1.valueKeys[x];
                            }                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            side.a.RFstateReport = 5; 
                            counter = 0;
                            flowDisplay1 = 35;                                                                                    
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                            
                        case 6://numero de pago                           
                            for(x = 0; x < keysTerpel; x++)
                            {
                                bufferDisplay1.PaymentNumber[x] = bufferDisplay1.valueKeys[x];
                            }                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            side.a.RFstateReport = 5;   
                            counter = 0;
                            flowDisplay1 = 35;                                                                                    
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                    }                    
                    Display1_ClearRxBuffer();
                break;
            }       
            Display1_ClearRxBuffer();
        break;
            
        case 33: // identificacion fidelizacion
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    counter = 0;
                    switch(Display1_rxBuffer[3])
                    { 
                        case 0x1A:  //Cedula                             
                            if(side.a.ActivoRedencion == 1 ){
                                bufferDisplay1.documentID = 3;
                                bufferDisplay1.idType = 5;
                                flowDisplay1 = 35;
                                side.a.RFstateReport = 4; 
                                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay1 = 32;
                                numberKeys1 = 0;
                                keysTerpel = 16;
                                bufferDisplay1.idType = 3;
                                bufferDisplay1.flagKeyboard = 1;
                                SetPicture(1, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay1.flagKeyboard = 1;                            
                        break;
                        
                        case 0x1B:  //extranjería                                                                                       
                            if(side.a.ActivoRedencion == 1 ){
                                bufferDisplay1.documentID = 4 ;
                                bufferDisplay1.idType = 5;
                                flowDisplay1 = 35;
                                side.a.RFstateReport = 4; 
                                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay1 = 32;
                                numberKeys1 = 0;
                                keysTerpel = 16;
                                bufferDisplay1.idType = 4;
                                SetPicture(1, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay1.flagKeyboard = 1;                            
                        break;
                        case 0x1c: //PASAPORTE                              
                            if(side.a.ActivoRedencion == 1 ){
                                bufferDisplay1.documentID = 5;
                                bufferDisplay1.idType = 5;
                                flowDisplay1 = 35;
                                side.a.RFstateReport = 4; 
                                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay1 = 32;
                                numberKeys1 = 0;
                                keysTerpel = 16;
                                bufferDisplay1.idType = 5;
                                SetPicture(1, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay1.flagKeyboard = 1;                                                    
                        break;
                        case 0x1d: //Lifemiles                            
                            if(side.a.ActivoRedencion == 1 ){
                                bufferDisplay1.idType = 5;
                                bufferDisplay1.documentID = 2;
                                flowDisplay1 = 35;
                                side.a.RFstateReport = 4; 
                                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay1 = 40; 
                                bufferDisplay1.idType = 2;
                                SetPicture(1, DISPLAY_ID_LIFE_MILES);                                                             
                            }                                                                                     
                        break;
                        case 0x1e: //Tarjeta pre inscrita                            
                            if(side.a.ActivoRedencion == 1 ){
                                bufferDisplay1.documentID = 1;
                                bufferDisplay1.idType = 5;
                                flowDisplay1 = 35;
                                side.a.RFstateReport = 4;
                                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay1 = 32;
                                numberKeys1 = 0;
                                keysTerpel = 16;
                                bufferDisplay1.idType = 1;
                                SetPicture(1, DISPLAY_PASAPORTE);                             
                            }                            
                            bufferDisplay1.flagKeyboard = 1;                                                    
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                        break;
                    }                    
                }                
				vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
                
            }                      
			Display1_ClearRxBuffer();
        break;
        
        case 34:
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay1.idTerpelFideliza[x] = 0x00;
            }
            if(code_pirata(magneticReader[1],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){
				    bufferDisplay1.idTerpelFideliza[x-1] = temporal[x];                    
                }
                bufferDisplay1.idTerpelFideliza[0] = x-2;
                // Authorization request
                SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                flowDisplay1 = 35;  
                side.a.RFstateReport = 2;                        
                side.a.ActivoFideliza = 2;
                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);                                                                            
                Display1_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            AuthType = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            AuthType = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            }            
        break;
        case 35:            
            //Touch for return to init display
            //vTaskDelay( 2000 / portTICK_PERIOD_MS );               
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            side.a.ActivoFideliza = 3;
                            side.a.RFstateReport = 3;
                            bufferDisplay1.FidelConf = 0;
                            side.a.ActivoRedencion = 0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            counter      = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            side.a.ActivoFideliza = 3;
                            side.a.RFstateReport = 3;
                            bufferDisplay1.FidelConf = 0;
                            side.a.ActivoRedencion = 0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            ShiftState   = 0;
                            counter      = 0;
                        break;
                    }                    
                }
                Display1_ClearRxBuffer(); 
            }            
        break;
        
        case 36:      
            counter ++;
            side.a.ActivoFideliza = 0;
            side.a.RFstateReport  = 0;
            if(validaclientefiel == 1){
                for(x = 0; x < 17; x++)
                {
                    WriteMessage(1,NameCustomer[x],4,x,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage[x],6,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage1[x],8,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage2[x],10,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage3[x],12,x+1,2,0x0000,'Y');
                }
            }
            if(validaclientefiel == 2){                
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage[x],6,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage1[x],8,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage2[x],10,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage3[x],12,x+1,1,0x0000,'Y');
                }
            }                        
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Usuario correcto                          
                            if(AuthType == 1){
                                flowDisplay1 =10;
                                SetPicture(1, DISPLAY_ID_TERPEL);
                            }else{
                                flowDisplay1 =3;
                                SetPicture(1, DISPLAY_FORMA_PROGRAMACION); 
                            }
                            side.a.ActivoFideliza = 3;
                            side.a.RFstateReport = 3;
                            if(validaclientefiel == 1){
                                bufferDisplay1.FidelConf = 1;
                            }else{
                                bufferDisplay1.FidelConf = 0;
                            }
                            counter = 0;
                        break;
                        case 0x0B:  //Usuario incorrecto
                            flowDisplay1 = 33;
                            side.a.ActivoFideliza = 3;                            
                            bufferDisplay1.FidelConf = 0;
                            side.a.RFstateReport = 3;
                            counter = 0;
                            SetPicture(1, DISPLAY_IDEN_FIDELIZACION);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            side.a.ActivoFideliza = 3;
                            side.a.RFstateReport = 3;
                            bufferDisplay1.FidelConf = 0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            counter      = 0;
                        break;
                    }                    
                }            
                Display1_ClearRxBuffer();  
            }                               
        break;
        
        case 38:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x53:
                            bufferDisplay1.lastSale = true;
                            flowDisplay1 = 39;                            
                            SetPicture(1, DISPLAY_FORMA_DE_PAGO_TERPEL);
                        break;
                        case 0x54:  //Solicita teclado 
                            for(x = 0; x < 20; x++)
                            {
                                bufferDisplay1.valueKeys[x] = 0x00;
                            }
                            bufferDisplay1.lastSale = false;
                            flowDisplay1 = 32;
                            numberKeys1 = 0;
                            keysTerpel = 10;                            
                            bufferDisplay1.flagKeyboard = 3;
                            SetPicture(1, DISPLAY_INTRODUZCA_VALOR);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                        break;                                                                       
                    }                    
                }
                Display1_ClearRxBuffer();
            }            
        break;
            
        case 39: 
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x1A: //VOUCHER     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay1 = 35;
                            side.a.ActivoRedencion = 1;
                            side.a.RFstateReport = 4;
                            bufferDisplay1.idType = 6;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1B: //Sodexo     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay1 = 35;
                            side.a.ActivoRedencion = 1;
                            side.a.RFstateReport = 4;
                            bufferDisplay1.idType = 4;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1C: //MASTER     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay1 = 35;
                            side.a.ActivoRedencion = 1;
                            side.a.RFstateReport = 4;
                            bufferDisplay1.idType = 2;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);	
                        break;                        
                        case 0x1D:  //LIFEMILES                             
                            flowDisplay1 = 33;
                            side.a.ActivoRedencion = 1;                                                          
                            SetPicture(1, DISPLAY_PAGO_LM);  
                        break;
                        case 0x1E: //Debito     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay1 = 35;
                            side.a.ActivoRedencion = 1;
                            side.a.RFstateReport = 4;
                            bufferDisplay1.idType = 3;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1F: //VISA    1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay1 = 35;
                            side.a.ActivoRedencion = 1;
                            side.a.RFstateReport = 4;
                            bufferDisplay1.idType = 1;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                        break;                                                                       
                    }                    
                }
                Display1_ClearRxBuffer();
            } 
        break;
        
        case 40:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0xB6:
                            if(bufferDisplay1.idType ==2){
                                flowDisplay1 = 34;
                                SetPicture(1, DISPLAY_ESPERANDO_ID_TERPEL);
                            }
                            if(bufferDisplay1.idType =='F'){
                                flowDisplay1 = 42;
                                SetPicture(1, DISPLAY_ESPERANDO_ID_TERPEL);
                            }
                        break;
                        case 0xB7:  //Solicita teclado 
                            flowDisplay1 = 32;
                            numberKeys1 = 0;
                            keysTerpel = 20;                                                        
                            SetPicture(1, DISPLAY_PASAPORTE);
                            if(bufferDisplay1.idType !='F'){
                                for(x = 0; x < 20; x++)
                                {
                                    bufferDisplay1.valueKeys[x] = 0x00;
                                }
                                bufferDisplay1.flagKeyboard = 1;                                
                            }else{
                                for(x = 0; x < 20; x++)
                                {
                                    bufferDisplay1.valueKeys[x] = 0x00;
                                }
                                bufferDisplay1.flagKeyboard = 2;                                
                            }
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                        break;
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            ShiftState = 0;
                        break;                                               
                    }                    
                }
                Display1_ClearRxBuffer();
            }            
        break;
            
        case 41: 
            bufferDisplay1.saleNumber[0] = 9;
			for (x = 1; x < 10; x++){
                bufferDisplay1.saleNumber[x] = 0x00;
            }
            for(x = 0; x < 14; x++)
            {
                WriteMessage(1,NumSale[x],4,x+5,1,0x0000,'Y');
            }
            for(x = 0; x < 10; x++)
            {
                WriteMessage(1,cardmessage[x],6,x+5,1,0x0000,'Y');                
            }
            for(x = 1; x < 10; x++)
            {
                bufferDisplay1.saleNumber[x] = cardmessage[x-1];                
            }            
            if(bufferDisplay1.idType ==5){
                for(x = 0; x < 9; x++)
                {
                    WriteMessage(1,VolSale[x],8,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,cardmessage1[x],10,x+5,1,0x0000,'Y');
                }
            }
            else{
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,MonSale[x],8,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,bufferDisplay1.MoneyPay[x],10,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 21; x++)
                {
                    WriteMessage(1,MonSalePayed[x],12,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,bufferDisplay1.MoneyPayed[x],14,x+5,1,0x0000,'Y');
                }                 
            }            
            if(bufferDisplay1.idType ==5){
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,MonSale[x],12,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,bufferDisplay1.MoneyPay[x],14,x+5,1,0x0000,'Y');
                }  
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,MilageSale[x],16,x+5,1,0x0000,'Y');
                }            
                for(x = 0; x < 6; x++)
                {
                    WriteMessage(1,cardmessage3[x],18,x+5,1,0x0000,'Y');
                }
            }                
            
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Monto correcto
                            if(bufferDisplay1.idType ==5){
                                flowDisplay1 = 40; 
                                bufferDisplay1.idType = 'F'; //forma pago
                                if(bufferDisplay1.documentID == 2){
                                    SetPicture(1, DISPLAY_ID_LIFE_MILES);  
                                }else{
                                    bufferDisplay1.flagKeyboard = 2;
                                    flowDisplay1 = 32;
                                    numberKeys1 = 0;
                                    keysTerpel = 16;
                                    SetPicture(1, DISPLAY_PASAPORTE);
                                }
                            }else{                            
                                flowDisplay1 = 32;
                                numberKeys1 = 0;
                                keysTerpel = 10;                            
                                bufferDisplay1.flagKeyboard = 4;                                
                                SetPicture(1, DISPLAY_INTRODUZCA_VALOR); 
                                WriteLCD(1,'$',3,2,1,0x0000,'N');
                            }
                        break;
                        
                        case 0x0B:  //Monto incorrecto incorrecto                            
                            bufferDisplay1.flagPrint =  0;
                            bufferDisplay1.idType = 0x00;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            side.a.RFstateReport = 7;
                            SetPicture(1, DISPLAY_INICIO0);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            bufferDisplay1.FidelConf = 0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                        break;
                    }                    
                }
                Display1_ClearRxBuffer(); 
            }                                
        break;
         
        case 42:
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay1.idFormaPago[x] = 0x00;
            }
            if(code_pirata(magneticReader[1],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){
				    bufferDisplay1.idFormaPago[x-1] = temporal[x];                    
                }
                bufferDisplay1.idFormaPago[0] = x-2;
                // Authorization request
                SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                flowDisplay1 = 14;    
                hiddenKeys = 20;
                controlChar ='*';
                numberKeys1=0;
                bufferDisplay1.flagKeyboard = 8;
                SetPicture(1,DISPLAY_PASS_ALFNUM); 
                Display1_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            AuthType = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay1 = 0;
                            bufferDisplay1.flagPrint =  0;
                            PresetFlag = 0;
                            iButtonFlag = 0;
                            AuthType = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            }            
        break;
            
        
        case 43:                                                
            for(x = 0; x < 25; x++)
            {
                WriteMessage(1,cardmessage[x],6,x+1,1,0x0000,'Y');
            }            
            for(x = 0; x < 25; x++)
            {
                WriteMessage(1,cardmessage1[x],10,x+1,1,0x0000,'Y');
            }    
            for(x = 0; x < 25; x++)
            {
                WriteMessage(1,cardmessage2[x],14,x+1,1,0x0000,'Y');
            }
            for(x = 0; x < 25; x++)
            {
                WriteMessage(1,cardmessage3[x],18,x+1,1,0x0000,'Y');
            }
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Imprimir comprobante
                            printPayment(EEPROM_1_ReadByte(8),side.a.RF);
                            vTaskDelay( 500 / portTICK_PERIOD_MS ); 
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            SetPicture(1, DISPLAY_INICIO0); 
                            for(x = 0; x < 7; x++)
                            {
                                bufferDisplay1.saleValue[x] = 0x00;
                            }
                        break;
                        
                        case 0x0B:  //No imprimir comprobante                                                       
                            bufferDisplay1.idType = 0x00;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            SetPicture(1, DISPLAY_INICIO0);
                            for(x = 0; x < 7; x++)
                            {
                                bufferDisplay1.saleValue[x] = 0x00;
                            }
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            bufferDisplay1.FidelConf = 0;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            for(x = 0; x < keysTerpel; x++)
                            {
                                bufferDisplay1.saleValue[x] = 0x00;
                            }
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            }                                 
        break;
            
        case 44:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Mas voucher
                            bufferDisplay1.lastSale = false;
                            flowDisplay1 = 35;
                            side.a.ActivoRedencion = 1;
                            side.a.RFstateReport = 4;
                            bufferDisplay1.idType = 6;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);
                        break;
                        
                        case 0x0B:  //Finalizar                                                       
                            side.a.RFstateReport = 6;                             
                            flowDisplay1 = 35;                                                                                    
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay1.flagPrint =  0;
                            side.a.ActivoRedencion = 0;
							side.a.RFstateReport = 7;
                            flowPos      = 0;
                            flowDisplay1 = 0;                            
                            PresetFlag   = 0;
                            iButtonFlag  = 0;
                            for(x = 0; x < keysTerpel; x++)
                            {
                                bufferDisplay1.saleValue[x] = 0x00;
                            }
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            } 
        break;
        
    }    
}

/*
*********************************************************************************************************
*                                         void PollingDisplay2(void)
*
* Description : Pregunta estado al surtidor 
*               
*
*********************************************************************************************************
*/
void PollingDisplay2(void){    
    uint8 x,y;    
    tempcont =EEPROM_1_ReadByte(225);
    if(counter2 >= tempcont*100 && tempcont > 0){ //70 segs aprox
        bufferDisplay2.flagPrint =  0;
        flowDisplay2 = 's'; 
        flowPosB     = 0;                           
        PresetFlag2  = 0;
        iButtonFlag2 = 0;
        counter2     = 0;
        SetPicture(2, DISPLAY_TIEMPO_EXPIRADO);
    }
    switch(flowDisplay2){
        case 's':
        if(Display2_GetRxBufferSize() == 8)
            {   
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Return to initial screen                                                                                    
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            AuthType2 = 0;
                            counter2  = 0;
                            Display2_ClearRxBuffer();
                        break;
                        case 0x94:  //Return to initial screen                                                                                    
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            AuthType2 = 0;
                            counter2  = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }               
                Display2_ClearRxBuffer();
            }
        break;
        case 0:
			//InitDisplay2();            
            if(NumPositions == 2){
                SetPicture(2, DISPLAY_INICIO0);
            }else{
                SetPicture(2, DISPLAY_SELECCIONE_POSICION);
            } 
            bufferDisplay2.flagActiveSale = false;
            flowDisplay2 = 1;
            Display2_ClearRxBuffer();            
        break;
        case 1: //Menu             
            if(NumPositions > 2)
            {
                if(bufferDisplay2.flagActiveSale)
                {
                    flowDisplay2 = flowPosB;            
                }
                if(bufferDisplay4.flagActiveSale)
                {
                    flowDisplay4 = flowPosD;
                    selectPosB = 2;
                }
            }
            if(Display2_GetRxBufferSize() == 8)
            {   
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {                                             
                    if(NumPositions == 2 && bufferDisplay2.PrintEnd == 0){
                        flowDisplay2 = 2;                               //Pantalla forma de pago                      
                        if(EEPROM_1_ReadByte(215)!= 11){
                            SetPicture(2, DISPLAY_FORMA_PAGO_DESEADA);                                                
							Display2_ClearRxBuffer();
                        }else{
                            SetPicture(2,DISPLAY_FORMA_PAGO_DESEADA_TERPEL);
                        }                                              
                    }else{
                        switch(Display2_rxBuffer[3]){
				        case 0x57:						        //POS A                                                                                                                       
                                if(bufferDisplay2.flagActiveSale || bufferDisplay2.PrintEnd == 1){
                                    flowDisplay2 = flowPos;      //Si está vendiendo en esta posición regresa a su flujo
                                }else{
                                    if(EEPROM_1_ReadByte(215)!= 11){
                                        SetPicture(2, DISPLAY_FORMA_PAGO_DESEADA);                                                
                                    }else{
                                        SetPicture(2,DISPLAY_FORMA_PAGO_DESEADA_TERPEL);
                                    }
                                    selectPosB    = 1;
                                    flowDisplay2  = 2;
									Display2_ClearRxBuffer();
                                }
                                if (bufferDisplay4.flagActiveSale){
                                    flowDisplay4 = flowPosD;    //Si la venta está activa en POS B regresa a su flujo
                                }
                                else{
                                    flowDisplay4 = 0; 
                                    flowPosD     = 0;
                                }
					    break;
                            		       
					    case 0x56:  				            //POS B                                                                 
                                if(bufferDisplay2.flagActiveSale){
                                    flowDisplay2 = flowPosB;      //Si está vendiendo en esta posición regresa a su flujo
                                }
                                else{
                                    flowDisplay2 = 0;
                                    flowPosB     = 0;
                                } 
                                if (bufferDisplay4.flagActiveSale || bufferDisplay4.PrintEnd == 1){                                    
                                    flowDisplay4 = flowPosD;    //Si la venta está activa en POS B regresa a su flujo
                                }else{
                                    if(EEPROM_1_ReadByte(215)!= 11){
                                        SetPicture(2, DISPLAY_FORMA_PAGO_DESEADA);                                                
                                    }else{
                                        SetPicture(2,DISPLAY_FORMA_PAGO_DESEADA_TERPEL);
                                    }
							        selectPosB    = 2;
                                    flowDisplay4  = 2;                            
                                }                           
					    break;                                                   
				    }                      
                    }
                }  
                Display2_ClearRxBuffer();
                vTaskDelay( 10 / portTICK_PERIOD_MS );
            }
            
        break;
        case 2: //Menu de metodo de pago
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x0D:  //Pantalla efectivo   
                            if(EEPROM_1_ReadByte(221) == 1)
                            {
                                AuthType2 = 2;
                                bufferDisplay2.saleType = 1;
                                if(EEPROM_1_ReadByte(215)!= 11){
                                    flowDisplay2 = 3;                                                                         
                                    SetPicture(2, DISPLAY_FORMA_PROGRAMACION);                                      
                                }else{
                                    flowDisplay2 = 37;                                       
                                    SetPicture(2, DISPLAY_FIDELIZACION);  
                                }
                            }else{
                                SetPicture(2, DISPLAY_CANCELADO_X_PC);
                                vTaskDelay( 900 / portTICK_PERIOD_MS );
                                flowDisplay2 = 0; 
                                Display2_ClearRxBuffer();                                                               
                            }
                        break;
                        case 0x0E:  //Pantalla credito 
                            for(x = 0; x < 10; x++)
                            {                                
                                bufferDisplay2.CreditpresetValue[0][x] = 0x00;
                                bufferDisplay2.CreditpresetValue[1][x] = 0x00;                                
                            }                            
                            if(EEPROM_1_ReadByte(221) == 1)
                            {                                
                                bufferDisplay2.saleType = 2;  
                                AuthType2 = 1;
                                if(EEPROM_1_ReadByte(215)!= 11){
                                    flowDisplay2 = 10;
                                    SetPicture(2, DISPLAY_ID_DIGITAL);
                                }else{
                                    flowDisplay2 = 37;
                                    SetPicture(2, DISPLAY_FIDELIZACION);
                                }                                
                                Display2_ClearRxBuffer();
                            }else
                            {
                                SetPicture(2, DISPLAY_CANCELADO_X_PC);
                                vTaskDelay( 900 / portTICK_PERIOD_MS );
                                flowDisplay2 = 0; 
                                counter2 = 0;
                                Display2_ClearRxBuffer();                                                             
                            }                            
                        break;
                            
                        case 0x0F: //Forma de pago
                            if(EEPROM_1_ReadByte(221) == 1)
                            {
                                flowDisplay2 = 38;                            
                                SetPicture(2, DISPLAY_SELECCION_VENTA);
                            }
                        break;
                            
                        case 0x45:  //Pantalla otras opciones 
                            flowDisplay2 = 12;                            
                            SetPicture(2,DISPLAY_OPERACIONES); 
                            AuthType2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay2.flagPrint =  0;                            
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay2.flagPrint =  0;                            
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }
                } 
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();                
            }            
        break;
        
        case 37: // Desea fidelizar            
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    side.b.ActivoFideliza = 0;
                    side.b.ActivoRedencion = 0;
                    switch(Display2_rxBuffer[3])
                    {                                                                                                                         
                        case 0x0A: //Si                                                                                   
                            flowDisplay2 = 33;
                            SetPicture(2, DISPLAY_IDEN_FIDELIZACION);                              
                        break;
                        case 0x0B:  //No 
                            if(AuthType2 == 1){
                                flowDisplay2 =10;                                
                                SetPicture(2, DISPLAY_ID_TERPEL);
                            }else{
                                flowDisplay2 =3;                                
                                SetPicture(2, DISPLAY_FORMA_PROGRAMACION); 
                            }                                                                                     
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            counter2     = 0;
                        break;
                    }                    
                }                                
                Display2_ClearRxBuffer(); 
            }            
        break;
                        
        case 3:  //Menu de tipo de preset
            for(x = 0; x <10; x++)
            {
                bufferDisplay2.presetValue[0][x] = 0x00;
                bufferDisplay2.presetValue[1][x] = 0x00;
            }
            Credit_Auth_OK2 = 0;
            counter2 ++;
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    counter2 = 0;
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x0F:  //Preset dinero                
                            flowDisplay2 = 4;                              
                            bufferDisplay2.presetType[0] = 2;
                            bufferDisplay2.presetType[1] = '$';
                            numberKeys2 = 0;
                            SetPicture(2,DISPLAY_INTRODUZCA_VALOR);   
                            WriteLCD(2,'$',3,2,1,0x0000,'N');							
                            if(EEPROM_1_ReadByte(2) > 0)
                            {
                                flagPoint2 = 0;
                            }else
                            {
                                flagPoint2 = 1;
                            }
                            Display2_ClearRxBuffer();
                        break; 
                        case 0x10:  //Preset volumen                 
                            flowDisplay2 = 4;                            
                            bufferDisplay2.presetType[0] = 1;
                            bufferDisplay2.presetType[1] = 'G';
                            numberKeys2 = 0;                            
                            SetPicture(2,DISPLAY_INTRODUZCA_VOLUMEN);                            
                            WriteLCD(2,'G',3,2,1,0x0000,'N');                            							
                            if(EEPROM_1_ReadByte(3) > 0) //VolDec
                            {
                                flagPoint2 = 0;
                            }else
                            {
                                flagPoint2 = 1;
                            }
                            Display2_ClearRxBuffer();
                        break;
                        case 0x43:  //Preset full 
                            bufferDisplay2.presetType[0] = 3;
                            bufferDisplay2.presetType[1] = 'F';                            
                            for(x = 1; x <(digits - 1); x++)
                            {
                                bufferDisplay2.presetValue[0][x] = '9';
                            }                            
                            bufferDisplay2.presetValue[0][x] = '0';
                            bufferDisplay2.presetValue[0][x + 1] = '0';
                            bufferDisplay2.presetValue[0][0] = digits;
                            for(x = 0; x <= bufferDisplay2.presetValue[0][0]; x++)
                            {
                                bufferDisplay2.presetValue[1][x] = bufferDisplay2.presetValue[0][x];
                            }
                            flowDisplay2 = 5;
                            SetPicture(2,DISPLAY_SELECCIONE_PRODUCTO4); 
                            Display2_ClearRxBuffer();                         
                        break;
                        case 0x94:  //Retroceso 
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            SetPicture(2,DISPLAY_INICIO0); 
                            Display2_ClearRxBuffer();                                                       
                        break;
                        case 0x3B:  //Pantalla Inicial    
                            flowDisplay2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            AuthType2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay2.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;                            
                            AuthType2    = 0;
                            counter2     = 0;
                            Display2_ClearRxBuffer();
                        break;                        
                    }
                }                  
                //vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();
            }
           
        break;
        
        case 4:    // Teclado general                
            counter2 ++;
            switch (alphanumeric_keyboard2(digits + 1,0))
            {
                case 0:  //Pantalla Inicial    
                    flowDisplay2 = 0;
                    AuthType2 = 0;
                    SetPicture(2,DISPLAY_INICIO0);
                    Display2_ClearRxBuffer();                            
                break;
                    
                case 1: //Enter
                    counter2 = 0;
                    for(x = 0; x <= bufferDisplay2.valueKeys[0]; x++)
                    {
                        bufferDisplay2.presetValue[0][x] = bufferDisplay2.valueKeys[x];
                        bufferDisplay2.presetValue[1][x] = bufferDisplay2.valueKeys[x];
                    }  
                    IntValueB = 0;
                    for(x = 0; x < 10; x++)
                    {                           
                        bufferDisplay2.PresetTemp[x] = 0x00;                         
                    }                    
                    // Convierte valor del preset en entero
                    for(x = 1; x < 10; x++)
                    {
                        if(bufferDisplay2.presetValue[0][x] != '.' && bufferDisplay2.presetValue[0][x] != ',' && bufferDisplay2.presetValue[0][x] != 0x00)
                        {
                           bufferDisplay2.PresetTemp[x - 1] = bufferDisplay2.presetValue[0][x] - 48;
                        }
                    }                      
                    // Convierte valor del preset en entero
                    for(x = 0; x < bufferDisplay2.presetValue[0][0]; x++)
                    {                                
                        IntValueB = 10 * IntValueB + bufferDisplay2.PresetTemp[x];                            
                    } 
                    
                   // Rechaza transaccion si el Preset es menor a COP$1000
                    if(bufferDisplay2.presetType[0] == 2)
                    {
                    	if(IntValueB < 1000)
                    	{
                        	AuthType2 = 0;
                        	bufferDisplay2.flagPrint =  0;
                        	flowDisplay2 = 0;
                        	SetPicture(2,DISPLAY_INICIO0); 
                    	}
                    	else
                    	{
                        	flowDisplay2 = 5;   //caso para seleccion de producto
                        	SetPicture(2, DISPLAY_SELECCIONE_PRODUCTO4);
                    	}
                    }
                    else
                    {                        
                        if((bufferDisplay2.presetValue[0][0] > 0 && IntValueB != 0) && (bufferDisplay2.presetValue[0][0] < 7 && IntValueB >= 1))
                        {
                            flowDisplay2 = 5;   //caso para seleccion de producto
                        	SetPicture(2, DISPLAY_SELECCIONE_PRODUCTO4);  
                        }
                        else
                        {
                            AuthType2 = 0;
                        	bufferDisplay2.flagPrint =  0;
                        	flowDisplay2 = 0;
                        	SetPicture(2,DISPLAY_INICIO0);
                        }                   	
                    }
                    Display2_ClearRxBuffer();                    
                break;
            }

        break;
            
        case 5: //Menu de seleccion de producto
            counter2 = counter2 + 3;
            if(side.b.GradesHose[1] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(2, producto[side.b.GradesHose[1]-1][x],9+x,11); //FontSpace(LCD, caracter,posx,posy)
                //WriteMessage(1, producto[side.a.GradesHose[1]-1][x],11,6+x,2,0x0000,'Y'); //WriteMessage(1, producto1[x],11,7+x,2,0x0000,'Y');
                }
            }
            if(side.b.GradesHose[2] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(2, producto[side.b.GradesHose[2]-1][x],10+x,17); //FontSpace(LCD, caracter,posx,posy)
                //WriteMessage(1, producto[side.a.GradesHose[2]-1][x],17,7+x,2,0x0000,'Y');//WriteMessage(1, producto2[x],17,8+x,2,0x0000,'Y');
                }
            }
            if(side.b.GradesHose[3] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(2, producto[side.b.GradesHose[3]-1][x],11+x,23);
                //WriteMessage(1, producto[side.a.GradesHose[3]-1][x],23,8+x,2,0x0000,'Y');
                }
            }
            if(side.b.GradesHose[4] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(2, producto[side.b.GradesHose[4]-1][x],12+x,29);
                //WriteMessage(1, producto[side.a.GradesHose[4]-1][x],29,9+x,2,0x0000,'Y');
                }
            }  
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x80:  //Grado 1 
                            if(side.b.hoseNumber > 0)
                            {
                                numberKeys2 = 0; 
                                flowDisplay2 = 9;
                                side.b.hose = 1;                            
                                //Credit
                                if(AuthType2 == 2)
                                {
									if(KmCash[1] == 0x01)
                                        {
                                            bufferDisplay2.flagKeyboard = 2; 
                                            SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                        }else{
                                            bufferDisplay2.flagKeyboard = 1; 
                                            SetPicture(2, DISPLAY_DIGITE_PLACA);
                                                                         

                                        } 
                                }                            
                                //Cash
                                if(AuthType2 == 1)
                                {                    
                                    bufferDisplay2.flagKeyboard = 2;
                                    SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter2 = 0;
                            Display2_ClearRxBuffer();
                        break;        
                        case 0x81:  //Grado 2
                            if(side.b.hoseNumber > 1)
                            {
                                numberKeys2 = 0;
                                flowDisplay2 = 9;
                                side.b.hose = 2;                          
                                //Credit
                                if(AuthType2 == 2)
                                {
                                    if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay2.flagKeyboard = 2; 
                                        SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay2.flagKeyboard = 1; 
                                        SetPicture(2, DISPLAY_DIGITE_PLACA);

                                    } 
                                }
                                
                                //Cash
                                if(AuthType2 == 1)
                                {                    
                                    bufferDisplay2.flagKeyboard = 2;
                                    SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                            
                        case 0x7F:  //Grado 3
                            if(side.b.hoseNumber > 2)
                            {
                                numberKeys2 = 0;
                                flowDisplay2 = 9;
                                side.b.hose = 3;                            
                                //Credit
                                if(AuthType2 == 2)

                                {
									if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay2.flagKeyboard = 2; 
                                        SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay2.flagKeyboard = 1; 
                                        SetPicture(2, DISPLAY_DIGITE_PLACA);
                                    } 
                                }
                                
                                //Cash
                                if(AuthType2 == 1)
                                {                    
                                    bufferDisplay2.flagKeyboard = 2;
                                    SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter2 = 0;
                            Display2_ClearRxBuffer();
                        break;   
                        
                        case 0xB8:  //Grado 4 
                            if(side.b.hoseNumber > 3)
                            {
                                numberKeys2 = 0;
                                flowDisplay2 = 9;
                                side.b.hose = 4;                           
                                //Credit
                                if(AuthType2 == 2)
                                {
									if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay2.flagKeyboard = 2; 
                                        SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay2.flagKeyboard = 1; 
                                        SetPicture(2, DISPLAY_DIGITE_PLACA);
                                    } 
                                }                            
                                //Cash
                                if(AuthType2 == 1)
                                {                    
                                    bufferDisplay2.flagKeyboard = 2;
                                    SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Retroceso
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                            Display2_ClearRxBuffer();                                                    
                        break;
                            
                        case 0x7E:  //Pantalla Inicial    
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                counter2 = 0;
                Display2_ClearRxBuffer();               
            }
            
        break;
                    
        case 6: //Pantalla de impresion SI/NO
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x39:  //Si imprimir  
                            flowDisplay2 = 7;
                            numberKeys2 = 0;
                            bufferDisplay2.flagPrint =  1;                            
							bufferDisplay2.PrintFlagEOT = 0;
                            SetPicture(2,DISPLAY_SUBA_MANIJA); 
                            Display2_ClearRxBuffer();                           
                        break; 
                        case 0x38:  //No imprimir 
                            flowDisplay2 = 7;//Esperando estado del dispensador 
                            bufferDisplay2.flagPrint =  0;                                                                
							bufferDisplay2.PrintFlagEOT = 0;
                            SetPicture(2,DISPLAY_SUBA_MANIJA);
                            Display2_ClearRxBuffer();
                        break;
                        case 0x7E:  //Pantalla Inicial                                                                                    
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint = 0;
                            AuthType2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                } 
                //vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();             
            }
                        
        break;                                             
        case 7: //Preset ON y espera descuelgue de manguera
            PresetFlag2 = 1;  
            counter2 = counter2 + 4;
            vTaskDelay( 40 / portTICK_PERIOD_MS );
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            AuthType2 = 0;
                            bufferDisplay2.zeroSend = 1;
                            vTaskDelay( 50 / portTICK_PERIOD_MS );
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            AuthType2 = 0;
                            bufferDisplay2.zeroSend = 1;
                            vTaskDelay( 50 / portTICK_PERIOD_MS );
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display2_ClearRxBuffer();                
            }                      
        break;
            
        case 8:       
            //Pump Busy...
            vTaskDelay( 10 / portTICK_PERIOD_MS ); 
            if(NumPositions > 2)
            {
                flowDisplay2 = 1;
            }
            counter2 = 0;
        break;
            
        case 9: // Keyboard    
            if(upcount2[0] == 1){
                if(upcount2[1] == 1){
                    counter2 ++;
                    upcount2[1] = 0;
                }else{
                    upcount2[1] = 1;
                }
            }else{
                counter2++;
            }
            switch (alphanumeric_keyboard2(11,0))
            {
                case 0: //Cancel
                    switch(bufferDisplay2.flagKeyboard)
                    {
                        case 1://License plate
                            for(x = 0; x < 11; x++)
                            {
                                bufferDisplay2.licenceSale[x] = 0;
                            }
                            flowDisplay2 = 0;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 2://Mileage
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay2.mileageSale[x] = 0;
                            }
                            counter2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 3://CC/NIT
                            for(x = 0; x < 11; x++)
                            {
                                bufferDisplay2.identySale[x] = 0;
                            }
                            counter2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        case 4://ID
                            for(x = 0; x < 11; x++)
                            {
                                bufferDisplay2.shiftId[x] = 0;
                            }
                            counter2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                    Display2_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay2.flagKeyboard)
                    {
                        case 1://Licence plate
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay2.licenceSale[x] = 0x00;
                            }
                            
                            for(x = 0; x <= bufferDisplay2.valueKeys[0]; x++)
                            {
                                bufferDisplay2.licenceSale[x] = bufferDisplay2.valueKeys[x];
                            }
                            counter2 = 0;
                            flowDisplay2 = 6;                               
                            SetPicture(2, DISPLAY_DESEA_IMPRIMIR_RECIBO);                                                         
                        break;
                        
                        case 2:  //Mileage
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay2.mileageSale[x] = 0x00;
                            }
                            for(x = 0; x <= bufferDisplay2.valueKeys[0]; x++)
                            {
                                bufferDisplay2.mileageSale[x] = bufferDisplay2.valueKeys[x];
                            }
                            
                            if(AuthType2 == 1)
                            {
                                flowDisplay2 = 7;                                
                                SetPicture(2,DISPLAY_SUBA_MANIJA);
                            }
                            if(AuthType2 == 2)
                            {
                                if(KmCash[1] == 0x01)
                                {   
                                    numberKeys2 = 0; 
                                    flowDisplay2 = 9;
                                    bufferDisplay2.flagKeyboard = 1; 
                                    SetPicture(2, DISPLAY_DIGITE_PLACA);
                                }                                         
                            } 
                            counter2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 3://CC/NIT
                            for(x = 0; x <= bufferDisplay2.valueKeys[0]; x++)
                            {
                                bufferDisplay2.identySale[x] = bufferDisplay2.valueKeys[x];
                            }
                            counter2 = 0;
                            Display2_ClearRxBuffer();
                        case 4://ID
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay2.shiftId[x] = bufferDisplay2.valueKeys[x];
                            }
                            flowDisplay2 = 14;      //Pide clave                            
                            numberKeys2 = 0;
                            hiddenKeys  = 10;
                            controlChar = '*';
                            counter2    = 0;
                            bufferDisplay2.flagKeyboard = 3;
                            SetPicture(2,DISPLAY_INGRESE_PASSWORD);
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                //Display2_ClearRxBuffer();    
                break;

            }  
            Display2_ClearRxBuffer();           
        break;    
    ////////////////// CASOS PARA CRÉDITO  /////////////////////
        case 10:
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0xB6:  //Solicitud ibutton  
                            flowDisplay2 = 11;
                            numberKeys2  = 0;                            
                            //bufferDisplay2.flagPrint =  1;
                            counter2 = 0;
                            bufferDisplay2.idType = 1;
                            SetPicture(2,DISPLAY_ESPERANDO_ID);                            
                        break; 
                        case 0xB7:  //ID por número
                            if(EEPROM_1_ReadByte(215)!= 11){
                            	flowDisplay2 = 24;
                            	numberKeys2 = 0;  
                                counter2 = 0;
                            	//bufferDisplay2.flagPrint =  1;
                            	Tag_ClearRxBuffer();
                            	Tag_ClearTxBuffer();
                            	Tag_PutChar('O');
                            	Tag_PutChar('K');
                            	Tag_PutChar(0x02);
                            	vTaskDelay( 100 / portTICK_PERIOD_MS );
                            	SetPicture(2, DISPLAY_ESPERANDO_ID);                           
                            }else{
                            	flowDisplay2 = 25;
                                numberKeys2 = 0;
                                bufferDisplay2.idType = 3;
                            	vTaskDelay( 100 / portTICK_PERIOD_MS );
                            	SetPicture(2, DISPLAY_SELECCIONE_OP_TERPEL);
                            }              
                            counter2 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                        break;
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay2.flagPrint =  0;
                            bufferDisplay2.idType = 0;
                            flowDisplay2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                        break;
                    }                    
                }                                
                Display2_ClearRxBuffer();
            }                                  
        break;
        
        case 11: //Lectura del iButton  
            counter2 ++;
            for(x = 0; x < 30; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 25; x++)
            {
                bufferDisplay2.idSerial[x] = 0x00;
            }
            if(touch_present(2) == 1)
            {
				if(touch_write(2,0x33))
                {
					for(x = 1; x <= 8; x++)
                    {
						temporal[x] = touch_read_byte(2);
					}
					y = 0;
					for(x = 1; x < 8; x++)
                    {
                        y = crc_check(y,temporal[x]);
                    }
					if(y == temporal[8])
                    {
						bufferDisplay2.idSerial[0] = 16;
						y = 16;
						for(x = 1; x <= 8; x++)
                        {
							if((temporal[x] & 0x0F) >= 10)
                            {
								bufferDisplay2.idSerial[y] = (temporal[x] & 0x0F) + 55;
							}else{
								bufferDisplay2.idSerial[y] = (temporal[x] & 0x0F) + 48;				
							}
                            y--;
							if(((temporal[x] >> 4) & 0x0F) >= 10)
                            {
								bufferDisplay2.idSerial[y] = ((temporal[x] >> 4) & 0x0F) + 55;
							}else{
								bufferDisplay2.idSerial[y] = ((temporal[x] >> 4) & 0x0F) + 48;				
							}
                            y--;
						}                        
                        SetPicture(2,DISPLAY_ID_RECONOCIDO);                                           
                        vTaskDelay( 500 / portTICK_PERIOD_MS ); 
                        iButtonFlag2 = 1;
                        SetPicture(2, DISPLAY_FORMA_PROGRAMACION);
                        flowDisplay2 = 3;
                        counter2     = 0;
					}                                     
				}
                else //iButton Error
                {
                    SetPicture(2,DISPLAY_ID_NO_RECONOCIDO);                                           
                    Display2_ClearRxBuffer();
                    vTaskDelay( 200 / portTICK_PERIOD_MS );    
                    SetPicture(2, DISPLAY_INICIO0);
                    flowDisplay2 = 0;
                    bufferDisplay2.flagPrint =  0;
                    PresetFlag2 = 0;
                    iButtonFlag2 = 0;
                    AuthType2 = 0;                    
                }
			}
           //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                
                //vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
                Display2_ClearRxBuffer();
            }                                             
        break;
        case 24:
            counter2 ++;
            for(x=0;x<=29;x++){
                temporal[x]=0x00;
            }
            for(x=0;x<=24;x++){
                bufferDisplay2.idSerial[x]=0x00;
            }
            if(serial_codetag(2)==1){
                for(x=0;x<=temporal[0];x++){
                    bufferDisplay2.idSerial[x]=temporal[x];
                }
                bufferDisplay2.idSerial[0]=16;
				y=16;
				for(x=1;x<=8;x++){
					if((temporal[x]&0x0F)>=10){
						bufferDisplay2.idSerial[y]=(temporal[x]&0x0F)+55;
					}else{
						bufferDisplay2.idSerial[y]=(temporal[x]&0x0F)+48;				
					}
                    y--;
					if(((temporal[x]>>4)&0x0F)>=10){
						bufferDisplay2.idSerial[y]=((temporal[x]>>4)&0x0F)+55;
					}else{
						bufferDisplay2.idSerial[y]=((temporal[x]>>4)&0x0F)+48;				
					}
                    y--;
				}                
                // Authorization request
                SetPicture(2,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag2 = 1;
                SetPicture(2, DISPLAY_FORMA_PROGRAMACION);
                flowDisplay2 = 3;
                counter2 = 0;
            }
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display2_ClearRxBuffer();
            } 
        break;
         
        case 25:
            counter2 ++;
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0xB6:  //Autorizacion con tarjeta   
                            flowDisplay2 = 26;
                            numberKeys2 = 0;                            
                            bufferDisplay2.flagPrint =  1;
                            counter2 = 0;
                            SetPicture(2, DISPLAY_ESPERANDO_ID_TERPEL);                            
                        break; 
                        case 0xB7:  //Saldo                           
                        	flowDisplay2 = 27;
                        	numberKeys2 = 0;   
                            side.b.ActivoFideliza = 3;   
                            side.b.RFstateReport = 3;
                            bufferDisplay2.FidelConf = 0;
                            counter2 = 0;
                        	SetPicture(2, DISPLAY_ESPERANDO_ID_TERPEL);                                                                                  
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                            SetPicture(2, DISPLAY_INICIO0);                            
                        break;
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay2.flagPrint =  0;
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            AuthType2    = 0;
                            counter2     = 0;
                        break;
                    }                    
                }             
                Display2_ClearRxBuffer();
            }                        
        break;
            
        case 26:
            counter ++;
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay2.idSerial[x] = 0x00;
            }
            if(code_pirata(magneticReader[2],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){                    
				    bufferDisplay2.idSerial[x-1] = temporal[x];                    
                }
                bufferDisplay2.idSerial[0] = x-2;
                // Authorization request
                SetPicture(2,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag2 = 1;
                flowDisplay2 = 14;
                bufferDisplay2.flagKeyboard = 4;
                numberKeys2 = 0;
                hiddenKeys = 5;
                controlChar ='*';
                counter2 = 0;
                SetPicture(2,DISPLAY_INGRESE_PASSWORD);  
                Display2_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2  = 0;
                            PresetFlag2   = 0;
                            iButtonFlag2  = 0;
                            AuthType2     = 0;
                            counter2      = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2  = 0;
                            PresetFlag2   = 0;
                            iButtonFlag2  = 0;
                            AuthType2     = 0;
                            counter2      = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display2_ClearRxBuffer();
            } 
        break;
        
        case 27:
            counter ++;
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay2.idSerial[x] = 0x00;
            }
            if(code_pirata(magneticReader[2],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){                    
				    bufferDisplay2.idSerial[x-1] = temporal[x];                    
                }
                bufferDisplay2.idSerial[0] = x-2;
                // Authorization request
                SetPicture(2,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag2 = 2;
                flowDisplay2 = 14;
                bufferDisplay2.flagKeyboard = 7;
                numberKeys2 = 0;
                hiddenKeys = 5;
                controlChar ='*';
                counter2 = 0;
                SetPicture(2,DISPLAY_INGRESE_PASSWORD);  
                Display2_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay2.flagPrint =  0;
                            flowPosB      = 0;
                            flowDisplay2  = 0;
                            PresetFlag2   = 0;
                            iButtonFlag2  = 0;
                            AuthType2     = 0;
                            counter2      = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2  = 0;
                            PresetFlag2   = 0;
                            iButtonFlag2  = 0;
                            AuthType2     = 0;
                            counter2      = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display2_ClearRxBuffer();
            }
        break;
        case 28:            
            side.b.rfState = RF_ASK_BALANCE;
            counter2 ++;
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowPosB      = 0;
                            flowDisplay2  = 0;                            
                            PresetFlag2   = 0;
                            iButtonFlag2  = 0;
                            counter2      = 0;
                        break;                       
                        
                        case 0x94:  //Cancel Button                                                        
                            //SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            flowPosB = 0;
                            bufferDisplay2.flagPrint =  0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            ShiftState   = 0;
                            AuthType2    = 0;     
                            counter2     = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display2_ClearRxBuffer();             
        break;
        
        case 29:
            if(cardmessagedisplay == 1){
                for(x = 1; x < 31; x++)
                {
                    WriteMessage(2, Encabezado1[x],4,x-1,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 4; x < 31; x++)
                {
                    WriteMessage(2, Encabezado2[x],6,x-4,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++) //nombre
                {
                    WriteMessage(2, nombre[x],8,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 20; x++)
                {
                    WriteMessage(2, Company[x],8,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++) //placa
                {
                    WriteMessage(2, placa[x],10,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2, LicensePlate[x],10,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)//tarjeta
                {
                    WriteMessage(2,tarjeta[x],12,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 5; x++)
                {
                    WriteMessage(2,'*',12,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 3; x++)
                {
                    WriteMessage(2,cardNumberA[x],12,x+13,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)//saldo
                {
                    WriteMessage(2,saldo_d[x],14,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 18; x++)
                {
                    WriteMessage(2,BalanceA[x],14,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)//saldo aprobado
                {
                    WriteMessage(2,saldo_a[x],16,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 18; x++)
                {
                    WriteMessage(2,BalanceB[x],16,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
            }
            if(cardmessagedisplay == 2)
            {
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage[x],6,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage1[x],8,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage2[x],10,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage3[x],12,x,1,0x0000,'Y');
                }
            }
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:
                            printBalance(EEPROM_1_ReadByte(9),side.d.dir);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            bufferDisplay2.flagPrint =  0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            ShiftState   = 0; 
                            SetPicture(2, DISPLAY_INICIO0);
                        break;
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            ShiftState   = 0;
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display2_ClearRxBuffer();             
        break;
    ///////////////FIN CASOS PARA CRÉDITO  /////////////////////  
    
    //////////// CASOS PARA CONFIGURACIONES  ///////////////////
        case 12:
            counter2++;
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x46:  //Turnos                                                 
                            flowDisplay2 = 13; 
                            if(EEPROM_1_ReadByte(221) == 1)
                            {
                                SetPicture(2,DISPLAY_CERRAR_TURNO);
                            }else
                            {
                                SetPicture(2,DISPLAY_ABRIR_TURNO);
                            }                           
                            counter2 = 0;
                        break;
                        case 0x55:  //Configurar módulo 
                            flowDisplay2 = 14;
                            bufferDisplay2.flagKeyboard = 6;
                            numberKeys2 = 0;
                            hiddenKeys = 5;
                            controlChar ='*';
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INGRESE_PASSWORD); 
                            Display2_ClearRxBuffer();
                        break;
                            
                        case 0xB5:  //Copia de recibo                             
                            side.b.RFstateReport = 1;
                            side.b.rfStateCopy = RF_COPY_RECEIPT;
                            SetPicture(2,DISPLAY_IMPRIMIENDO_RECIBO); 
                            flowDisplay2  = 23;
                            bufferDisplay2.PrintCopy = 1;
                            counter2 = 0;
                            Display2_ClearRxBuffer();                            
                        break;
                        
                        case 0x3B:  //Pantalla Inicial    
                            flowDisplay2 = 0;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INICIO0); 
                            Display2_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            Display2_ClearRxBuffer();
                        break;
                    }
                }                  
                vTaskDelay( 10 / portTICK_PERIOD_MS ); 
                Display2_ClearRxBuffer();
            }
        break;

        case 13:  //Pantalla de apertura/Cierre de turno
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x47:  //Cambio de turno: Abrir  
                            flowDisplay2 = 9;
                            numberKeys2 = 0;    
                            bufferDisplay2.flagKeyboard = 4;
                            SetPicture(2,DISPLAY_INTRODUZCA_CEDULA); 
                            Display2_ClearRxBuffer();
                        break;
                        case 0x48:  //Cambio de turno: Cerrar 
                            flowDisplay2 = 9;
                            numberKeys2 = 0;   
                            bufferDisplay2.flagKeyboard = 4;
                            SetPicture(2,DISPLAY_INTRODUZCA_CEDULA);  
                            Display2_ClearRxBuffer();
                        break;                         
                        case 0x7E:  //Pantalla Inicial 
                             bufferDisplay2.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay2.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }
                
                vTaskDelay( 10 / portTICK_PERIOD_MS ); 
                Display2_ClearRxBuffer();
            }                        
        break; 
            
        case 14: //Teclado general      
            switch (alphanumeric_keyboard2(hiddenKeys,controlChar))
            {
                case 0: //Cancelar
                    switch(bufferDisplay2.flagKeyboard)
                    {
                        case 1://ID Estacion
                            
                            for(x = 0; x <= 4; x++)
                            {
                                idStation[x] = 0;
                            }                            
                            flowDisplay2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 2://Umbral
                                                      
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                pumpGap[x] = 0;
                            }                            
                            flowDisplay2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 3://Pass turno
                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.shiftPassword[x] = 0;
                            }
                            
                            flowDisplay2 = 0;
                            ShiftStateB = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 4://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.passCard[x] = 0;
                            }
                            flowDisplay2 = 0;
                        break;
                        case 5://Pass
                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.shiftPassword[x] = 0;
                            }
                            
                            flowDisplay2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                            
                        case 6://Pass
                            
                            for(x = 1; x <= configAccess[0]; x++)
                            {
                                configAccess[x] = 0;
                            }                            
                            flowDisplay2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 7://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.passCard[x] = 0;
                            }
                            flowDisplay2 = 0;
                        break;
                        case 8://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.passCard[x] = 0;
                            }
                            flowDisplay2 = 0;
                        break;
                        case 9://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.valueKeys[x] = 0;
                            }
                            flowDisplay2 = 0;
                        break;
                    }                    
                    Display2_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay2.flagKeyboard)
                    {   
                        case 1://ID Estacion
                            
                            for(x = 0; x <= 4; x++)
                            {
                                idStation[x] = bufferDisplay2.valueKeys[x + 1];                                
                            }
                            
                            idStation[4] = 0x00;
                            intIDStation = atoi(idStation);
                            IDCast[0] = intIDStation;
                            IDCast[1] = intIDStation >> 8;
                            EEPROM_1_WriteByte(IDCast[0],10);
                            EEPROM_1_WriteByte(IDCast[1],11);
                            flowDisplay2 = 15;
                            SetPicture(2,DISPLAY_CONFIGURACIONES);
                        break;
                        case 2://Umbral
                            
                            for(x = 1; x <= bufferDisplay2.valueKeys[0]; x++)
                            {
                                pumpGap[x] = bufferDisplay2.valueKeys[x] - 48;
                            }
                            PositionGAP = 0;
                            for(x = 1; x <= bufferDisplay2.valueKeys[0]; x++)
                            {
                                PositionGAP = pumpGap[x] + PositionGAP * 10;
                            }  
                            
                            side.a.RF = side.a.dir + PositionGAP;
                            side.b.RF = side.b.dir + PositionGAP;
                            side.c.RF = side.c.dir + PositionGAP;
                            side.d.RF = side.d.dir + PositionGAP;
                            
                            // Almacena posicion RF
                            EEPROM_1_WriteByte(side.a.RF,200);
                            EEPROM_1_WriteByte(side.b.RF,201);
                            EEPROM_1_WriteByte(side.c.RF,202);
                            EEPROM_1_WriteByte(side.d.RF,203);
                           
                           
                            flowDisplay2 = 15;
                            SetPicture(2,DISPLAY_CONFIGURACIONES);
                        break;
                        case 3://Pass turno
                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.shiftPassword[x] = bufferDisplay2.valueKeys[x];
                            }
                            
                            flowDisplay2 = 19;
                            ShiftStateB = 1;
                            side.b.RFstateReport = 1;
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                        case 4://Pass Card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.passCard[x] = bufferDisplay2.valueKeys[x];
                            }
                            vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                            iButtonFlag2 = 2;
                            SetPicture(2, DISPLAY_FORMA_PROGRAMACION);
                            flowDisplay2 = 3;
                        break;
                        case 5://Pass
                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.shiftPassword[x] = bufferDisplay2.valueKeys[x];
                            }
                            
                            flowDisplay2 = 15;
                            SetPicture(2,DISPLAY_CONFIGURACIONES);
                        break; 
                        case 6://Pass
                            
                            for(x = 1; x <= configAccess[0]; x++)
                            {
                                configAccess[x] = bufferDisplay2.valueKeys[x];
                            }
                            
                            if(configAccess[1] == passwordPump[1] && configAccess[2] == passwordPump[2] && configAccess[3] == passwordPump[3] && configAccess[4] == passwordPump[4])
                            {                                
                                SetPicture(2,DISPLAY_PASSWORD_VALIDO);
                               
                                vTaskDelay( 700 / portTICK_PERIOD_MS );
                                flowDisplay2 = 15;
                                SetPicture(2,DISPLAY_CONFIGURACIONES);
                            }else
                            {
                                SetPicture(2,DISPLAY_PASSWORD_INVALIDO);
                               
                                vTaskDelay( 700 / portTICK_PERIOD_MS );
                                flowDisplay2 = 0;
                                SetPicture(2,DISPLAY_INICIO0);
                            }
                        break;
                        case 7://Pass Card
                            for(x = 0; x < 20; x++)
                            {
                                bufferDisplay2.passCard[x] = 0x00;
                            }
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.passCard[x] = bufferDisplay2.valueKeys[x];
                            }
                            side.b.RFstateReport = 2;
                            vTaskDelay( 500 / portTICK_PERIOD_MS );  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);
                            flowDisplay2 = 28;
                        break;
                        case 8://Pass Card forma pago                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay2.passCard[x] = bufferDisplay2.valueKeys[x];
                            }
                            side.b.RFstateReport = 5;
                            vTaskDelay( 100 / portTICK_PERIOD_MS );  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);
                            flowDisplay2 = 35;
                        break;
                        case 9://tiempo contador                            
                            for(x = 1; x < hiddenKeys + 1; x++)
                            {
                                TimeValue[x-1] = bufferDisplay2.valueKeys[x];
                            } 
                            TimeValue[2] = 0x00;
                            EEPROM_1_WriteByte(atoi(TimeValue),225); 
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);
                            vTaskDelay( 500 / portTICK_PERIOD_MS );   
                            flowDisplay2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                    }                    
                    Display2_ClearRxBuffer();
                break;
            }            
        break;
            
        case 15: // Menu de configuraciones
            counter ++;
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x82:  //ID Estacion  
                            flowDisplay2 = 14;
                            numberKeys2 = 0; 
                            controlChar = 0;
                            hiddenKeys  = 5;
                            counter2 = 0;
                            bufferDisplay2.flagKeyboard = 1;
                            SetPicture(2,DISPLAY_INTRODUZCA_VALOR);                            
                        break;
                        case 0x65:  //Test Impresoras 
                            flowDisplay2 = 16; 
                            counter2 = 0;
                            PrintTest();
                            SetPicture(2,DISPLAY_AMBAS_IMPRESORAS_FUNCIONANDO);                           
                        break;  
                        
						case 0x83:  //KM efectivo 
                            flowDisplay2 = 30;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_KM_EFECTIVO);                            
                        break;
                        case 0x5A:  //Umbral 
                            flowDisplay2 = 14;
                            numberKeys2 = 0;
                            controlChar = 0;
                            hiddenKeys  = 3;
                            for(x = 0; x < 3; x++)
                            {
                                pumpGap[x]  = 0x00;
                            }
                            pumpGap[0]  = 2;
                            counter2 = 0;
                            bufferDisplay2.flagKeyboard = 2;
                            SetPicture(2,DISPLAY_INTRODUZCA_VALOR);                            
                        break;
                        case 0x5B:  //Lectores banda 
                            flowDisplay2 = 31;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_LECTORES_BANDA);                            
                        break;
                        case 0x58:  //Hora y Fecha
                            flowDisplay2 = 14;
                            numberKeys2 = 0; 
                            controlChar = 0;
                            hiddenKeys  = 3;
                            counter2 = 0;
                            TimeValue[0]= 0x00;
                            TimeValue[1]= 0x00;
                            TimeValue[2]= 0x00;
                            bufferDisplay2.flagKeyboard = 9;
                            SetPicture(2,DISPLAY_INTRODUZCA_VALOR);                           
                        break;
                        case 0x7E:  //Pantalla Inicial  
                            bufferDisplay2.flagPrint =  0;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial   
                            bufferDisplay2.flagPrint =  0;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;

                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS ); 
                Display2_ClearRxBuffer();
            }                        
        break; 
            
        case 16:  //Menu de impresoras 1
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x38:  //No funcionan  
                            flowDisplay2 = 17;
                            SetPicture(2,DISPLAY_IMPRESORA_NO_FUNCIONANDO);                            
                        break;
                        case 0x39:  //Si funcionan
                            flowDisplay2 = 15; 
                            EEPROM_1_WriteByte(1,8);
                            EEPROM_1_WriteByte(2,9);
                            SetPicture(2,DISPLAY_CONFIGURACIONES);
                        break;
                                               
                        case 0x7E:  //Pantalla Inicial  
                             bufferDisplay2.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay2.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                        break;
                    }                    
                }
                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();
            }                        
        break;
            
        case 17:  //Menu de impresoras 2
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x8C:  //1 no funciona  
                            flowDisplay2 = 15; 
                            EEPROM_1_WriteByte(2,8);
                            EEPROM_1_WriteByte(2,9);
                            SetPicture(2,DISPLAY_CONFIGURACIONES);                            
                        break;
                        case 0x8D:  //2 no funciona
                            flowDisplay2 = 15; 
                            EEPROM_1_WriteByte(1,8);
                            EEPROM_1_WriteByte(1,9);
                            SetPicture(2,DISPLAY_CONFIGURACIONES); 
                        break;
                            
                        case 0x8E:  //ninguna funciona
                            flowDisplay2 = 15; 
                            EEPROM_1_WriteByte(0,8);
                            EEPROM_1_WriteByte(0,9);
                            SetPicture(2,DISPLAY_CONFIGURACIONES); 
                        break;
                                               
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay2.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;

                        break;
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay2.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay2 = 0;

                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();
            }                        
        break;
            
        case 18:  //Pantalla de ocnfiguracion de fecha y hora
            if(leer_hora() == 1)
            {
                WriteLCD(2,(((timeDownHandle[1] & 0x10) >> 4) + 48), 13, 8, 1, 0x0000, 'N');
                WriteLCD(2,((timeDownHandle[1] & 0x0F) + 48), 13, 9, 1, 0x0000, 'N');
                WriteLCD(2, ':', 13, 10, 1, 0x0000, 'N');
                WriteLCD(2,(((timeDownHandle[0] & 0xF0) >> 4) + 48), 13, 11, 1, 0x0000, 'N');
                WriteLCD(2,((timeDownHandle[0] & 0x0F) + 48), 13, 12, 1, 0x0000, 'N');               
            }
            if(leer_fecha() == 1)
            {                
                WriteLCD(2,(((dateDownHandle[0] & 0x30) >> 4) + 48), 21, 8, 1, 0x0000, 'N');
                WriteLCD(2,((dateDownHandle[0] & 0x0F) + 48), 21, 9, 1, 0x0000, 'N');
                WriteLCD(2, '/', 21, 10, 1, 0x0000, 'N');
                WriteLCD(2,(((dateDownHandle[1] & 0x10) >> 4) + 48), 21, 11, 1, 0x0000, 'N');
                WriteLCD(2,((dateDownHandle[1] & 0x0F) + 48), 21, 12, 1, 0x0000, 'N');
                WriteLCD(2, '/', 21, 13, 1, 0x0000, 'N');
                WriteLCD(2,(((dateDownHandle[2] & 0xF0) >> 4) + 48), 21, 14, 1, 0x0000, 'N');
                WriteLCD(2,((dateDownHandle[2] & 0x0F) + 48), 21, 15, 1, 0x0000, 'N');
            }
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                       

                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                        break;
                    }                    
                }
                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();
            }                        
        break;
            
        case 19:            
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;                            
                            flowPosB     = 0;
                            PresetFlag2  = 0;                            
                            iButtonFlag2 = 0;
                            ShiftState   = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowDisplay2 = 0;             
                            flowPosB     = 0;
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            ShiftState   = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display2_ClearRxBuffer();            
        break;
            
         // Credit NOT authorized
        case 21:            
            SetPicture(2, DISPLAY_AUTORIZACION_RECHAZADA);
            bufferDisplay2.flagPrint = 0;
            flowPosB     = 0;
            PresetFlag2  = 0;
            iButtonFlag2 = 0;
            counter2     = 0;
            for(x = 0; x < 9; x++)
            {
                FontSpace(2, mensaje[x],1+x,17);
                FontSpace(2, mensaje[x],1+x,21);                    
            }
            side.b.ActivoFideliza = 3;                                        
            side.b.RFstateReport = 3;
            bufferDisplay2.FidelConf = 0;
            side.b.rfState = RF_IDLE;
            vTaskDelay( 2000 / portTICK_PERIOD_MS );
            flowDisplay2 = 0;
            SetPicture(2, DISPLAY_INICIO0);
        break;
            // Wrong Grade handle
        case 22:            
            SetPicture(2, DISPLAY_AUTORIZACION_RECHAZADA);
            bufferDisplay2.flagPrint = 0;
            
            for(x = 0; x < 8; x++)
            {                
                FontSpace(2, mensaje3[x],1+x,17);                                   
            }
            for(x = 0; x < 10; x++)
            {                
                FontSpace(2, mensaje4[x],1+x,21);                    
            }
            side.b.ActivoFideliza = 3;                                        
            side.b.RFstateReport = 3;
            bufferDisplay2.FidelConf = 0;
            vTaskDelay( 2000 / portTICK_PERIOD_MS );
            flowDisplay2 = 0;
            AuthType2    = 0;
            counter2     = 0;
            SetPicture(2, DISPLAY_INICIO0);
        break;
        case 23: //Pantalla imprimiendo durate copia de recibo

            if(bufferDisplay2.PrintCopy == 0)
            {
                CounterB = 0;
                //vTaskDelay( 2000 / portTICK_PERIOD_MS );
                //flowDisplay2 = 0;
                Display2_ClearRxBuffer();
            }
            else
            {
                if(CounterB < 100)  // 20 segundos de espera aprox.
                {
                    vTaskDelay( 100 / portTICK_PERIOD_MS );
                    CounterB++; 
                }
                else
                {
                    CounterB = 0;
                    flowDisplay2 = 0;               
                    Display2_ClearRxBuffer();
                } 

            }      
        break;
        //////////////////CASOS ADICIONALES CONFIGURACIÓN ///////
        case 30://KM efectivo
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {  
                        case 0x0A:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            ShiftStateB = 0;
                            KmCash[0] = 0x01;
                            KmCash[1] = 0x01;
                            WriteEeprom(500,KmCash);
                        break;
                        
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            ShiftStateB = 0;
                            KmCash[0] = 0x01;
                            KmCash[1] = 0x00;
                            WriteEeprom(500,KmCash);
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            ShiftStateB = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            ShiftStateB = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display2_ClearRxBuffer();            
        break;
            
        case 31://Banda
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {  
                        case 0x0A:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            ShiftStateB = 0;
                            magneticReader[0] = 0x02;
                            magneticReader[1] = 'A';
                            magneticReader[2] = 'A';
                            WriteEeprom(503,magneticReader);
                        break;
                        
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            ShiftStateB = 0;
                            magneticReader[0] = 0x02;
                            magneticReader[1] = 'A';
                            magneticReader[2] = 'B';
                            WriteEeprom(503,magneticReader);
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            ShiftStateB = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            ShiftStateB = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display2_ClearRxBuffer();            
        break;
               
        ///////////////// CASOS FIDELIZACIÓN TERPEL /////////////        
        case 32: //Teclado general  
            counter2++;
            switch (alphanumeric_keyboard2(keysTerpelB,0))
            {
                case 0: //Cancelar
                    switch(bufferDisplay2.flagKeyboard)
                    {                        
                        case 1://Cedula                            
                            for(x = 0; x < keysTerpelB; x++)
                            {
                                bufferDisplay2.idTerpelFideliza[x] = 0;
                            }                            
                            flowDisplay2 = 0;
                            ShiftState = 0;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;   
                        case 2://Tarjeta para forma pago                            
                            for(x = 0; x < keysTerpelB; x++)
                            {
                                bufferDisplay2.idFormaPago[x] = 0;
                            }                            
                            flowDisplay2 = 0;
                            ShiftStateB  = 0;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;                            
                        case 3://Tarjeta para forma pago                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay2.saleNumber[x] = 0;
                            }                            
                            flowDisplay2 = 0;
                            ShiftStateB = 0;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 4://Tarjeta para forma pago                            
                            for(x = 0; x < 8; x++)
                            {
                                bufferDisplay2.MoneyPay[x] = 0;
                            }                            
                            flowDisplay2 = 0;
                            ShiftStateB = 0;
                            counter2 = 0;
							side.b.RFstateReport = 7;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 5://Tarjeta para forma pago                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay2.idFormaPago[x] = 0;
                            }                            
                            flowDisplay2 = 0;
                            ShiftStateB = 0;
                            counter2 = 0;
							if(bufferDisplay2.idType == 6)
                                side.b.RFstateReport = 7;							
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                            
                        case 6://Tarjeta para forma pago                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay2.PaymentNumber[x] = 0;
                            }                            
                            flowDisplay2 = 0;
                            ShiftStateB  = 0;
                            counter2 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                    }                    
                    Display2_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay2.flagKeyboard)
                    {                           
                        case 1://Datos fidelización                            
                            for(x = 0; x < keysTerpelB; x++)
                            {
                                bufferDisplay2.idTerpelFideliza[x] = bufferDisplay2.valueKeys[x];
                            }                            
                            flowDisplay2 = 35;  
                            if(side.b.ActivoRedencion == 1){
                                side.b.RFstateReport = 4;                                
                            }else{
                                side.b.RFstateReport = 2;                        
                                side.b.ActivoFideliza = 2;
                            }
                            counter2 = 0;
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                        break;                            
                        case 2://LFM Forma de pago                            
                            for(x = 0; x < keysTerpelB; x++)
                            {
                                bufferDisplay2.idFormaPago[x] = bufferDisplay2.valueKeys[x];
                            }
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            for(x = 0; x < 21; x++)
                            {
                                bufferDisplay2.valueKeys[x] = 0x00;
                            }
                            flowDisplay2 = 14;    
                            hiddenKeys = 20;
                            controlChar ='*';
                            numberKeys2 = 0;
                            counter2 = 0;
                            bufferDisplay2.flagKeyboard = 8;
                            SetPicture(2,DISPLAY_PASS_ALFNUM);
                        break;                            
                        case 3://numero de venta FP                            
                            for(x = 0; x < keysTerpelB; x++)
                            {
                                bufferDisplay2.saleNumber[x] = bufferDisplay2.valueKeys[x];
                            }                            
                            flowDisplay2 = 39;
                            counter2 = 0;
                            SetPicture(2, DISPLAY_FORMA_DE_PAGO_TERPEL);
                        break;                            
                        case 4://valor voucher                             
                            for(x = 0; x < keysTerpelB + 1; x++)
                            {
                                bufferDisplay2.MoneyPay[x] = 0x00;
                            }
                            for(x = 1; x <= bufferDisplay2.valueKeys[0]; x++)
                            {
                                bufferDisplay2.MoneyPay[x-1] = bufferDisplay2.valueKeys[x];
                            }
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            writevalueB = atoi(bufferDisplay2.MoneyPay);
                            resB =(atoi(bufferDisplay2.saleValue)-atoi(bufferDisplay2.MoneyPayed));
                            if( abs(resB) >= writevalueB && writevalueB > 0 )
                            {
                                for(x = 0; x < keysTerpelB + 1; x++)
                                {
                                    bufferDisplay2.valueKeys[x] = 0x00;
                                }
                                flowDisplay2 = 32;
                                numberKeys2 = 0;
                                keysTerpelB = 20;
                                if(bufferDisplay2.idType == 6){
                                    bufferDisplay2.flagKeyboard = 5;
                                }else{
                                    for(x = 0; x < keysTerpelB; x++)
                                    {
                                        bufferDisplay2.idFormaPago[x] = 0x00;
                                    }
                                    bufferDisplay2.flagKeyboard = 6;
                                }
                                SetPicture(2, DISPLAY_PASAPORTE);
                            }else{                            
                                flowDisplay2 = 32;
                                numberKeys2 = 0;
                                keysTerpelB = 10;                            
                                bufferDisplay2.flagKeyboard = 4;                                
                                SetPicture(2, DISPLAY_INTRODUZCA_VALOR); 
                                WriteLCD(2,'$',3,2,1,0x0000,'N');
                            }
                            counter2 = 0;
                        break;                            
                        case 5://pin voucher                           
                            for(x = 0; x < keysTerpelB; x++)
                            {
                                bufferDisplay2.idFormaPago[x] = bufferDisplay2.valueKeys[x];
                            }                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            side.b.RFstateReport = 5;                            
                            flowDisplay2 = 35; 
                            counter2 = 0;
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                        break;                            
                        case 6://numero de pago                           
                            for(x = 0; x < keysTerpelB; x++)
                            {
                                bufferDisplay2.PaymentNumber[x] = bufferDisplay2.valueKeys[x];
                            }                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            side.b.RFstateReport = 5;                            
                            flowDisplay2 = 35;        
                            counter2 = 0;
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                    }                    
                    Display2_ClearRxBuffer();
                break;
            }       
            Display2_ClearRxBuffer();
        break;
            
        case 33: // identificacion fidelizacion
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    counter2 = 0;
                    switch(Display2_rxBuffer[3])
                    {  
                        case 0x1A:  //Cedula
                            if(side.b.ActivoRedencion == 1 ){
                                bufferDisplay2.documentID = 3 ;
                                bufferDisplay2.idType = 5;
                                flowDisplay2 = 35;
                                side.b.RFstateReport = 4; 
                                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay2 = 32;
                                numberKeys2 = 0;
                                keysTerpelB = 16;
                                bufferDisplay2.idType = 3;
                                SetPicture(2, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay2.flagKeyboard = 1; 
                        break;
                        
                        case 0x1B:  //extranjería                                                        
                            if(side.b.ActivoRedencion == 1 ){
                                bufferDisplay2.documentID = 4 ;
                                bufferDisplay2.idType = 5;
                                flowDisplay2 = 35;
                                side.b.RFstateReport = 4; 
                                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay2 = 32;
                                numberKeys2 = 0;
                                keysTerpelB = 16;
                                bufferDisplay2.idType = 4;
                                SetPicture(2, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay2.flagKeyboard = 1; 
                        break;
                        case 0x1c: //PASAPORTE
                            if(side.b.ActivoRedencion == 1 ){
                                bufferDisplay2.documentID = 5;
                                bufferDisplay2.idType = 5;
                                flowDisplay2 = 35;
                                side.b.RFstateReport = 4; 
                                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay2 = 32;
                                numberKeys2 = 0;
                                keysTerpelB = 16;
                                bufferDisplay2.idType = 5;
                                SetPicture(2, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay2.flagKeyboard = 1;                            
                        break;
                        case 0x1d: //Lifemiles
                            if(side.b.ActivoRedencion == 1 ){
                                bufferDisplay2.idType = 5;
                                bufferDisplay2.documentID = 2;
                                flowDisplay2 = 35;
                                side.b.RFstateReport = 4; 
                                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay2 = 40; 
                                bufferDisplay2.idType = 2;
                                SetPicture(2, DISPLAY_ID_LIFE_MILES);                                                             
                            }                               
                        break;
                        case 0x1e: //Tarjeta pre inscrita
                            if(side.b.ActivoRedencion == 1 ){
                                bufferDisplay2.documentID = 1;
                                bufferDisplay2.idType = 5;
                                flowDisplay2 = 35;
                                side.b.RFstateReport = 4;
                                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay2 = 32;
                                numberKeys2 = 0;
                                keysTerpelB = 16;
                                bufferDisplay2.idType = 1;
                                SetPicture(2, DISPLAY_PASAPORTE);                             
                            }     
                            bufferDisplay2.flagKeyboard = 1;                            
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            ShiftStateB = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            ShiftStateB = 0;
                        break;
                    }                    
                }                
                Display2_ClearRxBuffer(); 
            }                       
        break;
            
        case 34:
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay2.idTerpelFideliza[x] = 0x00;
            }
            if(code_pirata(magneticReader[2],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){
				    bufferDisplay2.idTerpelFideliza[x-1] = temporal[x];                    
                }
                bufferDisplay2.idTerpelFideliza[0] = x-2;
                // Authorization request
                SetPicture(2,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                flowDisplay2 = 35;  
                side.b.RFstateReport = 2;                        
                side.b.ActivoFideliza = 2;
                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);                              
                Display2_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            AuthType2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            AuthType2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                                
                Display2_ClearRxBuffer();
            }            
        break;
            
        case 35:            
            //Touch for return to init display
            //vTaskDelay( 2000 / portTICK_PERIOD_MS );               
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            side.b.ActivoFideliza = 3;
                            side.b.RFstateReport = 3;
                            bufferDisplay2.FidelConf = 0;
                            side.b.ActivoRedencion = 0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            side.b.ActivoFideliza = 3;
                            side.b.RFstateReport = 3;
                            bufferDisplay2.FidelConf = 0;
                            side.b.ActivoRedencion = 0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                        break;
                    }                    
                }
                Display2_ClearRxBuffer(); 
            }            
        break;
            
        case 36:  
            counter2 ++;
            side.b.ActivoFideliza = 0;
            side.b.RFstateReport = 0;
            if(validaclientefiel2 == 1){
                for(x = 0; x < 17; x++)
                {
                    WriteMessage(2,NameCustomer[x],4,x,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessageB[x],6,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage1B[x],8,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage2B[x],10,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage3B[x],12,x+1,2,0x0000,'Y');
                }
            }
            if(validaclientefiel2 == 2){                
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessageB[x],6,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage1B[x],8,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage2B[x],10,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage3B[x],12,x+1,1,0x0000,'Y');
                }
            } 
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Usuario correcto                          
                            if(AuthType2 == 1){
                                flowDisplay2 =10;
                                SetPicture(2, DISPLAY_ID_TERPEL);
                            }else{
                                flowDisplay2 =3;
                                SetPicture(2, DISPLAY_FORMA_PROGRAMACION); 
                            }
                            side.b.ActivoFideliza = 3;
                            side.b.RFstateReport = 3;
                            if(validaclientefiel2 == 1){
                                bufferDisplay2.FidelConf = 1;
                            }else{
                                bufferDisplay2.FidelConf = 0;
                            }
                            counter2 = 0;
                        break;
                        case 0x0B:  //Usuario incorrecto                                                       
                            side.b.ActivoFideliza = 3;
                            flowDisplay2 = 33;
                            bufferDisplay2.FidelConf = 0;
                            side.b.RFstateReport = 3;
                            counter2 = 0;
                            SetPicture(2, DISPLAY_IDEN_FIDELIZACION);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            side.b.ActivoFideliza = 3;
                            side.b.RFstateReport = 3;
                            bufferDisplay2.FidelConf = 0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            counter2     = 0;
                        break;
                    }                    
                }
                Display2_ClearRxBuffer();   
            }                              
        break;
         
        case 38:
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x53:
                            bufferDisplay2.lastSale = true;
                            flowDisplay2 = 39;                            
                            SetPicture(2, DISPLAY_FORMA_DE_PAGO_TERPEL);
                        break;
                        case 0x54:  //Solicita teclado 
                            for(x = 0; x < 20; x++)
                            {
                                bufferDisplay2.valueKeys[x] = 0x00;
                            }
                            bufferDisplay2.lastSale = false;
                            flowDisplay2 = 32;
                            numberKeys2 = 0;
                            keysTerpelB = 10;                            
                            bufferDisplay2.flagKeyboard = 3;
                            SetPicture(2, DISPLAY_INTRODUZCA_VALOR);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2   = 0;
                            iButtonFlag2  = 0;
                        break;                                                                       
                    }                    
                }
                Display2_ClearRxBuffer();
            }            
        break;
            
        case 39: 
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x1A: //VOUCHER     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay2 = 35;
                            side.b.ActivoRedencion = 1;
                            side.b.RFstateReport = 4;
                            bufferDisplay2.idType = 6;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1B: //Sodexo     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay2 = 35;
                            side.b.ActivoRedencion = 1;
                            side.b.RFstateReport = 4;
                            bufferDisplay2.idType = 4;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1C: //MASTER     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay2 = 35;
                            side.b.ActivoRedencion = 1;
                            side.b.RFstateReport = 4;
                            bufferDisplay2.idType = 2;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);	
                        break;                        
                        case 0x1D:  //LIFEMILES                             
                            flowDisplay2 = 33;
                            side.b.ActivoRedencion = 1;                              
                            SetPicture(2, DISPLAY_PAGO_LM);  
                        break;
                        case 0x1E: //Debito     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay2 = 35;
                            side.b.ActivoRedencion = 1;
                            side.b.RFstateReport = 4;
                            bufferDisplay2.idType = 3;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1F: //VISA    1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay2 = 35;
                            side.b.ActivoRedencion = 1;
                            side.b.RFstateReport = 4;
                            bufferDisplay2.idType = 1;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                        break;                                                                       
                    }                    
                }
                Display2_ClearRxBuffer();
            } 
        break;
                        
        case 40:
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0xB6:
                            if(bufferDisplay2.idType ==2){
                                flowDisplay2 = 34;
                                SetPicture(2, DISPLAY_ESPERANDO_ID_TERPEL);
                            }
                            if(bufferDisplay2.idType =='F'){
                                flowDisplay2 = 42;
                                SetPicture(2, DISPLAY_ESPERANDO_ID_TERPEL);
                            }
                        break;
                        case 0xB7:  //Solicita teclado 
                            flowDisplay2 = 32;
                            numberKeys2 = 0;
                            keysTerpelB = 20;                                                        
                            SetPicture(2, DISPLAY_PASAPORTE);
                            if(bufferDisplay2.idType !='F'){
                                for(x = 0; x < 20; x++)
                                {
                                    bufferDisplay2.valueKeys[x] = 0x00;
                                }
                                bufferDisplay2.flagKeyboard = 1;                                
                            }else{
                                for(x = 0; x < 20; x++)
                                {
                                    bufferDisplay2.valueKeys[x] = 0x00;
                                }
                                bufferDisplay2.flagKeyboard = 2;                                
                            }
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                        break;                        
                    }                    
                }                                
                Display2_ClearRxBuffer();
            }            
        break;
        
        case 41:     
            bufferDisplay2.saleNumber[0] = 9;
			for (x = 1; x < 10; x++){
                bufferDisplay2.saleNumber[x] = 0x00;
            }
            for(x = 0; x < 14; x++)
            {
                WriteMessage(2,NumSale[x],4,x+5,1,0x0000,'Y');
            }
            for(x = 0; x < 10; x++)
            {
                WriteMessage(2,cardmessageB[x],6,x+5,1,0x0000,'Y');
            }
            for(x = 1; x < 10; x++)
            {
                bufferDisplay2.saleNumber[x] = cardmessageB[x-1];                
            } 
            if(bufferDisplay2.idType ==5){
                for(x = 0; x < 9; x++)
                {
                    WriteMessage(2,VolSale[x],8,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,cardmessage1B[x],10,x+5,1,0x0000,'Y');
                }
            }else{
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,MonSale[x],8,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,bufferDisplay2.MoneyPay[x],10,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 21; x++)
                {
                    WriteMessage(2,MonSalePayed[x],12,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,bufferDisplay2.MoneyPayed[x],14,x+5,1,0x0000,'Y');
                }                 
            }            
            if(bufferDisplay2.idType ==5){
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,MonSale[x],12,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,bufferDisplay2.MoneyPay[x],14,x+5,1,0x0000,'Y');
                }  
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,MilageSale[x],16,x+5,1,0x0000,'Y');
                }            
                for(x = 0; x < 6; x++)
                {
                    WriteMessage(2,cardmessage3B[x],18,x+5,1,0x0000,'Y');
                }
            }                            
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Monto correcto
                            if(bufferDisplay2.idType ==5){
                                flowDisplay2 = 40; 
                                bufferDisplay2.idType = 'F'; //forma pago
                                if(bufferDisplay2.documentID == 2){
                                    SetPicture(2, DISPLAY_ID_LIFE_MILES);  
                                }else{
                                    bufferDisplay2.flagKeyboard = 2;
                                    flowDisplay2 = 32;
                                    numberKeys2 = 0;
                                    keysTerpelB = 16;
                                    SetPicture(2, DISPLAY_PASAPORTE);
                                } 
                            }else{                            
                                flowDisplay2 = 32;
                                numberKeys2 = 0;
                                keysTerpelB = 10;                            
                                bufferDisplay2.flagKeyboard = 4;                                
                                SetPicture(2, DISPLAY_INTRODUZCA_VALOR); 
                                WriteLCD(2,'$',3,2,1,0x0000,'N');
                            }
                        break;
                        
                        case 0x0B:  //Monto incorrecto incorrecto                            
                            bufferDisplay2.flagPrint =  0;
                            bufferDisplay2.idType = 0x00;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
							if(bufferDisplay2.idType == 6)
                                side.b.RFstateReport = 7;
                            SetPicture(2, DISPLAY_INICIO0);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            bufferDisplay2.FidelConf = 0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                        break;
                    }                    
                }
                Display2_ClearRxBuffer();   
            }                              
        break;
         
        case 42:
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay2.idFormaPago[x] = 0x00;
            }
            if(code_pirata(magneticReader[2],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){
				    bufferDisplay2.idFormaPago[x-1] = temporal[x];                    
                }
                bufferDisplay2.idFormaPago[0] = x-2;
                // Authorization request
                SetPicture(2,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                flowDisplay2 = 14;    
                hiddenKeys = 20;
                controlChar ='*';
                numberKeys2=0;
                bufferDisplay2.flagKeyboard = 8;
                SetPicture(2,DISPLAY_PASS_ALFNUM); 
                Display2_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            AuthType2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay2 = 0;
                            bufferDisplay2.flagPrint =  0;
                            PresetFlag2 = 0;
                            iButtonFlag2 = 0;
                            AuthType2 = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }
                Display2_ClearRxBuffer();
            }            
        break;
                    
        case 43:                                                
            for(x = 0; x < 25; x++)
            {
                WriteMessage(2,cardmessageB[x],6,x+1,1,0x0000,'Y');
            }            
            for(x = 0; x < 25; x++)
            {
                WriteMessage(2,cardmessage1B[x],10,x+1,1,0x0000,'Y');
            }    
            for(x = 0; x < 25; x++)
            {
                WriteMessage(2,cardmessage2B[x],14,x+1,1,0x0000,'Y');
            }
            for(x = 0; x < 25; x++)
            {
                WriteMessage(2,cardmessage3B[x],18,x+1,1,0x0000,'Y');
            }
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Imprimir comprobante
                            printPayment(EEPROM_1_ReadByte(9),side.b.RF);
                            vTaskDelay( 500 / portTICK_PERIOD_MS ); 
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            SetPicture(2, DISPLAY_INICIO0); 
                            for(x = 0; x < 7; x++)
                            {
                                bufferDisplay2.saleValue[x] = 0x00;
                            }
                        break;
                        
                        case 0x0B:  //No imprimir comprobante                                                       
                            bufferDisplay2.idType = 0x00;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            SetPicture(2, DISPLAY_INICIO0);
                            for(x = 0; x < 7; x++)
                            {
                                bufferDisplay2.saleValue[x] = 0x00;
                            }
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            bufferDisplay2.FidelConf = 0;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            for(x = 0; x < keysTerpelB; x++)
                            {
                                bufferDisplay2.saleValue[x] = 0x00;
                            }
                        break;
                    }                    
                }
                Display2_ClearRxBuffer();         
            }                        
        break;
            
        case 44:
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Mas voucher
                            bufferDisplay2.lastSale = false;
                            flowDisplay2 = 35;
                            side.b.RFstateReport    = 4;
                            side.b.ActivoRedencion  = 1;  
                            bufferDisplay2.idType = 6;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);
                        break;
                        
                        case 0x0B:  //Finalizar                                                       
                            side.b.RFstateReport = 6;                             
                            flowDisplay2 = 35;                                                                                    
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay2.flagPrint =  0;
                            side.b.ActivoRedencion = 0;
							side.b.RFstateReport = 7;
                            flowPosB     = 0;
                            flowDisplay2 = 0;                            
                            PresetFlag2  = 0;
                            iButtonFlag2 = 0;
                            for(x = 0; x < keysTerpelB; x++)
                            {
                                bufferDisplay2.saleValue[x] = 0x00;
                            }
                        break;
                    }                    
                }
                Display2_ClearRxBuffer();
            } 
        break;
    }    
}

/*
*********************************************************************************************************
*                                         void PollingDisplay3(void)
*
* Description : Pregunta estado al surtidor 
*               
*
*********************************************************************************************************
*/
void PollingDisplay3(void){    
    uint8 x, y;    
    tempcont =EEPROM_1_ReadByte(225);
    if(counter3 >= tempcont*100 && tempcont > 0){ //70 segs aprox
        bufferDisplay3.flagPrint =  0;
        flowDisplay3 = 's'; 
        flowPosC     = 0;                           
        PresetFlag3  = 0;
        iButtonFlag3 = 0;
        counter3     = 0;
        SetPicture(1, DISPLAY_TIEMPO_EXPIRADO);
    }
    switch(flowDisplay3){
        case 's':
        if(Display1_GetRxBufferSize() == 8)
        {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Return to initial screen                                                                                    
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            AuthType3 = 0;
                            counter3  = 0;
                            Display1_ClearRxBuffer();
                        break;
                        case 0x94:  //Return to initial screen                                                                                    
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            AuthType3 = 0;
                            counter3  = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }               
                Display1_ClearRxBuffer();
            }
        break;
        case 0:                                                
            SetPicture(1, DISPLAY_SELECCIONE_POSICION);
            flowDisplay3 = 1; 
            vTaskDelay( 10 / portTICK_PERIOD_MS );
            bufferDisplay3.flagActiveSale = false;
            Display1_ClearRxBuffer();            
        break;
            
        case 1: //Menu 
             // Impresion de tiquete            
            if(bufferDisplay3.flagActiveSale){
                flowDisplay3 = flowPosC;            
            }
            if(bufferDisplay1.flagActiveSale){
                flowDisplay1 = flowPos;
                selectPos = 1;
            }
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {                                             
                    switch(Display1_rxBuffer[3]){
				        case 0x56:						        //POS A                                                                                                                       
                                if(bufferDisplay1.flagActiveSale || bufferDisplay1.PrintEnd == 1){
                                    flowDisplay1 = flowPos;      //Si está vendiendo en esta posición regresa a su flujo
                                }else{
                                    if(EEPROM_1_ReadByte(215)!= 11){
                                        SetPicture(1, DISPLAY_FORMA_PAGO_DESEADA);                                                
                                    }else{
                                        SetPicture(1,DISPLAY_FORMA_PAGO_DESEADA_TERPEL);
                                    }
                                    selectPos     = 1;
                                    flowDisplay1  = 2;
									Display1_ClearRxBuffer();
                                }
                                if (bufferDisplay3.flagActiveSale){
                                    flowDisplay3 = flowPosC;    //Si la venta está activa en POS B regresa a su flujo
                                }
                                else{
                                    flowDisplay3 = 0; 
                                    flowPosC     = 0;
                                }
					    break;
                            		       
					    case 0x57:  				            //POS B                                                                 
                                if(bufferDisplay1.flagActiveSale){
                                    flowDisplay1 = flowPos;      //Si está vendiendo en esta posición regresa a su flujo
                                }
                                else{
                                    flowDisplay1 = 0;
                                    flowPos      = 0;
                                } 
                                if (bufferDisplay3.flagActiveSale || bufferDisplay3.PrintEnd == 1){                                    
                                    flowDisplay3 = flowPosC;    //Si la venta está activa en POS B regresa a su flujo
                                }else{
                                    if(EEPROM_1_ReadByte(215)!= 11){
                                        SetPicture(1, DISPLAY_FORMA_PAGO_DESEADA);                                                
                                    }else{
                                        SetPicture(1,DISPLAY_FORMA_PAGO_DESEADA_TERPEL);
                                    }
							        selectPos     = 2;
                                    flowDisplay3  = 2;                            
                                }                           
					    break;                                                   
				    } 
                }
                Display1_ClearRxBuffer();
            }         
        break;
        case 2:  //Pantalla forma de pago
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C)){
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x0D:  //Pantalla efectivo   
                            if(EEPROM_1_ReadByte(222) == 1)
                            {
                                bufferDisplay3.saleType = 1;
                                AuthType3 = 2;
                                if(EEPROM_1_ReadByte(215)!= 11){
                                    flowDisplay3 = 3;                              
                                    SetPicture(1, DISPLAY_FORMA_PROGRAMACION);                                      
                                }else{
                                    flowDisplay3 = 37;   
                                    SetPicture(1, DISPLAY_FIDELIZACION);  
                                }
                            }else
                            {
                                SetPicture(1, DISPLAY_CANCELADO_X_PC);
                                vTaskDelay( 900 / portTICK_PERIOD_MS );
                                flowDisplay3 = 0;
                                Display1_ClearRxBuffer();
                            }
                        break;
                        case 0x0E:  //Pantalla credito 
                            for(x = 0; x < 10; x++)
                            {                                
                                bufferDisplay3.CreditpresetValue[0][x] = 0x00;
                                bufferDisplay3.CreditpresetValue[1][x] = 0x00;
                                
                            }
                            if(EEPROM_1_ReadByte(222) == 1)
                            {                                
                                bufferDisplay3.saleType = 2; 
                                AuthType3 = 1;
                                if(EEPROM_1_ReadByte(215)!= 11){
                                    flowDisplay3 = 10;
                                    SetPicture(1, DISPLAY_ID_DIGITAL);
                                }else{
                                    flowDisplay3 = 37;
                                    SetPicture(1, DISPLAY_FIDELIZACION);
                                }
                                Display1_ClearRxBuffer();
                            }else
                            {
                                SetPicture(1, DISPLAY_CANCELADO_X_PC);
                                vTaskDelay( 900 / portTICK_PERIOD_MS );
                                flowDisplay3 = 0; 
                                counter3 = 0;
                                Display1_ClearRxBuffer();
                            }
                        break;
                            
                        case 0x0F: //Forma de pago
                            if(EEPROM_1_ReadByte(222) == 1)
                            {
                                flowDisplay3 = 38;                            
                                SetPicture(1, DISPLAY_SELECCION_VENTA);
                            }
                        break;
                            
                        case 0x45:  //Pantalla otras opciones 
                            flowDisplay3 = 12;                            
                            SetPicture(1,  DISPLAY_OPERACIONES);
                            AuthType3 = 0;
                            Display1_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            SetPicture(1, DISPLAY_INICIO0);                               
                            vTaskDelay( 10 / portTICK_PERIOD_MS );
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            SetPicture(1, DISPLAY_INICIO0);                            
                            vTaskDelay( 10 / portTICK_PERIOD_MS );
                            Display1_ClearRxBuffer();
                        break;
                    }
                }                  
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
                Display1_ClearRxBuffer();
            }
        break;
            
        case 37: // Desea fidelizar            
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    side.c.ActivoFideliza = 0;
                    side.c.ActivoRedencion = 0;
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A: //Si                                                                                   
                            flowDisplay3 = 33;
                            SetPicture(1, DISPLAY_IDEN_FIDELIZACION);                              
                        break;
                        case 0x0B:  //No 
                            if(AuthType3 == 1){
                                flowDisplay3 =10;                                
                                SetPicture(1, DISPLAY_ID_TERPEL);
                            }else{
                                flowDisplay3 =3;
                                SetPicture(1, DISPLAY_FORMA_PROGRAMACION); 
                            }                                                                                   
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            counter3     = 0;
                        break;
                    }                    
                }                                
                Display1_ClearRxBuffer();
            }             
        break;
            
        case 3: //Pantalla ingreso de valores
            for(x = 0; x <10; x++)
            {
                bufferDisplay3.presetValue[0][x] = 0x00;
                bufferDisplay3.presetValue[1][x] = 0x00;
            }
            Credit_Auth_OK3 = 0;            
            counter3 ++;
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    counter3 = 0;
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x0F:  //Preset dinero                
                            flowDisplay3 = 4;                              
                            bufferDisplay3.presetType[0] = 2;
                            bufferDisplay3.presetType[1] = '$';
                            numberKeys3 = 0;
                            SetPicture(1, DISPLAY_INTRODUZCA_VALOR);   
                            WriteLCD(1, '$', 3, 2, 1, 0x0000, 'N');                            
                            if(EEPROM_1_ReadByte(2) > 0)
                            {
                                flagPoint3 = 0;
                            }else
                            {
                                flagPoint3 = 1;
                            }
                            Display1_ClearRxBuffer();
                        break; 
                        case 0x10:  //Preset volumen                 
                            flowDisplay3 = 4;                            
                            bufferDisplay3.presetType[0] = 1;
                            bufferDisplay3.presetType[1] = 'G';
                            numberKeys3 = 0;                            
                            SetPicture(1, DISPLAY_INTRODUZCA_VOLUMEN);                            
                            WriteLCD(1, 'G', 3, 2, 1, 0x0000, 'N');                            
                            if(EEPROM_1_ReadByte(3) > 0) //VolDec
                            {
                                flagPoint3 = 0;
                            }else
                            {
                                flagPoint3 = 1;
                            }
                            Display1_ClearRxBuffer();
                        break;
                        case 0x43:     //Preset full 
                            bufferDisplay3.presetType[0] = 3;
                            bufferDisplay3.presetType[1] = 'F';                            
                            for(x = 1; x <(digits - 1); x++)
                            {
                                bufferDisplay3.presetValue[0][x] = '9';
                            }                            
                            bufferDisplay3.presetValue[0][x] = '0';
                            bufferDisplay3.presetValue[0][x + 1] = '0';
                            bufferDisplay3.presetValue[0][0] = digits;
                            
                            for(x = 0; x <= bufferDisplay3.presetValue[0][0]; x++)
                            {
                                bufferDisplay3.presetValue[1][x] = bufferDisplay3.presetValue[0][x];
                            }                            
                            flowDisplay3 = 5;
                            SetPicture(1,DISPLAY_SELECCIONE_PRODUCTO4);
                            Display1_ClearRxBuffer();
                        break;
                        case 0x94:  //Retroceso
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            Display1_ClearRxBuffer();
                        break;
                        case 0x3B:  //Pantalla Inicial  
                            AuthType3 = 0;                        
                            flowDisplay3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);                            
                            Display1_ClearRxBuffer();
                        break;
                        case 0x7E:  //Pantalla Inicial  
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            counter3     = 0;
                            AuthType3    = 0;
                            SetPicture(1,DISPLAY_INICIO0);                             
                            Display1_ClearRxBuffer();
                        break;
                    }
                }  
                //CyDelay(10);
                //vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
                Display1_ClearRxBuffer();
            }
        break;
        
        case 4:             
            counter3 ++;
            switch (alphanumeric_keyboard3(digits + 1, 0))
            {
                case 0:  //Pantalla Inicial    
                    flowDisplay3 = 0;
                    SetPicture(1,DISPLAY_INICIO0); 
                    Display1_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    counter3 = 0;
                    for(x = 0; x <= bufferDisplay3.valueKeys[0]; x++)
                    {
                        bufferDisplay3.presetValue[0][x] = bufferDisplay3.valueKeys[x];
                        bufferDisplay3.presetValue[1][x] = bufferDisplay3.valueKeys[x];
                    }  
                    IntValueC = 0;
                    for(x = 0; x < 10; x++)
                    {                            
                        bufferDisplay3.PresetTemp[x] = 0x00;                          
                    }                    
                    // Convierte valor del preset en entero vector
                    for(x = 1; x < 10; x++)
                    {
                        if(bufferDisplay3.presetValue[0][x] != '.' && bufferDisplay3.presetValue[0][x] != ',' && bufferDisplay3.presetValue[0][x] != 0x00)
                        {
                           bufferDisplay3.PresetTemp[x - 1] = bufferDisplay3.presetValue[0][x] - 48;
                        }
                    }                      
                    // Convierte valor del preset en numero entero
                    for(x = 0; x < bufferDisplay3.presetValue[0][0]; x++)
                    {                                
                        IntValueC = 10 * IntValueC + bufferDisplay3.PresetTemp[x];                            
                    }                    
                    // Rechaza transaccion si el Preset es menor a  COP$1000
                    if(bufferDisplay3.presetType[0] == 2)
                    {
                    	if(IntValueC < 1000)
                    	{
                        	AuthType3 = 0;
                        	bufferDisplay3.flagPrint =  0;
                        	flowDisplay3 = 0;
                        	SetPicture(1,DISPLAY_INICIO0); 
                    	}
                    	else
                    	{
                        	flowDisplay3 = 5;   //caso para seleccion de producto
                        	SetPicture(1, DISPLAY_SELECCIONE_PRODUCTO4);
                    	}
                    }
                    else
                    {                        
                        if((bufferDisplay3.presetValue[0][0] > 0 && IntValueC != 0) && (bufferDisplay3.presetValue[0][0] < 7 && IntValueC >= 1))
                        {
                            flowDisplay3 = 5;   //caso para seleccion de producto
                        	SetPicture(1, DISPLAY_SELECCIONE_PRODUCTO4);  
                        }
                        else
                        {
                            AuthType3 = 0;
                        	bufferDisplay3.flagPrint =  0;
                        	flowDisplay3 = 0;
                        	SetPicture(1,DISPLAY_INICIO0);
                        }                   	
                    }		
                    Display1_ClearRxBuffer();
                break;
            }
        break;
            
        case 5: //Seleccion de producto               
            counter3 = counter3 + 3;
            if(side.c.GradesHose[1] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(1, producto[side.c.GradesHose[1]-1][x],9+x,11); //FontSpace(LCD, caracter,posx,posy)
                //WriteMessage(1, producto[side.a.GradesHose[1]-1][x],11,6+x,2,0x0000,'Y'); //WriteMessage(1, producto1[x],11,7+x,2,0x0000,'Y');
                }
            }
            if(side.c.GradesHose[2] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(1, producto[side.c.GradesHose[2]-1][x],10+x,17); //FontSpace(LCD, caracter,posx,posy)
                //WriteMessage(1, producto[side.a.GradesHose[2]-1][x],17,7+x,2,0x0000,'Y');//WriteMessage(1, producto2[x],17,8+x,2,0x0000,'Y');
                }
            }
            if(side.c.GradesHose[3] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(1, producto[side.c.GradesHose[3]-1][x],11+x,23);
                //WriteMessage(1, producto[side.a.GradesHose[3]-1][x],23,8+x,2,0x0000,'Y');
                }
            }
            if(side.c.GradesHose[4] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(1, producto[side.c.GradesHose[4]-1][x],12+x,29);
                //WriteMessage(1, producto[side.a.GradesHose[4]-1][x],29,9+x,2,0x0000,'Y');
                }
            }            
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x80:  //Grado 1 
                            if(side.c.hoseNumber > 0)
                            {
                                numberKeys3 = 0; 
                                flowDisplay3 = 9;
                                side.c.hose = 1;                         
                                //Credit
                                if(AuthType3 == 2)
                                {				
									if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay3.flagKeyboard = 2; 
                                        SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay3.flagKeyboard = 1; 
                                        SetPicture(1, DISPLAY_DIGITE_PLACA);
                                    }
                                }                                
                                //Cash
                                if(AuthType3 == 1)
                                {                    
                                    bufferDisplay3.flagKeyboard = 2;
                                    SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter3 = 0;
                            Display1_ClearRxBuffer();
                        break;                            
                        case 0x81:  //Grado 2 
                            if(side.c.hoseNumber > 1)
                            {
                                numberKeys3 = 0; 
                                flowDisplay3 = 9;
                                side.c.hose = 2;
                                //Credit
                                if(AuthType3 == 2)
                                {
                                   if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay3.flagKeyboard = 2; 
                                        SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay3.flagKeyboard = 1; 
                                        SetPicture(1, DISPLAY_DIGITE_PLACA);
                                    }
                                }                            
                                //Cash
                                if(AuthType3 == 1)
                                {                    
                                    bufferDisplay3.flagKeyboard = 2;
                                    SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter3 = 0;
                            Display1_ClearRxBuffer(); 
                        break;
                            
                        case 0x7F:  //Grado 3
                            if(side.c.hoseNumber > 2)
                            {
                                numberKeys3=0; 
                                flowDisplay3 = 9;
                                side.c.hose = 3;
                               //Credit
                                if(AuthType3 == 2)
                                {
									if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay3.flagKeyboard = 2; 
                                        SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay3.flagKeyboard = 1; 
                                        SetPicture(1, DISPLAY_DIGITE_PLACA);
                                    }
                                }                            
                                //Cash
                                if(AuthType3 == 1)
                                {                    
                                    bufferDisplay3.flagKeyboard = 2;
                                    SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter3 = 0;
                            Display1_ClearRxBuffer();
                        break;   
                        
                        case 0xB8:  //Grado 4 
                            if(side.c.hoseNumber > 3)
                            {
                                numberKeys3=0; 
                                flowDisplay3 = 9;
                                side.c.hose = 4;
                                //Credit
                                if(AuthType3 == 2)
                                {
									if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay3.flagKeyboard = 2; 
                                        SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay3.flagKeyboard = 1; 
                                        SetPicture(1, DISPLAY_DIGITE_PLACA);
                                    }
                                }                            
                                //Cash
                                if(AuthType3 == 1)
                                {                    
                                    bufferDisplay3.flagKeyboard = 2;
                                    SetPicture(1, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                } 
                            }
                            counter3 = 0;
                            Display1_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Retroceso
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            Display1_ClearRxBuffer();
                        break;
                            
                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
                Display1_ClearRxBuffer();
            }
        break;
                    
        case 6: // Print Screen
            counter3 = 0;
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x39:  //Print 
                            flowDisplay3 = 7;
                            numberKeys3 = 0;
                            bufferDisplay3.flagPrint =  1;                                                       
							bufferDisplay3.PrintFlagEOT = 0;
                            SetPicture(1, DISPLAY_SUBA_MANIJA);  
                            Display1_ClearRxBuffer();
                        break; 
                        case 0x38:  //No Print 

                            flowDisplay3 = 7; // Wait of handle up
                            bufferDisplay3.flagPrint =  0;                                                               
							bufferDisplay3.PrintFlagEOT = 0;
                            SetPicture(1, DISPLAY_SUBA_MANIJA);
                            Display1_ClearRxBuffer();
                        break;
                        case 0x7E:  //Return to initial screen                                                                                    
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            AuthType3 = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }               
                //vTaskDelay( 10 / portTICK_PERIOD_MS );              // 10mS delay
                Display1_ClearRxBuffer();
            }
        break;
                                        
            // PRESET flag ON and wait to handle up
        case 7:                       
            PresetFlag3 = 1;
            counter3 =counter3 + 4;
            vTaskDelay( 40 / portTICK_PERIOD_MS );
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            AuthType3 = 0;     
                            bufferDisplay3.zeroSend = 1;
                            vTaskDelay( 50 / portTICK_PERIOD_MS );                      
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            AuthType3 = 0;
                            bufferDisplay4.zeroSend = 1;
                            vTaskDelay( 50 / portTICK_PERIOD_MS );
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }
                
               Display1_ClearRxBuffer();
            }
           
        break;
            
          
        case 8:                          
           //Pump Busy...
            vTaskDelay( 10 / portTICK_PERIOD_MS ); 
            if(NumPositions > 2)
            {
                flowDisplay3 = 1;
            }
            counter3 = 0;
        break;
            
        case 9: //Keyboard  
            if(upcount3[0] == 1){
                if(upcount3[1] == 1){
                    counter3 ++;
                    upcount3[1] = 0;
                }else{
                    upcount3[1] = 1;
                }
            }else{
                counter3++;
            }
            switch (alphanumeric_keyboard3(11,0))
            {
                case 0: //Cancel
                    switch(bufferDisplay3.flagKeyboard)
                    {
                        case 1://License plate
                            for(x = 0; x < 11; x++)
                            {
                                bufferDisplay3.licenceSale[x] = 0;
                            }
                            flowDisplay3 = 0; 
                            counter3 = 0;
                            SetPicture(1, DISPLAY_INICIO0);
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 2://Mileage
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay3.mileageSale[x] = 0;
                            }
                            counter3 = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 3://CC/NIT
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay3.identySale[x] = 0;
                            }
                            counter3 = 0;
                            Display1_ClearRxBuffer();
                        break;
                            
                        case 4://ID
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay3.shiftId[x] = 0;
                            }
                            counter3 = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                    Display1_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay3.flagKeyboard)
                    {
                        case 1://License plate
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay3.licenceSale[x] = 0x00;
                            }                            
                            for(x = 0; x <= bufferDisplay3.valueKeys[0]; x++)
                            {
                                bufferDisplay3.licenceSale[x] = bufferDisplay3.valueKeys[x];
                            }
                            flowDisplay3 = 6;
                            counter3 = 0;
                            SetPicture(1, DISPLAY_DESEA_IMPRIMIR_RECIBO);                                 
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 2:// mileage
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay3.mileageSale[x] = 0;
                            }                         
                            for(x = 0; x <= bufferDisplay3.valueKeys[0]; x++)
                            {
                                bufferDisplay3.mileageSale[x] = bufferDisplay3.valueKeys[x];
                            }
                            
                            //Credit Sale
                            if(AuthType3 == 1)
                            {
                                flowDisplay3 = 7;                               
                                SetPicture(1, DISPLAY_SUBA_MANIJA);
                            }
                            if(AuthType3 == 2)
                            {

                                if(KmCash[1] == 0x01)
                                {   
                                    numberKeys3 = 0; 
                                    flowDisplay3 = 9;
                                    bufferDisplay3.flagKeyboard = 1; 
                                    SetPicture(1, DISPLAY_DIGITE_PLACA);
                                }                                         
                            } 
                            counter3 = 0;
                            Display1_ClearRxBuffer();                           
                        break;
                        
                        case 3:     //CC/NIT                            
                            for(x = 0; x <= bufferDisplay3.valueKeys[0]; x++)
                            {
                                bufferDisplay3.identySale[x] = bufferDisplay3.valueKeys[x];
                            }
                            counter3 = 0;
                            Display1_ClearRxBuffer();
                        break;
                        case 4:     //ID                            
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay3.shiftId[x] = bufferDisplay3.valueKeys[x];
                            }                            
                            flowDisplay3 = 14;          //password request                    
                            numberKeys3 = 0;
                            hiddenKeys = 10;
                            controlChar = '*';
                            counter3 = 0;
                            bufferDisplay3.flagKeyboard = 3;
                            SetPicture(1,DISPLAY_INGRESE_PASSWORD);
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                    //Display1_ClearRxBuffer();
                break;
            }  
            Display1_ClearRxBuffer();
        break;    
    
    ////////////////// CASOS PARA CRÉDITO  /////////////////////
        case 10:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0xB6:  //ibutton Request   
                            flowDisplay3 = 11;
                            numberKeys3 = 0;
                            counter3 = 0;
                            //bufferDisplay3.flagPrint =  1;
                            SetPicture(1, DISPLAY_ESPERANDO_ID);                            
                        break; 
                        case 0xB7:  //ID Number
                            if(EEPROM_1_ReadByte(215)!= 11){
                            	flowDisplay3 = 24;
                            	numberKeys3 = 0;                                
                            	//bufferDisplay3.flagPrint =  1;
                            	Tag_ClearRxBuffer();
                            	Tag_ClearTxBuffer();
                            	Tag_PutChar('O');
                            	Tag_PutChar('K');
                            	Tag_PutChar(0x01);
                            	vTaskDelay( 100 / portTICK_PERIOD_MS );
                            	SetPicture(1, DISPLAY_ESPERANDO_ID);                           
                            }else{
                            	flowDisplay3 = 25;
                                numberKeys3 = 0;
                                bufferDisplay3.idType = 3;
                            	vTaskDelay( 100 / portTICK_PERIOD_MS );
                            	SetPicture(1, DISPLAY_SELECCIONE_OP_TERPEL);
                            } 
                            counter3 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            SetPicture(1, DISPLAY_INICIO0);                            
                        break;
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            SetPicture(1, DISPLAY_INICIO0);                            
                        break;
                    }                    
                }             
                //vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break;
        
        case 11:
            // iButton read
            counter3 ++;
            for(x = 0; x < 30; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 25; x++)
            {
                bufferDisplay3.idSerial[x] = 0x00;
            }
            if(touch_present(1) == 1)
            {
				if(touch_write(1,0x33))
                {
					for(x = 1; x <= 8; x++)
                    {
						temporal[x] = touch_read_byte(1);  // Id
					}
					y = 0;
					for(x = 1; x < 8; x++)
                    {
                        y = crc_check(y,temporal[x]);      // Checksum
                    }					
                    if(y == temporal[8])
                    {
						bufferDisplay3.idSerial[0] = 16;
						y = 16;						
                        for(x = 1; x <= 8; x++)
                        {
							if((temporal[x] & 0x0F) >= 10)
                            {
								bufferDisplay3.idSerial[y] = (temporal[x] & 0x0F) + 55;
							}else{
								bufferDisplay3.idSerial[y] = (temporal[x] & 0x0F) + 48;				
							}
                            y--;
							if(((temporal[x] >> 4) & 0x0F) >= 10)
                            {
								bufferDisplay3.idSerial[y] = ((temporal[x] >> 4) & 0x0F) + 55;
							}else{
								bufferDisplay3.idSerial[y] = ((temporal[x] >> 4) & 0x0F) + 48;				
							}
                            y--;
						}                        
                        // Authorization request
                        SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                        vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                        iButtonFlag3 = 1;
                        SetPicture(1, DISPLAY_FORMA_PROGRAMACION);
                        flowDisplay3 = 3;      
                        counter3 = 0;
					}
				}else
                    {   // iButton Error
                        SetPicture(1,DISPLAY_ID_NO_RECONOCIDO);                                           
                        Display1_ClearRxBuffer();
                        vTaskDelay( 500 / portTICK_PERIOD_MS );    
                        SetPicture(1, DISPLAY_INICIO0);                        
                        bufferDisplay3.flagPrint =  0;
                        flowDisplay3 = 0;
                        PresetFlag3  = 0;
                        iButtonFlag3 = 0;
                        AuthType3    = 0;
                        counter3     = 0;
                    }
			}
                     
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);                            
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);                            
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display1_ClearRxBuffer();
            }
          
                                    
        break;
            
        case 24:
            counter3 ++;
            for(x=0;x<=29;x++){
                temporal[x]=0x00;
            }
            for(x=0;x<=24;x++){
                bufferDisplay3.idSerial[x]=0x00;
            }
            if(serial_codetag(1)==1){
                for(x=0;x<=temporal[0];x++){
                    bufferDisplay3.idSerial[x]=temporal[x];
                }
                bufferDisplay3.idSerial[0]=16;
				y=16;
				for(x=1;x<=8;x++){
					if((temporal[x]&0x0F)>=10){
						bufferDisplay3.idSerial[y]=(temporal[x]&0x0F)+55;
					}else{
						bufferDisplay3.idSerial[y]=(temporal[x]&0x0F)+48;				
					}
                    y--;
					if(((temporal[x]>>4)&0x0F)>=10){
						bufferDisplay3.idSerial[y]=((temporal[x]>>4)&0x0F)+55;
					}else{
						bufferDisplay3.idSerial[y]=((temporal[x]>>4)&0x0F)+48;				
					}
                    y--;
				}
                
                // Authorization request
                SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag3 = 1;
                SetPicture(1, DISPLAY_FORMA_PROGRAMACION);
                flowDisplay3 = 3;
                counter3 = 0;
            }
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            //SetPicture(1, DISPLAY_INICIO0);                            
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            flowPosC     = 0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            //SetPicture(1, DISPLAY_INICIO0);                            
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            flowPosC     = 0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;                            
                        break;
                    }                    
                }                
                Display1_ClearRxBuffer();
            } 
        break;
            
        case 25:
            counter3 ++;
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0xB6:  //Autorizacion con tarjeta   
                            flowDisplay3 = 26;
                            numberKeys3 = 0;                            
                            bufferDisplay3.flagPrint =  1;
                            counter3 = 0;
                            SetPicture(1, DISPLAY_ESPERANDO_ID_TERPEL);                            
                        break; 
                        case 0xB7:  //Saldo                           
                        	flowDisplay3 = 27;
                        	numberKeys3 = 0;  
                            side.c.ActivoFideliza = 3;   
                            side.c.RFstateReport = 3;
                            bufferDisplay3.FidelConf = 0;
                            counter3 = 0;
                        	SetPicture(1, DISPLAY_ESPERANDO_ID_TERPEL);                                                                                  
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3  = 0;
                            AuthType3     = 0;
                            counter3      = 0;
                            SetPicture(1, DISPLAY_INICIO0);                            
                        break;
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3  = 0;
                            AuthType3     = 0;
                            counter3      = 0;
                            SetPicture(1, DISPLAY_INICIO0);                            
                        break;
                    }                    
                }             
                Display1_ClearRxBuffer();
            }                        
        break;
            
        case 26:
            counter3 ++;
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay3.idSerial[x] = 0x00;
            }
            if(code_pirata(magneticReader[1],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){                    
				    bufferDisplay3.idSerial[x-1] = temporal[x];                    
                }
                bufferDisplay3.idSerial[0] = x-2;
                // Authorization request
                SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag3 = 2;
                flowDisplay3 = 14;
                bufferDisplay3.flagKeyboard = 4;
                numberKeys3 = 0;
                hiddenKeys = 5;
                controlChar ='*';
                counter3 = 0;
                SetPicture(1,DISPLAY_INGRESE_PASSWORD);  
                Display1_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);                            
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);                            
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display1_ClearRxBuffer();
            } 
        break;
        
        case 27:
            counter3 ++;
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay3.idSerial[x] = 0x00;
            }
            if(code_pirata(magneticReader[1],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){                    
				    bufferDisplay3.idSerial[x-1] = temporal[x];                    
                }
                bufferDisplay3.idSerial[0] = x-2;
                // Authorization request
                SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag3 = 2;
                flowDisplay3 = 14;
                bufferDisplay3.flagKeyboard = 7;
                numberKeys3 = 0;
                hiddenKeys = 5;
                controlChar ='*';
                counter3 = 0;
                SetPicture(1,DISPLAY_INGRESE_PASSWORD);  
                Display1_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);                            
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);                            
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3    = 0;
                            counter3     = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display1_ClearRxBuffer();
            }
        break;
        case 28:            
            side.c.rfState = RF_ASK_BALANCE;
            counter3++;
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            counter3     = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC      = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3   = 0;
                            iButtonFlag3  = 0;                            
                            ShiftState   = 0;
                            counter3     = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer();             
        break;
        
        case 29:
            if(cardmessagedisplay == 1){
                for(x = 1; x < 31; x++)
                {
                    WriteMessage(1, Encabezado1[x],4,x-1,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 4; x < 31; x++)
                {
                    WriteMessage(1, Encabezado2[x],6,x-4,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++) //nombre
                {
                    WriteMessage(1, nombre[x],8,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 20; x++)
                {
                    WriteMessage(1, Company[x],8,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++) //placa
                {
                    WriteMessage(1, placa[x],10,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1, LicensePlate[x],10,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)//tarjeta
                {
                    WriteMessage(1,tarjeta[x],12,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 5; x++)
                {
                    WriteMessage(1,'*',12,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 3; x++)
                {
                    WriteMessage(1,cardNumberA[x],12,x+13,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)//saldo
                {
                    WriteMessage(1,saldo_d[x],14,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 18; x++)
                {
                    WriteMessage(1,BalanceA[x],14,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)//saldo aprobado
                {
                    WriteMessage(1,saldo_a[x],16,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 18; x++)
                {
                    WriteMessage(1,BalanceB[x],16,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
            }
            if(cardmessagedisplay == 2)
            {
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage[x],6,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage1[x],8,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage2[x],10,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage3[x],12,x,1,0x0000,'Y');
                }
            }
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:
                            printBalance(EEPROM_1_ReadByte(8),side.c.dir);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            bufferDisplay3.flagPrint =  0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            ShiftState   = 0; 
                            SetPicture(1, DISPLAY_INICIO0);
                        break;
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            ShiftState   = 0;
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC      = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer(); 
            
        break;
    ///////////////FIN CASOS PARA CRÉDITO  /////////////////////  
    
    //////////// CASOS PARA CONFIGURACIONES  ///////////////////
        case 12:
            counter3++;
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x46:  //Turnos  							
                            flowDisplay3 = 13; 
                            if(EEPROM_1_ReadByte(222) == 1)
                            {
                                SetPicture(1,DISPLAY_CERRAR_TURNO);
                            }else
                            {
                                SetPicture(1,DISPLAY_ABRIR_TURNO);
                            } 
                            counter3 = 0;
                        break;
                        case 0x55:  //Configurar módulo 
                            flowDisplay3 = 14;
                            bufferDisplay3.flagKeyboard = 6;
                            numberKeys3 = 0;
                            hiddenKeys = 5;
                            controlChar ='*';
                            counter3 = 0;  
                            SetPicture(1,DISPLAY_INGRESE_PASSWORD);                           
                        break;
                        case 0xB5:  //Copia de recibo                             
                            side.c.RFstateReport = 1;
                            side.c.rfStateCopy = RF_COPY_RECEIPT;
                            SetPicture(1,DISPLAY_IMPRIMIENDO_RECIBO); 
                            bufferDisplay3.PrintCopy = 1;
                            counter3 = 0;
                            flowDisplay3  = 23;                                                                                                                             
                        break;
                        
                        case 0x3B:  //Pantalla Inicial    
                            flowDisplay3 = 0;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            Display1_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_INICIO0); 
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            Display1_ClearRxBuffer();
                        break;
                    }
                }                  
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }
        break;

        case 13:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x47:  //Open Shift  
                            flowDisplay3 = 9;
                            numberKeys3 = 0;    
                            bufferDisplay3.flagKeyboard = 4;
                            SetPicture(1,DISPLAY_INTRODUZCA_CEDULA);                            
                        break;
                        case 0x48:  //Close shift 
                            flowDisplay3 = 9;
                            numberKeys3 = 0;   
                            bufferDisplay3.flagKeyboard = 4;
                            SetPicture(1,DISPLAY_INTRODUZCA_CEDULA);                           
                        break;                         
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay3.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break; 
            
        case 14: //Teclado general      
            switch (alphanumeric_keyboard3(hiddenKeys,controlChar))
            {
                case 0: //Cancelar
                    switch(bufferDisplay3.flagKeyboard)
                    {
                        case 1://ID Estacion
                            for(x = 0; x <= 4; x++)
                            {
                                idStation[x] = 0;
                            }
                            flowDisplay3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 2://Umbral
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                pumpGap[x] = 0;
                            }
                            flowDisplay3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 3://Pass turno
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.shiftPassword[x] = 0;
                            }
                            flowDisplay3 = 0;
                            ShiftStateC  = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 4://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.passCard[x] = 0;
                            }
                            flowDisplay3 = 0;
                        break;
                        case 5://Pass
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.shiftPassword[x] = 0;
                            }
                            flowDisplay3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                            
                        case 6://Pass
                            for(x = 1; x <= configAccess[0]; x++)
                            {
                                configAccess[x] = 0;
                            }
                            flowDisplay3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 7://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.passCard[x] = 0;
                            }
                            flowDisplay3 = 0;
                        break;
                        case 8://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.passCard[x] = 0;
                            }
                            flowDisplay3 = 0;
                        break;
                        case 9://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.valueKeys[x] = 0;
                            }
                            flowDisplay3 = 0;
                        break;
                    }                    
                    Display1_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay3.flagKeyboard)
                    {   
                        case 1://ID Estacion
                            for(x = 0; x <= 4; x++)
                            {
                                idStation[x] = bufferDisplay3.valueKeys[x+1];                                
                            }
                            idStation[4] = 0x00;
                            intIDStation = atoi(idStation);
                            IDCast[0] = intIDStation;
                            IDCast[1] = intIDStation>>8;
                            EEPROM_1_WriteByte(IDCast[0],10);
                            EEPROM_1_WriteByte(IDCast[1],11);
                            flowDisplay3 = 15;
                            SetPicture(1,DISPLAY_CONFIGURACIONES);
                        break;
                        case 2://Umbral
                            for(x = 1; x <= bufferDisplay3.valueKeys[0]; x++)
                            {
                                pumpGap[x] = bufferDisplay3.valueKeys[x] - 48;
                            }
                            
                            PositionGAP = 0;
                            
                            for(x = 1; x <= bufferDisplay3.valueKeys[0]; x++)
                            {
                                PositionGAP = pumpGap[x] + PositionGAP * 10;
                            }  
                            
                            side.a.RF = side.a.dir + PositionGAP;
                            side.b.RF = side.b.dir + PositionGAP;
                            side.c.RF = side.c.dir + PositionGAP;
                            side.d.RF = side.d.dir + PositionGAP;
                            
                            // Almacena posicion RF
                            EEPROM_1_WriteByte(side.a.RF,200);
                            EEPROM_1_WriteByte(side.b.RF,201);
                            EEPROM_1_WriteByte(side.c.RF,202);
                            EEPROM_1_WriteByte(side.d.RF,203);
                            
                            flowDisplay3 = 15;
                            SetPicture(1,DISPLAY_CONFIGURACIONES);
                        break;
                        case 3://Pass turno
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.shiftPassword[x] = bufferDisplay3.valueKeys[x];
                            }
                            flowDisplay3 = 19;
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            side.c.RFstateReport = 1;
                            ShiftStateC = 1;
                        break;
                        case 4://Pass Card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.passCard[x] = bufferDisplay3.valueKeys[x];
                            }
                            vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                            iButtonFlag3 = 2;
                            SetPicture(1, DISPLAY_FORMA_PROGRAMACION);
                            flowDisplay3 = 3;
                        break;
                        case 5://Pass
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.shiftPassword[x] = bufferDisplay3.valueKeys[x];
                            }
                            flowDisplay3 = 15;
                            SetPicture(1,DISPLAY_CONFIGURACIONES);
                        break; 
                        case 6://Pass
                            for(x = 1; x <= configAccess[0]; x++)
                            {
                                configAccess[x] = bufferDisplay3.valueKeys[x];
                            }
                            if(configAccess[1] == passwordPump[1] && configAccess[2] == passwordPump[2] && configAccess[3] == passwordPump[3] && configAccess[4] == passwordPump[4])
                            {                                
                                SetPicture(1,DISPLAY_PASSWORD_VALIDO);
                                //CyDelay(700);
                                vTaskDelay( 700 / portTICK_PERIOD_MS );
                                flowDisplay3 = 15;
                                SetPicture(1,DISPLAY_CONFIGURACIONES);
                            }else{
                                SetPicture(1,DISPLAY_PASSWORD_INVALIDO);
                                //CyDelay(700);
                                vTaskDelay( 700 / portTICK_PERIOD_MS );
                                flowDisplay3 = 0;
                                SetPicture(1,DISPLAY_INICIO0);
                            }
                        break;
                        case 7://Pass Card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.passCard[x] = bufferDisplay3.valueKeys[x];
                            }
                            side.c.RFstateReport = 2;
                            vTaskDelay( 500 / portTICK_PERIOD_MS );  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);
                            flowDisplay3 = 28;
                        break;
                        case 8://Pass Card forma pago                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay3.passCard[x] = bufferDisplay3.valueKeys[x];
                            }
                            side.c.RFstateReport = 5;
                            vTaskDelay( 500 / portTICK_PERIOD_MS );  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);
                            flowDisplay3 = 35;
                        break;
                        case 9://tiempo contador                            
                            for(x = 1; x < hiddenKeys + 1; x++)
                            {
                                TimeValue[x-1] = bufferDisplay3.valueKeys[x];
                            } 
                            TimeValue[2] = 0x00;
                            EEPROM_1_WriteByte(atoi(TimeValue),225); 
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);
                            vTaskDelay( 500 / portTICK_PERIOD_MS );   
                            flowDisplay3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                    }                    
                    Display1_ClearRxBuffer();
                break;
            }            
        break;
            
        case 15: //Menu de configuraciones
            counter3++;
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x82:  //ID Estacion  
                            flowDisplay3 = 14;
                            numberKeys3 = 0; 
                            controlChar = 0;
                            hiddenKeys  = 5;
                            counter3 = 0;
                            bufferDisplay3.flagKeyboard = 1;
                            SetPicture(1,DISPLAY_INTRODUZCA_VALOR);                            
                        break;
                        case 0x83:  //KM efectivo 
                            flowDisplay3 = 30;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_KM_EFECTIVO);                            
                        break;
                        case 0x65:  //Test Impresoras 
                            flowDisplay3 = 16;
                            counter3 = 0;
                            PrintTest();
                            SetPicture(1,DISPLAY_AMBAS_IMPRESORAS_FUNCIONANDO);                           
                        break;        
                        case 0x5A:  //Umbral 
                            flowDisplay3 = 14;
                            numberKeys3 = 0;
                            controlChar = 0;
                            hiddenKeys  = 3;
                            counter3 = 0;
                            for(x = 0; x < 3; x++)
                            {
                                pumpGap[x]  = 0x00;
                            }
                            pumpGap[0]  = 2;
                            bufferDisplay3.flagKeyboard = 2;
                            SetPicture(1,DISPLAY_INTRODUZCA_VALOR);                            
                        break;
                        case 0x5B:  //Lectores banda 
                            flowDisplay3 = 31;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_LECTORES_BANDA);                            
                        break;
                        case 0x58:  //Hora y Fecha
                            flowDisplay3 = 14;
                            numberKeys3 = 0;  
                            controlChar = 0;
                            hiddenKeys  = 3;
                            counter3 = 0;
                            TimeValue[0]= 0x00;
                            TimeValue[1]= 0x00;
                            TimeValue[2]= 0x00;
                            bufferDisplay3.flagKeyboard = 9;
                            SetPicture(1,DISPLAY_INTRODUZCA_VALOR);                           
                        break;
                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                        break;
                    }                    
                }
                     
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break; 
            
        case 16: //Menu de configuraciones de impresoras 1
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x38:  //No funcionan  
                            flowDisplay3 = 17;
                            SetPicture(1,DISPLAY_IMPRESORA_NO_FUNCIONANDO);                            
                        break;
                        case 0x39:  //Si funcionan
                            flowDisplay3 = 15; 
                            EEPROM_1_WriteByte(1,8);
                            EEPROM_1_WriteByte(2,9);
                            SetPicture(1,DISPLAY_CONFIGURACIONES);
                        break;                                             
                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                        break;
                    }                    
                }
                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break;
            
        case 17: //Menu de configuraciones de impresoras 2
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {
                        case 0x8C:  //1 no funciona  
                            flowDisplay3 = 15; 
                            EEPROM_1_WriteByte(2,8);
                            EEPROM_1_WriteByte(2,9);
                            SetPicture(1,DISPLAY_CONFIGURACIONES);                            
                        break;
                        case 0x8D:  //2 no funciona
                            flowDisplay3 = 15;
                            EEPROM_1_WriteByte(1,8);
                            EEPROM_1_WriteByte(1,9);
                            SetPicture(1,DISPLAY_CONFIGURACIONES); 
                        break;
                            
                        case 0x8E:  //ninguna funciona
                            flowDisplay3 = 15; 
                            EEPROM_1_WriteByte(0,8);
                            EEPROM_1_WriteByte(0,9);
                            SetPicture(1,DISPLAY_CONFIGURACIONES); 
                        break;
                                               
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay3.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                        break;
                            
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay3.flagPrint =  0;
                            SetPicture(1,DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                        break;
                    }                    
                }

                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break;
            
        case 18: //Menu configuracion manual de fecha y hora
            if(leer_hora() == 1)
            {
                WriteLCD(1,(((timeDownHandle[1] & 0x10) >> 4) + 48),13,8,1,0x0000,'N');
                WriteLCD(1,((timeDownHandle[1] & 0x0F) + 48),13,9,1,0x0000,'N');
                WriteLCD(1,':',13,10,1,0x0000,'N');
                WriteLCD(1,(((timeDownHandle[0] & 0xF0)>>4)+48),13,11,1,0x0000,'N');
                WriteLCD(1,((timeDownHandle[0] & 0x0F)+48),13,12,1,0x0000,'N');               
            }
            if(leer_fecha() == 1)
            {                
                WriteLCD(1,(((dateDownHandle[0] & 0x30) >> 4) + 48),21,8,1,0x0000,'N');
                WriteLCD(1,((dateDownHandle[0] & 0x0F) + 48),21,9,1,0x0000,'N');
                WriteLCD(1,'/',21,10,1,0x0000,'N');
                WriteLCD(1,(((dateDownHandle[1] & 0x10) >> 4) + 48),21,11,1,0x0000,'N');
                WriteLCD(1,((dateDownHandle[1] & 0x0F) + 48),21,12,1,0x0000,'N');
                WriteLCD(1,'/',21,13,1,0x0000,'N');
                WriteLCD(1,(((dateDownHandle[2] & 0xF0) >> 4) + 48),21,14,1,0x0000,'N');
                WriteLCD(1,((dateDownHandle[2] & 0x0F) + 48),21,15,1,0x0000,'N');
            }
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                       
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);                            
                        break;
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);                            
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display1_ClearRxBuffer();
            }                        
        break;
            
        case 19:                        
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            ShiftState = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            ShiftState = 0;
                        break;
                    }                    
                }
                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer();            
        break;
            
        case 20: //pantalla de espera de autorizacion
            SetPicture(1, DISPLAY_ESPERANDO_AUTORIZACION);
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowDisplay3 = 0;
                            flowPosC     = 0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            ShiftState   = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer();
            
        break;
            
            
        case 21: //Pantalla de credito no autorizado            
            SetPicture(1, DISPLAY_AUTORIZACION_RECHAZADA);
            bufferDisplay3.flagPrint = 0;
            flowPosC     = 0;
            PresetFlag3  = 0;
            iButtonFlag3 = 0;
            counter3     = 0;
            for(x = 0; x < 9; x++)
            {
                FontSpace(1, mensaje[x],1+x,17);
                FontSpace(1, mensaje[x],1+x,21);                    
            }
            side.c.ActivoFideliza = 3;                                        
            side.c.RFstateReport = 3;
            bufferDisplay3.FidelConf = 0;
            side.c.rfState = RF_IDLE;
            vTaskDelay( 2000 / portTICK_PERIOD_MS );
            flowDisplay3 = 0;
            SetPicture(1, DISPLAY_INICIO0);
        break;
                    
        case 22: // Pantalla de Manguera equivocada           
            SetPicture(1, DISPLAY_AUTORIZACION_RECHAZADA);
            bufferDisplay3.flagPrint = 0;
            for(x = 0; x < 8; x++)
            {                
                FontSpace(1, mensaje3[x],1+x,17);                                   
            }
            for(x = 0; x < 10; x++)
            {                
                FontSpace(1, mensaje4[x],1+x,21);                    
            }
            side.c.ActivoFideliza = 3;                                        
            side.c.RFstateReport  = 3;
            bufferDisplay3.FidelConf = 0; 
            vTaskDelay( 2000 / portTICK_PERIOD_MS );
            flowDisplay3 = 0;
            AuthType3    = 0;
            counter3     = 0;
            SetPicture(1, DISPLAY_INICIO0);
        break;   

        case 23: //Pantalla imprimendo durante copia de recibo
            if(bufferDisplay3.PrintCopy == 0)
            {
                CounterC = 0;
                //flowDisplay3 = 0;
                Display1_ClearRxBuffer();
            }
            if(CounterC < 100)  // 20 segundos de espera aprox.
            {
                vTaskDelay( 100 / portTICK_PERIOD_MS );
                CounterC++; 
            }
            else
            {
                CounterC = 0;
                flowDisplay3 = 0;               
                Display1_ClearRxBuffer();
            } 

        break; 
        //////////////////CASOS ADICIONALES CONFIGURACIÓN ///////        
        case 30://KM efectivo
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {  
                        case 0x0A:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            ShiftStateC = 0;
                            KmCash[0] = 0x01;
                            KmCash[1] = 0x01;
                            WriteEeprom(500,KmCash);
                        break;
                        
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            ShiftStateC = 0;
                            KmCash[0] = 0x01;
                            KmCash[1] = 0x00;
                            WriteEeprom(500,KmCash);
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            ShiftStateC = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            ShiftStateC = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer();            
        break;   
        case 31://Banda		      
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {  
                        case 0x0A:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            ShiftStateC = 0;
                            magneticReader[0] = 0x02;
                            magneticReader[1] = 'A';
                            magneticReader[2] = 'A';
                            WriteEeprom(503,magneticReader);
                        break;
                        
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            ShiftStateC = 0;
                            magneticReader[0] = 0x02;
                            magneticReader[1] = 'A';
                            magneticReader[2] = 'B';
                            WriteEeprom(503,magneticReader);
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            ShiftStateC = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            ShiftStateC = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display1_ClearRxBuffer();            
        break; 
        ///////////////// CASOS FIDELIZACIÓN TERPEL /////////////        
         case 32: //Teclado general
            counter3++;
            switch (alphanumeric_keyboard3(keysTerpelC,0))
            {
                case 0: //Cancelar
                    switch(bufferDisplay3.flagKeyboard)
                    {                        
                        case 1://Cedula
                            
                            for(x = 0; x < keysTerpelC; x++)
                            {
                                bufferDisplay3.idTerpelFideliza[x] = 0;
                            }                            
                            flowDisplay3 = 0;
                            ShiftStateC = 0;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;   
                        case 2://Tarjeta para forma pago
                            
                            for(x = 0; x < keysTerpelC; x++)
                            {
                                bufferDisplay3.idFormaPago[x] = 0;
                            }                            
                            flowDisplay3 = 0;
                            ShiftStateC = 0;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 3://Tarjeta para forma pago                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay3.saleNumber[x] = 0;
                            }                            
                            flowDisplay3 = 0;
                            ShiftStateC = 0;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 4://Tarjeta para forma pago                            
                            for(x = 0; x < 8; x++)
                            {
                                bufferDisplay3.MoneyPay[x] = 0;
                            }                            
                            flowDisplay3 = 0;
                            ShiftStateC = 0;
                            counter3 = 0;
							side.c.RFstateReport = 7;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                        case 5://Tarjeta para forma pago                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay3.idFormaPago[x] = 0;
                            }                            
                            flowDisplay3 = 0;
                            ShiftStateC = 0;
                            counter3 = 0;
							if(bufferDisplay3.idType == 6)
                                side.c.RFstateReport = 7;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                            
                        case 6://Tarjeta para forma pago                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay3.PaymentNumber[x] = 0;
                            }                            
                            flowDisplay3 = 0;
                            ShiftStateC = 0;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_INICIO0);
                        break;
                    }                    
                    Display1_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay3.flagKeyboard)
                    {                           
                        case 1://Datos fidelización                            
                            for(x = 0; x < keysTerpelC; x++)
                            {
                                bufferDisplay3.idTerpelFideliza[x] = bufferDisplay3.valueKeys[x];
                            }                            
                            flowDisplay3 = 35;  
                            if(side.c.ActivoRedencion == 1){
                                side.c.RFstateReport = 4;                                
                            }else{
                                side.c.RFstateReport = 2;                        
                                side.c.ActivoFideliza = 2;
                            }
                            counter3 = 0;
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                            
                        case 2://LFM Forma de pago                            
                            for(x = 0; x < keysTerpelC; x++)
                            {
                                bufferDisplay3.idFormaPago[x] = bufferDisplay3.valueKeys[x];
                            }
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            for(x = 0; x < 21; x++)
                            {
                                bufferDisplay3.valueKeys[x] = 0x00;
                            }
                            flowDisplay3 = 14;    
                            hiddenKeys = 20;
                            controlChar ='*';
                            numberKeys3 = 0;
                            counter3 = 0;
                            bufferDisplay3.flagKeyboard = 8;
                            SetPicture(1,DISPLAY_PASS_ALFNUM);
                        break;
                            
                        case 3://numero de venta FP                            
                            for(x = 0; x < keysTerpelC; x++)
                            {
                                bufferDisplay3.saleNumber[x] = bufferDisplay3.valueKeys[x];
                            }                            
                            flowDisplay3 = 39;
                            counter3 = 0;
                            SetPicture(1, DISPLAY_FORMA_DE_PAGO_TERPEL);
                        break;
                            
                        case 4://valor voucher                             
                            for(x = 0; x < keysTerpelC + 1; x++)
                            {
                                bufferDisplay3.MoneyPay[x] = 0x00;
                            }
                            for(x = 1; x <= bufferDisplay3.valueKeys[0]; x++)
                            {
                                bufferDisplay3.MoneyPay[x-1] = bufferDisplay3.valueKeys[x];
                            }
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            writevalue = atoi(bufferDisplay3.MoneyPay);
                            res =(atoi(bufferDisplay3.saleValue)-atoi(bufferDisplay3.MoneyPayed));
                            if( abs(res) >= writevalue && writevalue > 0 )
                            {
                                for(x = 0; x < keysTerpelC + 1; x++)
                                {
                                    bufferDisplay3.valueKeys[x] = 0x00;
                                }
                                flowDisplay3 = 32;
                                numberKeys3 = 0;
                                keysTerpelC = 20;
                                if(bufferDisplay3.idType == 6){
                                    bufferDisplay3.flagKeyboard = 5;
                                }else{
                                    for(x = 0; x < keysTerpelC; x++)
                                    {
                                        bufferDisplay3.idFormaPago[x] = 0x00;
                                    }
                                    bufferDisplay3.flagKeyboard = 6;
                                }
                                SetPicture(1, DISPLAY_PASAPORTE);
                            }else{                            
                                flowDisplay3 = 32;
                                numberKeys3 = 0;
                                keysTerpelC = 10;                            
                                bufferDisplay3.flagKeyboard = 4;                                
                                SetPicture(1, DISPLAY_INTRODUZCA_VALOR); 
                                WriteLCD(1,'$',3,2,1,0x0000,'N');
                            }
                            counter3 = 0;
                        break;                            
                        case 5://pin voucher                           
                            for(x = 0; x < keysTerpelC; x++)
                            {
                                bufferDisplay3.idFormaPago[x] = bufferDisplay3.valueKeys[x];
                            }                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            side.c.RFstateReport = 5;                            
                            flowDisplay3 = 35;     
                            counter3 = 0;
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                        break;                            
                        case 6://numero de pago                           
                            for(x = 0; x < keysTerpelC; x++)
                            {
                                bufferDisplay3.PaymentNumber[x] = bufferDisplay3.valueKeys[x];
                            }                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            side.c.RFstateReport = 5;                            
                            flowDisplay3 = 35;
                            counter3 = 0;
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                    }                    
                    Display1_ClearRxBuffer();
                break;
            }       
            Display1_ClearRxBuffer();
        break;
            
        case 33: // identificacion fidelizacion
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    counter3 = 0;
                    switch(Display1_rxBuffer[3])
                    {  
                        case 0x1A:  //Cedula
                            if(side.c.ActivoRedencion == 1 ){
                                bufferDisplay3.documentID = 3 ;
                                bufferDisplay3.idType = 5;
                                flowDisplay3 = 35;
                                side.c.RFstateReport = 4; 
                                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay3 = 32;
                                numberKeys3 = 0;
                                keysTerpelC = 16;
                                bufferDisplay3.idType = 3;
                                SetPicture(1, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay3.flagKeyboard = 1;  
                        break;
                        case 0x1B:  //extranjería    
                            if(side.c.ActivoRedencion == 1 ){
                                bufferDisplay3.documentID = 4 ;
                                bufferDisplay3.idType = 5;
                                flowDisplay3 = 35;
                                side.c.RFstateReport = 4; 
                                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay3 = 32;
                                numberKeys3 = 0;
                                keysTerpelC = 16;
                                bufferDisplay3.idType = 4;
                                SetPicture(1, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay3.flagKeyboard = 1;                            
                        break;
                        case 0x1c: //PASAPORTE                              
                            if(side.c.ActivoRedencion == 1 ){
                                bufferDisplay3.documentID = 5;
                                bufferDisplay3.idType = 5;
                                flowDisplay3 = 35;
                                side.c.RFstateReport = 4; 
                                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay3 = 32;
                                numberKeys3 = 0;
                                keysTerpelC = 16;
                                bufferDisplay3.idType = 5;
                                SetPicture(1, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay3.flagKeyboard = 1;                                                    
                        break;
                        case 0x1d: //Lifemiles                            
                            if(side.c.ActivoRedencion == 1 ){
                                bufferDisplay3.idType = 5;
                                bufferDisplay3.documentID = 2;
                                flowDisplay3 = 35;
                                side.c.RFstateReport = 4; 
                                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay3 = 40; 
                                bufferDisplay3.idType = 2;
                                SetPicture(1, DISPLAY_ID_LIFE_MILES);                                                             
                            }                                                                                     
                        break;
                        case 0x1e: //Tarjeta pre inscrita                            
                            if(side.c.ActivoRedencion == 1 ){
                                bufferDisplay3.documentID = 1;
                                bufferDisplay3.idType = 5;
                                flowDisplay3 = 35;
                                side.c.RFstateReport = 4;
                                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay3 = 32;
                                numberKeys3 = 0;
                                keysTerpelC = 16;
                                bufferDisplay3.idType = 1;
                                SetPicture(1, DISPLAY_PASAPORTE);                             
                            }                            
                            bufferDisplay3.flagKeyboard = 1;  
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            ShiftStateC  = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            ShiftStateC  = 0;
                        break;
                    }                    
                }                
                Display1_ClearRxBuffer();  
            }                      
        break;
        
        case 34:
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay3.idTerpelFideliza[x] = 0x00;
            }
            if(code_pirata(magneticReader[1],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){                    
				    bufferDisplay3.idTerpelFideliza[x-1] = temporal[x];                    
                }
                bufferDisplay3.idTerpelFideliza[0] = x-2;
                // Authorization request
                SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                flowDisplay3 = 35;  
                side.c.RFstateReport = 2;                        
                side.c.ActivoFideliza = 2;
                SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);                             
                Display1_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3    = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3 = 0;
                            iButtonFlag3 = 0;
                            AuthType3 = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            }            
        break;
        case 35:            
            //Touch for return to init display
            //vTaskDelay( 2000 / portTICK_PERIOD_MS );   
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            side.c.ActivoFideliza = 3;
                            side.c.RFstateReport = 3;
                            bufferDisplay3.FidelConf = 0;
                            side.c.ActivoRedencion = 0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            side.c.ActivoFideliza = 3;
                            side.c.RFstateReport = 3;
                            bufferDisplay3.FidelConf = 0;
                            side.c.ActivoRedencion = 0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                        break;
                    }                    
                }
                Display1_ClearRxBuffer(); 
            }            
        break;
        
        case 36:    
            counter3 ++;
            side.c.ActivoFideliza = 0;
            side.c.RFstateReport  = 0;
            if(validaclientefiel3 == 1){
                for(x = 0; x < 17; x++)
                {
                    WriteMessage(1,NameCustomer[x],4,x,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage[x],6,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage1[x],8,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage2[x],10,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage3[x],12,x+1,2,0x0000,'Y');
                }
            }
            if(validaclientefiel3 == 2){                
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage[x],6,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage1[x],8,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage2[x],10,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(1,cardmessage3[x],12,x+1,1,0x0000,'Y');
                }
            }          
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Usuario correcto                          
                            if(AuthType3 == 1){
                                flowDisplay3 =10;
                                SetPicture(1, DISPLAY_ID_TERPEL);
                            }else{
                                flowDisplay3 =3;
                                SetPicture(1, DISPLAY_FORMA_PROGRAMACION); 
                            }
                            side.c.ActivoFideliza = 3;
                            side.c.RFstateReport = 3;
                            if(validaclientefiel3 == 1){
                                bufferDisplay3.FidelConf = 1;
                            }else{
                                bufferDisplay3.FidelConf = 0;
                            }
                            counter3 = 0;
                        break;
                        case 0x0B:  //Usuario incorrecto                                                       
                            side.c.ActivoFideliza = 3;
                            flowDisplay3 = 33;
                            bufferDisplay3.FidelConf = 0;
                            side.c.RFstateReport = 3;
                            counter3 = 0;
                            SetPicture(1, DISPLAY_IDEN_FIDELIZACION);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            side.c.ActivoFideliza = 3;
                            side.c.RFstateReport = 3;
                            bufferDisplay3.FidelConf = 0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            counter3     = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                        break;
                    }                    
                }                                
                Display1_ClearRxBuffer();   
            }                              
        break;
            
        case 38:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x53:
                            bufferDisplay3.lastSale = true;
                            flowDisplay3 = 39;                            
                            SetPicture(1, DISPLAY_FORMA_DE_PAGO_TERPEL);
                        break;
                        case 0x54:  //Solicita teclado 
                            for(x = 0; x < 20; x++)
                            {
                                bufferDisplay3.valueKeys[x] = 0x00;
                            }
                            bufferDisplay3.lastSale = false;
                            flowDisplay3 = 32;
                            numberKeys3 = 0;
                            keysTerpelC = 10;                            
                            bufferDisplay3.flagKeyboard = 3;
                            SetPicture(1, DISPLAY_INTRODUZCA_VALOR);
                        break;                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC      = 0;
                            flowDisplay3  = 0;                            
                            PresetFlag3   = 0;
                            iButtonFlag3  = 0;
                        break;                                                                       
                    }                    
                }
                Display1_ClearRxBuffer();
            }            
        break;
            
        case 39: 
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x1A: //VOUCHER     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay3 = 35;
                            side.c.ActivoRedencion = 1;
                            side.c.RFstateReport = 4;
                            bufferDisplay3.idType = 6;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1B: //Sodexo     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay3 = 35;
                            side.c.ActivoRedencion = 1;
                            side.c.RFstateReport = 4;
                            bufferDisplay3.idType = 4;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1C: //MASTER     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay3 = 35;
                            side.c.ActivoRedencion = 1;
                            side.c.RFstateReport = 4;
                            bufferDisplay3.idType = 2;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);	
                        break;                        
                        case 0x1D:  //LIFEMILES                             
                            flowDisplay3 = 33;
                            side.c.ActivoRedencion = 1;                            
                            SetPicture(1, DISPLAY_PAGO_LM);  
                        break;
                        case 0x1E: //Debito     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay3 = 35;
                            side.c.ActivoRedencion = 1;
                            side.c.RFstateReport = 4;
                            bufferDisplay3.idType = 3;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1F: //VISA    1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay3 = 35;
                            side.c.ActivoRedencion = 1;
                            side.c.RFstateReport = 4;
                            bufferDisplay3.idType = 1;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                        break;                                                                       
                    }                    
                }
                Display1_ClearRxBuffer();
            } 
        break;
        
        case 40:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0xB6:
                            if(bufferDisplay3.idType ==2){
                                flowDisplay3 = 34;
                                SetPicture(1, DISPLAY_ESPERANDO_ID_TERPEL);
                            }
                            if(bufferDisplay3.idType =='F'){
                                flowDisplay3 = 42;
                                SetPicture(1, DISPLAY_ESPERANDO_ID_TERPEL);
                            }
                        break;
                        case 0xB7:  //Solicita teclado 
                            flowDisplay3 = 32;
                            numberKeys3 = 0;
                            keysTerpelC = 20;                                                        
                            SetPicture(1, DISPLAY_PASAPORTE);
                            if(bufferDisplay3.idType !='F'){
                                for(x = 0; x < 20; x++)
                                {
                                    bufferDisplay3.valueKeys[x] = 0x00;
                                }
                                bufferDisplay3.flagKeyboard = 1;                                
                            }else{
                                for(x = 0; x < 20; x++)
                                {
                                    bufferDisplay3.valueKeys[x] = 0x00;
                                }
                                bufferDisplay3.flagKeyboard = 2;                                
                            }
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                        break;
                            
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                        break;                                                    
                    }                    
                }
                Display1_ClearRxBuffer();
            }            
        break;
        
        case 41: 
            bufferDisplay3.saleNumber[0] = 9;
			for (x = 1; x < 10; x++){
                bufferDisplay3.saleNumber[x] = 0x00;
            }
            for(x = 0; x < 14; x++)
            {
                WriteMessage(1,NumSale[x],4,x+5,1,0x0000,'Y');
            }
            for(x = 0; x < 10; x++)
            {
                WriteMessage(1,cardmessage[x],6,x+5,1,0x0000,'Y');
            }
            for(x = 1; x < 10; x++)
            {
                bufferDisplay3.saleNumber[x] = cardmessage[x-1];                
            }
            if(bufferDisplay3.idType ==5){
                for(x = 0; x < 9; x++)
                {
                    WriteMessage(1,VolSale[x],8,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,cardmessage1[x],10,x+5,1,0x0000,'Y');
                }
            }else{
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,MonSale[x],8,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,bufferDisplay3.MoneyPay[x],10,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 21; x++)
                {
                    WriteMessage(1,MonSalePayed[x],12,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,bufferDisplay3.MoneyPayed[x],14,x+5,1,0x0000,'Y');
                }                 
            }            
            if(bufferDisplay3.idType ==5){
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,MonSale[x],12,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,bufferDisplay3.MoneyPay[x],14,x+5,1,0x0000,'Y');
                }  
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(1,MilageSale[x],16,x+5,1,0x0000,'Y');
                }            
                for(x = 0; x < 6; x++)
                {
                    WriteMessage(1,cardmessage3[x],18,x+5,1,0x0000,'Y');
                }
            }                            
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Monto correcto
                            if(bufferDisplay3.idType ==5){
                                flowDisplay3 = 40; 
                                bufferDisplay3.idType = 'F'; //forma pago
                                if(bufferDisplay3.documentID == 2){
                                    SetPicture(1, DISPLAY_ID_LIFE_MILES);  
                                }else{
                                    bufferDisplay3.flagKeyboard = 2;
                                    flowDisplay3 = 32;
                                    numberKeys3 = 0;
                                    keysTerpelC = 16;
                                    SetPicture(1, DISPLAY_PASAPORTE);
                                } 
                            }else{                            
                                flowDisplay3 = 32;
                                numberKeys3  = 0;
                                keysTerpelC = 10;                            
                                bufferDisplay3.flagKeyboard = 4;                                
                                SetPicture(1, DISPLAY_INTRODUZCA_VALOR); 
                                WriteLCD(1,'$',3,2,1,0x0000,'N');
                            }
                        break;
                        
                        case 0x0B:  //Monto incorrecto incorrecto                            
                            bufferDisplay3.flagPrint =  0;
                            bufferDisplay3.idType = 0x00;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
							if(bufferDisplay3.idType == 6)
                                side.c.RFstateReport = 7;
                            SetPicture(1, DISPLAY_INICIO0);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            bufferDisplay3.FidelConf = 0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                        break;
                    }                    
                }
                Display1_ClearRxBuffer(); 
            }                                
        break;
         
        case 42:
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay3.idFormaPago[x] = 0x00;
            }
            if(code_pirata(magneticReader[1],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){
				    bufferDisplay3.idFormaPago[x-1] = temporal[x];                    
                }
                bufferDisplay3.idFormaPago[0] = x-2;
                // Authorization request
                SetPicture(1,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                flowDisplay3 = 14;    
                hiddenKeys = 20;
                controlChar ='*';
                numberKeys3=0;
                bufferDisplay3.flagKeyboard = 8;
                SetPicture(1,DISPLAY_PASS_ALFNUM); 
                Display1_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3 = 0;
                            Display1_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            flowDisplay3 = 0;
                            bufferDisplay3.flagPrint =  0;
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            AuthType3 = 0;
                            Display1_ClearRxBuffer();
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            }            
        break;
            
        
        case 43:                                                
            for(x = 0; x < 25; x++)
            {
                WriteMessage(1,cardmessage[x],6,x+1,1,0x0000,'Y');
            }            
            for(x = 0; x < 25; x++)
            {
                WriteMessage(1,cardmessage1[x],10,x+1,1,0x0000,'Y');
            }    
            for(x = 0; x < 25; x++)
            {
                WriteMessage(1,cardmessage2[x],14,x+1,1,0x0000,'Y');
            }
            for(x = 0; x < 25; x++)
            {
                WriteMessage(1,cardmessage3[x],18,x+1,1,0x0000,'Y');
            }
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Imprimir comprobante
                            printPayment(EEPROM_1_ReadByte(8),side.c.RF);
                            vTaskDelay( 500 / portTICK_PERIOD_MS ); 
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            SetPicture(1, DISPLAY_INICIO0); 
                            for(x = 0; x < 7; x++)
                            {
                                bufferDisplay3.saleValue[x] = 0x00;
                            }
                        break;
                        
                        case 0x0B:  //No imprimir comprobante                                                       
                            bufferDisplay3.idType = 0x00;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            SetPicture(1, DISPLAY_INICIO0);
                            for(x = 0; x < 7; x++)
                            {
                                bufferDisplay3.saleValue[x] = 0x00;
                            }
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            bufferDisplay3.FidelConf = 0;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            for(x = 0; x < keysTerpelC; x++)
                            {
                                bufferDisplay3.saleValue[x] = 0x00;
                            }
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            }                                 
        break;
          
         case 44:
            if(Display1_GetRxBufferSize() == 8)
            {
                if((Display1_rxBuffer[0] == 0xAA) && (Display1_rxBuffer[6] == 0xC3) && (Display1_rxBuffer[7] == 0x3C))
                {
                    switch(Display1_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Mas voucher
                            bufferDisplay3.lastSale = false;
                            flowDisplay3 = 35;
                            side.c.ActivoRedencion = 1;
                            side.c.RFstateReport = 4;
                            bufferDisplay3.idType = 6;  
                            SetPicture(1, DISPLAY_POR_FAVOR_ESPERE);
                        break;
                        
                        case 0x0B:  //Finalizar                                                       
                            side.c.RFstateReport = 6;                             
                            flowDisplay3 = 35;                                                                                    
                            SetPicture(1,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(1, DISPLAY_INICIO0);
                            bufferDisplay3.flagPrint =  0;
                            side.c.ActivoRedencion = 0;
							side.c.RFstateReport = 7;
                            flowPosC     = 0;
                            flowDisplay3 = 0;                            
                            PresetFlag3  = 0;
                            iButtonFlag3 = 0;
                            for(x = 0; x < keysTerpelC; x++)
                            {
                                bufferDisplay3.saleValue[x] = 0x00;
                            }
                        break;
                    }                    
                }
                Display1_ClearRxBuffer();
            } 
        break;
        
    }    
}

/*
*********************************************************************************************************
*                                         void PollingDisplay4(void)
*
* Description : Pregunta estado al surtidor 
*               
*
*********************************************************************************************************
*/
void PollingDisplay4(void){    
    uint8 x,y;    
    tempcont =EEPROM_1_ReadByte(225);
    if(counter4 >= tempcont*100 && tempcont > 0){ //70 segs aprox
        bufferDisplay4.flagPrint =  0;
        flowDisplay4 = 's'; 
        flowPosD     = 0;                           
        PresetFlag4  = 0;
        iButtonFlag4 = 0;
        counter4     = 0;
        SetPicture(2, DISPLAY_TIEMPO_EXPIRADO);
    }
    switch(flowDisplay4){
        case 's':
        if(Display2_GetRxBufferSize() == 8)
            {   
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Return to initial screen                                                                                    
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            AuthType4 = 0;
                            counter4  = 0;
                            Display2_ClearRxBuffer();
                        break;
                        case 0x94:  //Return to initial screen                                                                                    
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            AuthType4 = 0;
                            counter4  = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }               
                Display2_ClearRxBuffer();
            }
        break;
        case 0:			                      
            SetPicture(2, DISPLAY_SELECCIONE_POSICION);
          
            bufferDisplay4.flagActiveSale = false;
            flowDisplay4 = 1;
            Display2_ClearRxBuffer();                
        break;
        case 1: //Menu               
            if(bufferDisplay4.flagActiveSale)
            {
                flowDisplay4 = flowPosD;            
            }
            if(bufferDisplay2.flagActiveSale)
            {
                flowDisplay2 = flowPosB;
                selectPosB   = 1;
            }
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {                                             
                    switch(Display2_rxBuffer[3]){
				        case 0x57:						        //POS A                                                                                                                       
                                if(bufferDisplay2.flagActiveSale || bufferDisplay2.PrintEnd == 1){
                                    flowDisplay2 = flowPosB;      //Si está vendiendo en esta posición regresa a su flujo
                                }else{
                                    if(EEPROM_1_ReadByte(215)!= 11){
                                        SetPicture(2, DISPLAY_FORMA_PAGO_DESEADA);                                                
                                    }else{
                                        SetPicture(2,DISPLAY_FORMA_PAGO_DESEADA_TERPEL);
                                    }
                                    selectPosB     = 1;
                                    flowDisplay2   = 2;
									Display2_ClearRxBuffer();
                                }
                                if (bufferDisplay4.flagActiveSale){
                                    flowDisplay4 = flowPosD;    //Si la venta está activa en POS B regresa a su flujo
                                }
                                else{
                                    flowDisplay4 = 0;  
                                    flowPosD     = 0;
                                }
					    break;
                            		       
					    case 0x56:  				            //POS B                                                                 
                                if(bufferDisplay2.flagActiveSale){
                                    flowDisplay2 = flowPosB;      //Si está vendiendo en esta posición regresa a su flujo
                                }
                                else{
                                    flowDisplay2 = 0;
                                    flowPosB     = 0;
                                } 
                                if (bufferDisplay4.flagActiveSale || bufferDisplay4.PrintEnd == 1){                                    
                                    flowDisplay4 = flowPosD;    //Si la venta está activa en POS B regresa a su flujo
                                }else{
                                    if(EEPROM_1_ReadByte(215)!= 11){
                                        SetPicture(2, DISPLAY_FORMA_PAGO_DESEADA);                                                
                                    }else{
                                        SetPicture(2,DISPLAY_FORMA_PAGO_DESEADA_TERPEL);
                                    }
							        selectPosB    = 2;
                                    flowDisplay4  = 2;                            
                                }                           
					    break;                                                   
				    }
                } 
                Display2_ClearRxBuffer();
                vTaskDelay( 10 / portTICK_PERIOD_MS );
            }            
        break;
        case 2: //Menu de metodo de pago
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x0D:  //Pantalla efectivo   
                            if(EEPROM_1_ReadByte(223) == 1)
                            {
                                AuthType4 = 2;
                                bufferDisplay4.saleType = 1; 
                                if(EEPROM_1_ReadByte(215)!= 11){
                                    flowDisplay4 = 3;                                                                        
                                    SetPicture(2, DISPLAY_FORMA_PROGRAMACION);                                      
                                }else{
                                    flowDisplay4 = 37;                                       
                                    SetPicture(2, DISPLAY_FIDELIZACION);  
                                }
                            }else{
                                SetPicture(2, DISPLAY_CANCELADO_X_PC);
                                vTaskDelay( 900 / portTICK_PERIOD_MS );
                                flowDisplay4 = 0; 
                                Display2_ClearRxBuffer();                                                               
                            }
                        break;
                        case 0x0E:  //Pantalla credito 
                            for(x = 0; x < 10; x++)
                            {                                
                                bufferDisplay4.CreditpresetValue[0][x] = 0x00;
                                bufferDisplay4.CreditpresetValue[1][x] = 0x00;
                                
                            }                            
                            if(EEPROM_1_ReadByte(223) == 1)
                            {                                
                                AuthType4 = 1;
                                bufferDisplay4.saleType = 2;                                 
                                if(EEPROM_1_ReadByte(215)!= 11){
                                    flowDisplay4 = 10;
                                    SetPicture(2, DISPLAY_ID_DIGITAL);
                                }else{
                                    flowDisplay4 = 37;
                                    SetPicture(2, DISPLAY_FIDELIZACION);
                                }                                
                                Display2_ClearRxBuffer();
                            }else
                            {
                                SetPicture(2, DISPLAY_CANCELADO_X_PC);
                                vTaskDelay( 900 / portTICK_PERIOD_MS );
                                flowDisplay4 = 0;  
                                counter4 = 0;
                                Display2_ClearRxBuffer();                                                             
                            }                            
                        break;
                            
                        case 0x0F: //Forma de pago
                            if(EEPROM_1_ReadByte(223) == 1)
                            {
                                flowDisplay4 = 38;                            
                                SetPicture(2, DISPLAY_SELECCION_VENTA);
                            }
                        break;
                        case 0x45:  //Pantalla otras opciones 
                            flowDisplay4 = 12;                            
                            SetPicture(2,DISPLAY_OPERACIONES); 
                            AuthType4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay4.flagPrint =  0;                            
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay4.flagPrint =  0;                            
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            AuthType4    = 0;
                            counter4      = 0;
                            vTaskDelay( 10 / portTICK_PERIOD_MS );
                            Display2_ClearRxBuffer();
                        break;
                    }
                } 
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();                
            }             
        break;
         
        case 37: // Desea fidelizar            
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    side.d.ActivoFideliza = 0;
                    side.d.ActivoRedencion = 0;
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A: //Si                                                                                   
                            flowDisplay4 = 33;
                            SetPicture(2, DISPLAY_IDEN_FIDELIZACION);                              
                        break;
                        case 0x0B:  //No 
                            if(AuthType4 == 1){
                                flowDisplay4 =10;                                
                                SetPicture(2, DISPLAY_ID_TERPEL);
                            }else{
                                flowDisplay4 =3;                                
                                SetPicture(2, DISPLAY_FORMA_PROGRAMACION); 
                            }
                            side.d.ActivoFideliza = 0;                                                         
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            counter4     = 0;
                        break;
                    }                    
                }                                
                Display2_ClearRxBuffer(); 
            }            
        break;
                                
        case 3:  //Menu de tipo de preset
            for(x = 0; x <10; x++)
            {
                bufferDisplay4.presetValue[0][x] = 0x00;
                bufferDisplay4.presetValue[1][x] = 0x00;
            }
            Credit_Auth_OK4 = 0;
            counter4 ++;
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {                    
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x0F:  //Preset dinero                
                            flowDisplay4 = 4;                              
                            bufferDisplay4.presetType[0] = 2;
                            bufferDisplay4.presetType[1] = '$';
                            numberKeys4 = 0;
                            SetPicture(2,DISPLAY_INTRODUZCA_VALOR);   
                            WriteLCD(2,'$',3,2,1,0x0000,'N');							
                            if(EEPROM_1_ReadByte(2) > 0)
                            {
                                flagPoint4 = 0;
                            }else
                            {
                                flagPoint4 = 1;
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break; 
                        case 0x10:  //Preset volumen                 
                            flowDisplay4 = 4;                            
                            bufferDisplay4.presetType[0] = 1;
                            bufferDisplay4.presetType[1] = 'G';
                            numberKeys4 = 0;                            
                            SetPicture(2,DISPLAY_INTRODUZCA_VOLUMEN);                            
                            WriteLCD(2,'G',3,2,1,0x0000,'N');                            							
                            if(EEPROM_1_ReadByte(3) > 0) //VolDec
                            {
                                flagPoint4 = 0;
                            }else
                            {
                                flagPoint4 = 1;
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        case 0x43:  //Preset full 
                            bufferDisplay4.presetType[0] = 3;
                            bufferDisplay4.presetType[1] = 'F';
                            
                            for(x = 1; x <(digits - 1); x++)
                            {
                                bufferDisplay4.presetValue[0][x] = '9';
                            }                            
                            bufferDisplay4.presetValue[0][x] = '0';
                            bufferDisplay4.presetValue[0][x + 1] = '0';
                            bufferDisplay4.presetValue[0][0] = digits;
                            for(x = 0; x <= bufferDisplay4.presetValue[0][0]; x++)
                            {
                                bufferDisplay4.presetValue[1][x] = bufferDisplay4.presetValue[0][x];
                            }
                            flowDisplay4 = 5;
                            counter4 = 0;
                            SetPicture(2,DISPLAY_SELECCIONE_PRODUCTO4); 
                            Display2_ClearRxBuffer();                         
                        break;
                        case 0x94:  //Retroceso 
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            AuthType4 = 0;
                            counter4 = 0;
                            SetPicture(2,DISPLAY_INICIO0); 
                            Display2_ClearRxBuffer();                                                       
                        break;
                        case 0x3B:  //Pantalla Inicial  
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            AuthType4 = 0;
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;                            
                            AuthType4    = 0;
                            counter4     = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }
                }                  
                //vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();
            }
           
        break;
        
        case 4:    // Teclado general 
            counter4 ++;
            switch (alphanumeric_keyboard4(digits + 1,0))
            {
                case 0:  //Pantalla Inicial    
                    flowDisplay4 = 0;
                    AuthType4 = 0;
                    bufferDisplay4.flagPrint =  0;
                    SetPicture(2,DISPLAY_INICIO0);
                    Display2_ClearRxBuffer();                            
                break;
                    
                case 1: //Enter
                    counter4 = 0;
                    for(x = 0; x <= bufferDisplay4.valueKeys[0]; x++)
                    {
                        bufferDisplay4.presetValue[0][x] = bufferDisplay4.valueKeys[x];
                        bufferDisplay4.presetValue[1][x] = bufferDisplay4.valueKeys[x];
                    }  
                    IntValueD = 0;
                    for(x = 0; x < 10; x++)
                    {                  
                        bufferDisplay4.PresetTemp[x] = 0x00;                         
                    }
                    // Convierte valor del preset en entero
                    for(x = 1; x < 10; x++)
                    {
                        if(bufferDisplay4.presetValue[0][x] != '.' && bufferDisplay4.presetValue[0][x] != ',' && bufferDisplay4.presetValue[0][x] != 0x00)
                        {
                           bufferDisplay4.PresetTemp[x - 1] = bufferDisplay4.presetValue[0][x] - 48;
                        }           
                       
                    }                    
                    // Convierte valor del preset en entero
                    for(x = 0; x < bufferDisplay4.presetValue[0][0]; x++)
                    {
                        IntValueD = 10 * IntValueD + bufferDisplay4.PresetTemp[x];
                    }  
                    // Rechaza transaccion si el Preset es menor a  COP$1000
                    if(bufferDisplay4.presetType[0] == 2)
                    {
                    	if(IntValueD < 1000)
                    	{
                        	AuthType4 = 0;
                        	bufferDisplay4.flagPrint =  0;
                        	flowDisplay4 = 0;
                        	SetPicture(2,DISPLAY_INICIO0); 
                    	}
                    	else
                    	{
                        	flowDisplay4 = 5;   //caso para seleccion de producto
                        	SetPicture(2, DISPLAY_SELECCIONE_PRODUCTO4);
                    	}
                    }
                    else
                    {
                        
                        if((bufferDisplay4.presetValue[0][0] > 0 && IntValueD != 0) && (bufferDisplay4.presetValue[0][0] < 7 && IntValueD >= 1))
                        {
                            flowDisplay4 = 5;   //caso para seleccion de producto
                        	SetPicture(2, DISPLAY_SELECCIONE_PRODUCTO4);  
                        }
                        else
                        {
                            AuthType4 = 0;
                        	bufferDisplay4.flagPrint =  0;
                        	flowDisplay4 = 0;
                        	SetPicture(2,DISPLAY_INICIO0);
                        }                   	
                    }
                    Display2_ClearRxBuffer();
                break;
            }
        break;
            
        case 5: //Menu de seleccion de producto
            counter4 = counter4 + 3;
            if(side.d.GradesHose[1] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(2, producto[side.d.GradesHose[1]-1][x],9+x,11); //FontSpace(LCD, caracter,posx,posy)
                //WriteMessage(1, producto[side.a.GradesHose[1]-1][x],11,6+x,2,0x0000,'Y'); //WriteMessage(1, producto1[x],11,7+x,2,0x0000,'Y');
                }
            }
            if(side.d.GradesHose[2] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(2, producto[side.d.GradesHose[2]-1][x],10+x,17); //FontSpace(LCD, caracter,posx,posy)
                //WriteMessage(1, producto[side.a.GradesHose[2]-1][x],17,7+x,2,0x0000,'Y');//WriteMessage(1, producto2[x],17,8+x,2,0x0000,'Y');
                }
            }
            if(side.d.GradesHose[3] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(2, producto[side.d.GradesHose[3]-1][x],11+x,23);
                //WriteMessage(1, producto[side.a.GradesHose[3]-1][x],23,8+x,2,0x0000,'Y');
                }
            }
            if(side.d.GradesHose[4] !=0)
            {
                for(x = 1; x < 11; x++)
                {
                FontSpace(2, producto[side.d.GradesHose[4]-1][x],12+x,29);
                //WriteMessage(1, producto[side.a.GradesHose[4]-1][x],29,9+x,2,0x0000,'Y');
                }
            }  
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x80:  //Grado 1 
                            if(side.d.hoseNumber > 0)
                            {
                                numberKeys4 = 0; 
                                flowDisplay4 = 9;
                                side.d.hose = 1;                            
                                //Credit
                                if(AuthType4 == 2)
                                {
                                    if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay4.flagKeyboard = 2; 
                                        SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay4.flagKeyboard = 1; 
                                        SetPicture(2, DISPLAY_DIGITE_PLACA);
                                    } 
                                }
                                //Cash
                                if(AuthType4 == 1)
                                {                    
                                    bufferDisplay4.flagKeyboard = 2;
                                    SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break;        
                        case 0x81:  //Grado 2
                            if(side.d.hoseNumber > 1)
                            {
                                numberKeys4 = 0;
                                flowDisplay4 = 9;
                                side.d.hose = 2;                          
                                //Credit
                                if(AuthType4 == 2)
                                {
									if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay4.flagKeyboard = 2; 
                                        SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay4.flagKeyboard = 1; 
                                        SetPicture(2, DISPLAY_DIGITE_PLACA);
                                    } 
                                }
                                //Cash
                                if(AuthType4 == 1)
                                {                    
                                    bufferDisplay4.flagKeyboard = 2;
                                    SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                            
                        case 0x7F:  //Grado 3
                            if(side.d.hoseNumber > 2)
                            {
                                numberKeys4 = 0;
                                flowDisplay4 = 9;
                                side.d.hose = 3;                            
                                //Credit
                                if(AuthType4 == 2)
                                {
									if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay4.flagKeyboard = 2; 
                                        SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay4.flagKeyboard = 1; 
                                        SetPicture(2, DISPLAY_DIGITE_PLACA);
                                    } 
                                }                                
                                //Cash
                                if(AuthType4 == 1)
                                {                    
                                    bufferDisplay4.flagKeyboard = 2;
                                    SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break;   
                        
                        case 0xB8:  //Grado 4 
                            if(side.d.hoseNumber > 3)
                            {
                                numberKeys4 = 0;
                                flowDisplay4 = 9;
                                side.d.hose = 4;                           
                                //Credit
                                if(AuthType4 == 2)
                                {
									if(KmCash[1] == 0x01)
                                    {
                                        bufferDisplay4.flagKeyboard = 2; 
                                        SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);
                                    }else{
                                        bufferDisplay4.flagKeyboard = 1; 
                                        SetPicture(2, DISPLAY_DIGITE_PLACA);
                                    } 
                                }
                                //Cash
                                if(AuthType4 == 1)
                                {                    
                                    bufferDisplay4.flagKeyboard = 2;
                                    SetPicture(2, DISPLAY_INTRODUZCA_KILOMETRAJE);                            
                                }
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Retroceso
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            SetPicture(2,DISPLAY_INICIO0);    
                            Display2_ClearRxBuffer();                                                    
                        break;
                            
                        case 0x7E:  //Pantalla Inicial    
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();               
            }            
        break;
                    
        case 6: //Pantalla de impresion SI/NO
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x39:  //Si imprimir  
                            flowDisplay4 = 7;
                            numberKeys4 = 0;
                            bufferDisplay4.flagPrint =  1;
							bufferDisplay4.PrintFlagEOT = 0;
                            SetPicture(2,DISPLAY_SUBA_MANIJA); 
                            Display2_ClearRxBuffer();                           
                        break; 
                        case 0x38:  //No imprimir 
                            flowDisplay4 = 7;//Esperando estado del dispensador 
                            bufferDisplay4.flagPrint =  0;                                                                
							bufferDisplay4.PrintFlagEOT = 0;
                            SetPicture(2,DISPLAY_SUBA_MANIJA);
                            Display2_ClearRxBuffer();
                        break;
                        case 0x7E:  //Pantalla Inicial                                                                                    
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint = 0;
                            AuthType4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                } 
                //vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();             
            }            
        break;                                             
        case 7: //Preset ON y espera descuelgue de manguera
            PresetFlag4 = 1;  
            counter4 = counter4 + 4;
            vTaskDelay( 40 / portTICK_PERIOD_MS );
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            AuthType4 = 0;
                            bufferDisplay4.zeroSend = 1;
                            vTaskDelay( 50 / portTICK_PERIOD_MS );
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            AuthType4 = 0;
                            bufferDisplay4.zeroSend = 1;
                            vTaskDelay( 50 / portTICK_PERIOD_MS );
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display2_ClearRxBuffer();                
            }                      
        break;
            
        case 8:           
            //Pump Busy...
            vTaskDelay( 10 / portTICK_PERIOD_MS ); 
            if(NumPositions > 2)
            {
                flowDisplay4 = 1;
            }
            counter4 = 0;
        break;
            
        case 9: // Keyboard     
            if(upcount4[0] == 1){
                if(upcount4[1] == 1){
                    counter4 ++;
                    upcount4[1] = 0;
                }else{
                    upcount4[1] = 1;
                }
            }else{
                counter4++;
            }
            switch (alphanumeric_keyboard4(11,0))
            {
                case 0: //Cancel
                    switch(bufferDisplay4.flagKeyboard)
                    {
                        case 1://License plate
                            for(x = 0; x < 11; x++)
                            {
                                bufferDisplay4.licenceSale[x] = 0;
                            }
                            flowDisplay4 = 0;
                            counter4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 2://Mileage
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay4.mileageSale[x] = 0;
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 3://CC/NIT
                            for(x = 0; x < 11; x++)
                            {
                                bufferDisplay4.identySale[x] = 0;
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        case 4://ID
                            for(x = 0; x < 11; x++)
                            {
                                bufferDisplay4.shiftId[x] = 0;
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                    Display2_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay4.flagKeyboard)
                    {
                        case 1://Licence plate
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay4.licenceSale[x] = 0x00;
                            }                            
                            for(x = 0; x <= bufferDisplay4.valueKeys[0]; x++)
                            {
                                bufferDisplay4.licenceSale[x] = bufferDisplay4.valueKeys[x];
                            }
                            flowDisplay4 = 6;
                            counter4 = 0;
                            SetPicture(2, DISPLAY_DESEA_IMPRIMIR_RECIBO);                                 
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 2:  //Mileage
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay4.mileageSale[x] = 0x00;
                            }
                            for(x = 0; x <= bufferDisplay4.valueKeys[0]; x++)
                            {
                                bufferDisplay4.mileageSale[x] = bufferDisplay4.valueKeys[x];
                            }
                            
                            if(AuthType4 == 1)
                            {
                                flowDisplay4 = 7;                                
                                SetPicture(2,DISPLAY_SUBA_MANIJA);
                            }
                            if(AuthType4 == 2)
                            {
                                if(KmCash[1] == 0x01)
                                {   
                                    numberKeys4 = 0; 
                                    flowDisplay4 = 9;
                                    bufferDisplay4.flagKeyboard = 1; 
                                    SetPicture(2, DISPLAY_DIGITE_PLACA);
                                }                                         
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 3://CC/NIT
                            for(x = 0; x <= bufferDisplay4.valueKeys[0]; x++)
                            {
                                bufferDisplay4.identySale[x] = bufferDisplay4.valueKeys[x];
                            }
                            counter4 = 0;
                            Display2_ClearRxBuffer();
                        case 4://ID
                            for(x = 0; x <= 10; x++)
                            {
                                bufferDisplay4.shiftId[x] = bufferDisplay4.valueKeys[x];
                            }
                            flowDisplay4 = 14;      //Pide clave                            
                            numberKeys4 = 0;
                            hiddenKeys  = 10;
                            controlChar ='*';
                            counter4 = 0;
                            bufferDisplay4.flagKeyboard = 3;
                            SetPicture(2,DISPLAY_INGRESE_PASSWORD);
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                //Display2_ClearRxBuffer();    
                break;

            }  
            Display2_ClearRxBuffer();           
        break;    
    ////////////////// CASOS PARA CRÉDITO  /////////////////////
        case 10:
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0xB6:  //Solicitud ibutton  
                            flowDisplay4 = 11;
                            numberKeys4  = 0;  
                            counter4 = 0;
                            //bufferDisplay4.flagPrint =  1;
                            SetPicture(2,DISPLAY_ESPERANDO_ID);                            
                        break; 
                        case 0xB7:  //ID por número
                            if(EEPROM_1_ReadByte(215)!= 11){
                            	flowDisplay4 = 24;
                            	numberKeys4 = 0;                            
                            	//bufferDisplay4.flagPrint =  1;
                            	Tag_ClearRxBuffer();
                            	Tag_ClearTxBuffer();
                            	Tag_PutChar('O');
                            	Tag_PutChar('K');
                            	Tag_PutChar(0x02);
                            	vTaskDelay( 100 / portTICK_PERIOD_MS );
                            	SetPicture(2, DISPLAY_ESPERANDO_ID);                           
                            }else{
                            	flowDisplay4 = 25;
                                numberKeys4 = 0;
                                bufferDisplay4.idType = 3;
                            	vTaskDelay( 100 / portTICK_PERIOD_MS );
                            	SetPicture(2, DISPLAY_SELECCIONE_OP_TERPEL);
                            }    
                            counter4 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                        break;
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                        break;
                    }                    
                }                
                //vTaskDelay( 10 / portTICK_PERIOD_MS ); 
                Display2_ClearRxBuffer();
            } 
                                  
        break;
        
        case 11: //Lectura del iButton
            counter4 ++;
            for(x = 0; x < 30; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 25; x++)
            {
                bufferDisplay4.idSerial[x] = 0x00;
            }
            if(touch_present(2) == 1)
            {
				if(touch_write(2,0x33))
                {
					for(x = 1; x <= 8; x++)
                    {
						temporal[x] = touch_read_byte(2);
					}
					y = 0;
					for(x = 1; x < 8; x++)
                    {
                        y = crc_check(y,temporal[x]);
                    }
					if(y == temporal[8])
                    {
						bufferDisplay4.idSerial[0] = 16;
						y = 16;
						for(x = 1; x <= 8; x++)
                        {
							if((temporal[x] & 0x0F) >= 10)
                            {
								bufferDisplay4.idSerial[y] = (temporal[x] & 0x0F) + 55;
							}else{
								bufferDisplay4.idSerial[y] = (temporal[x] & 0x0F) + 48;				
							}
                            y--;
							if(((temporal[x] >> 4) & 0x0F) >= 10)
                            {
								bufferDisplay4.idSerial[y] = ((temporal[x] >> 4) & 0x0F) + 55;
							}else{
								bufferDisplay4.idSerial[y] = ((temporal[x] >> 4) & 0x0F) + 48;				
							}
                            y--;
						}                        
                        SetPicture(2,DISPLAY_ID_RECONOCIDO);                                           
                        vTaskDelay( 500 / portTICK_PERIOD_MS ); 
                        iButtonFlag4 = 1;
                        SetPicture(2, DISPLAY_FORMA_PROGRAMACION);
                        flowDisplay4 = 3;
                        counter4     = 0;
					}                                     
				}
                else //iButton Error
                {
                    SetPicture(2,DISPLAY_ID_NO_RECONOCIDO);                                           
                    Display2_ClearRxBuffer();
                    vTaskDelay( 500 / portTICK_PERIOD_MS );    
                    SetPicture(2, DISPLAY_INICIO0);
                    flowDisplay4 = 0;
                    bufferDisplay4.flagPrint =  0;
                    PresetFlag4 = 0;
                    iButtonFlag4 = 0;
                    AuthType4 = 0;
                    Display2_ClearRxBuffer();
                }
			}
           //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                
                //vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
                Display2_ClearRxBuffer();
            }                                                        
        break; 
        
        case 24:
            counter4 ++;
            for(x=0;x<=29;x++){
                temporal[x]=0x00;
            }
            for(x=0;x<=24;x++){
                bufferDisplay4.idSerial[x]=0x00;
            }
            if(serial_codetag(2)==1){
                for(x=0;x<=temporal[0];x++){
                    bufferDisplay4.idSerial[x]=temporal[x];
                }
                bufferDisplay4.idSerial[0]=16;
				y=16;
				for(x=1;x<=8;x++){
					if((temporal[x]&0x0F)>=10){
						bufferDisplay4.idSerial[y]=(temporal[x]&0x0F)+55;
					}else{
						bufferDisplay4.idSerial[y]=(temporal[x]&0x0F)+48;				
					}
                    y--;
					if(((temporal[x]>>4)&0x0F)>=10){
						bufferDisplay4.idSerial[y]=((temporal[x]>>4)&0x0F)+55;
					}else{
						bufferDisplay4.idSerial[y]=((temporal[x]>>4)&0x0F)+48;				
					}
                    y--;
				}                
                // Authorization request
                SetPicture(2,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag4 = 1;
                SetPicture(2, DISPLAY_FORMA_PROGRAMACION);
                flowDisplay4 = 3;
                counter4 = 0;
            }
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display2_ClearRxBuffer();
            } 
        break;    
            
        case 25:
            counter4++;
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0xB6:  //Autorizacion con tarjeta   
                            flowDisplay4 = 26;
                            numberKeys4 = 0;                    
                            counter4 = 0;
                            bufferDisplay4.flagPrint =  1;
                            SetPicture(2, DISPLAY_ESPERANDO_ID_TERPEL);                            
                        break; 
                        case 0xB7:  //Saldo                           
                        	flowDisplay4 = 27;
                        	numberKeys4 = 0;    
                            side.d.ActivoFideliza = 3;   
                            side.d.RFstateReport = 3;
                            bufferDisplay4.FidelConf = 0;
                            counter4 = 0;
                        	SetPicture(2, DISPLAY_ESPERANDO_ID_TERPEL);                                                                                  
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            SetPicture(2, DISPLAY_INICIO0);                            
                        break;
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                        break;
                    }                    
                }             
                Display2_ClearRxBuffer();
            }                        
        break;
            
        case 26:
            counter ++;
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay4.idSerial[x] = 0x00;
            }
            if(code_pirata(magneticReader[2],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){                    
				    bufferDisplay4.idSerial[x-1] = temporal[x];                    
                }
                bufferDisplay4.idSerial[0] = x-2;
                // Authorization request
                SetPicture(2,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag4 = 2;
                flowDisplay4 = 14;
                bufferDisplay4.flagKeyboard = 4;
                numberKeys4 = 0;
                hiddenKeys = 5;
                controlChar ='*';
                counter4 = 0;
                SetPicture(2,DISPLAY_INGRESE_PASSWORD);  
                Display2_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                
                Display2_ClearRxBuffer();
            } 
        break;
        
        case 27:
            counter ++;
            for(x = 0; x < 30; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 25; x++)
            {
                bufferDisplay4.idSerial[x] = 0x00;
            }
            if(code_pirata(magneticReader[2],'5') == 1)
            {	
                for (x = 2; x < 24; x++ ){
                    if(temporal[x] == 0x3F)
                        break;
				    bufferDisplay4.idSerial[x-1] = temporal[x];                    
                }
                bufferDisplay4.idSerial[0] = x-2;
                // Authorization request
                SetPicture(2,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                iButtonFlag4 = 1;
                flowDisplay4 = 14;
                bufferDisplay4.flagKeyboard = 7;
                numberKeys4 = 0;
                hiddenKeys = 5;
                controlChar ='*';
                SetPicture(2,DISPLAY_INGRESE_PASSWORD);  
                Display2_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            //SetPicture(2, DISPLAY_INICIO0);                          
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;                            
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            //SetPicture(2, DISPLAY_INICIO0);                            
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            AuthType4    = 0;
                            counter4     = 0;                            
                        break;
                    }                    
                }                
                Display2_ClearRxBuffer();
            }
        break;
        case 28:            
            side.d.rfState = RF_ASK_BALANCE;
            counter4++;
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4   = 0;
                            iButtonFlag4  = 0;
                            counter4      = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            ShiftState   = 0;
                            counter4     = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display2_ClearRxBuffer();             
        break;
        
        case 29:
            if(cardmessagedisplay == 1){
                for(x = 1; x < 31; x++)
                {
                    WriteMessage(2, Encabezado1[x],4,x-1,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 4; x < 31; x++)
                {
                    WriteMessage(2, Encabezado2[x],6,x-4,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++) //nombre
                {
                    WriteMessage(2, nombre[x],8,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 20; x++)
                {
                    WriteMessage(2, Company[x],8,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++) //placa
                {
                    WriteMessage(2, placa[x],10,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2, LicensePlate[x],10,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)//tarjeta
                {
                    WriteMessage(2,tarjeta[x],12,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 5; x++)
                {
                    WriteMessage(2,'*',12,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 3; x++)
                {
                    WriteMessage(2,cardNumberA[x],12,x+13,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)//saldo
                {
                    WriteMessage(2,saldo_d[x],14,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 18; x++)
                {
                    WriteMessage(2,BalanceA[x],14,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)//saldo aprobado
                {
                    WriteMessage(2,saldo_a[x],16,x,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
                for(x = 0; x < 18; x++)
                {
                    WriteMessage(2,BalanceB[x],16,x+8,1,0x0000,'Y');//WriteMessage(2, producto1[x],11,7+x,2,0x0000,'Y');
                }
            }
            if(cardmessagedisplay == 2)
            {
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage[x],6,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage1[x],8,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage2[x],10,x,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage3[x],12,x,1,0x0000,'Y');
                }
            }
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:
                            printBalance(EEPROM_1_ReadByte(9),side.d.dir);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            ShiftStateD  = 0; 
                            SetPicture(2, DISPLAY_INICIO0);
                        break;
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            ShiftStateD   = 0;
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display2_ClearRxBuffer();             
        break;
    ///////////////FIN CASOS PARA CRÉDITO  /////////////////////  
    
    //////////// CASOS PARA CONFIGURACIONES  ///////////////////
        case 12:
            counter4++;
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x46:  //Turnos 
							
                            flowDisplay4 = 13; 
                            if(EEPROM_1_ReadByte(223) == 1)
                            {
                                SetPicture(2,DISPLAY_CERRAR_TURNO);
                            }else
                            {
                                SetPicture(2,DISPLAY_ABRIR_TURNO);
                            } 
                            counter4 = 0;                           
                        break;
                        case 0x55:  //Configurar módulo 
                            flowDisplay4 = 14;
                            bufferDisplay4.flagKeyboard = 6;
                            numberKeys4 = 0;
                            hiddenKeys = 5;
                            controlChar ='*';
                            counter4 = 0;
                            SetPicture(2,DISPLAY_INGRESE_PASSWORD); 
                            Display2_ClearRxBuffer();
                        break;
                            
                        case 0xB5:  //Copia de recibo                             
                            side.d.RFstateReport = 1;
                            counter4 = 0;
                            side.d.rfStateCopy = RF_COPY_RECEIPT;
                            SetPicture(2,DISPLAY_IMPRIMIENDO_RECIBO);                       
                            flowDisplay4  = 23;
                            bufferDisplay4.PrintCopy = 1;
                            Display2_ClearRxBuffer();                            
                        break;
                        
                        case 0x3B:  //Pantalla Inicial    
                            flowDisplay4 = 0;
                            SetPicture(2,DISPLAY_INICIO0); 
                            Display2_ClearRxBuffer();
                        break;
                            
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            counter4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            counter4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            Display2_ClearRxBuffer();
                        break;
                    }
                }  
                
                vTaskDelay( 10 / portTICK_PERIOD_MS ); 
                Display2_ClearRxBuffer();
            }
        break;

        case 13:  //Pantalla de apertura/Cierre de turno
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x47:  //Cambio de turno: Abrir  
                            flowDisplay4 = 9;
                            numberKeys4 = 0;    
                            bufferDisplay4.flagKeyboard = 4;
                            SetPicture(2,DISPLAY_INTRODUZCA_CEDULA); 
                            Display2_ClearRxBuffer();
                        break;
                        case 0x48:  //Cambio de turno: Cerrar 
                            flowDisplay4 = 9;
                            numberKeys4 = 0;   
                            bufferDisplay4.flagKeyboard = 4;
                            SetPicture(2,DISPLAY_INTRODUZCA_CEDULA);  
                            Display2_ClearRxBuffer();
                        break;                         
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }
                
                vTaskDelay( 10 / portTICK_PERIOD_MS ); 
                Display2_ClearRxBuffer();
            }                        
        break; 
            
        case 14: //Teclado general      
            switch (alphanumeric_keyboard4(hiddenKeys,controlChar))
            {
                case 0: //Cancelar
                    switch(bufferDisplay4.flagKeyboard)
                    {
                        case 1://ID Estacion                            
                            for(x = 0; x <= 4; x++)
                            {
                                idStation[x] = 0;
                            }                            
                            flowDisplay4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 2://Umbral                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                pumpGap[x] = 0;
                            }                            
                            flowDisplay4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 3://Pass turno                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.shiftPassword[x] = 0;
                            }
                            
                            flowDisplay4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 4://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.passCard[x] = 0;
                            }
                            flowDisplay4 = 0;
                        break;
                        case 5://Pass
                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.shiftPassword[x] = 0;
                            }
                            
                            flowDisplay4 = 0;
                            ShiftStateD  = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                            
                        case 6://Pass
                            
                            for(x = 1; x <= configAccess[0]; x++)
                            {
                                configAccess[x] = 0;
                            }
                            
                            flowDisplay4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 7://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.passCard[x] = 0;
                            }
                            flowDisplay4 = 0;
                        break;
                        case 8://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.passCard[x] = 0;
                            }
                            flowDisplay4 = 0;
                        break;
                        case 9://Pass card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.valueKeys[x] = 0;
                            }
                            flowDisplay4 = 0;
                        break;
                    }                    
                    Display2_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay4.flagKeyboard)
                    {   
                        case 1://ID Estacion
                            
                            for(x = 0; x <= 4; x++)
                            {
                                idStation[x] = bufferDisplay4.valueKeys[x + 1];                                
                            }
                            
                            idStation[4] = 0x00;
                            intIDStation = atoi(idStation);
                            IDCast[0] = intIDStation;
                            IDCast[1] = intIDStation >> 8;
                            EEPROM_1_WriteByte(IDCast[0],10);
                            EEPROM_1_WriteByte(IDCast[1],11);
                            flowDisplay4 = 15;
                            SetPicture(2,DISPLAY_CONFIGURACIONES);
                        break;
                        case 2://Umbral
                            
                            for(x = 1; x <= bufferDisplay4.valueKeys[0]; x++)
                            {
                                pumpGap[x] = bufferDisplay4.valueKeys[x] - 48;
                            }
                            
                            PositionGAP = 0;
                            
                            for(x = 1; x <= bufferDisplay4.valueKeys[0]; x++)
                            {
                                PositionGAP = pumpGap[x] + PositionGAP * 10;
                            }  
                            
                            side.a.RF = side.a.dir + PositionGAP;
                            side.b.RF = side.b.dir + PositionGAP;
                            side.c.RF = side.c.dir + PositionGAP;
                            side.d.RF = side.d.dir + PositionGAP;
                            
                            // Almacena posicion RF
                            EEPROM_1_WriteByte(side.a.RF,200);
                            EEPROM_1_WriteByte(side.b.RF,201);
                            EEPROM_1_WriteByte(side.c.RF,202);
                            EEPROM_1_WriteByte(side.d.RF,203);
                            
                            flowDisplay4 = 15;
                            SetPicture(2,DISPLAY_CONFIGURACIONES);
                        break;
                        case 3://Pass turno
                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.shiftPassword[x] = bufferDisplay4.valueKeys[x];
                            }
                            
                            flowDisplay4 = 19;
                            ShiftStateD = 1;
                            side.d.RFstateReport = 1;
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                        case 4://Pass Card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.passCard[x] = bufferDisplay4.valueKeys[x];
                            }
                            vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                            iButtonFlag4 = 2;
                            SetPicture(2, DISPLAY_FORMA_PROGRAMACION);
                            flowDisplay4 = 3;
                        break;
                        case 5://Pass
                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.shiftPassword[x] = bufferDisplay4.valueKeys[x];
                            }
                            
                            flowDisplay4 = 15;
                            SetPicture(2,DISPLAY_CONFIGURACIONES);
                        break; 
                        case 6://Pass                            
                            for(x = 1; x <= configAccess[0]; x++)
                            {
                                configAccess[x] = bufferDisplay4.valueKeys[x];
                            }                            
                            if(configAccess[1] == passwordPump[1] && configAccess[2] == passwordPump[2] && configAccess[3] == passwordPump[3] && configAccess[4] == passwordPump[4])
                            {                                
                                SetPicture(2,DISPLAY_PASSWORD_VALIDO);                               
                                vTaskDelay( 700 / portTICK_PERIOD_MS );
                                flowDisplay4 = 15;
                                SetPicture(2,DISPLAY_CONFIGURACIONES);
                            }else
                            {
                                SetPicture(2,DISPLAY_PASSWORD_INVALIDO);                               
                                vTaskDelay( 700 / portTICK_PERIOD_MS );
                                flowDisplay4 = 0;
                                SetPicture(2,DISPLAY_INICIO0);
                            }
                        break;
                        case 7://Pass Card
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.passCard[x] = bufferDisplay4.valueKeys[x];
                            }
                            side.d.RFstateReport = 2;
                            vTaskDelay( 500 / portTICK_PERIOD_MS );  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);
                            flowDisplay4 = 28;
                        break;
                        case 8://Pass Card forma pago                            
                            for(x = 0; x < hiddenKeys; x++)
                            {
                                bufferDisplay4.passCard[x] = bufferDisplay4.valueKeys[x];
                            }
                            side.d.RFstateReport = 5;
                            vTaskDelay( 500 / portTICK_PERIOD_MS );  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);
                            flowDisplay4 = 35;
                        break;
                        case 9://tiempo contador                            
                            for(x = 1; x < hiddenKeys + 1; x++)
                            {
                                TimeValue[x-1] = bufferDisplay4.valueKeys[x];
                            } 
                            TimeValue[2] = 0x00;
                            EEPROM_1_WriteByte(atoi(TimeValue),225); 
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);
                            vTaskDelay( 500 / portTICK_PERIOD_MS );   
                            flowDisplay4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                    }                    
                    Display2_ClearRxBuffer();
                break;
            }            
        break;
            
        case 15: // Menu de configuraciones
            counter4++;
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x82:  //ID Estacion  
                            flowDisplay4 = 14;
                            numberKeys4 = 0; 
                            controlChar = 0;
                            hiddenKeys  = 5;
                            counter4 = 0;
                            bufferDisplay4.flagKeyboard = 1;
                            SetPicture(2,DISPLAY_INTRODUZCA_VALOR);                            
                        break;
                        case 0x83:  //KM efectivo 
                            flowDisplay4 = 30;
                            counter4 = 0;
                            SetPicture(2,DISPLAY_KM_EFECTIVO);                            
                        break;
                        case 0x65:  //Test Impresoras 
                            flowDisplay4 = 16; 
                            counter4 = 0;
                            PrintTest();
                            SetPicture(2,DISPLAY_AMBAS_IMPRESORAS_FUNCIONANDO);                           
                        break;                        
                        case 0x5A:  //Umbral 
                            flowDisplay4 = 14;
                            numberKeys4 = 0;
                            controlChar = 0;
                            hiddenKeys  = 3;
                            counter4 = 0;
                            for(x = 0; x < 3; x++)
                            {
                                pumpGap[x]  = 0x00;
                            }
                            pumpGap[0]  = 2;
                            counter4 = 0;
                            bufferDisplay4.flagKeyboard = 2;
                            SetPicture(2,DISPLAY_INTRODUZCA_VALOR);                            
                        break;
                        case 0x5B:  //Lectores banda 
                            flowDisplay4 = 31;
                            counter4 = 0;
                            SetPicture(2,DISPLAY_LECTORES_BANDA);                            
                        break;
                        case 0x58:  //Hora y Fecha
                            flowDisplay4 = 14;
                            numberKeys4 = 0;                             
                            controlChar = 0;
                            hiddenKeys  = 3;
                            counter4 = 0;
                            TimeValue[0]= 0x00;
                            TimeValue[1]= 0x00;
                            TimeValue[2]= 0x00;
                            bufferDisplay4.flagKeyboard = 9;
                            SetPicture(2,DISPLAY_CONFIGURAR_FECHA_HORA);                           
                        break;
                        case 0x7E:  //Pantalla Inicial  
                            bufferDisplay4.flagPrint =  0;
                            counter4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial   
                            bufferDisplay4.flagPrint =  0;
                            counter4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS ); 
                Display2_ClearRxBuffer();
            }                        
        break; 
            
        case 16:  //Menu de impresoras 1
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x38:  //No funcionan  
                            flowDisplay4 = 17;
                            SetPicture(2,DISPLAY_IMPRESORA_NO_FUNCIONANDO);                            
                        break;
                        case 0x39:  //Si funcionan
                            flowDisplay4 = 15; 
                            EEPROM_1_WriteByte(1,8);
                            EEPROM_1_WriteByte(2,9);
                            SetPicture(2,DISPLAY_CONFIGURACIONES);
                        break;
                                               
                        case 0x7E:  //Pantalla Inicial  
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                        break;
                    }                    
                }
                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();
            }                        
        break;
            
        case 17:  //Menu de impresoras 2
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {
                        case 0x8C:  //1 no funciona  
                            flowDisplay4 = 15; 
                            EEPROM_1_WriteByte(2,8);
                            EEPROM_1_WriteByte(2,9);
                            SetPicture(2,DISPLAY_CONFIGURACIONES);                            
                        break;
                        case 0x8D:  //2 no funciona
                            flowDisplay4 = 15; 
                            EEPROM_1_WriteByte(1,8);
                            EEPROM_1_WriteByte(1,9);
                            SetPicture(2,DISPLAY_CONFIGURACIONES); 
                        break;
                            
                        case 0x8E:  //ninguna funciona
                            flowDisplay4 = 15; 
                            EEPROM_1_WriteByte(0,8);
                            EEPROM_1_WriteByte(0,9);
                            SetPicture(2,DISPLAY_CONFIGURACIONES); 
                        break;
                                               
                        case 0x7E:  //Pantalla Inicial 
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                        break;
                        case 0x94:  //Pantalla Inicial 
                            bufferDisplay4.flagPrint =  0;
                            SetPicture(2,DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();
            }                        
        break;
            
        case 18:  //Pantalla de ocnfiguracion de fecha y hora
            if(leer_hora() == 1)
            {
                WriteLCD(2,(((timeDownHandle[1] & 0x10) >> 4) + 48), 13, 8, 1, 0x0000, 'N');
                WriteLCD(2,((timeDownHandle[1] & 0x0F) + 48), 13, 9, 1, 0x0000, 'N');
                WriteLCD(2, ':', 13, 10, 1, 0x0000, 'N');
                WriteLCD(2,(((timeDownHandle[0] & 0xF0) >> 4) + 48), 13, 11, 1, 0x0000, 'N');
                WriteLCD(2,((timeDownHandle[0] & 0x0F) + 48), 13, 12, 1, 0x0000, 'N');               
            }
            if(leer_fecha() == 1)
            {                
                WriteLCD(2,(((dateDownHandle[0] & 0x30) >> 4) + 48), 21, 8, 1, 0x0000, 'N');
                WriteLCD(2,((dateDownHandle[0] & 0x0F) + 48), 21, 9, 1, 0x0000, 'N');
                WriteLCD(2, '/', 21, 10, 1, 0x0000, 'N');
                WriteLCD(2,(((dateDownHandle[1] & 0x10) >> 4) + 48), 21, 11, 1, 0x0000, 'N');
                WriteLCD(2,((dateDownHandle[1] & 0x0F) + 48), 21, 12, 1, 0x0000, 'N');
                WriteLCD(2, '/', 21, 13, 1, 0x0000, 'N');
                WriteLCD(2,(((dateDownHandle[2] & 0xF0) >> 4) + 48), 21, 14, 1, 0x0000, 'N');
                WriteLCD(2,((dateDownHandle[2] & 0x0F) + 48), 21, 15, 1, 0x0000, 'N');
            }
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                       

                        case 0x7E:  //Pantalla Inicial
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                        break;
                        case 0x94:  //Pantalla Inicial
                            bufferDisplay4.flagPrint =  0;
                            flowDisplay4 = 0;
                            SetPicture(2,DISPLAY_INICIO0);                            
                        break;
                    }                    
                }
                
                vTaskDelay( 10 / portTICK_PERIOD_MS );
                Display2_ClearRxBuffer();
            }                        
        break;
            
        case 19: // Pantalla esperando... (cierre o apertura de turno)           
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            ShiftState   = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            ShiftState   = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display2_ClearRxBuffer();
            
        break;
            
         // Credit NOT authorized
        case 21:            
            SetPicture(2, DISPLAY_AUTORIZACION_RECHAZADA);
            bufferDisplay4.flagPrint = 0;
            flowPosD     = 0;
            PresetFlag4  = 0;
            iButtonFlag4 = 0;
            counter4     = 0;
            for(x = 0; x < 9; x++)
            {
                FontSpace(2, mensaje[x],1+x,17);
                FontSpace(2, mensaje[x],1+x,21);                    
            }
            side.d.ActivoFideliza = 3;                                        
            side.d.RFstateReport = 3;
            bufferDisplay4.FidelConf = 0;
            side.d.rfState = RF_IDLE;
            vTaskDelay( 2000 / portTICK_PERIOD_MS );
            flowDisplay4 = 0;
            SetPicture(2, DISPLAY_INICIO0);
        break;
            
            // Wrong Grade handle
        case 22:            
            SetPicture(2, DISPLAY_AUTORIZACION_RECHAZADA);
            bufferDisplay4.flagPrint = 0;            
            for(x = 0; x < 8; x++)
            {                
                FontSpace(2, mensaje3[x],1+x,17);                                   
            }
            for(x = 0; x < 10; x++)
            {                
                FontSpace(2, mensaje4[x],1+x,21);                    
            }
            side.d.ActivoFideliza = 3;                                        
            side.d.RFstateReport = 3;
            bufferDisplay4.FidelConf = 0; 
            vTaskDelay( 2000 / portTICK_PERIOD_MS );
            flowDisplay4 = 0;
            AuthType4    = 0;
            counter4     = 0;
            SetPicture(2, DISPLAY_INICIO0);
        break;
        
        case 23: //Pantalla imprimiendo durante la copia de recibo
            if(bufferDisplay4.PrintCopy == 0)
            {
                CounterD = 0;
                //flowDisplay4 = 0;
                Display2_ClearRxBuffer();
            }
            else
            {
                if(CounterD < 100)  // 20 segundos de espera aprox.
                {
                    vTaskDelay( 100 / portTICK_PERIOD_MS );
                    CounterD++; 
                }
                else
                {
                    CounterD = 0;
                    flowDisplay4 = 0;               
                    Display2_ClearRxBuffer();
                } 
            }         
        break;
        //////////////////CASOS ADICIONALES CONFIGURACIÓN ///////
        case 30://KM efectivo
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {  
                        case 0x0A:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            ShiftStateD = 0;
                            KmCash[0] = 0x01;
                            KmCash[1] = 0x01;
                            WriteEeprom(500,KmCash);
                        break;
                        
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            ShiftStateC = 0;
                            KmCash[0] = 0x01;
                            KmCash[1] = 0x00;
                            WriteEeprom(500,KmCash);
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            ShiftStateD = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            ShiftStateD = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display2_ClearRxBuffer();            
        break;
            
        case 31://KM efectivo
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {  
                        case 0x0A:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            ShiftStateD = 0;
                            magneticReader[0] = 0x02;
                            magneticReader[1] = 'A';
                            magneticReader[2] = 'A';
                            WriteEeprom(503,magneticReader);
                        break;
                        
                        case 0x0B:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            ShiftStateC = 0;
                            magneticReader[0] = 0x02;
                            magneticReader[1] = 'A';
                            magneticReader[2] = 'B';
                            WriteEeprom(503,magneticReader);
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            ShiftStateD = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            ShiftStateD = 0;
                        break;
                    }                    
                }                
                vTaskDelay( 10 / portTICK_PERIOD_MS );              //Freertos delay
            }
            Display2_ClearRxBuffer();            
        break;
            
        ///////////////// CASOS FIDELIZACIÓN TERPEL /////////////        
        case 32: //Teclado general      
            switch (alphanumeric_keyboard4(keysTerpelD,0))
            {
                case 0: //Cancelar
                    switch(bufferDisplay4.flagKeyboard)
                    {                        
                        case 1://Cedula
                            
                            for(x = 0; x < keysTerpelD; x++)
                            {
                                bufferDisplay4.idTerpelFideliza[x] = 0;
                            }                            
                            flowDisplay4 = 0;
                            ShiftStateD  = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;   
                        case 2://Tarjeta para forma pago                            
                            for(x = 0; x < keysTerpelD; x++)
                            {
                                bufferDisplay4.idFormaPago[x] = 0;
                            }                            
                            flowDisplay4 = 0;
                            ShiftStateD  = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;                            
                        case 3://Tarjeta para forma pago                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay4.saleNumber[x] = 0;
                            }                            
                            flowDisplay4 = 0;
                            ShiftStateD = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 4://Tarjeta para forma pago                            
                            for(x = 0; x < 8; x++)
                            {
                                bufferDisplay4.MoneyPay[x] = 0;
                            }                            
                            flowDisplay4 = 0;
                            ShiftStateD = 0;
							side.d.RFstateReport = 7;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                        case 5://Tarjeta para forma pago                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay4.idFormaPago[x] = 0;
                            }                            
                            flowDisplay4 = 0;
                            ShiftStateD = 0;
							if(bufferDisplay4.idType == 6)
                                side.d.RFstateReport = 7;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                            
                        case 6://Tarjeta para forma pago                            
                            for(x = 0; x < 10; x++)
                            {
                                bufferDisplay4.PaymentNumber[x] = 0;
                            }                            
                            flowDisplay4 = 0;
                            ShiftStateD  = 0;
                            SetPicture(2,DISPLAY_INICIO0);
                        break;
                    }                    
                    Display2_ClearRxBuffer();
                break;
                    
                case 1: //Enter
                    switch(bufferDisplay4.flagKeyboard)
                    {                           
                        case 1://Datos fidelización                            
                            for(x = 0; x < keysTerpelD; x++)
                            {
                                bufferDisplay4.idTerpelFideliza[x] = bufferDisplay4.valueKeys[x];
                            }                            
                            flowDisplay4 = 35;  
                            if(side.d.ActivoRedencion == 1){
                                side.d.RFstateReport = 4;                                
                            }else{
                                side.d.RFstateReport = 2;                        
                                side.d.ActivoFideliza = 2;
                            }
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                        break;                            
                        case 2://LFM Forma de pago                            
                            for(x = 0; x < keysTerpelD; x++)
                            {
                                bufferDisplay4.idFormaPago[x] = bufferDisplay4.valueKeys[x];
                            }
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            for(x = 0; x < 21; x++)
                            {
                                bufferDisplay4.valueKeys[x] = 0x00;
                            }
                            flowDisplay4 = 14;    
                            hiddenKeys = 20;
                            controlChar ='*';
                            numberKeys4 = 0;
                            bufferDisplay4.flagKeyboard = 8;
                            SetPicture(2,DISPLAY_PASS_ALFNUM);
                        break;                            
                        case 3://numero de venta FP                            
                            for(x = 0; x < keysTerpelD; x++)
                            {
                                bufferDisplay4.saleNumber[x] = bufferDisplay4.valueKeys[x];
                            }                            
                            flowDisplay4 = 39;
                            SetPicture(2, DISPLAY_FORMA_DE_PAGO_TERPEL);
                        break;                            
                        case 4://valor voucher                             
                            for(x = 0; x < keysTerpelD + 1; x++)
                            {
                                bufferDisplay4.MoneyPay[x] = 0x00;
                            }
                            for(x = 1; x <= bufferDisplay4.valueKeys[0]; x++)
                            {
                                bufferDisplay4.MoneyPay[x-1] = bufferDisplay4.valueKeys[x];
                            }
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            writevalueB = atoi(bufferDisplay4.MoneyPay);
                            resB =(atoi(bufferDisplay4.saleValue)-atoi(bufferDisplay4.MoneyPayed));
                            if( abs(resB) >= writevalueB && writevalueB > 0 )
                            {
                                for(x = 0; x < keysTerpelD + 1; x++)
                                {
                                    bufferDisplay4.valueKeys[x] = 0x00;
                                }
                                flowDisplay4 = 32;
                                numberKeys4 = 0;
                                keysTerpelD = 20;
                                if(bufferDisplay4.idType == 6){
                                    bufferDisplay4.flagKeyboard = 5;
                                }else{
                                    for(x = 0; x < keysTerpelD; x++)
                                    {
                                        bufferDisplay4.idFormaPago[x] = 0x00;
                                    }
                                    bufferDisplay4.flagKeyboard = 6;
                                }
                                SetPicture(2, DISPLAY_PASAPORTE);
                            }else{                            
                                flowDisplay4 = 32;
                                numberKeys4 = 0;
                                keysTerpelD = 10;                            
                                bufferDisplay4.flagKeyboard = 4;                                
                                SetPicture(2, DISPLAY_INTRODUZCA_VALOR); 
                                WriteLCD(2,'$',3,2,1,0x0000,'N');
                            }
                        break;                            
                        case 5://pin voucher                           
                            for(x = 0; x < keysTerpelD; x++)
                            {
                                bufferDisplay4.idFormaPago[x] = bufferDisplay4.valueKeys[x];
                            }                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            side.d.RFstateReport = 5;                            
                            flowDisplay4 = 35;                                                                                    
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                        break;                            
                        case 6://numero de pago                           
                            for(x = 0; x < keysTerpelD; x++)
                            {
                                bufferDisplay4.PaymentNumber[x] = bufferDisplay4.valueKeys[x];
                            }                            
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            side.d.RFstateReport = 5;                            
                            flowDisplay4 = 35;                                                                                    
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                    }                    
                    Display2_ClearRxBuffer();
                break;
            }       
            Display2_ClearRxBuffer();
        break;
            
        case 33: // identificacion fidelizacion
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    counter4 = 0;
                    switch(Display2_rxBuffer[3])
                    {  
                        case 0x1A:  //Cedula
                            if(side.d.ActivoRedencion == 1 ){
                                bufferDisplay4.documentID = 3 ;
                                bufferDisplay4.idType = 5;
                                flowDisplay4 = 35;
                                side.d.RFstateReport = 4; 
                                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay4 = 32;
                                numberKeys4 = 0;
                                keysTerpelD = 16;
                                bufferDisplay4.idType = 3;
                                SetPicture(2, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay4.flagKeyboard = 1;    
                        break;
                        
                        case 0x1B:  //extranjería                                                        
                             if(side.d.ActivoRedencion == 1 ){
                                bufferDisplay4.documentID = 4 ;
                                bufferDisplay4.idType = 5;
                                flowDisplay4 = 35;
                                side.d.RFstateReport = 4; 
                                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay4 = 32;
                                numberKeys4 = 0;
                                keysTerpelD = 16;
                                bufferDisplay4.idType = 4;
                                SetPicture(2, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay4.flagKeyboard = 1;  
                        break;
                        case 0x1c: //PASAPORTE
                            if(side.d.ActivoRedencion == 1 ){
                                bufferDisplay4.documentID = 5;
                                bufferDisplay4.idType = 5;
                                flowDisplay4 = 35;
                                side.d.RFstateReport = 4; 
                                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay4 = 32;
                                numberKeys4 = 0;
                                keysTerpelD = 16;
                                bufferDisplay4.idType = 5;
                                SetPicture(2, DISPLAY_PASAPORTE);                             
                            }
                            bufferDisplay4.flagKeyboard = 1;                            
                        break;
                        case 0x1d: //Lifemiles                            
                            if(side.d.ActivoRedencion == 1 ){
                                bufferDisplay4.idType = 5;
                                bufferDisplay4.documentID = 2;
                                flowDisplay4 = 35;
                                side.d.RFstateReport = 4; 
                                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay4 = 40; 
                                bufferDisplay4.idType = 2;
                                SetPicture(2, DISPLAY_ID_LIFE_MILES);                                                             
                            }                                                                                     
                        break;
                        case 0x1e: //Tarjeta pre inscrita                            
                            if(side.d.ActivoRedencion == 1 ){
                                bufferDisplay4.documentID = 1;
                                bufferDisplay4.idType = 5;
                                flowDisplay4 = 35;
                                side.d.RFstateReport = 4;
                                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                            }else{
                                flowDisplay4 = 32;
                                numberKeys4 = 0;
                                keysTerpelD = 16;
                                bufferDisplay4.idType = 1;
                                SetPicture(2, DISPLAY_PASAPORTE);                             
                            }                            
                            bufferDisplay4.flagKeyboard = 1;                            
                        break;
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            ShiftStateD = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            ShiftStateD = 0;
                        break;
                    }                    
                }                                               
                Display2_ClearRxBuffer(); 
            }             
        break;
            
        case 34:
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay4.idTerpelFideliza[x] = 0x00;
            }
            if(code_pirata(magneticReader[2],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){
				    bufferDisplay4.idTerpelFideliza[x-1] = temporal[x];                    
                }
                bufferDisplay4.idTerpelFideliza[0] = x-2;
                // Authorization request
                SetPicture(2,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                flowDisplay4 = 35;  
                side.d.RFstateReport = 2;                        
                side.d.ActivoFideliza = 2;
                SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);                               
                Display2_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            AuthType4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            AuthType4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }                                
                Display2_ClearRxBuffer();
            }            
        break;
            
        case 35:            
            //Touch for return to init display
            //vTaskDelay( 2000 / portTICK_PERIOD_MS );   
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            side.d.ActivoFideliza = 3;
                            side.d.RFstateReport = 3;
                            bufferDisplay4.FidelConf = 0;
                            side.d.ActivoRedencion = 0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            side.d.ActivoFideliza = 3;
                            side.d.RFstateReport = 3;
                            bufferDisplay4.FidelConf = 0;
                            side.d.ActivoRedencion = 0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                        break;
                    }                    
                }
                Display2_ClearRxBuffer(); 
            }            
        break;
            
        case 36:    
            counter4 ++;
            side.d.ActivoFideliza = 0;
            side.d.RFstateReport = 0;
            if(validaclientefiel4 == 1){
                for(x = 0; x < 17; x++)
                {
                    WriteMessage(2,NameCustomer[x],4,x,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessageB[x],6,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage1B[x],8,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage2B[x],10,x+1,2,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage3B[x],12,x+1,2,0x0000,'Y');
                } 
            }
            if(validaclientefiel4 == 2){                
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessageB[x],6,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage1B[x],8,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage2B[x],10,x+1,1,0x0000,'Y');
                }
                for(x = 0; x < 25; x++)
                {
                    WriteMessage(2,cardmessage3B[x],12,x+1,1,0x0000,'Y');
                } 
            }
                       
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Usuario correcto                          
                            if(AuthType4 == 1){
                                flowDisplay4 =10;
                                SetPicture(2, DISPLAY_ID_TERPEL);
                            }else{
                                flowDisplay4 =3;
                                SetPicture(2, DISPLAY_FORMA_PROGRAMACION); 
                            }
                            side.d.ActivoFideliza = 3;
                            side.d.RFstateReport = 3;
                            if(validaclientefiel4 == 1){
                                bufferDisplay4.FidelConf = 1;
                            }else{
                                bufferDisplay4.FidelConf = 0;
                            }
                            counter4 = 0;
                        break;
                        case 0x0B:  //Usuario incorrecto                                                       
                            side.d.ActivoFideliza = 3;
                            flowDisplay4 = 33;
                            bufferDisplay4.FidelConf = 0;
                            side.d.RFstateReport = 3;
                            counter4 = 0;
                            SetPicture(2, DISPLAY_IDEN_FIDELIZACION);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            side.d.ActivoFideliza = 3;
                            side.d.RFstateReport = 3;
                            bufferDisplay4.FidelConf = 0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            counter4     = 0;
                        break;
                    }                    
                }
                Display2_ClearRxBuffer();   
            }                              
        break;
         
        case 38:
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x53:
                            bufferDisplay4.lastSale = true;
                            flowDisplay4 = 39;                            
                            SetPicture(2, DISPLAY_FORMA_DE_PAGO_TERPEL);
                        break;
                        case 0x54:  //Solicita teclado 
                            for(x = 0; x < 20; x++)
                            {
                                bufferDisplay4.valueKeys[x] = 0x00;
                            }
                            bufferDisplay4.lastSale = false;
                            flowDisplay4 = 32;
                            numberKeys4 = 0;
                            keysTerpelD = 10;                            
                            bufferDisplay4.flagKeyboard = 3;
                            SetPicture(2, DISPLAY_INTRODUZCA_VALOR);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4   = 0;
                            iButtonFlag4  = 0;
                        break;                                                                       
                    }                    
                }
                Display2_ClearRxBuffer();
            }            
        break;
            
        case 39: 
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x1A: //VOUCHER     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay4 = 35;
                            side.d.ActivoRedencion = 1;
                            side.d.RFstateReport = 4;
                            bufferDisplay4.idType = 6;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1B: //Sodexo     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay4 = 35;
                            side.d.ActivoRedencion = 1;
                            side.d.RFstateReport = 4;
                            bufferDisplay4.idType = 4;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1C: //MASTER     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay4 = 35;
                            side.d.ActivoRedencion = 1;
                            side.d.RFstateReport = 4;
                            bufferDisplay4.idType = 2;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);	
                        break;                        
                        case 0x1D:  //LIFEMILES                             
                            flowDisplay4 = 33;
                            side.d.ActivoRedencion = 1;  
                            SetPicture(2, DISPLAY_PAGO_LM);
                        break;
                        case 0x1E: //Debito     1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay4 = 35;
                            side.d.ActivoRedencion = 1;
                            side.d.RFstateReport = 4;
                            bufferDisplay4.idType = 3;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                        case 0x1F: //VISA    1.VISA 2.MASTER 3.Debito 4.SODEXO 5. LM 6.VOUCHER
                            flowDisplay4 = 35;
                            side.d.ActivoRedencion = 1;
                            side.d.RFstateReport = 4;
                            bufferDisplay4.idType = 1;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);	
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                        break;                                                                       
                    }                    
                }
                Display2_ClearRxBuffer();
            } 
        break;
        
        case 40:
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0xB6:
                            if(bufferDisplay4.idType ==2){
                                flowDisplay4 = 34;
                                SetPicture(2, DISPLAY_ESPERANDO_ID_TERPEL);
                            }
                            if(bufferDisplay4.idType =='F'){
                                flowDisplay4 = 42;
                                SetPicture(2, DISPLAY_ESPERANDO_ID_TERPEL);
                            }
                        break;
                        case 0xB7:  //Solicita teclado 
                            flowDisplay4 = 32;
                            numberKeys4 = 0;
                            keysTerpelD = 20;                                                        
                            SetPicture(2, DISPLAY_PASAPORTE);
                            if(bufferDisplay4.idType !='F'){
                                for(x = 0; x < 20; x++)
                                {
                                    bufferDisplay4.valueKeys[x] = 0x00;
                                }
                                bufferDisplay4.flagKeyboard = 1;                                
                            }else{
                                for(x = 0; x < 20; x++)
                                {
                                    bufferDisplay4.valueKeys[x] = 0x00;
                                }
                                bufferDisplay4.flagKeyboard = 2;                                
                            }
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                        break;
                            
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                        break;                                                    
                    }                    
                }                                
                Display2_ClearRxBuffer();
            }            
        break;
         
        case 41:  
            bufferDisplay4.saleNumber[0] = 9;
			for (x = 1; x < 10; x++){
                bufferDisplay4.saleNumber[x] = 0x00;
            }
            for(x = 0; x < 14; x++)
            {
                WriteMessage(2,NumSale[x],4,x+5,1,0x0000,'Y');
            }
            for(x = 0; x < 10; x++)
            {
                WriteMessage(2,cardmessageB[x],6,x+5,1,0x0000,'Y');
            }
            for(x = 1; x < 10; x++)
            {
                bufferDisplay4.saleNumber[x] = cardmessageB[x-1];                
            }
            if(bufferDisplay4.idType ==5){
                for(x = 0; x < 9; x++)
                {
                    WriteMessage(2,VolSale[x],8,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,cardmessage1B[x],10,x+5,1,0x0000,'Y');
                }
            }else{
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,MonSale[x],8,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,bufferDisplay4.MoneyPay[x],10,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 21; x++)
                {
                    WriteMessage(2,MonSalePayed[x],12,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,bufferDisplay4.MoneyPayed[x],14,x+5,1,0x0000,'Y');
                }                 
            }            
            if(bufferDisplay4.idType ==5){
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,MonSale[x],12,x+5,1,0x0000,'Y');
                }
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,bufferDisplay4.MoneyPay[x],14,x+5,1,0x0000,'Y');
                }  
                for(x = 0; x < 8; x++)
                {
                    WriteMessage(2,MilageSale[x],16,x+5,1,0x0000,'Y');
                }            
                for(x = 0; x < 6; x++)
                {
                    WriteMessage(2,cardmessage3B[x],18,x+5,1,0x0000,'Y');
                }
            }                            
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Monto correcto
                            if(bufferDisplay4.idType ==5){
                                flowDisplay4 = 40; 
                                bufferDisplay4.idType = 'F'; //forma pago
                                if(bufferDisplay4.documentID == 2){
                                    SetPicture(2, DISPLAY_ID_LIFE_MILES);  
                                }else{
                                    bufferDisplay4.flagKeyboard = 2;
                                    flowDisplay4 = 32;
                                    numberKeys4 = 0;
                                    keysTerpelD = 16;
                                    SetPicture(2, DISPLAY_PASAPORTE);
                                }  
                            }else{                            
                                flowDisplay4 = 32;
                                numberKeys4 = 0;
                                keysTerpelD = 10;                            
                                bufferDisplay4.flagKeyboard = 4;                                
                                SetPicture(2, DISPLAY_INTRODUZCA_VALOR); 
                                WriteLCD(2,'$',3,2,1,0x0000,'N');
                            }
                        break;
                        
                        case 0x0B:  //Monto incorrecto incorrecto                            
                            bufferDisplay4.flagPrint =  0;
                            bufferDisplay4.idType = 0x00;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
							if(bufferDisplay4.idType == 6)
                                side.c.RFstateReport = 7;
                            SetPicture(2, DISPLAY_INICIO0);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            bufferDisplay4.FidelConf = 0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                        break;
                    }                    
                }
                Display2_ClearRxBuffer();   
            }                              
        break;
         
        case 42:
            for(x = 0; x < 150; x++)
            {
                temporal[x] = 0x00;
            }
            for(x = 0; x < 150; x++)
            {
                bufferDisplay4.idFormaPago[x] = 0x00;
            }
            if(code_pirata(magneticReader[2],'5') == 1)
            {	
                for (x = 2; x < temporal[0]; x++ ){
				    bufferDisplay4.idFormaPago[x-1] = temporal[x];                    
                }
                bufferDisplay4.idFormaPago[0] = x-2;
                // Authorization request
                SetPicture(2,DISPLAY_ID_RECONOCIDO);                                                                 
                vTaskDelay( 500 / portTICK_PERIOD_MS );                       
                flowDisplay4 = 14;    
                hiddenKeys = 20;
                controlChar ='*';
                numberKeys4 = 0;
                bufferDisplay4.flagKeyboard = 8;
                SetPicture(2,DISPLAY_PASS_ALFNUM); 
                Display2_ClearRxBuffer();                                                                        									                                       
			}                     
            //Touch for return to init display
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                        
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            AuthType4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                        
                        case 0x94:  //Cancel Button                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            flowDisplay4 = 0;
                            bufferDisplay4.flagPrint =  0;
                            PresetFlag4 = 0;
                            iButtonFlag4 = 0;
                            AuthType4 = 0;
                            Display2_ClearRxBuffer();
                        break;
                    }                    
                }
                Display2_ClearRxBuffer();
            }            
        break;
                    
        case 43:                                                
            for(x = 0; x < 25; x++)
            {
                WriteMessage(2,cardmessageB[x],6,x+1,1,0x0000,'Y');
            }            
            for(x = 0; x < 25; x++)
            {
                WriteMessage(2,cardmessage1B[x],10,x+1,1,0x0000,'Y');
            }    
            for(x = 0; x < 25; x++)
            {
                WriteMessage(2,cardmessage2B[x],14,x+1,1,0x0000,'Y');
            }
            for(x = 0; x < 25; x++)
            {
                WriteMessage(2,cardmessage3B[x],18,x+1,1,0x0000,'Y');
            }
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Imprimir comprobante
                            printPayment(EEPROM_1_ReadByte(9),side.d.RF);
                            vTaskDelay( 500 / portTICK_PERIOD_MS ); 
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            SetPicture(2, DISPLAY_INICIO0); 
                            for(x = 0; x < 7; x++)
                            {
                                bufferDisplay4.saleValue[x] = 0x00;
                            }
                        break;
                        
                        case 0x0B:  //No imprimir comprobante                                                       
                            bufferDisplay4.idType = 0x00;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            SetPicture(2, DISPLAY_INICIO0);
                            for(x = 0; x < 7; x++)
                            {
                                bufferDisplay4.saleValue[x] = 0x00;
                            }
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            bufferDisplay4.FidelConf = 0;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            for(x = 0; x < keysTerpelD; x++)
                            {
                                bufferDisplay4.saleValue[x] = 0x00;
                            }
                        break;
                    }                    
                }
                Display2_ClearRxBuffer();         
            }                        
        break;
        
         case 44:
            if(Display2_GetRxBufferSize() == 8)
            {
                if((Display2_rxBuffer[0] == 0xAA) && (Display2_rxBuffer[6] == 0xC3) && (Display2_rxBuffer[7] == 0x3C))
                {
                    switch(Display2_rxBuffer[3])
                    {                                                                                                 
                        case 0x0A:  //Mas voucher
                            bufferDisplay4.lastSale = false;
                            flowDisplay4 = 35;
                            side.d.ActivoRedencion = 1;
                            side.d.RFstateReport = 4;
                            bufferDisplay4.idType = 6;  
                            SetPicture(2, DISPLAY_POR_FAVOR_ESPERE);
                        break;
                        
                        case 0x0B:  //Finalizar                                                       
                            side.d.RFstateReport = 6;                             
                            flowDisplay4 = 35;                                                                                    
                            SetPicture(2,DISPLAY_POR_FAVOR_ESPERE);
                        break;
                            
                        case 0x7E:  //Init Screen                                                        
                            SetPicture(2, DISPLAY_INICIO0);
                            bufferDisplay4.flagPrint =  0;
                            side.d.ActivoRedencion = 0;
							side.d.RFstateReport = 7;
                            flowPosD     = 0;
                            flowDisplay4 = 0;                            
                            PresetFlag4  = 0;
                            iButtonFlag4 = 0;
                            for(x = 0; x < keysTerpelD; x++)
                            {
                                bufferDisplay4.saleValue[x] = 0x00;
                            }
                        break;
                    }                    
                }
                Display2_ClearRxBuffer();
            } 
        break;
    }    
}


/*
 * Actualiza los precios con los valores almacenados en la memoria
 */
void ReadPPUFromEEprom(void)
{
    uint8 i, x;
                               
    //PPU recovery from EEprom
        for(i = 0; i <  side.a.hoseNumber; i++)
        {   
            if(i == 0)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.a.ppuAuthorized[0][x] =  EEPROM_1_ReadByte(20 + x); //PPU to EEprom
                }
            }
            
            if(i == 1)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.a.ppuAuthorized[1][x] =  EEPROM_1_ReadByte(25 + x); //PPU to EEprom
                }
            }
            if(i == 2)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.a.ppuAuthorized[2][x] =  EEPROM_1_ReadByte(30 + x); //PPU to EEprom
                }
            }
            if(i == 3)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.a.ppuAuthorized[3][x] =  EEPROM_1_ReadByte(35 + x); //PPU to EEprom
                }
            }
                    
        }
        
        for(i = 0; i <  side.b.hoseNumber; i++)
        {   
            if(i == 0)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.b.ppuAuthorized[0][x] =  EEPROM_1_ReadByte(40 + x); //PPU to EEprom
                }
            }
            
            if(i == 1)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.b.ppuAuthorized[1][x] =  EEPROM_1_ReadByte(45 + x); //PPU to EEprom
                }
            }
            if(i == 2)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.b.ppuAuthorized[2][x] =  EEPROM_1_ReadByte(50 + x); //PPU to EEprom
                }
            }
            if(i == 3)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.b.ppuAuthorized[3][x] =  EEPROM_1_ReadByte(55 + x); //PPU to EEprom
                }
            }
                    
        }
        for(i = 0; i <  side.c.hoseNumber; i++)
        {   
            if(i == 0)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.c.ppuAuthorized[0][x] =  EEPROM_1_ReadByte(60 + x); //PPU to EEprom
                }
            }
            
            if(i == 1)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.c.ppuAuthorized[1][x] =  EEPROM_1_ReadByte(65 + x); //PPU to EEprom
                }
            }
            if(i == 2)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.c.ppuAuthorized[2][x] =  EEPROM_1_ReadByte(70 + x); //PPU to EEprom
                }
            }
            if(i == 3)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.c.ppuAuthorized[3][x] =  EEPROM_1_ReadByte(75 + x); //PPU to EEprom
                }
            }
                    
        }
        for(i = 0; i <  side.d.hoseNumber; i++)
        {   
            if(i == 0)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.d.ppuAuthorized[0][x] =  EEPROM_1_ReadByte(80 + x); //PPU to EEprom
                }
            }
            
            if(i == 1)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.d.ppuAuthorized[1][x] =  EEPROM_1_ReadByte(85 + x); //PPU to EEprom
                }
            }
            if(i == 2)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.d.ppuAuthorized[2][x] =  EEPROM_1_ReadByte(90 + x); //PPU to EEprom
                }
            }
            if(i == 3)
            {
                for(x = 0; x < 5 ; x++ )
                {
                    side.d.ppuAuthorized[3][x] =  EEPROM_1_ReadByte(95 + x); //PPU to EEprom
                }
            }
                    
        }
}


/*
 * Realiza el preset tanto en credito como en efectivo
 */
void PresetAuthorize(uint8 Position)
{
    uint8 x;
    side.a.changePPU = false;
    side.b.changePPU = false;
    side.c.changePPU = false;
    side.d.changePPU = false;

    if(Position == side.a.dir)
    {
    if(PresetFlag == 1)
    {
        //Detecta la manija subida 
        side.a.activeHose = PumpHoseActiveState(side.a.dir);
                
        //Habilita consulta de credito con el servidor
        if(iButtonFlag == 1 && side.a.activeHose == side.a.hose) 
        {
            CreditAuth = RF_CREDITSALEAUTH;
            side.a.RFstateReport = 1;
            iButtonFlag = 0;            
        }
        if(iButtonFlag == 2 && side.a.activeHose == side.a.hose) 
        {
            CreditAuth = RF_CREDITSALEAUTH;
            side.a.RFstateReport = 2;
            iButtonFlag = 0;            
        }
                    
        //iButton Autorizado
        if(Credit_Auth_OK == 1 && AuthType == 1)
        {
            if (side.a.activeHose == side.a.hose)
            {   
                //Cambia precio segun el nivel
                priceChange(side.a.dir, side.a.grade, ppuiButtonA);
                
                // PRESET
                if(PresetData(side.a.dir, side.a.activeHose, bufferDisplay1.CreditpresetValue[0], bufferDisplay1.CreditpresetType[0] & 0x03) == 1)
                {                                     
                    get_state(side.a.dir);
              
                    //Authoriza
                    Authorization(side.a.dir);                                                         
                    side.a.RFstateReport = 1;                                     
                    bufferDisplay1.flagActiveSale = true;
                    if(NumPositions == 4){
                        SetPicture(1, DISPLAY_DESPACHANDO);
                        vTaskDelay( 200 / portTICK_PERIOD_MS );
                        SetPicture(1, DISPLAY_SELECCIONE_POSICION);
                    }else{
                        SetPicture(1, DISPLAY_DESPACHANDO);
                        ShowMessage(1,(bufferDisplay1.CreditpresetValue[0]),18);
                    } 
                    flowDisplay1 = 8;
                    flowPos = flowDisplay1;
                    PresetFlag = 0;
                    Credit_Auth_OK = 0; 
                    // PPU                                                        
                    for(x = 0; x < 5 ; x++ )
                    {
                        ppuiButtonA[x] = 0x00;                            
                    }
                    return;
                }else
                {
                    flowDisplay1 = 0;
                    SetPicture(1, DISPLAY_ERROR);
                    vTaskDelay( 200 / portTICK_PERIOD_MS );
                    SetPicture(1, DISPLAY_INICIO0);
                    PresetFlag = 0;
                    AuthType = 0;
                    Credit_Auth_OK = 0;                    
                }
            }
        }            
           //Venta en efectivo
            if(AuthType == 2)
            {       
                //Grade selected  =  Grade pump handle
                if (side.a.activeHose == side.a.hose)
                {                                 
                    //Actualiza precios por el almacenado en la memoria
                    
                    ReadPPUFromEEprom();
                    priceChange(side.a.dir, side.a.activeHose - 1, side.a.ppuAuthorized[side.a.activeHose - 1]);
                    
                    // PRESET
                    if(PresetData(side.a.dir, side.a.hose, bufferDisplay1.presetValue[0], bufferDisplay1.presetType[0] & 0x03) == 1)
                    {                                           

                        get_state(side.a.dir);

                        //Authorize
                        Authorization(side.a.dir);                                                         
                        side.a.RFstateReport = 1;                  
                        bufferDisplay1.flagActiveSale = true;
                        if(NumPositions == 4){
                            SetPicture(1, DISPLAY_DESPACHANDO);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            SetPicture(1, DISPLAY_SELECCIONE_POSICION);
                        }else{
                            SetPicture(1, DISPLAY_DESPACHANDO);
                            ShowMessage(1,(bufferDisplay1.presetValue[1]),18);
                        }                    
                        flowDisplay1 = 8;
                        flowPos = 8;                    
                        PresetFlag = 0;                    
                        return;                      
                        
                    }else
                    {
                        flowDisplay1 = 0;
                        SetPicture(1, DISPLAY_ERROR);
                        vTaskDelay( 200 / portTICK_PERIOD_MS );
                        SetPicture(1, DISPLAY_INICIO0);
                        PresetFlag = 0;  
                        flowPos = 0;
                        return;                  
                        
                    }
                }
            }
        }
    }
    
    if(Position == side.b.dir)
    {
        if(PresetFlag2 == 1)
        {
            side.b.activeHose = PumpHoseActiveState(side.b.dir);  
            
            if(iButtonFlag2 == 1 && side.b.activeHose == side.b.hose)
            {
                CreditAuth2 = RF_CREDITSALEAUTH;
                side.b.RFstateReport = 1;
                iButtonFlag2 = 0;
            }
            if(iButtonFlag2 == 2 && side.b.activeHose == side.b.hose) 
            {
                CreditAuth2 = RF_CREDITSALEAUTH;
                side.b.RFstateReport = 2;
                iButtonFlag2 = 0;           
            }            
            //iButton Authorized Credit
            if(Credit_Auth_OK2 == 1 && AuthType2 == 1)
            {                          
                if (side.b.activeHose == side.b.hose)
                {   
                    priceChange(side.b.dir, side.b.grade, ppuiButtonB);
                    
                    if(PresetData(side.b.dir, side.b.activeHose, bufferDisplay2.CreditpresetValue[0], bufferDisplay2.CreditpresetType[0] & 0x03) == 1)
                    {                    
                        get_state(side.b.dir);

                        // Authorize
                        Authorization(side.b.dir);
                        side.b.RFstateReport = 1;                                        
        				bufferDisplay2.flagActiveSale = true;
                        if(NumPositions == 4){
                            SetPicture(2, DISPLAY_DESPACHANDO);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            SetPicture(2, DISPLAY_SELECCIONE_POSICION);
                        }else{
                            SetPicture(2, DISPLAY_DESPACHANDO);
                            ShowMessage(2,(bufferDisplay2.CreditpresetValue[0]),18);
                        } 
                        flowDisplay2 = 8;
                        flowPosB = flowDisplay2;
                        PresetFlag2 = 0;
                        // PPU                                                        
                        for(x = 0; x < 5 ; x++ )
                        {
                            ppuiButtonB[x] = 0x00;                            
                        }
                        return;
                        
                    }else
                    {
                        flowDisplay2 = 0;
                        SetPicture(2, DISPLAY_ERROR);
                        vTaskDelay(200 / portTICK_PERIOD_MS);
                        SetPicture(2, DISPLAY_INICIO0);
                        PresetFlag2 = 0;
                        AuthType2 = 0;
                        Credit_Auth_OK2 = 0;
                        return;
                        
                    }
                }
            }
            
             // Cash Sale
            if(AuthType2 == 2)
            {   
                //Grade selected  =  Grade pump handle                   
                if (side.b.activeHose == side.b.hose)
                {
                    ReadPPUFromEEprom();             
                    priceChange(side.b.dir, side.b.activeHose - 1, side.b.ppuAuthorized[side.b.activeHose - 1]);
                    
                    if(PresetData(side.b.dir, side.b.hose, bufferDisplay2.presetValue[0], bufferDisplay2.presetType[0] & 0x03) == 1)
                    {                    
                        get_state(side.b.dir);
                        //Authorize
                        Authorization(side.b.dir);
                        side.b.RFstateReport = 1;                       
        				bufferDisplay2.flagActiveSale = true;					
                        if(NumPositions == 4){
                            SetPicture(2, DISPLAY_DESPACHANDO);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            SetPicture(2, DISPLAY_SELECCIONE_POSICION);
                        }else{
                            SetPicture(2, DISPLAY_DESPACHANDO);
                            ShowMessage(2,(bufferDisplay2.presetValue[1]),18);
                        }
                        flowDisplay2 = 8;
                        flowPosB = flowDisplay2;
                        PresetFlag2 = 0;  
                        return;                
                        
                    }else
                    {
                        flowDisplay2 = 0;
                        SetPicture(2, DISPLAY_ERROR);
                        vTaskDelay(200 / portTICK_PERIOD_MS);
                        SetPicture(2, DISPLAY_INICIO0);
                        PresetFlag2 = 0;
                        return;                 
                        
                    }
                }
            }
        }
    }
    if(Position == side.c.dir)
    {
        if(PresetFlag3 == 1)
        {
            //Detecta la manija subida 
            side.c.activeHose = PumpHoseActiveState(side.c.dir);
                    
            //Habilita consulta de credito con el servidor
            if(iButtonFlag3 == 1 && side.c.activeHose == side.c.hose) 
            {
                CreditAuth3 = RF_CREDITSALEAUTH;
                side.c.RFstateReport = 1;
                iButtonFlag3 = 0;
                //side.c.rfState = RF_IDLE;                
            }
            if(iButtonFlag3 == 2 && side.c.activeHose == side.c.hose) 
            {
                CreditAuth3 = RF_CREDITSALEAUTH;
                side.c.RFstateReport = 2;
                iButtonFlag3 = 0;
                //side.a.rfState = RF_IDLE;            
            }
            
            //iButton Autorizado
            if(Credit_Auth_OK3 == 1 && AuthType3 == 1)
            {
                if (side.c.activeHose == side.c.hose)
                {   
                    //Cambia precio segun el nivel
                    priceChange(side.c.dir, side.c.grade, ppuiButtonA);
                    
                    // PRESET
                    if(PresetData(side.c.dir, side.c.activeHose, bufferDisplay3.CreditpresetValue[0], bufferDisplay3.CreditpresetType[0] & 0x03) == 1)
                    {                                     
                        get_state(side.c.dir);              
                        //Authoriza
                        Authorization(side.c.dir);                                                         
                        side.c.RFstateReport = 1;                    
                        bufferDisplay3.flagActiveSale = true;
                        if(NumPositions == 4){
                            SetPicture(1, DISPLAY_DESPACHANDO);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            SetPicture(1, DISPLAY_SELECCIONE_POSICION);
                        }else{
                            SetPicture(1, DISPLAY_DESPACHANDO);
                            ShowMessage(1,(bufferDisplay3.CreditpresetValue[1]),18);
                        }
                        flowDisplay3 = 8;
                        flowPosC = flowDisplay3;
                        PresetFlag3 = 0;
                        Credit_Auth_OK3 = 0; 
                        // PPU                                                        
                        for(x = 0; x < 5 ; x++ )
                        {
                            ppuiButtonA[x] = 0x00;                            
                        }
                    }else
                    {
                        flowDisplay3 = 0;
                        SetPicture(1, DISPLAY_ERROR);
                        vTaskDelay( 200 / portTICK_PERIOD_MS );
                        //SetPicture(1, DISPLAY_INICIO0);
                        PresetFlag3 = 0;
                        AuthType3 = 0;
                        Credit_Auth_OK3 = 0;                    
                    }
                }
            }
           //Venta en efectivo
            if(AuthType3 == 2)
            {       
                //Grade selected  =  Grade pump handle
                if (side.c.activeHose == side.c.hose)
                {                    
                        //Actualiza precios por el almacenado en la memoria
                    ReadPPUFromEEprom();
                    priceChange(side.c.dir, side.c.activeHose - 1, side.c.ppuAuthorized[side.c.activeHose - 1]);
                    
                    // PRESET
                    if(PresetData(side.c.dir, side.c.hose, bufferDisplay3.presetValue[0], bufferDisplay3.presetType[0] & 0x03) == 1)
                    {                                           
                        get_state(side.c.dir);        
                        //Authorize
                        Authorization(side.c.dir);                                                         
                        side.c.RFstateReport = 1;                            
                        bufferDisplay3.flagActiveSale = true;
                        if(NumPositions == 4){
                            SetPicture(1, DISPLAY_DESPACHANDO);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            SetPicture(1, DISPLAY_SELECCIONE_POSICION);
                        }else{
                            SetPicture(1, DISPLAY_DESPACHANDO);
                            ShowMessage(1,(bufferDisplay3.presetValue[1]),18);
                        }
                        flowDisplay3 = 8;
                        flowPosC = flowDisplay3;                             
                        PresetFlag3 = 0;
                        
                        return;                                                  
                    }else
                    {                                                        
                        SetPicture(1, DISPLAY_ERROR);
                        vTaskDelay( 200 / portTICK_PERIOD_MS );
                        //SetPicture(1, DISPLAY_INICIO0);
                        PresetFlag3 = 0;  
                        flowPosC = 0; 
                        flowDisplay3 = 0;
                        return;                  
                        
                    }
                }
            }
        }
    } 
    if(Position == side.d.dir)
    {
        if(PresetFlag4 == 1)
        {
            side.d.activeHose = PumpHoseActiveState(side.d.dir);  
            
            if(iButtonFlag4 == 1 && side.d.activeHose == side.d.hose)
            {
                CreditAuth4 = RF_CREDITSALEAUTH;
                side.d.RFstateReport = 1;
                iButtonFlag4 = 0;
                //side.d.rfState = RF_IDLE;
            }  
            if(iButtonFlag4 == 2 && side.d.activeHose == side.d.hose) 
            {
                CreditAuth4 = RF_CREDITSALEAUTH;
                side.d.RFstateReport = 2;
                iButtonFlag4 = 0;
                //side.a.rfState = RF_IDLE;            
            }
            //iButton Authorized Credit
            if(Credit_Auth_OK4 == 1 && AuthType4 == 1)
            {                          
                if (side.d.activeHose == side.d.hose)
                {   
                    priceChange(side.d.dir, side.d.grade, ppuiButtonB);                
                    if(PresetData(side.d.dir, side.d.activeHose, bufferDisplay4.CreditpresetValue[0], bufferDisplay4.CreditpresetType[0] & 0x03) == 1)
                    {                    
                        get_state(side.d.dir);
                        // Authorize
                        Authorization(side.d.dir);
                        side.d.RFstateReport = 1;                                        
        				bufferDisplay4.flagActiveSale = true;					
                        if(NumPositions == 4){
                            SetPicture(2, DISPLAY_DESPACHANDO);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            SetPicture(2, DISPLAY_SELECCIONE_POSICION);
                        }else{
                            SetPicture(2, DISPLAY_DESPACHANDO);
                            ShowMessage(2,(bufferDisplay4.CreditpresetValue[0]),18);
                        }
                        PresetFlag4 = 0;
                        flowDisplay4 = 8;
                        flowPosD = flowDisplay4;
                        for(x = 0; x < 5 ; x++ )
                        {
                            ppuiButtonB[x] = 0x00;                            
                        }
                        return;
                        
                    }else
                    {
                        flowDisplay4 = 0;
                        SetPicture(2, DISPLAY_ERROR);
                        vTaskDelay(200 / portTICK_PERIOD_MS);
                        SetPicture(2, DISPLAY_INICIO0);
                        PresetFlag4 = 0;
                        AuthType4 = 0;
                        Credit_Auth_OK4 = 0;
                        return;
                        
                    }
                }
            }        
             // Cash Sale
            if(AuthType4 == 2)
            {   
                //Grade selected  =  Grade pump handle                   
                if (side.d.activeHose == side.d.hose)
                {
                    if(!RFOnline)
                        side.d.grade = side.d.activeHose - 1;
                    ReadPPUFromEEprom();             
                    priceChange(side.d.dir, side.d.activeHose - 1, side.d.ppuAuthorized[side.d.activeHose - 1]);
                    
                    if(PresetData(side.d.dir, side.d.hose, bufferDisplay4.presetValue[0], bufferDisplay4.presetType[0] & 0x03) == 1)
                    {                    
                        get_state(side.d.dir);
                        //Authorize
                        Authorization(side.d.dir);
                        side.d.RFstateReport = 1;                                        
        				bufferDisplay4.flagActiveSale = true;					
                        if(NumPositions == 4){
                            SetPicture(2, DISPLAY_DESPACHANDO);
                            vTaskDelay( 200 / portTICK_PERIOD_MS );
                            SetPicture(2, DISPLAY_SELECCIONE_POSICION);
                        }else{
                            SetPicture(2, DISPLAY_DESPACHANDO);
                            ShowMessage(2,(bufferDisplay4.presetValue[1]),18);
                        } 
                        flowDisplay4 = 8;
                        flowPosD = flowDisplay4;                        
                        PresetFlag4 = 0;
                       
                        return;                
                        
                    }else
                    {
                        flowDisplay4 = 0;
                        SetPicture(2, DISPLAY_ERROR);
                        vTaskDelay(200 / portTICK_PERIOD_MS);
                        SetPicture(2, DISPLAY_INICIO0);
                        PresetFlag4 = 0;
                        return;                                     
                    }
                }
            }
        }
    }
}  

/* Display Task */
void Display_Task(void *arg)
{
   TickType_t xLastWakeTime;
    const TickType_t xFrequency = 10;
    
    xLastWakeTime = xTaskGetTickCount();
    selectPos   = 1;
    selectPosB  = 1;
    OSonline    = 1;
    counter     = 0;
    counter2    = 0;
    counter3    = 0;
    counter4    = 0;
    InitDisplay1();
    while(1) 
    {
        if(NumPositions <=2){
            flowDisplay3 = 0;
            flowDisplay4 = 0;
            PollingDisplay1();
            PollingDisplay2();   
        }
        if(NumPositions > 2)
        {               
            switch(selectPos){
                case 1:
                    PollingDisplay1();
                break;
                    
                case 2:
                    PollingDisplay3();
                break;                            
            }
            switch(selectPosB){
                case 1:
                    PollingDisplay2();
                break;
                    
                case 2:
                    PollingDisplay4();
                break;                            
            }
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

// Almacena las variables preset y placa para impresion
void DataPrinter(uint8 Position)
{
    uint8 x;
                  
    if(Position == side.a.dir)
    {
        //Preset
        for(x = 0; x < 10; x++)
        {
            bufferDisplay1.PrintPreset[0][x] = 0x00;
            bufferDisplay1.PrintPreset[1][x] = 0x00;
        }
        
        for(x = 0; x < 10; x++)
        {						   							
            bufferDisplay1.PrintPreset[0][x] = bufferDisplay1.presetValue[0][x];
            bufferDisplay1.PrintPreset[1][x] = bufferDisplay1.presetValue[1][x];
        }
        
        //Placa
        for(x = 0; x < 11; x++)
        {
    	    bufferDisplay1.PrintLicense[x] = 0x00;	
    	}
        
        for(x = 0; x < 11; x++)
        {
    	    bufferDisplay1.PrintLicense[x] = bufferDisplay1.licenceSale[x];	
    	}
        
        // tipo de transaccion
        bufferDisplay1.PrintType = 0;
        bufferDisplay1.PrintType = bufferDisplay1.presetType[1];
    }
  
    if(Position == side.b.dir)
    {
        //Preset
        for(x = 0; x < 10; x++)
        {
            bufferDisplay2.PrintPreset[0][x] = 0x00;
            bufferDisplay2.PrintPreset[1][x] = 0x00;
        }
        
        for(x = 0; x < 10; x++)
        {						   							
            bufferDisplay2.PrintPreset[0][x] = bufferDisplay2.presetValue[0][x];
            bufferDisplay2.PrintPreset[1][x] = bufferDisplay2.presetValue[1][x];
        }
        
        //Placa
        for(x = 0; x < 11; x++)
        {
    	    bufferDisplay2.PrintLicense[x] = 0x00;	
    	}
        
        for(x = 0; x < 11; x++)
        {
    	    bufferDisplay2.PrintLicense[x] = bufferDisplay2.licenceSale[x];	
    	}
        
        // tipo de transaccion
        bufferDisplay2.PrintType = 0;
        bufferDisplay2.PrintType = bufferDisplay2.presetType[1];
    }
    
    if(Position == side.c.dir)
    {
        //Preset
        for(x = 0; x < 10; x++)
        {
            bufferDisplay3.PrintPreset[0][x] = 0x00;
            bufferDisplay3.PrintPreset[1][x] = 0x00;
        }
        
        for(x = 0; x < 10; x++)
        {						   							
            bufferDisplay3.PrintPreset[0][x] = bufferDisplay3.presetValue[0][x];
            bufferDisplay3.PrintPreset[1][x] = bufferDisplay3.presetValue[1][x];
        }
        
        //Placa
        for(x = 0; x < 11; x++)
        {
    	    bufferDisplay3.PrintLicense[x] = 0x00;	
    	}
        
        for(x = 0; x < 11; x++)
        {
    	    bufferDisplay3.PrintLicense[x] = bufferDisplay3.licenceSale[x];	
    	}
        
        // tipo de transaccion
        bufferDisplay3.PrintType = 0;
        bufferDisplay3.PrintType = bufferDisplay3.presetType[1];
    }
    
    if(Position == side.d.dir)
    {
        //Preset
        for(x = 0; x < 10; x++)
        {
            bufferDisplay4.PrintPreset[0][x] = 0x00;
            bufferDisplay4.PrintPreset[1][x] = 0x00;
        }
        
        for(x = 0; x < 10; x++)
        {						   							
            bufferDisplay4.PrintPreset[0][x] = bufferDisplay4.presetValue[0][x];
            bufferDisplay4.PrintPreset[1][x] = bufferDisplay4.presetValue[1][x];
        }
        
        //Placa
        for(x = 0; x < 11; x++)
        {
    	    bufferDisplay4.PrintLicense[x] = 0x00;	
    	}
        
        for(x = 0; x < 11; x++)
        {
    	    bufferDisplay4.PrintLicense[x] = bufferDisplay4.licenceSale[x];	
    	}
        
        // tipo de transaccion
        bufferDisplay4.PrintType = 0;
        bufferDisplay4.PrintType = bufferDisplay4.presetType[1];
    }
}

void PumpAction(uint8 PositionPump, uint8 State)
{   
    uint8 x;
      
    // Current Loop recovery
    if(ActualState[PositionPump] == PUMP_FAIL && State != PUMP_FAIL)
    {
        flowDisplay1 = 0;
        flowDisplay2 = 0;
        flowDisplay3 = 0;
        flowDisplay4 = 0;
        //InitPump();
    }
    
    // Zero Sale detect
    if((ActualState[PositionPump] == PUMP_BUSY && State == PUMP_IDLE) || (ActualState[PositionPump] == PUMP_AUTHORIZED && State == PUMP_IDLE) || (ActualState[PositionPump] == PUMP_BUSY && State == PUMP_CALLING))
    {

            if(PositionPump == side.a.dir)
            {
                bufferDisplay1.flagPrint = 0;
                bufferDisplay1.zeroSend  = 1;
                flowDisplay1 = 0;                
                side.a.rfState = RF_ZERO_SALE;
                bufferDisplay1.flagActiveSale = false;
                ActualState[PositionPump] = State;
                flowPos = 0;
                pollTotals = 0;
				bufferDisplay1.PrintEnd = 0;
				side.a.FlagTotal = 0;
				bufferDisplay1.VarActual = 1;
                return;
            }
            if(PositionPump == side.b.dir)
            {
                bufferDisplay2.flagPrint = 0;
                bufferDisplay2.zeroSend  = 1;
                flowDisplay2 = 0;
                side.b.rfState = RF_ZERO_SALE;
                bufferDisplay2.flagActiveSale = false;
                ActualState[PositionPump] = State;
                flowPosB = 0;
                pollTotalsB = 0;
				bufferDisplay2.PrintEnd = 0;
				side.b.FlagTotal = 0;
				bufferDisplay2.VarActual = 1;
                return;
            }
            if(PositionPump == side.c.dir)
            {
                bufferDisplay3.flagPrint = 0;
                bufferDisplay3.zeroSend  = 1;
                flowDisplay3 = 0;
                side.c.rfState = RF_ZERO_SALE;
                bufferDisplay3.flagActiveSale = false;
                ActualState[PositionPump] = State;
                flowPosC = 0;
                pollTotalsC = 0;
				bufferDisplay3.PrintEnd = 0;
				side.c.FlagTotal = 0;
				bufferDisplay3.VarActual = 1;
                return;
            }
            if(PositionPump == side.d.dir)
            {
                bufferDisplay4.flagPrint = 0;
                bufferDisplay4.zeroSend  = 1;
                flowDisplay4 = 0;
                side.d.rfState = RF_ZERO_SALE;
                bufferDisplay4.flagActiveSale = false;                
                ActualState[PositionPump] = State;
                flowPosD = 0;
                pollTotalsD = 0;
				bufferDisplay4.PrintEnd = 0;
				side.d.FlagTotal = 0;
				bufferDisplay4.VarActual = 1;
                return;
            }
                         
    }

    //Actualize state
    ActualState[PositionPump] = State;
       
    switch(State)
    {
        case PUMP_FAIL:          
            
            SetPicture(1, DISPLAY_ERROR);
            SetPicture(2, DISPLAY_ERROR);
            side.a.rfState = RF_ERROR;
            side.b.rfState = RF_ERROR;
            side.c.rfState = RF_ERROR;
            side.d.rfState = RF_ERROR;
            InitDisplay1();
            InitDisplay2();
                         
        break;
        case PUMP_IDLE:

            if(PositionPump == side.a.dir)
            {   
                bufferDisplay1.flagActiveSale = false;
                flowPos = 0;
                side.a.rfState = RF_IDLE;                 
            }                    
            if(PositionPump == side.b.dir)
            {              			                
                bufferDisplay2.flagActiveSale = false;
                flowPosB = 0;
                side.b.rfState = RF_IDLE;                 
            }
            if(PositionPump == side.c.dir)
            {                               			                
                bufferDisplay3.flagActiveSale = false;
                flowPosC = 0;
                side.c.rfState = RF_IDLE;                 
            }
            if(PositionPump == side.d.dir)
            {                               			                
                bufferDisplay4.flagActiveSale = false;
                flowPosD = 0;
                side.d.rfState = RF_IDLE;                 
            }
                         
        break;
            
        case PUMP_CALLING:                            
            PresetAuthorize(PositionPump);                                                 
        break;
            
        case PUMP_AUTHORIZED:

        break;
            
        case PUMP_BUSY:          
                                 
                if(PositionPump == side.a.dir)
                {
                    bufferDisplay1.flagActiveSale = true;
                    bufferDisplay1.flagEndSale = false;
                    bufferDisplay1.PrintEnd = 1;
                    if(bufferDisplay1.saleType == 1) //efectivo
                    {
                        side.a.rfState = RF_DELIVERING;
                    }
                    else
                    {
                        if(side.b.BusyChange == 1)
                        {
                            side.a.rfState = RF_DELIVERING;
                        }
                    }              
                }
                if(PositionPump == side.b.dir)
                {
                    bufferDisplay2.flagActiveSale = true;
                    bufferDisplay2.flagEndSale = false;
                    bufferDisplay2.PrintEnd = 1;
                    if(bufferDisplay2.saleType == 1) //efectivo
                    {
                        side.b.rfState = RF_DELIVERING;
                    }
                    else
                    {
                        if(side.b.BusyChange == 1)
                        {
                            side.b.rfState = RF_DELIVERING;
                        }
                    }               
                }
                if(PositionPump == side.c.dir)
                {
                    bufferDisplay3.flagActiveSale = true;
                    bufferDisplay3.flagEndSale = false;
                    bufferDisplay3.PrintEnd = 1;
                    if(bufferDisplay3.saleType == 1) //efectivo
                    {
                        side.c.rfState = RF_DELIVERING;
                    }
                    else
                    {
                        if(side.c.BusyChange == 1)
                        {
                            side.c.rfState = RF_DELIVERING;
                        }
                    }               
                }
                if(PositionPump == side.d.dir)
                {
                    bufferDisplay4.flagActiveSale = true;
                    bufferDisplay4.flagEndSale = false;
                    bufferDisplay4.PrintEnd = 1;
                    if(bufferDisplay4.saleType == 1) //efectivo
                    {
                        side.d.rfState = RF_DELIVERING;
                    }
                    else
                    {
                        if(side.d.BusyChange == 1)
                        {
                            side.d.rfState = RF_DELIVERING;
                        }
                    }                 
                }      
        break;
        case PUMP_PEOT:            
            if(getSale(PositionPump))
            {
                if(PositionPump == side.a.dir)
                {  
                    
                    bufferDisplay1.flagEndSale = true;
                    side.a.RFstateReport = 1;
                    bufferDisplay1.EndSaleReport = 1;
                    
                    if(bufferDisplay1.saleType == 1)
                    {
                        if(RfActive)
                        {
                            side.a.grade = side.a.activeHose - 1;
                            if(bufferDisplay1.flagPrint == 1)
                            {                            
                                for(x = 0; x < 10; x++)                    //NUMERO DE VENTA
                                {   										    							
                    		        side.a.saleNumber[x] = 0x00;
                    	        }
                                DataPrinter(side.a.dir);                                                        
                            }
                            else
                            {                                                      
                                bufferDisplay1.PrintFlagEOT = 0;
                                bufferDisplay1.PrintEnd = 0;                          
                            }
                        }
                        else
                        {
                            if(bufferDisplay1.flagPrint == 1)
                            {
                                DataPrinter(side.a.dir);
                                bufferDisplay1.PrintFlagEOT     = 1;
                               
                            }else
                            {
                                bufferDisplay1.PrintFlagEOT = 0;
                                bufferDisplay1.PrintEnd = 0;
                             
                            }
                        }
                    }
                    
                    if(AuthType == 1)
                    { 
                        priceChange(side.a.dir, side.a.grade, side.a.ppuAuthorized[side.a.grade]);
                    }
                    AuthType = 0;
                    iButtonFlag = 0;
                    PresetFlag = 0;
                    flowDisplay1 = 0;
                    flowPos = 0;
                    bufferDisplay1.flagActiveSale   = false;
                    pollTotals = 1;                    
               }               
                if(PositionPump == side.b.dir)
                {                                                                               
                    bufferDisplay2.flagEndSale = true;
                    side.b.RFstateReport = 1;
                    bufferDisplay2.EndSaleReport = 1;           
                    
                    if(bufferDisplay2.saleType == 1)
                    {
                        if(RfActive)
                        {
                            side.b.grade = side.b.activeHose - 1;
                            if(bufferDisplay2.flagPrint == 1)
                            {
                                for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
                                {   										    							
                    		        side.b.saleNumber[x] = 0x00;
                    	        }
                                DataPrinter(side.b.dir);                                                        
                            }
                            else
                            {                   
                                bufferDisplay2.PrintFlagEOT = 0;
                                bufferDisplay2.PrintEnd = 0;                          
                            }
                        }
                        else
                        {
                            if(bufferDisplay2.flagPrint == 1)
                            {
                                DataPrinter(side.b.dir);
    							bufferDisplay2.PrintFlagEOT = 1;
                            }
                            else
                            {
                                bufferDisplay2.PrintFlagEOT = 0;
                                bufferDisplay2.PrintEnd = 0;
                            }
                        }
                    }              
                    if(AuthType2 == 1)
                    {
                        priceChange(side.b.dir, side.b.grade, side.b.ppuAuthorized[side.b.grade]);
                    }
                    AuthType2 = 0;
                    iButtonFlag2 = 0;
                    PresetFlag2 =0;        
                    pollTotalsB = 1;
                    flowDisplay2 = 0;
                    flowPosB = 0;
                    bufferDisplay2.flagActiveSale = false;
                    
                }        
                if(PositionPump == side.c.dir)
                {                                                         
                    
                    bufferDisplay3.flagEndSale = true;
                    side.c.RFstateReport = 1;
                    bufferDisplay3.EndSaleReport = 1;
                    if(bufferDisplay3.saleType == 1)
                    {
                        if(RfActive)
                        {
                            side.c.grade = side.c.activeHose - 1;
                            if(bufferDisplay3.flagPrint == 1)
                            {
                                for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
                                {   										    							
                    		        side.c.saleNumber[x] = 0x00;
                    	        }
                                DataPrinter(side.c.dir);
                                                          
                            }else
                            {                             
                                bufferDisplay3.PrintFlagEOT = 0;
                                bufferDisplay3.PrintEnd = 0; 
                            }
                        }
                        else
                        {
                            if(bufferDisplay3.flagPrint == 1)
                            {
                                DataPrinter(side.c.dir);
                                bufferDisplay3.PrintFlagEOT     = 1;
                            }
                            else
                            {
                                bufferDisplay3.PrintFlagEOT = 0;
                                bufferDisplay3.PrintEnd = 0;
                            }
                        }
                    }
                    if(AuthType3 == 1)
                    {
                        priceChange(side.c.dir, side.c.grade, side.c.ppuAuthorized[side.c.grade]);
                    }
                    AuthType3 = 0;
                    iButtonFlag3 = 0;
                    PresetFlag3 = 0;
                    pollTotalsC = 1;
                    flowDisplay3 = 0;
                    flowPosC = 0;
                    bufferDisplay3.flagActiveSale = false;
                    
                } 
                if(PositionPump == side.d.dir)
                {                                                          
                    
                    bufferDisplay4.flagEndSale = true;
                    side.d.RFstateReport = 1;
                    bufferDisplay4.EndSaleReport = 1;
                    
                    if(bufferDisplay4.saleType == 1)
                    {
                        if(RfActive)
                        {
                            side.d.grade = side.d.activeHose - 1;
                            if(bufferDisplay4.flagPrint == 1)
                            {
                                for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
                                {   										    							
                    		        side.d.saleNumber[x] = 0x00;
                    	        }
                                DataPrinter(side.d.dir);                            
                            }
                            else
                            {
                                bufferDisplay4.PrintFlagEOT = 0;
                                bufferDisplay4.PrintEnd = 0;                           
                            }
                        }
                        else
                        {
                            if(bufferDisplay4.flagPrint == 1)
                            {
                                DataPrinter(side.d.dir);
    							bufferDisplay4.PrintFlagEOT = 1;
                            }else
                            {
                                bufferDisplay4.PrintFlagEOT = 0;
                                bufferDisplay4.PrintEnd = 0;
                            }
                        }
                    }
                    if(AuthType4 == 1)
                    {
                        priceChange(side.d.dir, side.d.grade, side.d.ppuAuthorized[side.d.grade]);
                    }
                    
                    if(RfActive)
                    {
                        bufferDisplay4.VarActual = 1;
                    }
                    AuthType4 = 0;
                    iButtonFlag4 = 0;
                    PresetFlag4 = 0; 
                    pollTotalsD = 1;
                    flowDisplay4 = 0;
                    flowPosD = 0;
                    bufferDisplay4.flagActiveSale = false;
                    
                }                  
            }                       
        break;
            
        case PUMP_FEOT:            
            if(getSale(PositionPump))
            {
               if(PositionPump == side.a.dir)
               {    
                    bufferDisplay1.flagEndSale = true;
                    side.a.RFstateReport = 1;
                    bufferDisplay1.EndSaleReport = 1;                      
                    
                    if(bufferDisplay1.saleType == 1)
                    {
                        if(RfActive)
                        {
                            side.a.grade = side.a.activeHose - 1;
                            if(bufferDisplay1.flagPrint == 1)
                            {
                                for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
                                {   										    							
                    		        side.a.saleNumber[x] = 0x00;
                    	        }
                                DataPrinter(side.a.dir);
                                                           
                            }else
                            {                         
                                bufferDisplay1.PrintFlagEOT = 0;
                                bufferDisplay1.PrintEnd = 0;
                            }
                        }
                        else
                        {
                            if(bufferDisplay1.flagPrint == 1)
                            {
                                DataPrinter(side.a.dir);
                                bufferDisplay1.PrintFlagEOT     = 1;
                               

                            }else
                            {
                                bufferDisplay1.PrintFlagEOT = 0;
                                bufferDisplay1.PrintEnd = 0;
                            }
                        }
                    }
                    if(AuthType == 1)
                    {
                        priceChange(side.a.dir, side.a.grade, side.a.ppuAuthorized[side.a.grade]);
                    }
                    AuthType = 0;
                    iButtonFlag = 0;
                    PresetFlag = 0;
                    flowDisplay1 = 0;
                    flowPos = 0;
                    pollTotals = 1;
                    bufferDisplay1.flagActiveSale = false;
               }              
               if(PositionPump == side.b.dir)
               {                                                           
                     
                    bufferDisplay2.flagEndSale = true;
                    side.b.RFstateReport = 1;
                    bufferDisplay2.EndSaleReport = 1;  
                 
                    if(bufferDisplay2.saleType == 1)
                    {
                        if(RfActive)
                        {
                            side.b.grade = side.b.activeHose - 1;
                            if(bufferDisplay2.flagPrint == 1)
                            {
                                for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
                                {   										    							
                    		        side.b.saleNumber[x] = 0x00;
                    	        }
                                DataPrinter(side.b.dir);                                
                            }
                            else
                            {                                                     
                                bufferDisplay2.PrintFlagEOT = 0;
                                bufferDisplay2.PrintEnd = 0;                              
                            }
                        }
                        else
                        {
                            if(bufferDisplay2.flagPrint == 1)
                            {
                                DataPrinter(side.b.dir);
                                bufferDisplay2.PrintFlagEOT     = 1;

                            }else
                            {
                                bufferDisplay2.PrintFlagEOT = 0;
                                bufferDisplay2.PrintEnd = 0;
                            }
                        }
                    }
                    if(AuthType2 == 1)
                    {
                        priceChange(side.b.dir, side.b.grade, side.b.ppuAuthorized[side.b.grade]);
                    }
                    AuthType2 = 0;
                    iButtonFlag2 = 0;
                    PresetFlag2 = 0;
                    pollTotalsB = 1;
                    flowDisplay2 = 0;
                    flowPosB = 0;
                    bufferDisplay2.flagActiveSale = false;
                    
                }            
               if(PositionPump == side.c.dir)
               {                                                                               
                    bufferDisplay3.flagEndSale = true;
                    side.c.RFstateReport = 1;
                    bufferDisplay3.EndSaleReport = 1;
                    if(bufferDisplay3.saleType == 1)
                    {
                        if(RfActive)
                        {
                            side.c.grade = side.c.activeHose - 1;
                            if(bufferDisplay3.flagPrint == 1)
                            {
                                for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
                                {   										    							
                    		        side.c.saleNumber[x] = 0x00;
                    	        }
                                DataPrinter(side.c.dir);
                                
                            }else
                            {                          
                                bufferDisplay3.PrintFlagEOT = 0;
                                bufferDisplay3.PrintEnd = 0;
                            }
                        }
                        else
                        {
                            if(bufferDisplay3.flagPrint == 1)
                            {
                                DataPrinter(side.c.dir);
                                bufferDisplay3.PrintFlagEOT     = 1;                           
                            }
                            else
                            {
                                bufferDisplay3.PrintFlagEOT = 0;
                                bufferDisplay3.PrintEnd = 0;
                            }
                        }
                    }
                    if(AuthType3 == 1)
                    {
                        priceChange(side.c.dir, side.c.grade, side.c.ppuAuthorized[side.c.grade]);
                    }
                    AuthType3 = 0;
                    iButtonFlag3 = 0;
                    PresetFlag3 = 0;
                    pollTotalsC = 1;
                    flowDisplay3 = 0;
                    flowPosC = 0;
                    bufferDisplay3.flagActiveSale = false;
                    
                }                
               if(PositionPump == side.d.dir)
               {                                                                               
                    bufferDisplay4.flagEndSale = true;
                    side.d.RFstateReport = 1;
                    bufferDisplay4.EndSaleReport = 1;
                    
                    if(bufferDisplay4.saleType == 1)
                    {
                        if(RfActive)
                        {
                            side.d.grade = side.d.activeHose - 1;
                            if(bufferDisplay4.flagPrint == 1)
                            {
                                for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
                                {   										    							
                    		        side.d.saleNumber[x] = 0x00;
                    	        }
                                DataPrinter(side.d.dir);
                                
                            }
                            else
                            {                          
                                bufferDisplay4.PrintFlagEOT = 0;
                                bufferDisplay4.PrintEnd = 0;
                            }
                        }
                        else
                        {
                            if(bufferDisplay4.flagPrint == 1)
                            {
                                DataPrinter(side.d.dir);
                                bufferDisplay4.PrintFlagEOT     = 1;                                             
                            }
                            else
                            {
                                bufferDisplay4.PrintFlagEOT = 0;
                                bufferDisplay4.PrintEnd = 0;                         
                            }
                        }
                    }
                    if(AuthType4 == 1)
                    {
                        priceChange(side.d.dir, side.d.grade, side.d.ppuAuthorized[side.d.grade]);
                    }
                    if(RfActive)
                    {
                        bufferDisplay4.VarActual = 1;
                    }
                    AuthType4 = 0;
                    iButtonFlag4 = 0;
                    PresetFlag4 = 0;
                    pollTotalsD = 1;
                    flowDisplay4 = 0;
                    flowPosD = 0;
                    bufferDisplay4.flagActiveSale = false;
                }                 
            }         
        break;
            
        case PUMP_STOPPED:

        break;
            
        default:
        break;
    }   
    
}

bool LoopOpen(void)
{
    switch (NumPositions)
    {
        case 1:
            if(StatePosition[0] != 0)
            {
               return true;
            }
            else
            {
                return false;
            }
        break;
        case 2:
            if(StatePosition[0] != 0 && StatePosition[1] != 0)
            {
               
                return true;
            }
            else
            {
                RF_Connection_PutChar(side.a.pumpState);
                RF_Connection_PutChar(side.b.pumpState);
                return false;
            }      
        break;
        case 3: 
            if(StatePosition[0] != 0 && StatePosition[1] != 0 && StatePosition[2] != 0)
            {
               return true;
            }
            else
            {
                return false;
            }      
        break;
        case 4: 
            if(StatePosition[0] != 0 && StatePosition[1] != 0 && StatePosition[2] != 0 && StatePosition[3] != 0)
            {
               return true; 
            }
            else
            {
                return false;
            }      
        break;
        default:
            return false;
        break;
    }
}

void CheckInitState(void)
{
    uint8 i;
    
    for(i = 0; i < NumPositions; i++)
    {
        if(InitState[i] == PUMP_PEOT || InitState[i] == PUMP_FEOT)
        {
            flowDisplay1 = 0;
        }        
    }
}

void SetPPU(void)
{
    uint8 i;
  
    // PPU Change
        if(side.a.changePPU)
        {
            for(i = 0; i <  side.a.hoseNumber; i++)
            {   
                if(i == 0)
                {
                    if(priceChange(side.a.dir, i, side.a.ppuAuthorized[i]))
                    {
                        //side.a.changePPU = false;
                    }
                }
                if(i == 1)
                {
                    if(priceChange(side.a.dir, i, side.a.ppuAuthorized[i]))
                    {
                        //side.a.changePPU = false;
                    }
                }
                if(i == 2)
                {
                    if(priceChange(side.a.dir, i, side.a.ppuAuthorized[i]))
                    {
                        //side.a.changePPU = false;
                    }
                }
                if(i == 3)
                {
                    if(priceChange(side.a.dir, i, side.a.ppuAuthorized[i]))
                    {
                        //side.a.changePPU = false;
                    }
                }
            }  
        }
        
        if(side.b.changePPU)
        {
            for(i = 0; i <  side.b.hoseNumber; i++)
            {   
                if(i == 0)
                {
                    if(priceChange(side.b.dir, i, side.b.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
                if(i == 1)
                {
                    if(priceChange(side.b.dir, i, side.b.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
                if(i == 2)
                {
                    if(priceChange(side.b.dir, i, side.b.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
                if(i == 3)
                {
                    if(priceChange(side.b.dir, i, side.b.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
            }
        }
        
        if(side.c.changePPU)
        {
            for(i = 0; i <  side.c.hoseNumber; i++)
            {   
                if(i == 0)
                {
                    if(priceChange(side.c.dir, i, side.c.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
                if(i == 1)
                {
                    if(priceChange(side.c.dir, i, side.c.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
                if(i == 2)
                {
                    if(priceChange(side.c.dir, i, side.c.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
                if(i == 3)
                {
                    if(priceChange(side.c.dir, i, side.c.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
            }
        }
        
        if(side.d.changePPU)
        {
            for(i = 0; i <  side.d.hoseNumber; i++)
            {   
                if(i == 0)
                {
                    if(priceChange(side.d.dir, i, side.d.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
                if(i == 1)
                {
                    if(priceChange(side.d.dir, i, side.d.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
                if(i == 2)
                {
                    if(priceChange(side.d.dir, i, side.d.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
                if(i == 3)
                {
                    if(priceChange(side.d.dir, i, side.d.ppuAuthorized[i]))
                    {
                        //side.b.changePPU = false;
                    }
                }
            }
        }
   
    side.a.changePPU = false;
    side.b.changePPU = false;
    side.c.changePPU = false;
    side.d.changePPU = false;
}


/* Pump Task */
void Pump_Task(void *arg)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 1;
    uint8 i;
    
    xLastWakeTime = xTaskGetTickCount();
    
    // Vector State Init
    for(i = 0; i < 8; i++)
    {
        StatePosition[i] = 0x00;
    }
    
    CheckInitState();   
    ReadPPUFromEEprom();                       
    side.a.changePPU = true;
    side.b.changePPU = true;
    if(NumPositions == 4){
        side.c.changePPU = true;
        side.d.changePPU = true;
    }
    SetPPU();
       
    while(1) 
    {    
        
        // Polling 
        for(i = 0; i < NumPositions; i++)
        {               
            if(i == 0)
            {      
                StatePosition[0] = get_state(side.a.dir);
                side.a.pumpState = StatePosition[0];
            }
            if(i == 1)
            {
                StatePosition[1] = get_state(side.b.dir);
                side.b.pumpState = StatePosition[1];
            }
            if(i == 2)
            {
                StatePosition[2] = get_state(side.c.dir);
                side.c.pumpState = StatePosition[2];
            }
            if(i == 3)
            {
                StatePosition[3] = get_state(side.d.dir);
                side.d.pumpState = StatePosition[3];
            }       
        }
        
        // Detecting loop open
        if(LoopOpen())
        {
            for(i = 0; i < NumPositions; i++)
            {               
                if(i == 0)
                {                  
                    PumpAction(side.a.dir, StatePosition[i]);
                }
                if(i == 1)
                {              
                    PumpAction(side.b.dir, StatePosition[i]);
                }
                if(i == 2)
                {                
                    PumpAction(side.c.dir, StatePosition[i]);
                }
                if(i == 3)
                {                  
                    PumpAction(side.d.dir, StatePosition[i]);
                }       
            }      
        }else
        {
            PumpAction(side.a.dir, 0);           
        }    
     
        // Totals
        if(pollTotals == 1)
        {   
            if(getTotals(side.a.dir))
            {
                side.a.RFstateReport = 1;
                side.b.RFstateReport = 0;
                side.a.FlagTotal = 1;               
                pollTotals = 0;
            }
        }
        
        if(pollTotalsB == 1)
        {
            if(getTotals(side.b.dir))
            {
                side.b.RFstateReport = 1;
                side.a.RFstateReport = 0;
                side.b.FlagTotal = 1;
                pollTotalsB = 0;
            }
        }
        
        if(pollTotalsC == 1)
        {
            if(getTotals(side.c.dir))
            {
                side.c.RFstateReport = 1;
                side.d.RFstateReport = 0;
                side.c.FlagTotal = 1;
                pollTotalsC = 0;
            }
         }
 
        if(pollTotalsD == 1)
        {
           if(getTotals(side.d.dir))
           {
                side.c.RFstateReport = 0;
                side.d.RFstateReport = 1;
                side.d.FlagTotal = 1;
                pollTotalsD = 0;
           }                
        }
        
        if(side.a.changePPU || side.b.changePPU || side.c.changePPU || side.d.changePPU)
        {
            SetPPU();
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
/* [] END OF FILE */

