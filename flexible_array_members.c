#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_DIMENSIONS 3


typedef struct Person {
    char *name;
    bool active;
    int dimensions;
    double pos[MAX_DIMENSIONS]; // array with a fixed size, 3 * 8 bytes in size      
} Person; 

typedef struct PersonFlex {
    char *name;
    bool active;
    int dimensions;
    float pos[];   // flexible array member, placeholder for memory       
} PersonFlex; 

typedef struct BluetoothHeader
{
    uint16_t pdu_type: 4;
    uint16_t rfu_1 : 2;
    uint16_t tx_add: 1;
    uint16_t rx_add: 1;
    uint16_t length: 6;
    uint16_t rfu_2: 2;
} BluetoothHeader;

typedef struct packet {
    BluetoothHeader header;
    uint8_t payload[];  // flexible array representing the byte stream for a bluetooth payload in a packet
} Packet;


// allocate memory for a PersonFlex struct 
// + memory space for the array member (dimensions * nb of bytes hold by a double)
PersonFlex *alloc_person(int dimensions) {

    // GENERIC WAY of calculating the size for our array based on its number of wished elements 
    //                  regardless of the data type the array
    // 1.(PersonFlex *)0 = pointer to PersonFlex init with NULL
    // 2. ->pos[0] = accessing the first elem from the array member of the pointer to PersonFlex
    size_t size = sizeof((PersonFlex *)0)->pos[0];  

    printf("sizeof array member of struct PersonFlex: %llu\n", size);
    // 3 Creating the struct using dynamic allocation
    //.  Allocating space for the struct + the array with the above calculation
    PersonFlex *person = malloc(sizeof(PersonFlex) + dimensions * size);

    // always make sure malloc() was successful
    // otherwise the code after the if block might try to access a NULL pointer
    if (!person)
    {
        return NULL;
    }
    
    person->dimensions = dimensions; // init the dimension field of the struct
    return person;
}

// Reading a Bluetooth packet
// Using the technique of a struct combined with a flexible array member inside it
void read_bluetooth_packet(Packet *packet) {
    int len = packet->header.length;
    for (int i = 0; i < len; i++)
    {
        printf("%x", packet->payload[i]);
    }
    printf("\n");
}

/**
 * We will see how to use flexible array memebers
 * A very useful practise, widely used in telecommunications protocols
 * especially in network programming 
 * 
 * Flexible arrays can only be declared in structs when there are last members
 */
int main() {

    printf("\n=== Flexible Array Members ===\n");

    printf("sizeof(Person): %lu\n", sizeof(Person));
    printf("sizeof(PersonFlex): %lu\n", sizeof(PersonFlex));

    alloc_person(3);

    // the first two bytes = bluetooth header
    // So the header will tell of the length of the bluetooth payload
    // the rest is the paylod
    const uint8_t rx_buffer[] = {0x41, 0x06, 0xCA, 0xFE, 0xCA, 0xFE, 0xCA, 0xFE}; 
    read_bluetooth_packet((Packet *) rx_buffer);
    
    printf("\n");

    return EXIT_SUCCESS;
}