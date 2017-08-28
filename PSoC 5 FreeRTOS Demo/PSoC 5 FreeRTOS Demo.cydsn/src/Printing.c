/*
*********************************************************************************************************
*                                           GRP500 CODE
*
*                             (c) Copyright 2013; Sistemas Insepet LTDA
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
*                                               GRP500 CODE
*
*                                             CYPRESS PSoC5LP
*                                                with the
*                                            CY8C5969AXI-LP035
*
* Filename      : Print.c
* Version       : V1.00
* Programmer(s) : 
                  
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#include <device.h>
#include <stdlib.h>
#include <string.h>
#include "Variables.h"
#include "I2C.h"
#include "protocol.h"
#include "Logos.h"


/*
*********************************************************************************************************
*                                            MENSAJES
*********************************************************************************************************
*/

//uint8 title1[30]          = "     ESTACION DE SERVICIO     ";
//uint8 title2[30]          = "       TERPEL LA CASONA       ";
//uint8 title3[30]          = "         14.992.210-7         ";
//uint8 title4[30]          = "           4226353            ";
//uint8 title5[30]          = "             CALI             ";
//uint8 footer1[30]         = "       EDS CERTIFICADA        ";
//uint8 footer2[30]         = "    NO VALIDO COMO FACTURA    ";
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
			for(i=0;i<=755;i++){
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
			for(i=0;i<=755;i++){
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
    if(pos == side.a.dir || pos == side.c.dir)
    {
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortA,logoPrint[1]);    
        }else{
            printLogoK(printPortB,logoPrint[1]);
        }
    }
    if(pos == side.b.dir || pos == side.d.dir)
    {
        if(PrinterType[1] == 1)
        {
            printLogoP(printPortB,logoPrint[1]);    
        }else{
            printLogoK(printPortB,logoPrint[1]);
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
    
    for(x = 1; x <= 30; x++)
    {
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
    ////////////////////// FIN DE ENCABEZADO ////////////////////////////////////////
    for(x = 0; x < 13; x++)
    {										                            //POSICION								
		write_psoc1(val,msn_pos[x]);
	}
    write_psoc1(val,((pos / 10) + 48));
	write_psoc1(val,((pos % 10) + 48));
    write_psoc1(val,10);
    
    
    for(x = 0; x < 13; x++)                                             //NUMERO DE VENTA
    {										    							
		write_psoc1(val,msn_numero[x]);
	}    	
    if(pos == side.a.dir){
        for(x=0;x < 10;x++){										    //NUMERO DE VENTA							
    		write_psoc1(val,side.a.saleNumber[x]);
    	}
    }
    if(pos == side.b.dir)
    {
        for(x = 0; x < 10; x++)                                         //NUMERO DE VENTA
        {										    							
    		write_psoc1(val,side.b.saleNumber[x]);
    	}
    }
    if(pos == side.c.dir)
    {
        for(x = 0; x < 10; x++)                                        //NUMERO DE VENTA
        {										    							
    		write_psoc1(val,side.c.saleNumber[x]);
    	}
    }
    if(pos == side.d.dir)
    {
        for(x = 0; x < 10; x++)                                       //NUMERO DE VENTA
        {										    							
    		write_psoc1(val,side.d.saleNumber[x]);
    	}
    }
    write_psoc1(val,10);
    ////////////// DATOS DE VENTA /////////////////////////////
	if(pos == side.a.dir)
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
        write_psoc1(val,0x20);
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x2F);
        for(x = 0; x < 5; x++)                                      //Simbolos $/G
        {																	
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,10);
        
        
        for(x = 0; x < 13; x++)                                     //Volumen
        {																	
    		write_psoc1(val,msn_vol[x]);
    	} 
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
        write_psoc1(val,0x20);
        for(x = 0; x < 5; x++)                                      //Simbolos $/G
        {																	
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,10);
       
        for(x = 0; x < 13; x++)                                     //Dinero
        {																	
    		write_psoc1(val,msn_din[x]);
    	}
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
        write_psoc1(val,0x20);
        write_psoc1(val,PRN_CURRENCY[0]);        
        write_psoc1(val,10);
        
        if(bufferDisplay1.saleType == 1)
        {
    		for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val, msn_placa[x]);                          //PLACA
    		} 
    		for(x = 1; x <= bufferDisplay1.licenceSale[0]; x++)
            {
    			write_psoc1(val,bufferDisplay1.licenceSale[x]);	
    		}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val, PRN_PRESET[x]);                          //Preset
    		} 
            
            if (digits < 7)
            {
                if(bufferDisplay1.presetType[0] == 1)
                {
                    if(bufferDisplay1.presetValue[0][1] == 0x30)
                        bufferDisplay1.presetValue[0][1] = 0x00;
                    if(bufferDisplay1.presetValue[0][1] == 0x00 && bufferDisplay1.presetValue[0][2] == 0x30)
                        bufferDisplay1.presetValue[0][2] = 0x00;
                    if(ppux10 ==1){
                        if(bufferDisplay1.presetValue[0][1] == 0x00 && bufferDisplay1.presetValue[0][2] == 0x00 && bufferDisplay1.presetValue[0][3] == 0x30)
                            bufferDisplay1.presetValue[0][3] = 0x00;
                    }
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay1.presetValue[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay1.presetValue[0][bufferDisplay1.presetValue[0][0]+ 1 - x]);
                        if(ppux10 ==1){
                            if(x == VolDec)
                                write_psoc1(val,'.');
                        }else{
                            if(x == VolDec + 1)
                                write_psoc1(val,'.');
                        }
                	}                    
                }
                else{
                    ///////////////////////////////////////////////////////////////
                    for (x = 1; x < 5; x++ )
                    {
                        if (bufferDisplay1.presetValue[0][x] != 0x30)
                            break;
                        if (bufferDisplay1.presetValue[0][x] == 0x30)
                        {
                            bufferDisplay1.presetValue[0][x] = 0x00;                   
                        }                
                    }
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay1.presetValue[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay1.presetValue[0][bufferDisplay1.presetValue[0][0]+ 1 - x]);
                        if(x == VolDec+1)
                            write_psoc1(val,'.');
                	}                    
                }        	    
            }else
            {
                if(bufferDisplay1.presetType[0] == 1)
                {
                    if(bufferDisplay1.presetValue[1][1] == 0x00)
                        bufferDisplay1.presetValue[1][1] = 0x30;
                   // if(bufferDisplay1.presetValue[1][1] == 0x00 && bufferDisplay1.presetValue[1][2] == 0x30)
                    //    bufferDisplay1.presetValue[1][2] = 0x00;
                    
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay1.presetValue[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay1.presetValue[1][bufferDisplay1.presetValue[1][0]+ 1 - x]);
                        //if(x == VolDec + 1)
                           // write_psoc1(val,'.');
                	}
                }
                else{                                        
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay1.presetValue[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val, bufferDisplay1.presetValue[1][bufferDisplay1.presetValue[1][0]+ 1 - x]);

                	}
                }                                        
            }
            write_psoc1(val,' ');
            write_psoc1(val,bufferDisplay1.presetType[1]);
            write_psoc1(val,10);
        }                
  	    if(bufferDisplay1.saleType == 2)
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
            		
			for(x= 0;x < 13;x++)
            {										//DATOS IBUTTON								
				write_psoc1(val,PRN_SERIAL[x]);
			} 
			for(x = 1; x <= bufferDisplay1.idSerial[0]; x++)
            {
				write_psoc1(val,bufferDisplay1.idSerial[x]);	
			}			
			write_psoc1(val,10);	
			for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, msn_placa[x]);
			} 
            
            
			for(x = 0; x < 8; x++)
            {
				write_psoc1(val, LicensePlate[x]);	// variable placa
			}
            
            
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_BALANCE[x]);
			} 
			for(x = 0; x < 10; x++)
            {
				write_psoc1(val, BalanceA[x]); // variable saldo	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_COMPANY[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val, Company[x]);	//  variable compañia
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_ACCOUNT[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val, CountID[x]);	//variable cuenta
			}
            write_psoc1(val,10);
			
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSDAY[x]);
			} 
			
			write_psoc1(val, DayVisit);	
			
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSWEEK[x]);
			} 
			
			write_psoc1(val,WeekVisit);				
            write_psoc1(val,10);
            
            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSMONTH[x]);
			} 
			
			write_psoc1(val, MonthVisit);		
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYDAY[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeDay[x]);	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYWEEK[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val, VolumeWeek[x]);	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYMONTH[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeMonth[x]);	
			}
            write_psoc1(val,10);
            
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
    
	if(pos == side.b.dir)
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
        write_psoc1(val,0x20);
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x2F);
        for(x = 0; x < 5; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,10);
        
        for(x = 0; x < 13; x++)
        {										                    //Volumen							
    		write_psoc1(val,msn_vol[x]);
    	} 
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
        write_psoc1(val,0x20);
        for(x = 0; x < 5; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,10);
        
        
        for(x = 0; x < 13; x++)
        {										                    //Dinero							
    		write_psoc1(val,msn_din[x]);
    	}
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
        write_psoc1(val,0x20);
        write_psoc1(val,PRN_CURRENCY[0]);        
        write_psoc1(val,10);
        
        if(bufferDisplay2.saleType == 1)
        {
    		for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,msn_placa[x]);                          //PLACA
    		} 
    		for(x = 1; x <= bufferDisplay2.licenceSale[0]; x++)
            {
    			write_psoc1(val,bufferDisplay2.licenceSale[x]);	
    		}
            write_psoc1(val,10);
            for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,PRN_PRESET[x]);                          //Preset
    		} 
    		if (digits < 7)
            {
                if(bufferDisplay2.presetType[0] == 1)
                {
                    if(bufferDisplay2.presetValue[0][1] == 0x30)
                        bufferDisplay2.presetValue[0][1] = 0x00;
                    if(bufferDisplay2.presetValue[0][1] == 0x00 && bufferDisplay2.presetValue[0][2] == 0x30)
                        bufferDisplay2.presetValue[0][2] = 0x00;
                    if(ppux10 ==1){
                        if(bufferDisplay2.presetValue[0][1] == 0x00 && bufferDisplay2.presetValue[0][2] == 0x00 && bufferDisplay2.presetValue[0][3] == 0x30)
                            bufferDisplay2.presetValue[0][3] = 0x00;
                    }
                    
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay2.presetValue[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay2.presetValue[0][bufferDisplay2.presetValue[0][0]+ 1 - x]);
                        if(ppux10 ==1){
                            if(x == VolDec)
                                write_psoc1(val,'.');
                        }else{
                            if(x == VolDec + 1)
                                write_psoc1(val,'.');
                        }
                	}                    
                }
                else{
                    ///////////////////////////////////////////////////////////////
                    for (x = 1; x < 5; x++ )
                    {
                        if (bufferDisplay2.presetValue[0][x] != 0x30)
                            break;
                        if (bufferDisplay2.presetValue[0][x] == 0x30)
                        {
                            bufferDisplay2.presetValue[0][x] = 0x00;                   
                        }                
                    }
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay2.presetValue[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay2.presetValue[0][bufferDisplay2.presetValue[0][0]+ 1 - x]);
                        if(x == VolDec+1)
                            write_psoc1(val,'.');
                	}                    
                }        	    
            }else
            {
                if(bufferDisplay2.presetType[0] == 1)
                {
                    if(bufferDisplay2.presetValue[1][1] == 0x00)
                        bufferDisplay2.presetValue[1][1] = 0x30;
                   // if(bufferDisplay1.presetValue[1][1] == 0x00 && bufferDisplay1.presetValue[1][2] == 0x30)
                    //    bufferDisplay1.presetValue[1][2] = 0x00;
                    
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay2.presetValue[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay2.presetValue[1][bufferDisplay2.presetValue[1][0]+ 1 - x]);
                        //if(x == VolDec + 1)
                           // write_psoc1(val,'.');
                	}
                }
                else{                                        
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay2.presetValue[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val, bufferDisplay2.presetValue[1][bufferDisplay2.presetValue[1][0]+ 1 - x]);

                	}
                }                                        
            }
            write_psoc1(val,' ');
            write_psoc1(val,bufferDisplay2.presetType[1]);
            write_psoc1(val,10);
        }
                
  	    if(bufferDisplay2.saleType == 2)
        {		
            for(x = 0;x < 13;x++)
            {																		
				write_psoc1(val,PRN_MILLEAGE[x]);
			}	
			for(x = 1; x <= bufferDisplay2.mileageSale[0]; x++)
            {
				write_psoc1(val,bufferDisplay2.mileageSale[x]);	
			}
            write_psoc1(val,10);
            		
			for(x = 0;x < 13; x++)
            {										//DATOS IBUTTON								
				write_psoc1(val,PRN_SERIAL[x]);
			} 
			for(x = 1; x <= bufferDisplay2.idSerial[0]; x++)
            {
				write_psoc1(val,bufferDisplay2.idSerial[x]);	
			}			
			write_psoc1(val,10);	
			for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,msn_placa[x]);
			} 
			for(x = 0; x < 8; x++)
            {
				write_psoc1(val, LicensePlate2[x]);	// variable placa
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_BALANCE[x]);
			} 
			for(x = 0; x < 10; x++)
            {
				write_psoc1(val,BalanceB[x]); // variable saldo	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_COMPANY[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val,CompanyB[x]);	//  variable compañia
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_ACCOUNT[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val,CountIDB[x]);	//variable cuenta
			}
            write_psoc1(val,10);
			
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSDAY[x]);
			} 
			
			write_psoc1(val, DayVisitB);	
			
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSWEEK[x]);
			} 
			
			write_psoc1(val,WeekVisitB);				
            write_psoc1(val,10);
            
            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSMONTH[x]);
			} 
			
			write_psoc1(val, MonthVisitB);		
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYDAY[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeDayB[x]);	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYWEEK[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val, VolumeWeekB[x]);	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYMONTH[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeMonthB[x]);	
			}
            write_psoc1(val,10);
            
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
    
    if(pos == side.c.dir)
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
        write_psoc1(val,0x20);
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x2F);
        for(x = 0; x < 5; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,10);
        
        for(x = 0; x < 13; x++)
        {										                    //Volumen							
    		write_psoc1(val,msn_vol[x]);
    	} 
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
        write_psoc1(val,0x20);
        for(x = 0; x < 5; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,10);
        
       
        for(x = 0; x < 13; x++)
        {										                    //Dinero							
    		write_psoc1(val,msn_din[x]);
    	}
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
        write_psoc1(val,0x20);
        write_psoc1(val,PRN_CURRENCY[0]);        
        write_psoc1(val,10);
        
        if(bufferDisplay3.saleType == 1)
        {
    		for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,msn_placa[x]);                          //PLACA
    		} 
    		for(x = 1; x <= bufferDisplay3.licenceSale[0]; x++)
            {
    			write_psoc1(val,bufferDisplay3.licenceSale[x]);	
    		}
            write_psoc1(val,10);
            for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,PRN_PRESET[x]);                          //Preset
    		} 
    		if (digits < 7)
            {
                if(bufferDisplay3.presetType[0] == 1)
                {
                    if(bufferDisplay3.presetValue[0][1] == 0x30)
                        bufferDisplay3.presetValue[0][1] = 0x00;
                    if(bufferDisplay3.presetValue[0][1] == 0x00 && bufferDisplay3.presetValue[0][2] == 0x30)
                        bufferDisplay3.presetValue[0][2] = 0x00;
                    if(ppux10 ==1){
                        if(bufferDisplay3.presetValue[0][1] == 0x00 && bufferDisplay3.presetValue[0][2] == 0x00 && bufferDisplay3.presetValue[0][3] == 0x30)
                            bufferDisplay3.presetValue[0][3] = 0x00;
                    }
                    
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay3.presetValue[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay3.presetValue[0][bufferDisplay3.presetValue[0][0]+ 1 - x]);
                        if(ppux10 ==1){
                            if(x == VolDec)
                                write_psoc1(val,'.');
                        }else{
                            if(x == VolDec + 1)
                                write_psoc1(val,'.');
                        }
                	}                    
                }
                else{
                    ///////////////////////////////////////////////////////////////
                    for (x = 1; x < 5; x++ )
                    {
                        if (bufferDisplay3.presetValue[0][x] != 0x30)
                            break;
                        if (bufferDisplay3.presetValue[0][x] == 0x30)
                        {
                            bufferDisplay3.presetValue[0][x] = 0x00;                   
                        }                
                    }
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay3.presetValue[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay3.presetValue[0][bufferDisplay3.presetValue[0][0]+ 1 - x]);
                        if(x == VolDec+1)
                            write_psoc1(val,'.');
                	}                    
                }        	    
            }else
            {
                if(bufferDisplay3.presetType[0] == 1)
                {
                    if(bufferDisplay3.presetValue[1][1] == 0x00)
                        bufferDisplay3.presetValue[1][1] = 0x30;
                   // if(bufferDisplay1.presetValue[1][1] == 0x00 && bufferDisplay1.presetValue[1][2] == 0x30)
                    //    bufferDisplay1.presetValue[1][2] = 0x00;
                    
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay3.presetValue[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay3.presetValue[1][bufferDisplay3.presetValue[1][0]+ 1 - x]);
                        //if(x == VolDec + 1)
                           // write_psoc1(val,'.');
                	}
                }
                else{                                        
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay3.presetValue[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val, bufferDisplay3.presetValue[1][bufferDisplay3.presetValue[1][0]+ 1 - x]);

                	}
                }                                        
            }
            write_psoc1(val,' ');
            write_psoc1(val,bufferDisplay3.presetType[1]);
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
            		
			for(x = 0;x < 13; x++)
            {										//DATOS IBUTTON								
				write_psoc1(val,PRN_SERIAL[x]);
			} 
			for(x = 1; x <= bufferDisplay3.idSerial[0]; x++)
            {
				write_psoc1(val,bufferDisplay3.idSerial[x]);	
			}			
			write_psoc1(val,10);	
			for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,msn_placa[x]);
			} 
			for(x = 0; x < 8; x++)
            {
				write_psoc1(val, LicensePlate[x]);	// variable placa
			}                        
            write_psoc1(val,10);            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_BALANCE[x]);
			} 
			for(x = 0; x < 10; x++)
            {
				write_psoc1(val, BalanceA[x]); // variable saldo	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_COMPANY[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val, Company[x]);	//  variable compañia
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val, PRN_ACCOUNT[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val, CountID[x]);	//variable cuenta
			}
            write_psoc1(val,10);
			
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSDAY[x]);
			} 
			
			write_psoc1(val, DayVisit);	
			
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSWEEK[x]);
			} 
			
			write_psoc1(val,WeekVisit);				
            write_psoc1(val,10);
            
            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSMONTH[x]);
			} 
			
			write_psoc1(val, MonthVisit);		
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYDAY[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeDay[x]);	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYWEEK[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val, VolumeWeek[x]);	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYMONTH[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeMonth[x]);	
			}
            write_psoc1(val,10);
            
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
    
    if(pos == side.d.dir)
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
        write_psoc1(val,0x20);
        write_psoc1(val,PRN_CURRENCY[0]);
        write_psoc1(val,0x2F);
        for(x = 0; x < 5; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,10);
        
        for(x = 0; x < 13; x++)
        {										                    //Volumen							
    		write_psoc1(val,msn_vol[x]);
    	} 
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
        write_psoc1(val,0x20);
        for(x = 0; x < 5; x++)
        {										                    //Simbolos $/G							
    		write_psoc1(val,VolUnit[x]);
    	}
        write_psoc1(val,10);
        
       
        for(x = 0; x < 13; x++)
        {										                    //Dinero							
    		write_psoc1(val,msn_din[x]);
    	}
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
        write_psoc1(val,0x20);
        write_psoc1(val,PRN_CURRENCY[0]);        
        write_psoc1(val,10);
        
        if(bufferDisplay4.saleType == 1)
        {
    		for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,msn_placa[x]);                          //PLACA
    		} 
    		for(x = 1; x <= bufferDisplay4.licenceSale[0]; x++)
            {
    			write_psoc1(val,bufferDisplay4.licenceSale[x]);	
    		}
            write_psoc1(val,10);
            for(x = 0; x < 13; x++)
            {																		
    			write_psoc1(val,PRN_PRESET[x]);                          //Preset
    		} 
            if (digits < 7)
            {
                if(bufferDisplay4.presetType[0] == 1)
                {
                    if(bufferDisplay4.presetValue[0][1] == 0x30)
                        bufferDisplay4.presetValue[0][1] = 0x00;
                    if(bufferDisplay4.presetValue[0][1] == 0x00 && bufferDisplay4.presetValue[0][2] == 0x30)
                        bufferDisplay4.presetValue[0][2] = 0x00;
                    if(ppux10 ==1){
                        if(bufferDisplay4.presetValue[0][1] == 0x00 && bufferDisplay4.presetValue[0][2] == 0x00 && bufferDisplay4.presetValue[0][3] == 0x30)
                            bufferDisplay4.presetValue[0][3] = 0x00;
                    }
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay4.presetValue[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay4.presetValue[0][bufferDisplay4.presetValue[0][0]+ 1 - x]);
                        if(ppux10 ==1){
                            if(x == VolDec)
                                write_psoc1(val,'.');
                        }else{
                            if(x == VolDec + 1)
                                write_psoc1(val,'.');
                        }
                	}                    
                }
                else{
                    ///////////////////////////////////////////////////////////////
                    for (x = 1; x < 5; x++ )
                    {
                        if (bufferDisplay4.presetValue[0][x] != 0x30)
                            break;
                        if (bufferDisplay4.presetValue[0][x] == 0x30)
                        {
                            bufferDisplay4.presetValue[0][x] = 0x00;                   
                        }                
                    }
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay4.presetValue[0][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay4.presetValue[0][bufferDisplay4.presetValue[0][0]+ 1 - x]);
                        if(x == VolDec+1)
                            write_psoc1(val,'.');
                	}                    
                }        	    
            }else
            {
                if(bufferDisplay4.presetType[0] == 1)
                {
                    if(bufferDisplay4.presetValue[1][1] == 0x00)
                        bufferDisplay4.presetValue[1][1] = 0x30;
                   // if(bufferDisplay1.presetValue[1][1] == 0x00 && bufferDisplay1.presetValue[1][2] == 0x30)
                    //    bufferDisplay1.presetValue[1][2] = 0x00;
                    
                        ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay4.presetValue[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val,bufferDisplay4.presetValue[1][bufferDisplay4.presetValue[1][0]+ 1 - x]);
                        //if(x == VolDec + 1)
                           // write_psoc1(val,'.');
                	}
                }
                else{                                        
                    ///////////////////////////////////////////////////////////////
                    for(x = bufferDisplay4.presetValue[1][0]; x >= 1 ;x--)
                    {						   							
                        write_psoc1(val, bufferDisplay4.presetValue[1][bufferDisplay4.presetValue[1][0]+ 1 - x]);

                	}
                }                                        
            }
            write_psoc1(val,' ');
            write_psoc1(val,bufferDisplay4.presetType[1]);
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
            		
			for(x = 0;x < 13; x++)
            {										//DATOS IBUTTON								
				write_psoc1(val,PRN_SERIAL[x]);
			} 
			for(x = 1; x <= bufferDisplay4.idSerial[0]; x++)
            {
				write_psoc1(val,bufferDisplay4.idSerial[x]);	
			}			
			write_psoc1(val,10);	
			for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,msn_placa[x]);
			} 
			for(x = 0; x < 8; x++)
            {
				write_psoc1(val, LicensePlate2[x]);	// variable placa
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_BALANCE[x]);
			} 
			for(x = 0; x < 10; x++)
            {
				write_psoc1(val,BalanceB[x]); // variable saldo	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_COMPANY[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val,CompanyB[x]);	//  variable compañia
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_ACCOUNT[x]);
			} 
			for(x = 0; x < 20; x++)
            {
				write_psoc1(val,CountIDB[x]);	//variable cuenta
			}
            write_psoc1(val,10);
			
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSDAY[x]);
			} 
			
			write_psoc1(val, DayVisitB);	
			
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSWEEK[x]);
			} 
			
			write_psoc1(val,WeekVisitB);				
            write_psoc1(val,10);
            
            for(x = 0;x < 13; x++)
            {																		
				write_psoc1(val,PRN_VISITSMONTH[x]);
			} 
			
			write_psoc1(val, MonthVisitB);		
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYDAY[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeDayB[x]);	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYWEEK[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val, VolumeWeekB[x]);	
			}
            write_psoc1(val,10);
            
            for(x = 0; x < 13; x++)
            {																		
				write_psoc1(val,PRN_MONEYMONTH[x]);
			} 
			for(x = 0; x < 7; x++)
            {
				write_psoc1(val,VolumeMonthB[x]);	
			}
            write_psoc1(val,10);
            
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




/* [] END OF FILE */
