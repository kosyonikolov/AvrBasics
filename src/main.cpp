#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#include "usart.h"
#include "SerialPackets.h"

int main(void)
{
    // initialize communication channels
    UsartInit();

    // Prepare serial packets 
    uint8_t dataPacket[DATA_PACKET_LEN];
    uint8_t errorPacket[ERROR_PACKET_LEN];

    int gyro = 600; // About 360 deg/s

    // set bytes to initial values
    {
        memset(dataPacket, 0, DATA_PACKET_LEN);

        // header & footer
        dataPacket[0] = HEADER_BYTE_1;
        dataPacket[1] = HEADER_BYTE_2;

        errorPacket[0] = HEADER_BYTE_1;
        errorPacket[1] = HEADER_BYTE_2;

        // length and id (all packets are currently fixed size)
        dataPacket[OFFSET_PACKET_ID]   = DATA_PACKET_ID;
        errorPacket[OFFSET_PACKET_ID]  = ERROR_PACKET_ID;

        dataPacket[OFFSET_GYRO + 0] = gyro >> 8;
        dataPacket[OFFSET_GYRO + 1] = gyro & 0xFF;
        dataPacket[OFFSET_FORCE_LEFT + 2] = 23;
    }

    // --------------------------------------------------------------
    // ------------------ Main sensor reading loop ------------------
    // --------------------------------------------------------------

    // start timer 1 (16 bit) for timestamps
    TCNT1 = 0;
    // prescale = 1024 => 1 tick is about 1/8th of a millisecond
    // it will overflow every 8-9 seconds but that doesn't concern us
    // because only the time between packets is important
    TCCR1B = 0b101; 

    while (true)
    {
        // timestamp
        uint16_t packetTime = TCNT1;
        dataPacket[OFFSET_TIME]     = packetTime >> 8;
        dataPacket[OFFSET_TIME + 1] = packetTime & 0xFF;
        UsartSend((char*)dataPacket, DATA_PACKET_LEN);

        _delay_ms(1000.0 / 80); // 80 Hz target
    }
}