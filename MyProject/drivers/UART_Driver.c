/*
 * UART_Driver.c
 *
 * Created: 01/06/21 5:32:56 PM
 *  Author: cnast
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "UART_Driver.h"
#include "../include/delay.h"

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*							USAGE                                       */
/************************************************************************/
/*	Designing some functions to treat data transmission over RS232(UART)*/
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/* Desired baud rate: 250k												*/
/* Error rate: 0%												        */
/* Char size:8bits                                                      */
/* No parity															*/
/************************************************************************/

void uart0_init(void)
{
	//no serial line enabled while configuring occures	
	UCSR0B = 0x00;
	UCSR0A = 0x00;
	UCSR0C = 0x06;
	//baud rate set
	UBRR0L = 0x03; //lo
	UBRR0H = 0x00; //hi
	//enable serial line uart0
	UCSR0B = 0x98;
}


uint8_t uart0_receive_byte(void)
{
	uint8_t data , status;
	
	while (!( UCSR0A & (1<<RXC0 ) ) );
	status = UCSR0A;
	data = UDR0;	
	
	return(data);
}

void uart0_transmit_byte(uint8_t data)
{
	
	while(!( UCSR0A & (1<<UDRE0) ) );
	/*Waiting for databuffer to empty
	  and after that starting the transmission*/
	UDR0 = data; 
		
}

void uart0_transmitString_flash(int8_t* string)
{
	while(pgm_read_byte(&(*string)))
		uart0_transmit_byte(pgm_read_byte( & ( *string++ ) ) );
}

void uart0_transmit_string(int8_t* string)
{
	
	while (*string)
		uart0_transmit_byte(*string++);	
	
}

void uart0_print_temperaturehumidity(int8_t temp, unsigned char cur_count)
{
	unsigned char ten_count = 0;
	unsigned char hun_count = 0;
	
	int8_t datastring;
	
	while( temp >= 100 ) {
		hun_count++;
		temp -= 100;
	}
	
	uart0_transmit_string(hun_count);
	cur_count++;

	
	while( temp >= 10 ) {
		ten_count++;
		temp -= 10;
	}
	
	uart0_transmit_string(ten_count);
	cur_count++;	

	uart0_transmit_string(".");
	cur_count++;	
	uart0_transmit_string(temp);

}