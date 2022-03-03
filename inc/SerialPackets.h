#ifndef SERIAL_PACKETS_H
#define SERIAL_PACKETS_H

#include <stdint.h>

// ------------------------------------------------------------------------
// ------------------------- PACKET CONFIGURATION -------------------------
// ------------------------------------------------------------------------

// ---------------------------------
// packet lenghts (not only payload)
// ---------------------------------

const uint8_t DATA_PACKET_LEN = 19;
const uint8_t ERROR_PACKET_LEN = 5;

// total lenght of header + id
const uint8_t EXTRA_INFO_LEN = 2 + 1;

const uint8_t MIN_PACKET_LEN = 1;
const uint8_t MAX_PACKET_LEN = DATA_PACKET_LEN;

// ---------------------------------
// ---------- packet IDs -----------
// ---------------------------------

const uint8_t DATA_PACKET_ID = 0;
const uint8_t ERROR_PACKET_ID = 1;

// ---------------------------------
// -------- header & footer --------
// ---------------------------------

const uint8_t HEADER_BYTE_1 = 0xAA;
const uint8_t HEADER_BYTE_2 = 0xAA;
const uint8_t FOOTER_BYTE_1 = 0xF0;
const uint8_t FOOTER_BYTE_2 = 0x0F;

// ---------------------------------
// --------- Field lengths ---------
// ---------------------------------

// error packet
const uint8_t ERROR_ID_LEN = 1;

// data packet
const uint8_t GYRO_LEN        = 6;
const uint8_t FORCE_LEN       = 3;
const uint8_t TIME_LEN        = 2;
const uint8_t TEMPERATURE_LEN = 2;

// ---------------------------------
// --------- Field offsets ---------
// ---------------------------------

// common for all packets
const uint8_t OFFSET_PACKET_ID   = 2;

// data packet
const uint8_t OFFSET_TIME        = OFFSET_PACKET_ID     +   1;
const uint8_t OFFSET_GYRO        = OFFSET_TIME          +   TIME_LEN;
const uint8_t OFFSET_FORCE_LEFT  = OFFSET_GYRO          +   GYRO_LEN;
const uint8_t OFFSET_FORCE_RIGHT = OFFSET_FORCE_LEFT    +   FORCE_LEN;
const uint8_t OFFSET_TEMPERATURE = OFFSET_FORCE_RIGHT   +   FORCE_LEN;

// error packet
const uint8_t OFFSET_ERROR_ID    = OFFSET_PACKET_ID     +   1;

// ---------------------------------
// ---------- Error codes ----------
// ---------------------------------

// MPU error codes use bits 0 & 1
// Hx711 error codes use bits 2 & 3

const uint8_t ERROR_NO_ERROR = 0;
const uint8_t ERROR_MPU_INIT         = 1 << 0;
const uint8_t ERROR_MPU_READ         = 1 << 1;
const uint8_t ERROR_LEFT_FORCE_READ  = 1 << 2;
const uint8_t ERROR_RIGHT_FORCE_READ = 1 << 3;

#endif