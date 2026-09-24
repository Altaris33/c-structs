#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_DIMENSIONS 3


typedef struct PersonP {
    char *name;
    char *job;
    bool active;
    int dimensions;
    double pos[MAX_DIMENSIONS];       
} PersonP; 

typedef struct PersonArr {
    char *name;
    char job[64];
    bool active;
    int dimensions;
    double pos[MAX_DIMENSIONS];       
} PersonArr; 

/**
 * We will see the differences between using pointer members and array members
 * and how to handle each
 */
int main() {

    printf("\n=== Pointers Vs Array Members in Structures ===\n");

    // 1. Memory difference: How much each version take up in memory
    // the size of char * is by default 8 byte
    printf("sizeof(PersonP) = %lu\n", sizeof(PersonP));
    // the size of job[64] is fixed in size -> 64 char so 64 * 1 byte
    printf("sizeof(PersonA) = %lu\n", sizeof(PersonArr));

    // 2. Usage differences:
    // Pointer member : can be set because memory will be reallocated dynamically
    PersonP bill = {
        .name = "Bill Gates",
        .job = "Software Programmer", // pointer allocating memory, so at a given address
        .active = true,
    };

    // newly allocated memory i.e. new address
    bill.job = "I founded Microsoft";

    // Array member (char array here):
    PersonArr elon = {
        .name = "Elon Musk",
        .job = "Software Programmer", // the str literal is copied inside the array
        .active = true,
    };

    //elon.job = "new job"; // WRONG: we cannot assign a string array with the = operator
    // we have to use methods to copy the new string literal into our char array member
    // we will always be limited to copying str literal up to the size 
    // of our char array - 1
    strncpy(elon.job, "I am super rich", sizeof(elon.job) - 1);  // sizeof - 1 so that the \0 character has its slot
 
    printf("\n");

    return EXIT_SUCCESS;
}