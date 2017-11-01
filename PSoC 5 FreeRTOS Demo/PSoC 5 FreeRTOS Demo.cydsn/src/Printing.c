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
#include <stdlib.h>
#include <string.h>
#include "Variables.h"
#include "I2C.h"
#include "protocol.h"
#include "Logos.h"

/* RTOS includes. */
#include <FreeRTOS.h>
#include <semphr.h>
#include "os_mutex.h"
#include "os_resource.h"


/*
*********************************************************************************************************
*                                            MENSAJES
*********************************************************************************************************
*/

uint8 msn_fecha[13]       = "Fecha      : ";
uint8 msn_hora[13]        = "Hora       : ";
uint8 msn_placa[13]       = "Placa      : ";
uint8 PRN_MILLEAGE[13]    = "Kilometraje: ";
uint8 PRN_TRANSTYPE[13]   = "Tipo       : ";
uint8 msn_pos[13]         = "Posicion   : ";
uint8 PRN_PRODUCT[13]     = "Producto   : ";
uint8 msn_ppu[13]         = "Ppu        : ";
uint8 msn_vol[15]         = "Volumen    : ";
uint8 msn_din[15]         = "Dinero     : ";
uint8 msn_numero[13]      = "Consecutivo: ";
uint8 PRN_BALANCE[13]     = "Saldo      : ";
uint8 PRN_COMPANY[13]     = "Empresa    : ";
uint8 PRN_ACCOUNT[13]     = "Cuenta     : ";
uint8 PRN_SERIAL[13]      = "Serial     : ";
uint8 PRN_ACCOUNTTYPE[13] = "Tipo Cuenta: ";
uint8 PRN_VISITSDAY[13]   = "Visitas Dia: ";
uint8 PRN_VISITSWEEK[13]  = "Visitas Sem: ";
uint8 PRN_VISITSMONTH[13] = "Visitas Mes: ";
uint8 PRN_VOLUMEDAY[13]   = "Volumen Dia: ";
uint8 PRN_VOLUMEWEEK[13]  = "Volumen Sem: ";
uint8 PRN_VOLUMEMONTH[13] = "Volumen Mes: ";
uint8 PRN_MONEYDAY[13]    = "Dinero Dia : ";
uint8 PRN_MONEYWEEK[13]   = "Dinero Sem : ";
uint8 PRN_MONEYMONTH[13]  = "Dinero Mes : ";
uint8 PRN_PRESET[13]      = "Valor Prog.: ";
uint8 PRN_SIGNATURE[13]   = "Firma      : ";
uint8 PRN_ID[13]          = "Cedula     : ";
uint8 PRN_CURRENCY[1]     = "$";
uint8 SEPARATOR[30]       = "******************************";



