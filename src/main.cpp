#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "usart.h"

int main(void)
{
    // initialize communication channels
    UsartInit();

    int counter = 0;

    char buff[8];

    while (true)
    {
        itoa(counter, buff, 10);
        UsartSend("Hello "); 
        UsartSend(buff);
        UsartSend("\n");

        counter++;
    }

    while (1);
}