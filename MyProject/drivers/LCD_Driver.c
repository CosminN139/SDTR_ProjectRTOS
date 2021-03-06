/*
 * LCD_Driver.c
 *
 * Created: 11/07/20
 *  Author: Cosmin Nastase
 *	
 */ 

//////////////////////////////////////////////////////////////////////////
/*
					Usage
	This functionality treats the main functions needed to drive an HD44780 compatible
	LCD system. It is known that those lcd's are found in a variety of drivers and dimensions, but all of them
	sorts the display problem in the manner of timing from the original driver released by Hitachi in the 80s.
	So our task is to make an 20x4 LCD thingy to communicate as it needs with the system for display-ing some
	of characters sent by the uC itself,using the needed time constraints.
*/
//////////////////////////////////////////////////////////////////////////

//compiler-defined includes
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

//aditional system-defined includes
#include "FreeRTOS.h"
#include "task.h"
#include "../include/delay.h"

//user-defined includes
#include "LCD_Driver.h"
#include "../demos/testLED.h"


const uint8_t LcdCustomChar[] PROGMEM=//define 8 custom LCD chars
{
	0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, // 0. 0/5 full progress block
	0x00, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, // 1. 1/5 full progress block
	0x00, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x00, // 2. 2/5 full progress block
	0x00, 0x1F, 0x1C, 0x1C, 0x1C, 0x1C, 0x1F, 0x00, // 3. 3/5 full progress block
	0x00, 0x1F, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x00, // 4. 4/5 full progress block
	0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, // 5. 5/5 full progress block
	0x03, 0x07, 0x0F, 0x1F, 0x0F, 0x07, 0x03, 0x00, // 6. rewind arrow
	0x18, 0x1C, 0x1E, 0x1F, 0x1E, 0x1C, 0x18, 0x00  // 7. fast-forward arrow
};


void LCDsendChar(uint8_t ch)		//Sends Char to LCD
{
	//8 bit part
	DATA_PORT=ch;
	CONTROL_PORT|=1<<LCD_RS;
	CONTROL_PORT|=1<<LCD_E;
	_delay_us(5);
	CONTROL_PORT&=~(1<<LCD_E);
	CONTROL_PORT&=~(1<<LCD_RS);
	_delay_ms(100);
	
}
void LCDsendCommand(uint8_t cmd)	//Sends Command to LCD
{
	DATA_PORT		 =		cmd;
	CONTROL_PORT	|=	1<<LCD_E;
	_delay_us(5);
	CONTROL_PORT	&=	~(1<<LCD_E);
	_delay_ms(100);
}
void LCDinit(void)//Initializes LCD
{
	_delay_ms(1);
	DATA_PORT		=	0x00;
	CONTROL_PORT	=	0x00;
	_delay_ms(15);
	DATA_DDR		=	0xFF;
	CONTROL_DDR		=	0xE0;
	//^^^Port direction assignation and port init^^^
	//////////////////////////////////////////////////////////////////////////
	//Sending data configration bits
	/*
	0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4|0<<LCD_D3|0<<LCD_D2|0<<LCD_D1|0<<LCD_D0; -> Data port assignation
	1<<LCD_E|0<<LCD_RW|0<<LCD_RS;	-> Control port assignation
	*/
	DATA_PORT		=	0x30; //8 bit mode
	CONTROL_PORT	=	0xA0;
	_delay_us(5);
	CONTROL_PORT	&=	~(1<<LCD_E);
	_delay_ms(100);
	
	//increment address, invisible cursor shift
	/*
	0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4|1<<LCD_D3|1<<LCD_D2|0<<LCD_D1|0<<LCD_D0;
	1<<LCD_E|0<<LCD_RW|0<<LCD_RS;
	*/
	DATA_PORT		=	0x0C; //8 bit mode
	CONTROL_PORT	=	0xA0;
	_delay_us(5);
	CONTROL_PORT	&=	~(1<<LCD_E);
	_delay_ms(100);
	
	//init custom chars
	uint8_t ch=0, chn=0;
	while(ch<64)
	{
		LCDdefinechar((LcdCustomChar+ch),chn++);
		ch=ch+8;
	}

}
void LCDclr(void)				//Clears LCD
{
	LCDsendCommand(1<<LCD_CLR);
}
void LCDhome(void)			//LCD cursor home
{
	LCDsendCommand(1<<LCD_HOME);
}
void LCDstring(uint8_t* data, uint8_t nBytes)	//Outputs string to LCD
{
	register uint8_t i;

	// check to make sure we have a good pointer
	if (!data) return;

	// print data
	for(i=0; i<nBytes; i++)
	{
		LCDsendChar(data[i]);
	}
}

