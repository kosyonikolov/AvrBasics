#ifndef USART_H_
#define USART_H_

#define BAUD 57600 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

typedef unsigned char ubyte;

void UsartInit();
void UsartSend(const char data);
void UsartSend(const char* data, int len);
void UsartSend(const char* szData);
void UsartSend(int num);
void UsartSend(long num);
void UsartSend(unsigned int unum);
void UsartSend(unsigned long unum);
void UsartNewLine();

// must be multiple of two
#define RX_BUFFER_SIZE 64

ISR(USART_RX_vect);

// Read single character
// Returns false when no data is available
bool UsartRead(char* c);

// Read into len bytes into buffer
// Returns false when not enough data is available
bool UsartRead(char* buff, int len);

#endif /* UART_H_ */