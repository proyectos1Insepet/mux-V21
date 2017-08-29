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

#include <device.h>
#include "variables.h"
#include <code_pirata.h>
/* RTOS includes. */
#include <FreeRTOS.h>
#include <semphr.h>
#include "os_resource.h"

void send_pirata(uint8_t data_tx[],uint8_t tamano)
{
    uint16_t i=0;
    for(i=0;i<tamano; i++)
    {
        Tag_PutChar(data_tx[i]);
        //CyDelay(2);
        
    }      
}

uint8_t cs(uint8_t data_tx[],uint8_t tamano)
{
    uint8_t i  =0;
    uint8_t data_cs = 0;
    
    for(i=0;i<tamano;i++)
    {
        data_cs = data_cs + data_tx[i];   
    }
    
    data_cs = ~ data_cs;
    data_cs = data_cs & 0xff;
    return data_cs;
}

uint16_t tamano_buffer(uint8_t data_buffer[])
{
    uint16_t i;
    uint16_t z = 0;

    for(i=499; i > 0; i--)
    {

        if( data_buffer[i] == '#' || data_buffer[i] != '\0' ) break;
        z++;

    }

    z = 500 - z;

    return z;
}

void borrar(void)
{
    uint16_t i;
    for(i=0; i<500; i++)
    {
        buffer_RX[i] = '\0';
    }
    
    for(i=0; i<20; i++)
    {
        buffer_TX[i] = '\0';
    }
}


//**************************************************************
//LLEGADA DEL DATO PRINCIPLA, SE RECIVE EL DATO DE LA POSICION 
//Y EL TIPO DE LECTOR
//**************************************************************
uint8_t code_pirata(char pos, char tipo)
{

    uint16 x,i;                         //PUNTEROS
    uint16_t check;                       //CHECL ES EL VALOR PARA DEFINIR SI LA TRAMA LLEGO COMPLETA
    uint16 tamano;                      //TAMAÑO DEL VECTOR QUE LLEGO
    uint8_t copy_tipo;
 
    if(bandera_entrada == 0)            //BANDERA DE ENTRADA
    {
        Tag_ClearRxBuffer();
        Tag_ClearTxBuffer();    
        borrar();
        bandera_numero_entrada=0;
        bandera_posicion = pos;
        copy_tipo = tipo & 0x0f;
        switch(copy_tipo)
        {
            case 1:
            {
                byte_data = byte_ibutto;   
            }
            break;
            case 2:
            {
                byte_data = byte_tag;   
            }
            break;
            case 3:
            {
                byte_data = byte_RFID;   
            }
            break;
            case 4:
            {
                byte_data = byte_QR;   
            }
            break;
            case 5:
            {
                byte_data = byte_MAG;   
            }
            break;
        }
                
        buffer_TX[0] = 'A';
        buffer_TX[1] = 'T';
        buffer_TX[2] = '+';
        buffer_TX[3] = 'C';
        buffer_TX[4] = tipo;
        buffer_TX[5] = ';';
        buffer_TX[6] = 'P';
        buffer_TX[7] = pos;
        buffer_TX[8] = ';';
        buffer_TX[9] = cs(buffer_TX,9);
        //buffer_TX[9] = 'F';
        buffer_TX[10] = ';';
        buffer_TX[11] = '#';
        send_pirata(buffer_TX,12);
        //CyDelay(100);
        vTaskDelay( 100 / portTICK_PERIOD_MS );
        bandera_entrada = 1;
        return 0;
    }
    // envio del dato a la tarjeta pirata;
    
    //espera un rato hasta que le llege una informacion y si no llega se salga de la rutina
    else if(bandera_entrada == 1 &&  bandera_posicion == pos)
    {
        
        bandera_numero_entrada ++;
        bandera_entrada = 0;
        
        if(Tag_GetRxBufferSize() > 8 )
        {
	        x=0;		
            
            while(Tag_GetRxBufferSize() > 0 && x < 8)
            {
           		buffer_RX[x] = Tag_ReadRxData();
           		x++;
                CyDelay(1);                
        	}
            
            if(buffer_RX[7] > 0)
            {
                while(Tag_GetRxBufferSize() > 0)
                {
           		    buffer_RX[x] = Tag_ReadRxData();
           		    x++;
                    CyDelay(1); 
                    if( x == (buffer_RX[7]+9+15)) break;
                    
        	    }
            }
            
            Tag_ClearRxBuffer();
            Tag_ClearTxBuffer();
            //for(x=1; x < byte_data ; x++)
            //    {
            //        temporal[x] = buffer_RX[x+6];
            //    }
            //    temporal[0] = byte_data;
            //    bandera_entrada = 0;
            //return 1;
            bandera_numero_entrada = 0;
            bandera_entrada = 0;
            
            if(buffer_RX[5] == '2')
            {
                borrar();
                return 0;
            }

            else if(buffer_RX[5] == '1')
            {
                
                //check = tamano_buffer(buffer_RX);

                for(x=1;x < (buffer_RX[7] + 11);x++)
                {
                    temporal[x]=buffer_RX[x+8];
                }

                temporal[0]=buffer_RX[7]+11;
                borrar();
                return 1;
            }
            
            return 0;
		}
        
        else if(bandera_numero_entrada >= 60)
        {
            bandera_entrada = 0;
            bandera_numero_entrada = 0;
            return 0;
        }
            vTaskDelay( 100 / portTICK_PERIOD_MS );
    }
        
	return 0;
  
}

/* [] END OF FILE */

    