void LCDGotoXY(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	register uint8_t DDRAMAddr;
	// remap lines into proper order
	switch(y)
	{
		case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
		case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
		case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
		case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
		default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	}
	// set data address
	LCDsendCommand(1<<LCD_DDRAM | DDRAMAddr);
	
}
//Usage
//Copies string from flash memory to LCD at x y position
//const uint8_t welcomeln1[] PROGMEM="AVR LCD DEMO\0";
//CopyStringtoLCD(welcomeln1, 3, 1);

void CopyStringtoLCD(const uint8_t *FlashLoc, uint8_t x, uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++)
	{
		LCDsendChar((uint8_t)pgm_read_byte(&FlashLoc[i]));
	}
}
//defines char symbol in CGRAM

void LCDdefinechar(const uint8_t *pc,uint8_t char_code){
	uint8_t a, pcc;
	uint16_t i;
	a=(char_code<<3)|0x40;
	for (i=0; i<8; i++){
		pcc=pgm_read_byte(&pc[i]);
		LCDsendCommand(a++);
		LCDsendChar(pcc);
	}
}

void LCDshiftLeft(uint8_t n)	//Scroll n of characters Right
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x1E);
	}
}
void LCDshiftRight(uint8_t n)	//Scroll n of characters Left
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x18);
	}
}
void LCDcursorOn(void) //displays LCD cursor
{
	LCDsendCommand(0x0E);
}
void LCDcursorOnBlink(void)	//displays LCD blinking cursor
{
	LCDsendCommand(0x0F);
}
void LCDcursorOFF(void)	//turns OFF cursor
{
	LCDsendCommand(0x0C);
}
void LCDblank(void)		//blanks LCD
{
	LCDsendCommand(0x08);
}
void LCDvisible(void)		//Shows LCD
{
	LCDsendCommand(0x0C);
}
void LCDcursorLeft(uint8_t n)	//Moves cursor by n positions left
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x10);
	}
}
void LCDcursorRight(uint8_t n)	//Moves cursor by n positions left
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDsendCommand(0x14);
	}
}
//adapted from AVRLIB
void LCDprogressBar(uint8_t progress, uint8_t maxprogress, uint8_t length)
{
	uint8_t i;
	uint16_t pixelprogress;
	uint8_t character;

	// draw a progress bar displaying (progress / maxprogress)
	// starting from the current cursor position
	// with a total length of "length" characters
	// ***note, LCD chars 0-5 must be programmed as the bar characters
	// char 0 = empty ... char 5 = full

	// total pixel length of bargraph equals length*PROGRESSPIXELS_PER_CHAR;
	// pixel length of bar itself is
	pixelprogress = ((progress*(length*PROGRESSPIXELS_PER_CHAR))/maxprogress);
	
	// print exactly "length" characters
	for(i=0; i<length; i++)
	{
		// check if this is a full block, or partial or empty
		// (u16) cast is needed to avoid sign comparison warning
		if( ((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)+5) > pixelprogress )
		{
			// this is a partial or empty block
			if( ((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)) > pixelprogress )
			{
				// this is an empty block
				// use space character?
				character = 0;
			}
			else
			{
				// this is a partial block
				character = pixelprogress % PROGRESSPIXELS_PER_CHAR;
			}
		}
		else
		{
			// this is a full block
			character = 5;
		}
		
		// write character to display
		LCDsendChar(character);
	}

}
void LCD_printTempHum(uint16_t temp, unsigned char cur_count) {
	
	unsigned char ten_count = 0;
	unsigned char hun_count = 0;

	//LCDcursorRight(cur_count);
	while( temp >= 100 ) {
		hun_count++;
		temp -= 100;
	}
	
	LCDsendChar(hun_count + '0');
	cur_count++;

	//LCDcursorRight(cur_count);
	while( temp >= 10 ) {
		ten_count++;
		temp -= 10;
	}
	
	LCDsendChar(ten_count + '0');
	cur_count++;
	
	//LCDcursorRight(cur_count);
	LCDsendChar('.');
	cur_count++;
	
	//LCDcursorRight(cur_count);
	LCDsendChar((unsigned char) temp + '0');
	
	//LCDcursorRight(0);
}