/*
 * UART_Driver.h
 *
 * Created: 01/06/21 6:08:46 PM
 *  Author: cnast
 */ 


#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#ifndef uart0_tx_newline
#define uart0_tx_newline {uart0_transmit_byte(0x0D);uart0_transmit_byte(0x0A);}
#endif

void uart0_init(void);
uint8_t uart0_receive_byte(void);
void uart0_transmit_byte(uint8_t data);
void uart0_transmitString_flash(int8_t* string);
void uart0_transmit_string(int8_t* string);
void uart0_print_temperaturehumidity(int8_t temp , unsigned char cur_count);



#endif /* UART_DRIVER_H_ */