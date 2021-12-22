#include "usart.h"

void UsartInit()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#else
	UCSR0A &= ~(1 << U2X0);
	#endif
	UCSR0B|= (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);

	sei();
}

void UsartSend(const char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void UsartSend(const char* data, int len)
{
	while(len--)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *data++;
	}
}

void UsartSend(const char* szData)
{
	while(*szData)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *szData++;
	}
}

void UsartSend(int num)
{
	char buff[6];
	uint16_t unsignedVal;

	if(num < 0)
	{
		unsignedVal = -num;
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = '-';
	}
	else
	{
		unsignedVal = num;
	}
	

	char* ptr = buff;

	do 
	{
		*ptr++ = unsignedVal % 10 + '0';
		unsignedVal /= 10;
	} 
	while (unsignedVal);

	ptr--;

	while(ptr >= buff)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *ptr--;
	}
}

void UsartSend(long num)
{
	char buff[10];
	if(num < 0)
	{
		num=-num;
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = '-';
	}

	char* ptr = buff;

	do
	{
		*ptr++ = num%10 + '0';
		num/=10;
	} while (num);

	ptr--;

	while(ptr >= buff)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *ptr--;
	}
}

void UsartSend(unsigned int unum)
{
	char buff[5];
	char* ptr = buff;

	do
	{
		*ptr++ = unum%10 + '0';
		unum/=10;
	} while (unum);

	ptr--;

	while(ptr >= buff)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *ptr--;
	}
}

void UsartSend(unsigned long unum)
{
	char buff[10];
	char* ptr = buff;

	do
	{
		*ptr++ = unum%10 + '0';
		unum/=10;
	} while (unum);

	ptr--;

	while(ptr >= buff)
	{
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *ptr--;
	}
}

volatile char rxBuff[RX_BUFFER_SIZE];
volatile char rxIdx, rxLen;

#define UsartAvailable rxLen

ISR(USART_RX_vect)
{
	rxBuff[rxIdx++] = UDR0;
	rxIdx &= RX_BUFFER_SIZE - 1;
	if(!(rxLen & RX_BUFFER_SIZE)) rxLen++;
}

bool UsartRead(char* c)
{
	if(rxLen > 0)
	{
        const int startIdx = (rxIdx + RX_BUFFER_SIZE - rxLen) & (RX_BUFFER_SIZE - 1);
		*c = rxBuff[startIdx];
		rxLen--;
		return true;
	} 
    return false;
}

bool UsartRead(char* buff, int len)
{
	if(len > rxLen) return false;
	
	cli();

    // circular buffer read
    const int startIdx = (rxIdx + RX_BUFFER_SIZE - rxLen) & (RX_BUFFER_SIZE - 1);
    for (int i = 0; i < len; i++)
    {
        buff[i] = rxBuff[(startIdx + i) & (RX_BUFFER_SIZE - 1)];
    }
	rxLen -= len;

	sei();

	return true;
}

void UsartNewLine()
{
	UsartSend('\r');
	UsartSend('\n');
}