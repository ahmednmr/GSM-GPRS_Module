/*
 * main.c
 *
 *  Created on: 5 Oct 2015
 *      Author: EmbeddedFab
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "MCAL/UART.h"
#include <avr/interrupt.h>

#include "stdlib.h"
#include "string.h"

#define TRUE 1
#define FALSE 0

#define MAKE_CALL            0
#define SEND_SMS             0
#define Connect_To_GPRS      1

#if Connect_To_GPRS

#define WE_Network          1
#define Vodafone_Network    0

#define   HTTP  			0
#define   MQTT  			1
#endif

#if MQTT
#define Publish       1
#define Subscribe     1
#endif

#define Client_ID      "11232siy1weu1e21"        //16 digits
#define User_Name      "nmr"                     //3 digits
#define Password       "GXQD8VN78RAISAUH"        //MQTT Key

#define Channel_ID     "996736"                  //Your Channel ID
#define Write_Key      "RNNN90XKATASUZZG"        //Api Write Key
#define Data           "7"       				 //Data

#define DEFAULT_BUFFER_SIZE 100
char Rec_Data[DEFAULT_BUFFER_SIZE];
char Counter=0;


char Check_Respond(char * Expected_Respond);
char Check_Word_in_Respond(char * Word);
void Clear_REC_Buffer(void);


ISR (USART_RXC_vect)
{
	uint8_t oldsrg = SREG;
	cli();
	Rec_Data[Counter] = UDR;
	Counter++;
	if(Counter == DEFAULT_BUFFER_SIZE){
		Counter = 0; //pointer = 0;
	}
	SREG = oldsrg;
}


int main()
{
	init_UART();    //baudrate 9600
	sei();

	_delay_ms(2000);
	Clear_REC_Buffer();
	UART_SEND_string("ATE1\r");
	//	while(!((Check_Respond("\r\nOK\r\n"))||(Check_Respond("ATE0\r\r\n\r\nOK\r\n"))))
	//	{
	//		_delay_ms(1);
	//	}
	_delay_ms(3000);

#if MAKE_CALL

	UART_SEND_string("ATD01115948824;\r");
	//	while(!Check_Respond("\r\nOK\r\n"))
	//	{
	//		_delay_ms(1);
	//	}
	_delay_ms(3000);

#endif

#if SEND_SMS
	UART_SEND_string("AT+CMGF=1\r");
	//		while(!Check_Respond("\r\nOK\r\n"))
	//		{
	//			_delay_ms(1);
	//		}
	_delay_ms(1000);

	UART_SEND_string("AT+CMGS=\"01115948824\"\r");
	//		while(!Check_Respond("\r\nOK\r\n"))
	//		{
	//			_delay_ms(1);
	//		}
	_delay_ms(1000);

	UART_SEND_string("Hello From GSM Module");
	UART_SendChar(0x1A);
	//		while(!Check_Respond("\r\nOK\r\n"))
	//		{
	//			_delay_ms(1);
	//		}
	_delay_ms(3000);



#endif


#if Connect_To_GPRS


	UART_SEND_string("AT+CREG?\r");

	_delay_ms(3000);



	UART_SEND_string("AT+CIPSHUT\r");
	//	while(!Check_Respond("\r\nSHUT OK\r\n"))
	//	{
	//		_delay_ms(1);
	//	}
	_delay_ms(3000);


	UART_SEND_string("AT+CIPMUX=0\r");
	//	while(!Check_Respond("\r\nOK\r\n"))
	//	{
	//		_delay_ms(1);
	//	}
	_delay_ms(3000);

	UART_SEND_string("AT+CIPMODE=0\r");
	//	while(!Check_Respond("\r\nOK\r\n"))
	//	{
	//		_delay_ms(1);
	//	}
	_delay_ms(3000);

	UART_SEND_string("AT+CGATT=1\r");
	//	while(!Check_Respond("\r\nOK\r\n"))
	//	{
	//		_delay_ms(1);
	//	}
	_delay_ms(3000);

#if WE_Network
	UART_SEND_string("AT+CSTT=\"internet.TE.eg\",\"\",\"\"\r");
#endif

#if Vodafone_Network
	UART_SEND_string("AT+CSTT=\"internet.vodafone.net\",\"internet\",\"internet\"\r");
#endif
	//	while(!Check_Respond("\r\nOK\r\n"))
	//	{
	//		_delay_ms(1);
	//	}
	_delay_ms(3000);


	UART_SEND_string("AT+CIICR\r");
	//	while(!Check_Respond("\r\nOK\r\n"))
	//	{
	//		_delay_ms(1);
	//	}
	_delay_ms(3000);


	UART_SEND_string("AT+CIFSR\r");

	_delay_ms(3000);

#if HTTP

	UART_SEND_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r");
	//	while(!Check_Respond("CONNECT\r\n\r\nOK\r\n"))
	//	{
	//		_delay_ms(1);
	//	}
	_delay_ms(3000);


	UART_SEND_string("AT+CIPSEND\r");
	_delay_ms(2000);


	UART_SEND_string("GET /update?api_key=");
	UART_SEND_string(Write_Key);

	UART_SEND_string("&field2=");
	UART_SEND_string(Data);
	UART_SEND_string("\r\n");
	UART_SendChar(0x1A);
	_delay_ms(4000);

	_delay_ms(4000);

	_delay_ms(4000);



	UART_SEND_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r");
	_delay_ms(3000);
	UART_SEND_string("AT+CIPSEND\r");
	_delay_ms(3000);

	UART_SEND_string("GET /channels/");
	UART_SEND_string(Channel_ID);
	UART_SEND_string("/feeds/last.txt\r\n");
	UART_SendChar(0x1A);
	_delay_ms(3000);
	_delay_ms(3000);

#endif

#if MQTT

	UART_SEND_string("AT+CIPSTART=\"TCP\",\"mqtt.thingspeak.com\",1883\r");
//	while(!Check_Respond("CONNECT\r\n\r\nOK\r\n"))
//	{
//		_delay_ms(1);
//	}
	_delay_ms(6000);


	UART_SEND_string("AT+CIPSEND\r");
//	while(!Check_Respond("\r\nOK\r\n> "))
//	{
//		_delay_ms(1);
//	}
	_delay_ms(3000);


	UART_SendChar(0x10);
	UART_SendChar(0x33);
	UART_SendChar(0x00);
	UART_SendChar(0x04);
	UART_SEND_string("MQTT");
	UART_SendChar(0x04);
	UART_SendChar(0xC2);
	UART_SendChar(0x00);
	UART_SendChar(0x3C);
	UART_SendChar(0x00);
	UART_SendChar(0x10);
	UART_SEND_string(Client_ID);
	UART_SendChar(0x00);
	UART_SendChar(0x03);
	UART_SEND_string(User_Name);
	UART_SendChar(0x00);
	UART_SendChar(0x10);
	UART_SEND_string(Password);



	UART_SendChar(0x1A);

//	while(!Check_Word_in_Respond("+IPD"))
//	{
//		_delay_ms(1);
//	}
//	_delay_ms(1000);

	_delay_ms(4000);
	Clear_REC_Buffer();



#if Publish



	UART_SEND_string("AT+CIPSEND\r");
//	while(!Check_Respond("\r\nOK\r\n> "))
//	{
//		_delay_ms(1);
//	}
	_delay_ms(3000);


	UART_SendChar(0x30);
	UART_SendChar(0x39);
	UART_SendChar(0x00);
	UART_SendChar(0x36);

	UART_SEND_string("channels/");
	UART_SEND_string(Channel_ID);
	UART_SEND_string("/publish/fields/field1/");
	UART_SEND_string(Write_Key);
	UART_SEND_string(Data);


	UART_SendChar(0x1A);
	_delay_ms(5000);


#endif

#if Subscribe

	UART_SEND_string("AT+CIPSEND\r");
//	while(!Check_Respond("\r\nOK\r\n> "))
//	{
//		_delay_ms(1);
//	}
	_delay_ms(3000);

	UART_SendChar(0x82);
	UART_SendChar(0x2c);
	UART_SendChar(0x00);
	UART_SendChar(0x0A);
	UART_SendChar(0x00);
	UART_SendChar(0x27);
	UART_SEND_string("channels/");
	UART_SEND_string(Channel_ID);
	UART_SEND_string("/subscribe/fields/field1");
	UART_SendChar(0x00);

	UART_SendChar(0x1A);

// Ping to Keep alive
		while(1)
		{

		UART_SEND_string("AT+CIPSEND\r");
	//	while(!Check_Respond("\r\nOK\r\n> "))
	//	{
	//		_delay_ms(1);
	//	}
		_delay_ms(3000);

		UART_SendChar(0xC0);
		UART_SendChar(0x00);

		UART_SendChar(0x1A);
		_delay_ms(5000);
		_delay_ms(5000);


		}




#endif
#endif
#endif

	return 0;
}


char Check_Respond(char * Expected_Respond)
{
	char Respond_Length=0;

	Respond_Length=strlen(Expected_Respond);

	if(strncmp(Rec_Data,Expected_Respond, Respond_Length)==0)
	{
		Clear_REC_Buffer();
		return TRUE;
	}
	return FALSE;


}


char Check_Word_in_Respond(char * Word)
{


	if(strstr(Rec_Data,Word) != 0)
	{
		Clear_REC_Buffer();
		return TRUE;
	}

	return FALSE;
}

void Clear_REC_Buffer(void)
{
	Counter=0;
	memset(Rec_Data,0,DEFAULT_BUFFER_SIZE);
}







//
