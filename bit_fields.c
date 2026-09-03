#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

// Without using Bit Fields
// Let's use a struct to store on-off statuses for LED in an embedded system
typedef struct LedStatus {
    // uint8_t is 8 bits so 1 byte long
    uint8_t led_1;
    uint8_t led_2;
    uint8_t led_3;
} LedStatus;

// Using bit fields in a structure
// Using the notation : n (length in bits)
typedef struct LedStatusBF {
    uint8_t led_1 : 1;
    uint8_t led_2 : 1;
    uint8_t led_3 : 1;
} LedStatusBF;

typedef struct BleHeader
{
    uint16_t pdu_type: 4;
    uint16_t rfu_1 : 2;
    uint16_t tx_add : 1;
    uint16_t rx_add : 1;
    uint16_t length : 6;
    uint16_t rfu_2 : 2;
} BleHeader;


/**
 * Bit Fields are particular data types that can be declared within structs
 * 
 * Very useful in embedded systems or telecommunication protocol systems
 * 
 * DEFINITION: Fields in which we can specify a precise length in bits
 * 
 * It is particularly useful for precisely assigning memory bit by bit, without wasting any memory
 * Highly convenient for small systems where physical memory is limited
 * As well as telecom protocols systems, that use bit streams
 * One example is the use of Bluetooth Low Energy Data Packet
 * 
**/


/**
 * print a portion of memory bit by bit
 * 
 * Scan up all bit that make up the incoming bytes, starting from the least significant bit to the most
 * 
 * We iterate until we have read all the bytes to read
 * 
**/ 
void print_bits(uint8_t *data, int size) {
    for (int i = 0; i < size; i++)
    {
        uint8_t byte = data[i];
        // inner loop to scan & print each bit from the current byte (8-step for loop)
        for (int j = 0; j < 8; j++)
        {
            // bit mask
            // take the byte, shift it j bits to the right, towards the least significant bit
            // then apply a bitwise AND to 1 so we will only select 1 bit
            printf("%d", (byte >> j) & 1);
        }
    }   
    printf("\n");
}

int main() {

    printf("\n=== Structs: Bit Fields ===\n");

    printf("size of (LedStatus): %ld\n", sizeof(LedStatus));
    printf("size of (LedStatusBF): %ld\n", sizeof(LedStatusBF));

    LedStatusBF status = {
        .led_1 = 1,
        .led_2 = 1,
        .led_3 = 1,
    };

    // 11100000 : the 3 bits are init at the left side, all non-set bits are init to 0
    print_bits((uint8_t *) &status, sizeof(status));  // size is 1

    status.led_1 = 0;
    status.led_2 = 0;

    // 00100000
    print_bits((uint8_t *) &status, sizeof(status));  // size is 1

    // Context : Telecommunications
    // Let's see how bit fields are used in this context
    // Bluetooth Low Energy Data Packet
    // A struct for the header of the Packet Payload can be implemented using a struct and bit fields
    BleHeader header = {
        .pdu_type = 3,
        .tx_add = 1,
        .length = 7        
    };

    print_bits((uint8_t *) &header, sizeof(header));

    printf("\n");
       

    return EXIT_SUCCESS;
}