/*
*********************************************************************************************************
*                          				void print_logo_k(uint8 val, uint8 logo)
*
* Description : Envia por I2C los datos de los vectores de los logos. Usando impresora Kiosco
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

void printLogoK(uint8 val, uint8 logo){
	uint16 i;
	switch(logo){
		case 0:
			for(i=0;i<=1511;i++){
        		write_psoc1(val,biomax[i]);			
			}
		break;

		case 1:
			for(i=0;i<=1511;i++){
        		write_psoc1(val,brio[i]);			
			}
		break;			

		case 2:
			for(i=0;i<=1511;i++){
        		write_psoc1(val,cencosud[i]);			
			}
		break;	
			
		case 3:
			for(i=0;i<=1511;i++){
        		write_psoc1(val,ecospetrol[i]);			
			}
		break;

		case 4:
			for(i=0;i<=1511;i++){
        		write_psoc1(val,esso[i]);			
			}
		break;
			
		case 5:
			for(i=0;i<=944;i++){
        		write_psoc1(val,exito[i]);			
			}
		break;
			
		case 6:
//			for(i=0;i<=1511;i++){
//        		write_psoc1(val,National[i]);			
//			}
		break;	
			
		case 7:
			for(i=0;i<=944;i++){
        		write_psoc1(val,mineroil[i]);			
			}
		break;	
			
		case 8:
			for(i=0;i<=944;i++){
        		write_psoc1(val,mobil[i]);			
			}
		break;	
			
		case 9:
			for(i=0;i<=1511;i++){
        		write_psoc1(val,petrobras[i]);			
			}
		break;
			
		case 10:
			for(i=0;i<=755;i++){
        		write_psoc1(val,plus[i]);			
			}
		break;	
			
		case 11:
			for(i=0;i<=1511;i++){
        		write_psoc1(val,terpel[i]);			
			}
		break;
            
        case 12:
			for(i=0;i<=1511;i++){
        		write_psoc1(val,petromil[i]);			
			}
		break;
			
		case 13:
			for(i=0;i<=1511;i++){
        		write_psoc1(val,texaco[i]);			
			}
		break;	
			
		case 14:
			for(i=0;i<=755;i++){
        		write_psoc1(val,zeus[i]);			
			}
		break;
        
        case 15:
			for(i=0;i<=1511;i++){
        		write_psoc1(val,trebol[i]);			
			}
		break;
			
        case 255:
			
		break;
				
	}	
	write_psoc1(val,10);
	write_psoc1(val,0x1D);
	write_psoc1(val,0x4C);
	write_psoc1(val,0x07);
	write_psoc1(val,0x00);
	write_psoc1(val,10);
}

/*
*********************************************************************************************************
*                          				void print_logo_p(uint8 val, uint8 logo)
*
* Description : Envia por I2C los datos de los vectores de los logos. Para impresora panel
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

void printLogoP(uint8 val, uint8 logo){
	uint16 i;
	switch(logo){
		case 0:
			for(i=0;i<=943;i++){
        		write_psoc1(val,biomax1[i]);			
			}
		break;

		case 1:
			for(i=0;i<=943;i++){
        		write_psoc1(val,brio1[i]);			
			}
		break;			

		case 2:
			for(i=0;i<=943;i++){
        		write_psoc1(val,cencosud1[i]);			
			}
		break;	
			
		case 3:
			for(i=0;i<=943;i++){
        		write_psoc1(val,ecospetrol1[i]);			
			}
		break;

		case 4:
			for(i=0;i<=943;i++){
        		write_psoc1(val,esso1[i]);			
			}
		break;
			
		case 5:
			for(i=0;i<=943;i++){
        		write_psoc1(val,exito[i]);			
			}
		break;
			
		case 6:
			for(i=0;i<=943;i++){
        		write_psoc1(val,puma[i]);			
			}
		break;	
			
		case 7:
			for(i=0;i<=943;i++){
        		write_psoc1(val,mineroil1[i]);			
			}
		break;	
			
		case 8:
			for(i=0;i<=943;i++){
        		write_psoc1(val,mobil1[i]);			
			}
		break;	
			
		case 9:
			for(i=0;i<=943;i++){
        		write_psoc1(val,petrobras1[i]);			
			}
		break;
			
		case 10:
			for(i=0;i<=943;i++){
        		write_psoc1(val,plus1[i]);			
			}
		break;	
			
		case 11:
			for(i=0;i<=943;i++){
        		write_psoc1(val,terpel1[i]);			
			}
		break;
        
        case 12:
			for(i=0;i<=943;i++){
        		write_psoc1(val,petromil1[i]);			
			}
		break;
			
		case 13:
			for(i=0;i<=943;i++){
        		write_psoc1(val,texaco1[i]);			
			}
		break;	
			
		case 14:
			for(i=0;i<=943;i++){
        		write_psoc1(val,zeus1[i]);			
			}
		break;
        case 15:
			for(i=0;i<=943;i++){
        		write_psoc1(val,trebol1[i]);			
			}
		break;
            
        case 255:
			
		break;
			
				
	}	
	write_psoc1(val,0x1B);
	write_psoc1(val,0x40);
	write_psoc1(val,10);	
}


/*
*********************************************************************************************************
*                                         void imprimir(uint8 val)
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

void imprimir(uint8 val, uint8 pos){ //val, puerto de impresora
    uint8 x;  
    
    //Imprime LOGO
    if(pos == side.a.RF || pos == side.c.RF)
    {
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortA,EEPROM_1_ReadByte(215));    
        }else{
            printLogoK(printPortA,EEPROM_1_ReadByte(215));
        }
    }
    else //if(pos == side.b.RF || pos == side.d.RF)
    {
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortB,EEPROM_1_ReadByte(215));    
        }else{
            printLogoK(printPortB,EEPROM_1_ReadByte(215));
        }
    }
    
    write_psoc1(val,10);
    
    // Imprime encabezados
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado1[x]);
    }
    write_psoc1(val,10);
    
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado2[x]);
    }
    write_psoc1(val,10);
    
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado3[x]);
    }
    write_psoc1(val,10);
    
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado4[x]);
    }
    write_psoc1(val,10);
    
    LeerEeprom(200,31);
    for(x = 1; x <= 30; x++)
    {
        Encabezado5[x] = buffer_i2c[x];
        write_psoc1(val,Encabezado5[x]);
    }
    write_psoc1(val,10);
    
    for(x = 0; x < 30; x++)
    {
        write_psoc1(val,SEPARATOR[x]);
    }
    write_psoc1(val,10);
    for(x = 0; x < 13; x++)
    {										//FECHA								
		write_psoc1(val,msn_fecha[x]);
	}
    if(leer_fecha() == 1)
    {
		write_psoc1(val,(((dateDownHandle[0] & 0x30) >> 4) + 48));
		write_psoc1(val,((dateDownHandle[0] & 0x0F) + 48));
		write_psoc1(val,'/');
		write_psoc1(val,(((dateDownHandle[1] & 0x10) >> 4) + 48));
		write_psoc1(val,((dateDownHandle[1] & 0x0F) + 48));	
		write_psoc1(val,'/');
		write_psoc1(val,(((dateDownHandle[2] & 0xF0) >> 4) + 48));
		write_psoc1(val,((dateDownHandle[2] & 0x0F) + 48));			
	}		
    write_psoc1(val,10);
    for(x = 0;x < 13; x++)
    {										//HORA								
		write_psoc1(val,msn_hora[x]);
	}
    if(leer_hora() == 1)
    {										//HORA
		write_psoc1(val,(((timeDownHandle[1] & 0x30) >> 4) + 48));
		write_psoc1(val,((timeDownHandle[1] & 0x0F) + 48));
		write_psoc1(val,':');
		write_psoc1(val,(((timeDownHandle[0] & 0xF0) >> 4) + 48));
		write_psoc1(val,((timeDownHandle[0] & 0x0F) + 48));		
	}
    write_psoc1(val,10);
    for(x = 0; x < 30; x++)
    {
        write_psoc1(val,SEPARATOR[x]);
    }
    write_psoc1(val,10);
    ////////////////////// FIN DE ENCABEZADO ////////////////////////////////////////
    for(x = 0; x < 13; x++)
    {										                           //POSICION								
		write_psoc1(val,msn_pos[x]);
	}
    write_psoc1(val,((pos / 10) + 48));
	write_psoc1(val,((pos % 10) + 48));
    write_psoc1(val,10);
    
    
    for(x = 0; x < 13; x++)                                            //NUMERO DE VENTA
    {										    							
		write_psoc1(val,msn_numero[x]);
	}    	
    if(pos == side.a.RF)
    {
        for(x=0;x < 10;x++)
        {										                       //NUMERO DE VENTA							
    		write_psoc1(val,side.a.saleNumber[x]);
    	}
    }
    if(pos == side.b.RF)
    {
        for(x = 0; x < 10; x++)                                        //NUMERO DE VENTA
        {										    							
    		write_psoc1(val,side.b.saleNumber[x]);
    	}
    }
    if(pos == side.c.RF)
    {
        for(x = 0; x < 10; x++)                                        //NUMERO DE VENTA
        {										    							
    		write_psoc1(val,side.c.saleNumber[x]);
    	}
    }
    if(pos == side.d.RF)
    {
        for(x = 0; x < 10; x++)                                        //NUMERO DE VENTA
        {										    							
    		write_psoc1(val,side.d.saleNumber[x]);
    	}
    }
    write_psoc1(val,10);
    ////////////// DATOS DE VENTA /////////////////////////////
	if(pos == side.a.RF)
    {
        bufferDisplay1.flagPrint = 0;
        for(x = 0; x < 13; x++)                                     //Mensaje Producto	
        {																
    		write_psoc1(val,PRN_PRODUCT[x]);
    	}    	                        
        for(x = 0; x < 13; x++)                                     //Producto	
        {																
           write_psoc1(val,producto[side.a.GradesHose[side.a.hose] - 1][x]);
    	}                          

        
        write_psoc1(val,10);
        
        for(x = 0; x < 13; x++)                                     //PPU
        {																	
    		write_psoc1(val,msn_ppu[x]);
    	} 
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x2F);
        for(x = 0; x < 1; x++)                                      //Simbolos $/G
        {																	
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,0x20);
        
        if(digits >= 7)
        {
            if(side.a.ppuSale[2] == 0x30)
                side.a.ppuSale[2] = 0x00;
            for(x = 2; x <= side.a.ppuSale[0]; x++)
            {                                    
        		write_psoc1(val,side.a.ppuSale[x]);
        	}
        }else{
            if (ppux10 ==1){
                if(side.a.ppuSale[1]== 0x30)
                    side.a.ppuSale[1]= 0x00;
            }
            for(x = 1; x <= side.a.ppuSale[0]; x++)
            {						   							
        		write_psoc1(val,side.a.ppuSale[x]);
        	}
        }
        
        write_psoc1(val,10);
        
        
        for(x = 0; x < 13; x++)                                     //Volumen
        {																	
    		write_psoc1(val,msn_vol[x]);
    	} 
        
        for(x = 0; x < 1; x++)                                      //Simbolos $/G
        {																	
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,0x20);
        if (digits < 7){
            ///////////////////////////////////////////////////////////////
            if(side.a.volumeSale[1] == 0x30)
                side.a.volumeSale[1] = 0x00;
            if(side.a.volumeSale[1] == 0x00 && side.a.volumeSale[2] == 0x30)
                side.a.volumeSale[2] = 0x00;
            ///////////////////////////////////////////////////////////////
            for(x = side.a.volumeSale[0]; x >= 1 ;x--)
            {						   							
                write_psoc1(val,side.a.volumeSale[side.a.volumeSale[0]+ 1 - x]);
                if(x == VolDec + 1)
                    write_psoc1(val,',');
        	}
        }
        else{
            ///////////////////////////////////////////////////////////////
            for (x = 1; x < 5; x++ )
            {
                if (side.a.volumeSale[x] != 0x30)
                    break;
                if (side.a.volumeSale[x] == 0x30)
                {
                    side.a.volumeSale[x] = 0x00;                   
                }                
            }
            ///////////////////////////////////////////////////////////////
            for(x = side.a.volumeSale[0]; x >= 1 ;x--)
            {						   							
                write_psoc1(val,side.a.volumeSale[side.a.volumeSale[0]+ 1 - x]);
                if(x == VolDec+1)
                    write_psoc1(val,',');
        	}
        }

        write_psoc1(val,10);
       
        for(x = 0; x < 13; x++)                                     //Dinero
        {																	
    		write_psoc1(val,msn_din[x]);
    	}
        
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x20);
        if (digits < 7){
            /////////////////////////////////////////////////////////////
            if(side.a.moneySale[1] == 0x30)
                side.a.moneySale[1] = 0x00;
            if(side.a.moneySale[1] == 0x00 && side.a.moneySale[2] == 0x30)
                side.a.moneySale[2] = 0x00;
            /////////////////////////////////////////////////////////////
            for(x = 1; x <= side.a.moneySale[0]; x++)
            {						   							
        		write_psoc1(val,side.a.moneySale[x]);
                if(x == MoneyDec)
                    write_psoc1(val,',');
        	}
        }
        else{
            /////////////////////////////////////////////////////////////
            for (x = 1; x < 8; x++ )
            {
                if (side.a.moneySale[x] != 0x30)
                    break;
                if (side.a.moneySale[x] == 0x30)
                {
                    side.a.moneySale[x] = 0x00;                   
                }                
            }
            /////////////////////////////////////////////////////////////
            for(x = 1; x <= side.a.moneySale[0]; x++)
            {						   							
        		write_psoc1(val,side.a.moneySale[x]);
                if(x == MoneyDec)
                    write_psoc1(val,',');
        	}
            
        }
        write_psoc1(val,10);
        
        if(bufferDisplay1.saleType == 1) //Venta en efectivo
        {
    		for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val, msn_placa[x]);                          //PLACA
    		} 
    		for(x = 1; x <= bufferDisplay1.PrintLicense[0]; x++)
            {
    			write_psoc1(val,bufferDisplay1.PrintLicense[x]);	
    		}
            
            for(x = 0; x < 11; x++)
            {
    			bufferDisplay1.PrintLicense[x] = 0x00;	
    		}            
            write_psoc1(val,10);
			if(KmCash[1] == 0x01){
                for(x = 0; x < 13; x++)
                {																		
    				write_psoc1(val,PRN_MILLEAGE[x]);    //Km opcional en efectivo
    			}	
    			for(x = 1; x <= bufferDisplay1.mileageSale[0]; x++)
                {
    				write_psoc1(val,bufferDisplay1.mileageSale[x]);	
    			}
                write_psoc1(val,10);
            }
           
            for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val, PRN_PRESET[x]);                          //Preset
    		} 
            
            write_psoc1(val,bufferDisplay1.PrintType);
            write_psoc1(val,' ');
            if (digits < 7)
            {
                if(bufferDisplay1.presetType[0] == 1)
                {
                    if(bufferDisplay1.PrintPreset[0][1] == 0x30)
                        bufferDisplay1.PrintPreset[0][1] = 0x00;
                    if(bufferDisplay1.PrintPreset[0][1] == 0x00 && bufferDisplay1.PrintPreset[0][2] == 0x30)
                        bufferDisplay1.PrintPreset[0][2] = 0x00;


                        if(bufferDisplay1.PrintPreset[0][1] == 0x00 && bufferDisplay1.PrintPreset[0][2] == 0x00 && bufferDisplay1.PrintPreset[0][3] == 0x30)
                            bufferDisplay1.PrintPreset[0][3] = 0x00;


                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay1.PrintPreset[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay1.PrintPreset[0][bufferDisplay1.PrintPreset[0][0]+ 1 - x]);
                        if(ppux10 == 1){
                            if(x == VolDec)
                                write_psoc1(val,'.');
                        }else{
                            if(x == VolDec)

                                write_psoc1(val,'.');
                        }
                	}                    
                }
                else{
                    ///////////////////////////////////////////////////////////////
                    for (x = 1; x < 5; x++ )
                    {
                        if (bufferDisplay1.PrintPreset[0][x] != 0x30)
                            break;
                        if (bufferDisplay1.PrintPreset[0][x] == 0x30)
                        {
                            bufferDisplay1.PrintPreset[0][x] = 0x00;                   

                        }                
                    }
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay1.PrintPreset[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay1.PrintPreset[0][bufferDisplay1.PrintPreset[0][0]+ 1 - x]);
                        if(x == VolDec+1)
                            write_psoc1(val,'.');
                	}                    
                }        	    
            }else
            {
                if(bufferDisplay1.presetType[0] == 1)
                {
                    if(bufferDisplay1.PrintPreset[1][1] == 0x00)
                        bufferDisplay1.PrintPreset[1][1] = 0x30;
                   // if(bufferDisplay1.PrintPreset[1][1] == 0x00 && bufferDisplay1.PrintPreset[1][2] == 0x30)
                    //    bufferDisplay1.PrintPreset[1][2] = 0x00;
                    
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay1.PrintPreset[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay1.PrintPreset[1][bufferDisplay1.PrintPreset[1][0]+ 1 - x]);
                        //if(x == VolDec + 1)
                           // write_psoc1(val,'.');
                	}
                }
                else{                                        
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay1.PrintPreset[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val, bufferDisplay1.PrintPreset[1][bufferDisplay1.PrintPreset[1][0]+ 1 - x]);

                	}
                }                                        
            }

            write_psoc1(val,10);
        }                
  	    if(bufferDisplay1.saleType == 2) //Venta en credito
        {		
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MILLEAGE[x]);
			}	
			for(x = 1; x <= bufferDisplay1.mileageSale[0]; x++)
            {
				write_psoc1(val,bufferDisplay1.mileageSale[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 11; x++)
            {
				bufferDisplay1.mileageSale[x] = 0x00;	
			}		

			for(x= 0;x < 13;x++)
            {										//DATOS IBUTTON								
				write_psoc1(val,PRN_SERIAL[x]);
			} 
			for(x = 1; x <= bufferDisplay1.idSerial[0]; x++)
            {
				write_psoc1(val,bufferDisplay1.idSerial[x]);	
			}			
			write_psoc1(val,10);
            
            for(x = 0; x < 25; x++)
            {
				bufferDisplay1.idSerial[x] = 0x00;
			}
            
			for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, msn_placa[x]);
			}  
           
			for(x = 0; x < 8; x++)
            {
				write_psoc1(val, LicensePlate[x]);	// variable placa
			}
                     
            write_psoc1(val,10);
            
            for(x = 0; x < 8; x++)
            {
				LicensePlate[x] = 0x00;	// variable placa
			}
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_BALANCE[x]);
			} 
			for(x = 0; x < 10; x++)
            {
				write_psoc1(val, BalanceA[x]); // variable saldo	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 10; x++)
            {
				BalanceA[x] = 0x00; // variable saldo	
			}
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_COMPANY[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val, Company[x]);	//  variable compañia
			}
            write_psoc1(val,10);
            for(x = 0; x < 20; x++)
            {
				Company[x] = 0x00;	//  variable compañia
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_ACCOUNT[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val, CountID[x]);	//variable cuenta
			}
            write_psoc1(val,10);
			for(x = 0; x < 20; x++)
            {
				CountID[x] = 0x00;	//variable cuenta
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSDAY[x]);
			} 
			
			write_psoc1(val, DayVisit);	
			
            DayVisit = 0x00;
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSWEEK[x]);
			} 
			
			write_psoc1(val,WeekVisit);				
            write_psoc1(val,10);
            WeekVisit = 0x00;

            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSMONTH[x]);
			} 
			
			write_psoc1(val, MonthVisit);		
            write_psoc1(val,10);
            
            MonthVisit = 0x00;
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYDAY[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeDay[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeDay[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYWEEK[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val, VolumeWeek[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeWeek[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYMONTH[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeMonth[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeMonth[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_ACCOUNTTYPE[x]);
			} 
			for(x = 0; x < 16; x++)
            {
				write_psoc1(val,CountType[x]);	
			}
            write_psoc1(val,10);
            write_psoc1(val,10);
            for(x = 0; x < 16; x++)
            {
				CountType[x] = 0x00;	
			}
            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_SIGNATURE[x]);
			} 			
            write_psoc1(val,10);
            write_psoc1(val,10);
            write_psoc1(val,10);
            
            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_ID[x]);
			} 			
            write_psoc1(val,10);
            write_psoc1(val,10);
            write_psoc1(val,10);
	    }
    }
    
	if(pos == side.b.RF)
    {
        for(x = 0; x < 13; x++)                                     //Mensaje Producto	
        {																
    		write_psoc1(val,PRN_PRODUCT[x]);
    	}    	                        
        for(x = 0; x < 13; x++)                                     //Producto	
        {																
    		write_psoc1(val,producto[side.b.GradesHose[side.b.hose]-1][x]);
    	}
        write_psoc1(val,10);
        
        for(x = 0;x < 13;x++)
        {										//Ppu							
    		write_psoc1(val,msn_ppu[x]);
    	}  
        
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x2F);
        for(x = 0; x < 1; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,0x20);
        

        if(digits >= 7)
        {
            if(side.b.ppuSale[2] == 0x30)
                side.b.ppuSale[2] = 0x00;
            for(x = 2; x <= side.b.ppuSale[0]; x++)
            {                                    
        		write_psoc1(val,side.b.ppuSale[x]);
        	}
        }else{
            if (ppux10 ==1){
                if(side.b.ppuSale[1]== 0x30)
                    side.b.ppuSale[1]= 0x00;
            }
            for(x = 1; x <= side.b.ppuSale[0]; x++)
            {						   							
        		write_psoc1(val,side.b.ppuSale[x]);
        	}
        }

        write_psoc1(val,10);
        
        for(x = 0; x < 13; x++)
        {										                    //Volumen							
    		write_psoc1(val,msn_vol[x]);
    	}        
        
        for(x = 0; x < 1; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,0x20);
        
         if (digits < 7){
            ///////////////////////////////////////////////////////////////
            if(side.b.volumeSale[1] == 0x30)
                side.b.volumeSale[1] = 0x00;
            if(side.b.volumeSale[1] == 0x00 && side.b.volumeSale[2] == 0x30)
                side.b.volumeSale[2] = 0x00;
            ///////////////////////////////////////////////////////////////
            for(x = side.b.volumeSale[0]; x >= 1 ;x--)
            {						   							
                write_psoc1(val,side.b.volumeSale[side.b.volumeSale[0]+ 1 - x]);
                if(x == VolDec + 1)
                    write_psoc1(val,',');
        	}
        }else{
            ///////////////////////////////////////////////////////////////
            for (x = 1; x < 5; x++ )
            {
                if (side.b.volumeSale[x] != 0x30)
                    break;
                if (side.b.volumeSale[x] == 0x30)
                {
                    side.b.volumeSale[x] = 0x00;                   
                }                
            }
            ///////////////////////////////////////////////////////////////
            for(x = side.b.volumeSale[0]; x >= 1 ;x--)
            {						   							
                write_psoc1(val,side.b.volumeSale[side.b.volumeSale[0]+ 1 - x]);
                if(x == VolDec+1)
                    write_psoc1(val,',');
        	}
        }

        write_psoc1(val,10);
               
        for(x = 0; x < 13; x++)
        {										                    //Dinero							
    		write_psoc1(val,msn_din[x]);
    	}       
        
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x20);
        
         if (digits < 7){
            /////////////////////////////////////////////////////////////
            if(side.b.moneySale[1] == 0x30)
                side.b.moneySale[1] = 0x00;
            if(side.b.moneySale[1] == 0x00 && side.b.moneySale[2] == 0x30)
                side.b.moneySale[2] = 0x00;
            /////////////////////////////////////////////////////////////
            for(x = 1; x <= side.b.moneySale[0]; x++)
            {						   							
        		write_psoc1(val,side.b.moneySale[x]);
                if(x == MoneyDec)
                    write_psoc1(val,',');
        	}
        }else{
            /////////////////////////////////////////////////////////////
            for (x = 1; x < 8; x++ )
            {
                if (side.b.moneySale[x] != 0x30)
                    break;
                if (side.b.moneySale[x] == 0x30)
                {
                    side.b.moneySale[x] = 0x00;                   
                }                
            }
            /////////////////////////////////////////////////////////////
            for(x = 1; x <= side.b.moneySale[0]; x++)
            {						   							
        		write_psoc1(val,side.b.moneySale[x]);
                if(x == MoneyDec)
                    write_psoc1(val,',');
        	}
            
        }
              
        write_psoc1(val,10);
        
        if(bufferDisplay2.saleType == 1)
        {
    		for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,msn_placa[x]);                          //PLACA
    		} 
    		for(x = 1; x <= bufferDisplay2.PrintLicense[0]; x++)
            {
    			write_psoc1(val,bufferDisplay2.PrintLicense[x]);	
    		}
            
            for(x = 0; x < 11; x++)
            {
    			bufferDisplay2.PrintLicense[x] = 0x00;	  //Borra placa
    		}           
            write_psoc1(val,10);
            
			if(KmCash[1] == 0x01){
                for(x = 0; x < 13; x++)
                {																		
    				write_psoc1(val,PRN_MILLEAGE[x]);    //Km opcional en efectivo
    			}	
    			for(x = 1; x <= bufferDisplay2.mileageSale[0]; x++)
                {
    				write_psoc1(val,bufferDisplay2.mileageSale[x]);	
    			}
                write_psoc1(val,10);
            }

            for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,PRN_PRESET[x]);                          //Preset
    		} 
            
            write_psoc1(val,bufferDisplay2.PrintType);
            write_psoc1(val,' ');
    		if (digits < 7)
            {
                if(bufferDisplay2.presetType[0] == 1)
                {
                    if(bufferDisplay2.PrintPreset[0][1] == 0x30)
                        bufferDisplay2.PrintPreset[0][1] = 0x00;
                    if(bufferDisplay2.PrintPreset[0][1] == 0x00 && bufferDisplay2.PrintPreset[0][2] == 0x30)
                        bufferDisplay2.PrintPreset[0][2] = 0x00;

                        if(bufferDisplay2.PrintPreset[0][1] == 0x00 && bufferDisplay2.PrintPreset[0][2] == 0x00 && bufferDisplay2.PrintPreset[0][3] == 0x30)
                            bufferDisplay2.PrintPreset[0][3] = 0x00;
                    
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay2.PrintPreset[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay2.PrintPreset[0][bufferDisplay2.PrintPreset[0][0]+ 1 - x]);
                        if(ppux10 ==1){
                            if(x == VolDec)
                                write_psoc1(val,'.');
                        }else{
                            if(x == VolDec)

                                write_psoc1(val,'.');
                        }
                	}                    
                }
                else{
                    ///////////////////////////////////////////////////////////////
                    for (x = 1; x < 5; x++ )
                    {
                        if (bufferDisplay2.PrintPreset[0][x] != 0x30)
                            break;
                        if (bufferDisplay2.PrintPreset[0][x] == 0x30)
                        {
                            bufferDisplay2.PrintPreset[0][x] = 0x00;                   
                        }                
                    }
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay2.PrintPreset[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay2.PrintPreset[0][bufferDisplay2.PrintPreset[0][0]+ 1 - x]);
                        if(x == VolDec+1)
                            write_psoc1(val,'.');
                	}                    
                }        	    
            }else
            {
                if(bufferDisplay2.presetType[0] == 1)
                {
                    if(bufferDisplay2.PrintPreset[1][1] == 0x00)
                        bufferDisplay2.PrintPreset[1][1] = 0x30;

                    for(x = bufferDisplay2.PrintPreset[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay2.PrintPreset[1][bufferDisplay2.PrintPreset[1][0]+ 1 - x]);
                	}
                }
                else{                                                        

                    for(x = bufferDisplay2.PrintPreset[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val, bufferDisplay2.PrintPreset[1][bufferDisplay2.PrintPreset[1][0]+ 1 - x]);
                	}
                }                                        
            }

            write_psoc1(val,10);         
        }
                
  	    if(bufferDisplay2.saleType == 2)
        {		
            for(x = 0;x < 13;x++)
            {																		
				write_psoc1(val,PRN_MILLEAGE[x]);
			}	
			for(x = 1; x <= bufferDisplay2.mileageSale[0]; x++)   // KM
            {
				write_psoc1(val,bufferDisplay2.mileageSale[x]);	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 11; x++)
            {
				bufferDisplay2.mileageSale[x] = 0x00;	
			}           

			for(x = 0;x < 13; x++)
            {										//DATOS IBUTTON								
				write_psoc1(val,PRN_SERIAL[x]);
			} 
			for(x = 1; x <= bufferDisplay2.idSerial[0]; x++)
            {
				write_psoc1(val,bufferDisplay2.idSerial[x]);	
			}			
			write_psoc1(val,10);	
            for(x = 0; x < 25; x++)
            {
				bufferDisplay2.idSerial[x] = 0x00;	
			}
			for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,msn_placa[x]);
			} 
			for(x = 0; x < 8; x++)
            {
				write_psoc1(val, LicensePlate2[x]);	// variable placa
			}
            write_psoc1(val,10);
            for(x = 0; x < 8; x++)
            {
				LicensePlate2[x] = 0x00;	// variable placa
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_BALANCE[x]);
			} 
			for(x = 0; x < 10; x++)
            {
				write_psoc1(val,BalanceB[x]); // variable saldo	
			}
            write_psoc1(val,10);
            for(x = 0; x < 10; x++)
            {
				BalanceB[x] = 0x00; // variable saldo	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_COMPANY[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val,CompanyB[x]);	//  variable compañia
			}
            write_psoc1(val,10);
            for(x = 0; x < 20; x++)
            {
				CompanyB[x] = 0x00;	//  variable compañia
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_ACCOUNT[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val,CountIDB[x]);	//variable cuenta
			}
            write_psoc1(val,10);
			for(x = 0; x < 20; x++)
            {
				CountIDB[x] = 0x00;	//variable cuenta
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSDAY[x]);
			} 
			
			write_psoc1(val, DayVisitB);	
			DayVisitB = 0x00;

            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSWEEK[x]);
			} 
			
			write_psoc1(val,WeekVisitB);				
            write_psoc1(val,10);
            WeekVisitB = 0x00;

            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSMONTH[x]);
			} 
			
			write_psoc1(val, MonthVisitB);		
            write_psoc1(val,10);
            MonthVisitB = 0x00;

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYDAY[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeDayB[x]);	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 7; x++)
            {
				VolumeDayB[x] = 0x00;	
			}
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYWEEK[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val, VolumeWeekB[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeWeekB[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYMONTH[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeMonthB[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeMonthB[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_ACCOUNTTYPE[x]);
			} 
			for(x = 0; x < 16; x++)
            {
				write_psoc1(val,CountTypeB[x]);	
			}
            write_psoc1(val,10);
            write_psoc1(val,10);
            
            for(x = 0; x < 16; x++)
            {
				CountTypeB[x] = 0x00;	
			}
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_SIGNATURE[x]);
			} 			
            write_psoc1(val,10);
            write_psoc1(val,10);
            write_psoc1(val,10);
            
            for(x = 0;x < 13;x++)
            {																		
				write_psoc1(val,PRN_ID[x]);
			} 			
            write_psoc1(val,10);
            write_psoc1(val,10);
            write_psoc1(val,10);           
	    }
    } 
    
    if(pos == side.c.RF)
    {
        for(x = 0; x < 13; x++)                                     //Mensaje Producto	
        {																
    		write_psoc1(val,PRN_PRODUCT[x]);
    	}    	                        
        for(x = 0; x < 13; x++)                                     //Producto	
        {																
    		write_psoc1(val,producto[side.c.GradesHose[side.c.hose]-1][x]);
    	}
        write_psoc1(val,10);
        
        for(x = 0;x < 13;x++)
        {										//Ppu							
    		write_psoc1(val,msn_ppu[x]);
    	}       
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x2F);      
        for(x = 0; x < 1; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,0x20);
        

        if(digits >= 7)
        {
            if(side.c.ppuSale[2] == 0x30)
                side.c.ppuSale[2] = 0x00;
            for(x = 2; x <= side.c.ppuSale[0]; x++)
            {                                    
        		write_psoc1(val,side.c.ppuSale[x]);
        	}
        }else{
            if (ppux10 ==1){
                if(side.c.ppuSale[1]== 0x30)
                    side.c.ppuSale[1]= 0x00;
            }
            for(x = 1; x <= side.c.ppuSale[0]; x++)
            {						   							
        		write_psoc1(val,side.c.ppuSale[x]);
        	}
        }

        write_psoc1(val,10);
        
        for(x = 0; x < 13; x++)
        {										                    //Volumen							
    		write_psoc1(val,msn_vol[x]);
    	} 
        
        for(x = 0; x < 1; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,0x20);
        if (digits < 7){
            ///////////////////////////////////////////////////////////////
            if(side.c.volumeSale[1] == 0x30)
                side.c.volumeSale[1] = 0x00;
            if(side.c.volumeSale[1] == 0x00 && side.c.volumeSale[2] == 0x30)
                side.c.volumeSale[2] = 0x00;
            ///////////////////////////////////////////////////////////////
            for(x = side.c.volumeSale[0]; x >= 1 ;x--)
            {						   							
                write_psoc1(val,side.c.volumeSale[side.c.volumeSale[0]+ 1 - x]);
                if(x == VolDec + 1)
                    write_psoc1(val,',');
        	}
        }
        else{
            ///////////////////////////////////////////////////////////////
            for (x = 1; x < 5; x++ )
            {
                if (side.c.volumeSale[x] != 0x30)
                    break;
                if (side.c.volumeSale[x] == 0x30)
                {
                    side.c.volumeSale[x] = 0x00;                   
                }                
            }
            ///////////////////////////////////////////////////////////////
            for(x = side.c.volumeSale[0]; x >= 1 ;x--)
            {						   							
                write_psoc1(val,side.c.volumeSale[side.c.volumeSale[0]+ 1 - x]);
                if(x == VolDec+1)
                    write_psoc1(val,',');
        	}
        }

        write_psoc1(val,10);
               
        for(x = 0; x < 13; x++)
        {										                    //Dinero							
    		write_psoc1(val,msn_din[x]);
    	}
       
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x20);
       if (digits < 7){
            /////////////////////////////////////////////////////////////
            if(side.c.moneySale[1] == 0x30)
                side.c.moneySale[1] = 0x00;
            if(side.c.moneySale[1] == 0x00 && side.c.moneySale[2] == 0x30)
                side.c.moneySale[2] = 0x00;
            /////////////////////////////////////////////////////////////
            for(x = 1; x <= side.c.moneySale[0]; x++)
            {						   							
        		write_psoc1(val,side.c.moneySale[x]);
                if(x == MoneyDec)
                    write_psoc1(val,',');
        	}
        }
        else{
            /////////////////////////////////////////////////////////////
            for (x = 1; x < 8; x++ )
            {
                if (side.c.moneySale[x] != 0x30)
                    break;
                if (side.c.moneySale[x] == 0x30)
                {
                    side.c.moneySale[x] = 0x00;                   
                }                
            }
            /////////////////////////////////////////////////////////////
            for(x = 1; x <= side.c.moneySale[0]; x++)
            {						   							
        		write_psoc1(val,side.c.moneySale[x]);
                if(x == MoneyDec)
                    write_psoc1(val,',');
        	}
            
        }                
        write_psoc1(val,10);        
        if(bufferDisplay3.saleType == 1)
        {
    		for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,msn_placa[x]);                          //PLACA
    		} 
    		for(x = 1; x <= bufferDisplay3.PrintLicense[0]; x++)
            {
    			write_psoc1(val,bufferDisplay3.PrintLicense[x]);	
    		}
            write_psoc1(val,10);
            
            for(x = 0; x < 11; x++)
            {
    			bufferDisplay3.PrintLicense[x] = 0x00;	
    		}
			if(KmCash[1] == 0x01){
                for(x = 0; x < 13; x++)

                {																		
    				write_psoc1(val,PRN_MILLEAGE[x]);    //Km opcional en efectivo
    			}	
    			for(x = 1; x <= bufferDisplay3.mileageSale[0]; x++)
                {
    				write_psoc1(val,bufferDisplay3.mileageSale[x]);	
    			}
                write_psoc1(val,10);
            }
            for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,PRN_PRESET[x]);                          //Preset
    		} 
            
            write_psoc1(val,bufferDisplay3.PrintType);
            write_psoc1(val,' ');
    		if (digits < 7)
            {
                if(bufferDisplay3.presetType[0] == 1)
                {
                    if(bufferDisplay3.PrintPreset[0][1] == 0x30)
                        bufferDisplay3.PrintPreset[0][1] = 0x00;
                    if(bufferDisplay3.PrintPreset[0][1] == 0x00 && bufferDisplay3.PrintPreset[0][2] == 0x30)
                        bufferDisplay3.PrintPreset[0][2] = 0x00;


                        if(bufferDisplay3.PrintPreset[0][1] == 0x00 && bufferDisplay3.PrintPreset[0][2] == 0x00 && bufferDisplay3.PrintPreset[0][3] == 0x30)
                            bufferDisplay3.PrintPreset[0][3] = 0x00;


                    
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay3.PrintPreset[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay3.PrintPreset[0][bufferDisplay3.PrintPreset[0][0]+ 1 - x]);
                        if(ppux10 ==1){
                            if(x == VolDec)
                                write_psoc1(val,'.');
                        }else{
                            if(x == VolDec)

                                write_psoc1(val,'.');
                        }
                	}                    
                }
                else{
                    ///////////////////////////////////////////////////////////////
                    for (x = 1; x < 5; x++ )
                    {
                        if (bufferDisplay3.PrintPreset[0][x] != 0x30)
                            break;
                        if (bufferDisplay3.PrintPreset[0][x] == 0x30)
                        {
                            bufferDisplay3.PrintPreset[0][x] = 0x00;                   

                        }                
                    }
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay3.PrintPreset[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay3.PrintPreset[0][bufferDisplay3.PrintPreset[0][0]+ 1 - x]);
                        if(x == VolDec+1)
                            write_psoc1(val,'.');
                	}                    
                }        	    
            }else
            {
                if(bufferDisplay3.presetType[0] == 1)
                {
                    if(bufferDisplay3.PrintPreset[1][1] == 0x00)
                        bufferDisplay3.PrintPreset[1][1] = 0x30;





                    for(x = bufferDisplay3.PrintPreset[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay3.PrintPreset[1][bufferDisplay3.PrintPreset[1][0]+ 1 - x]);



                	}
                }
                else{                                        
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay3.PrintPreset[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val, bufferDisplay3.PrintPreset[1][bufferDisplay3.PrintPreset[1][0]+ 1 - x]);

                	}
                }                                        
            }
            


            write_psoc1(val,10);
        }
                
  	    if(bufferDisplay3.saleType == 2)
        {		
            for(x = 0;x < 13;x++)
            {																		
				write_psoc1(val,PRN_MILLEAGE[x]);
			}	
			for(x = 1; x <= bufferDisplay3.mileageSale[0]; x++)
            {
				write_psoc1(val,bufferDisplay3.mileageSale[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 11; x++)
            {
				bufferDisplay3.mileageSale[x] = 0x00;	
			}		

			for(x = 0;x < 13; x++)
            {										//DATOS IBUTTON								
				write_psoc1(val,PRN_SERIAL[x]);
			} 
			for(x = 1; x <= bufferDisplay3.idSerial[0]; x++)
            {
				write_psoc1(val,bufferDisplay3.idSerial[x]);	
			}			
			write_psoc1(val,10);
            for(x = 0; x < 25; x++)
            {
				bufferDisplay3.idSerial[x] = 0x00;	

			}

			for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,msn_placa[x]);
			} 
			for(x = 0; x < 8; x++)
            {
				write_psoc1(val, LicensePlate[x]);	// variable placa
			}                        
            write_psoc1(val,10);
            for(x = 0; x < 8; x++)
            {
				LicensePlate[x] = 0x00;	// variable placa
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_BALANCE[x]);
			} 
			for(x = 0; x < 10; x++)
            {
				write_psoc1(val, BalanceA[x]); // variable saldo	
			}
            write_psoc1(val,10);
            for(x = 0; x < 10; x++)
            {
				BalanceA[x] = 0x00; // variable saldo	
			}
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_COMPANY[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val, Company[x]);	//  variable compañia
			}
            write_psoc1(val,10);
            for(x = 0; x < 20; x++)
            {
				Company[x] = 0x00;	//  variable compañia
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_ACCOUNT[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val, CountID[x]);	//variable cuenta
			}
            write_psoc1(val,10);
            
			for(x = 0; x < 20; x++)
            {
				CountID[x] = 0x00;	//variable cuenta
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSDAY[x]);
			} 
			
			write_psoc1(val, DayVisit);	
			
            write_psoc1(val,10);
            DayVisit = 0x00;

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSWEEK[x]);
			} 
			
			write_psoc1(val,WeekVisit);				
            write_psoc1(val,10);
            WeekVisit = 0x00;

            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSMONTH[x]);
			} 
			
			write_psoc1(val, MonthVisit);		
            write_psoc1(val,10);
            MonthVisit = 0x00;

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYDAY[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeDay[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeDay[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYWEEK[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val, VolumeWeek[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeWeek[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYMONTH[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeMonth[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeMonth[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_ACCOUNTTYPE[x]);
			} 
			for(x = 0; x < 16; x++)
            {
				write_psoc1(val,CountType[x]);	
			}
            write_psoc1(val,10);
            write_psoc1(val,10);
            
            for(x = 0; x < 16; x++)
            {
				CountType[x] = 0x00;	
			}
            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_SIGNATURE[x]);
			} 			
            write_psoc1(val,10);
            write_psoc1(val,10);
            write_psoc1(val,10);
            
            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_ID[x]);
			} 			
            write_psoc1(val,10);
            write_psoc1(val,10);
            write_psoc1(val,10);          
	    }
    }
    
    if(pos == side.d.RF)
    {
        for(x = 0; x < 13; x++)                                     //Mensaje Producto	
        {																
    		write_psoc1(val,PRN_PRODUCT[x]);
    	}    	                        
        for(x = 0; x < 13; x++)                                     //Producto	
        {																
    		write_psoc1(val,producto[side.d.GradesHose[side.d.hose]-1][x]);
    	}
        write_psoc1(val,10);
        
        for(x = 0;x < 13;x++)
        {										//Ppu							
    		write_psoc1(val,msn_ppu[x]);
    	}   
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x2F);
        for(x = 0; x < 1; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,0x20);
        if(digits >= 7)
        {
            if(side.d.ppuSale[2] == 0x30)
                side.d.ppuSale[2] = 0x00;
            for(x = 2; x <= side.d.ppuSale[0]; x++)
            {                                    
        		write_psoc1(val,side.d.ppuSale[x]);
        	}
        }else{
            if (ppux10 ==1){
                if(side.d.ppuSale[1]== 0x30)
                    side.d.ppuSale[1]= 0x00;
            }
            for(x = 1; x <= side.d.ppuSale[0]; x++)
            {						   							
        		write_psoc1(val,side.d.ppuSale[x]);
        	}
        }
        write_psoc1(val,10);
        
        for(x = 0; x < 13; x++)
        {										                    //Volumen							
    		write_psoc1(val,msn_vol[x]);
    	} 
        for(x = 0; x < 1; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,0x20);
        if (digits < 7){
            ///////////////////////////////////////////////////////////////
            if(side.d.volumeSale[1] == 0x30)
                side.d.volumeSale[1] = 0x00;
            if(side.d.volumeSale[1] == 0x00 && side.d.volumeSale[2] == 0x30)
                side.d.volumeSale[2] = 0x00;
            ///////////////////////////////////////////////////////////////
            for(x = side.d.volumeSale[0]; x >= 1 ;x--)
            {						   							
                write_psoc1(val,side.d.volumeSale[side.d.volumeSale[0]+ 1 - x]);
                if(x == VolDec + 1)
                    write_psoc1(val,',');
        	}
        }
        else{
            ///////////////////////////////////////////////////////////////
            for (x = 1; x < 5; x++ )
            {
                if (side.d.volumeSale[x] != 0x30)
                    break;
                if (side.d.volumeSale[x] == 0x30)
                {
                    side.d.volumeSale[x] = 0x00;                   
                }                
            }
            ///////////////////////////////////////////////////////////////
            for(x = side.d.volumeSale[0]; x >= 1 ;x--)
            {						   							
                write_psoc1(val,side.d.volumeSale[side.d.volumeSale[0]+ 1 - x]);
                if(x == VolDec+1)
                    write_psoc1(val,',');
        	}
        }
  
        write_psoc1(val,10);        
        for(x = 0; x < 13; x++)
        {										                    //Dinero							
    		write_psoc1(val,msn_din[x]);
    	}
        
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x20);
        if (digits < 7){
            /////////////////////////////////////////////////////////////
            if(side.d.moneySale[1] == 0x30)
                side.d.moneySale[1] = 0x00;
            if(side.d.moneySale[1] == 0x00 && side.d.moneySale[2] == 0x30)
                side.d.moneySale[2] = 0x00;
            /////////////////////////////////////////////////////////////
            for(x = 1; x <= side.d.moneySale[0]; x++)
            {						   							
        		write_psoc1(val,side.d.moneySale[x]);
                if(x == MoneyDec)
                    write_psoc1(val,',');
        	}
        }
        else{
            /////////////////////////////////////////////////////////////
            for (x = 1; x < 8; x++ )
            {
                if (side.d.moneySale[x] != 0x30)
                    break;
                if (side.d.moneySale[x] == 0x30)
                {
                    side.d.moneySale[x] = 0x00;                   
                }                
            }
            /////////////////////////////////////////////////////////////
            for(x = 1; x <= side.d.moneySale[0]; x++)
            {						   							
        		write_psoc1(val,side.d.moneySale[x]);
                if(x == MoneyDec)
                    write_psoc1(val,',');
        	}            
        }
        write_psoc1(val,10);
        
        if(bufferDisplay4.saleType == 1)
        {
    		for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,msn_placa[x]);                          //PLACA
    		} 
    		for(x = 1; x <= bufferDisplay4.PrintLicense[0]; x++)
            {
    			write_psoc1(val,bufferDisplay4.PrintLicense[x]);	
    		}
            write_psoc1(val,10);            
            for(x = 0; x < 11; x++)
            {
    			bufferDisplay4.PrintLicense[x] = 0x00;	
    		}
            if(KmCash[1] == 0x01){
                for(x = 0; x < 13; x++)
                {																		
    				write_psoc1(val,PRN_MILLEAGE[x]);    //Km opcional en efectivo
    			}	
    			for(x = 1; x <= bufferDisplay4.mileageSale[0]; x++)
                {
    				write_psoc1(val,bufferDisplay4.mileageSale[x]);	
    			}
                write_psoc1(val,10);
            }
            for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,PRN_PRESET[x]);                          //Preset
    		}             
            write_psoc1(val,bufferDisplay4.PrintType);
            write_psoc1(val,' ');
            if (digits < 7)
            {
                if(bufferDisplay4.presetType[0] == 1)
                {
                    if(bufferDisplay4.PrintPreset[0][1] == 0x30)
                        bufferDisplay4.PrintPreset[0][1] = 0x00;
                    if(bufferDisplay4.PrintPreset[0][1] == 0x00 && bufferDisplay4.PrintPreset[0][2] == 0x30)
                        bufferDisplay4.PrintPreset[0][2] = 0x00;


                        if(bufferDisplay4.PrintPreset[0][1] == 0x00 && bufferDisplay4.PrintPreset[0][2] == 0x00 && bufferDisplay4.PrintPreset[0][3] == 0x30)
                            bufferDisplay4.PrintPreset[0][3] = 0x00;
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay4.PrintPreset[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay4.PrintPreset[0][bufferDisplay4.PrintPreset[0][0]+ 1 - x]);
                        if(ppux10 ==1){
                            if(x == VolDec)
                                write_psoc1(val,'.');
                        }else{
                            if(x == VolDec)

                                write_psoc1(val,'.');
                        }
                	}                    
                }
                else{
                    ///////////////////////////////////////////////////////////////
                    for (x = 1; x < 5; x++ )
                    {
                        if (bufferDisplay4.PrintPreset[0][x] != 0x30)
                            break;
                        if (bufferDisplay4.PrintPreset[0][x] == 0x30)
                        {
                            bufferDisplay4.PrintPreset[0][x] = 0x00;                   

                        }                
                    }
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay4.PrintPreset[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay4.PrintPreset[0][bufferDisplay4.PrintPreset[0][0]+ 1 - x]);
                        if(x == VolDec+1)
                            write_psoc1(val,'.');
                	}                    
                }        	    
            }else
            {
                if(bufferDisplay4.presetType[0] == 1)
                {
                    if(bufferDisplay4.PrintPreset[1][1] == 0x00)
                        bufferDisplay4.PrintPreset[1][1] = 0x30;

                    for(x = bufferDisplay4.PrintPreset[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay4.PrintPreset[1][bufferDisplay4.PrintPreset[1][0]+ 1 - x]);
                	}
                }
                else{                                        
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay4.PrintPreset[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val, bufferDisplay4.PrintPreset[1][bufferDisplay4.PrintPreset[1][0]+ 1 - x]);
                	}
                }                                        
            }            
            write_psoc1(val,10);
        }                
  	    if(bufferDisplay4.saleType == 2)
        {		
            for(x = 0;x < 13;x++)
            {																		
				write_psoc1(val,PRN_MILLEAGE[x]);
			}	
			for(x = 1; x <= bufferDisplay4.mileageSale[0]; x++)
            {
				write_psoc1(val,bufferDisplay4.mileageSale[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 11; x++)
            {
				bufferDisplay4.mileageSale[x] = 0x00;	
			}
            
			for(x = 0;x < 13; x++)
            {										//DATOS IBUTTON								
				write_psoc1(val,PRN_SERIAL[x]);
			} 
			for(x = 1; x <= bufferDisplay4.idSerial[0]; x++)
            {
				write_psoc1(val,bufferDisplay4.idSerial[x]);	
			}			
			write_psoc1(val,10);
            
            for(x = 0; x < 25; x++)
            {
				bufferDisplay4.idSerial[x] = 0x00;	
			}
			for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,msn_placa[x]);
			} 
			for(x = 0; x < 8; x++)
            {
				write_psoc1(val, LicensePlate2[x]);	// variable placa
			}
            write_psoc1(val,10);
            for(x = 0; x < 8; x++)
            {
				LicensePlate2[x] = 0x00;	// variable placa
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_BALANCE[x]);
			} 
			for(x = 0; x < 10; x++)
            {
				write_psoc1(val,BalanceB[x]); // variable saldo	
			}
            write_psoc1(val,10);
            for(x = 0; x < 10; x++)
            {
				BalanceB[x] = 0x00; // variable saldo	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_COMPANY[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val,CompanyB[x]);	//  variable compañia
			}
            write_psoc1(val,10);
            for(x = 0; x < 20; x++)
            {
				CompanyB[x] = 0x00;	//  variable compañia
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_ACCOUNT[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val,CountIDB[x]);	//variable cuenta
			}
            write_psoc1(val,10);
			for(x = 0; x < 20; x++)
            {
				CountIDB[x] = 0x00;	//variable cuenta
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSDAY[x]);
			} 
			
			write_psoc1(val, DayVisitB);	
			
            write_psoc1(val,10);
            DayVisitB = 0x00;

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSWEEK[x]);
			} 
			
			write_psoc1(val,WeekVisitB);				
            write_psoc1(val,10);
            WeekVisitB = 0x00;

            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSMONTH[x]);
			} 
			
			write_psoc1(val, MonthVisitB);		
            write_psoc1(val,10);
            MonthVisitB = 0x00;

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYDAY[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeDayB[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeDayB[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYWEEK[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val, VolumeWeekB[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeWeekB[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYMONTH[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeMonthB[x]);	
			}
            write_psoc1(val,10);
            for(x = 0; x < 7; x++)
            {
				VolumeMonthB[x] = 0x00;	
			}

            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_ACCOUNTTYPE[x]);
			} 
			for(x = 0; x < 16; x++)
            {
				write_psoc1(val,CountTypeB[x]);	
			}
            write_psoc1(val,10);
            write_psoc1(val,10);
            for(x = 0; x < 16; x++)
            {
				CountTypeB[x] = 0x00;	

			}
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_SIGNATURE[x]);
			} 			
            write_psoc1(val,10);
            write_psoc1(val,10);
            write_psoc1(val,10);
            
            for(x = 0;x < 13;x++)
            {																		
				write_psoc1(val,PRN_ID[x]);
			} 			
            write_psoc1(val,10);
            write_psoc1(val,10);
            write_psoc1(val,10);                       
	    }
    }
    
     ////////////////  PIE DE PÁGINA /////////////////////////
    for(x = 0; x < 30; x++)
    {
        write_psoc1(val,SEPARATOR[x]);
    }
    write_psoc1(val,10);
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Pie1[x]);
    }
    write_psoc1(val,10); 
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Pie2[x]);
    }    
    write_psoc1(val,10); 
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Pie3[x]);
    }   
    write_psoc1(val,10); 
    write_psoc1(val,10);
    write_psoc1(val,10);
	write_psoc1(val,10);
    write_psoc1(val,10);
	write_psoc1(val,0x1D);
	write_psoc1(val,0x56);
	write_psoc1(val,0x31);	
    
}

/*
*********************************************************************************************************
*                                         void printBalance(uint8 val)
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
void printBalance(uint8 val,uint8 pos){
    uint8 x;
    uint8 nombre[8]  = {"NOMBRE :"};
    uint8 placa[8]   = {"PLACA  :"};
    uint8 tarjeta[8] = {"TARJETA:"};
    uint8 saldo_d[21]  = {"SALDO DISPONIBLE:    "};
    uint8 saldo_a[21]  = {"SALDO EN APROBACION: "};
    
    if(pos == side.a.dir || pos == side.c.dir)
    {
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortA,EEPROM_1_ReadByte(215));    
        }else{
            printLogoK(printPortA,EEPROM_1_ReadByte(215));
        }
    }
    if(pos == side.b.dir || pos == side.d.dir)
    {
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortB,EEPROM_1_ReadByte(215));    
        }else{
            printLogoK(printPortB,EEPROM_1_ReadByte(215));
        }
    }
    
    vTaskDelay( 100 / portTICK_PERIOD_MS );
    
    write_psoc1(val,10);
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado1[x]);
    }
    write_psoc1(val,10);
    
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado2[x]);
    }
    write_psoc1(val,10);
    
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado3[x]);
    }
    write_psoc1(val,10);
    
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado4[x]);
    }
    write_psoc1(val,10);
    LeerEeprom(200,31);
    for(x = 1; x <= 30; x++)
    {
        Encabezado5[x] = buffer_i2c[x];
        write_psoc1(val,Encabezado5[x]);
    }
    write_psoc1(val,10);
    
    for(x = 0; x < 30; x++)
    {
        write_psoc1(val,SEPARATOR[x]);
    }
    write_psoc1(val,10);
    for(x = 0; x < 13; x++)
    {										//FECHA								
		write_psoc1(val,msn_fecha[x]);
	}
    if(leer_fecha() == 1)
    {
		write_psoc1(val,(((dateDownHandle[0] & 0x10) >> 4) + 48));
		write_psoc1(val,((dateDownHandle[0] & 0x0F) + 48));
		write_psoc1(val,'/');
		write_psoc1(val,(((dateDownHandle[1] & 0x10) >> 4) + 48));
		write_psoc1(val,((dateDownHandle[1] & 0x0F) + 48));	
		write_psoc1(val,'/');
		write_psoc1(val,(((dateDownHandle[2] & 0xF0) >> 4) + 48));
		write_psoc1(val,((dateDownHandle[2] & 0x0F) + 48));			
	}		
    write_psoc1(val,10);
    for(x = 0;x < 13; x++)
    {										//HORA								
		write_psoc1(val,msn_hora[x]);
	}
    if(leer_hora() == 1)
    {										//HORA
		write_psoc1(val,(((timeDownHandle[1] & 0x30) >> 4) + 48));
		write_psoc1(val,((timeDownHandle[1] & 0x0F) + 48));
		write_psoc1(val,':');
		write_psoc1(val,(((timeDownHandle[0] & 0xF0) >> 4) + 48));
		write_psoc1(val,((timeDownHandle[0] & 0x0F) + 48));		
	}
    write_psoc1(val,10);
    for(x = 0; x < 30; x++)
    {
        write_psoc1(val,SEPARATOR[x]);
    }
    write_psoc1(val,10);
    if(cardmessagedisplay== 1){
    //////DATOS DE SALDO //////
        for(x = 0; x < 8; x++)
        {
            write_psoc1(val,nombre[x]);
        }
        for(x = 0; x < 20; x++)
        {
            write_psoc1(val,Company[x]);
        }
        write_psoc1(val,10);
        
        for(x = 0; x < 8; x++)
        {
            write_psoc1(val,placa[x]);
        }
        for(x = 0; x < 8; x++)
        {
            write_psoc1(val,LicensePlate[x]);
        }
        write_psoc1(val,10);
        
        for(x = 0; x < 8; x++)
        {
            write_psoc1(val,tarjeta[x]);
        }
        for(x = 0; x < 5; x++)
        {
            write_psoc1(val,'*');
        }
        for(x = 0; x < 3; x++)
        {
            write_psoc1(val,cardNumberA[x]);
        }
        write_psoc1(val,10);
        
        for(x = 0; x < 21; x++)
        {
            write_psoc1(val,saldo_d[x]);
        }
        write_psoc1(val,10);
        for(x = 0; x < 18; x++)
        {
            write_psoc1(val,BalanceA[x]);
        }
        write_psoc1(val,10);
        
        for(x = 0; x < 21; x++)
        {
            write_psoc1(val,saldo_a[x]);
        }
        write_psoc1(val,10);
        for(x = 0; x < 18; x++)
        {
            write_psoc1(val,BalanceB[x]);
        }
        write_psoc1(val,10);
    }
    if(cardmessagedisplay == 2){
        for(x = 0; x < 25; x++)
        {
            write_psoc1(val,cardmessage[x]);
        }        
        write_psoc1(val,10);
        for(x = 0; x < 25; x++)
        {
            write_psoc1(val,cardmessage1[x]);
        }        
        write_psoc1(val,10);
        for(x = 0; x < 25; x++)
        {
            write_psoc1(val,cardmessage2[x]);
        }        
        write_psoc1(val,10);
        for(x = 0; x < 25; x++)
        {
            write_psoc1(val,cardmessage3[x]);
        }        
        write_psoc1(val,10);
        
    }
     ////////////////  PIE DE PÁGINA /////////////////////////
    for(x = 0; x < 30; x++)
    {
        write_psoc1(val,SEPARATOR[x]);
    }
    write_psoc1(val,10);
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Pie1[x]);
        //write_psoc1(val,footer1[x]);
    }
    write_psoc1(val,10); 
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Pie2[x]);
        //write_psoc1(val,footer2[x]);
    }    
    write_psoc1(val,10); 
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Pie3[x]);
        //write_psoc1(val,footer2[x]);
    }   
    write_psoc1(val,10); 
    write_psoc1(val,10);
    write_psoc1(val,10);
	write_psoc1(val,10);
    write_psoc1(val,10);
	write_psoc1(val,0x1D);
	write_psoc1(val,0x56);
	write_psoc1(val,0x31);	
    
}

/*
*********************************************************************************************************
*                                         void printPayment(uint8 val)
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
void printPayment(uint8 val,uint8 pos){
    uint8 x;
    
    if(pos == side.a.dir || pos == side.c.dir)
    {
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortA,EEPROM_1_ReadByte(215));    
        }else{
            printLogoK(printPortA,EEPROM_1_ReadByte(215));
        }
    }
    if(pos == side.b.dir || pos == side.d.dir)
    {
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortB,EEPROM_1_ReadByte(215));    
        }else{
            printLogoK(printPortB,EEPROM_1_ReadByte(215));
        }
    }
    write_psoc1(val,10);
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado1[x]);
        //write_psoc1(val,title1[x]);
    }
    write_psoc1(val,10);
    
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado2[x]);
        //write_psoc1(val,title2[x]);
    }
    write_psoc1(val,10);
    
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado3[x]);
        //write_psoc1(val,title3[x]);
    }
    write_psoc1(val,10);
    
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Encabezado4[x]);
        //write_psoc1(val,title4[x]);
    }
    write_psoc1(val,10);
    LeerEeprom(200,31);
    for(x = 1; x <= 30; x++)
    {
        Encabezado5[x] = buffer_i2c[x];
        write_psoc1(val,Encabezado5[x]);
        //write_psoc1(val,title5[x]);
    }
    write_psoc1(val,10);
    
    for(x = 0; x < 30; x++)
    {
        write_psoc1(val,SEPARATOR[x]);
    }
    write_psoc1(val,10);
    for(x = 0; x < 13; x++)
    {										//FECHA								
		write_psoc1(val,msn_fecha[x]);
	}
    if(leer_fecha() == 1)
    {
		write_psoc1(val,(((dateDownHandle[0] & 0x30) >> 4) + 48));
		write_psoc1(val,((dateDownHandle[0] & 0x0F) + 48));
		write_psoc1(val,'/');
		write_psoc1(val,(((dateDownHandle[1] & 0x10) >> 4) + 48));
		write_psoc1(val,((dateDownHandle[1] & 0x0F) + 48));	
		write_psoc1(val,'/');
		write_psoc1(val,(((dateDownHandle[2] & 0xF0) >> 4) + 48));
		write_psoc1(val,((dateDownHandle[2] & 0x0F) + 48));			
	}		
    write_psoc1(val,10);
    for(x = 0;x < 13; x++)
    {										//HORA								
		write_psoc1(val,msn_hora[x]);
	}
    if(leer_hora() == 1)
    {										//HORA
		write_psoc1(val,(((timeDownHandle[1] & 0x10) >> 4) + 48));
		write_psoc1(val,((timeDownHandle[1] & 0x0F) + 48));
		write_psoc1(val,':');
		write_psoc1(val,(((timeDownHandle[0] & 0xF0) >> 4) + 48));
		write_psoc1(val,((timeDownHandle[0] & 0x0F) + 48));		
	}
    write_psoc1(val,10);
    for(x = 0; x < 30; x++)
    {
        write_psoc1(val,SEPARATOR[x]);
    }
    write_psoc1(val,10);
    for(x = 0; x <= 24; x++)
    {
        write_psoc1(val,cardmessage[x]);
        //write_psoc1(val,title1[x]);
    }
    write_psoc1(val,10);
    
    for(x = 0; x <= 24; x++)
    {
        write_psoc1(val,cardmessage1[x]);
        //write_psoc1(val,title2[x]);
    }
        
    write_psoc1(val,10);    
    for(x = 0; x <= 24; x++)
    {
        write_psoc1(val,cardmessage2[x]);
        //write_psoc1(val,title3[x]);
    }
    write_psoc1(val,10);
    
    for(x = 0; x <= 24; x++)
    {
        write_psoc1(val,cardmessage3[x]);
        //write_psoc1(val,title3[x]);
    }
    write_psoc1(val,10);
     ////////////////  PIE DE PÁGINA /////////////////////////
    for(x = 0; x < 30; x++)
    {
        write_psoc1(val,SEPARATOR[x]);
    }
    write_psoc1(val,10);
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Pie1[x]);
    }
    write_psoc1(val,10); 
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Pie2[x]);
    }    
    write_psoc1(val,10); 
    for(x = 1; x <= 30; x++)
    {
        write_psoc1(val,Pie3[x]);
    }   
    write_psoc1(val,10); 
    write_psoc1(val,10);
    write_psoc1(val,10);
	write_psoc1(val,10);
    write_psoc1(val,10);
	write_psoc1(val,0x1D);
	write_psoc1(val,0x56);
	write_psoc1(val,0x31);	
    
}


/* [] END OF FILE */
