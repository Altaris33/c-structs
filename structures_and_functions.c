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
    double pos[MAX_DIMENSIONS];   
    struct Person *friend;      
} Person; 

// 1st way :
// create & return a bill variable that is returned as a copy of the struct
Person create_bill(){
    return (Person) {
        .name = "Bill",
        .pos = {1, 2, 3},
        .dimensions = 2,
        .active = true,
    };
}

// 2nd way: Dynamically allocate memory for a struct & return a pointer(an address) to the struct
Person *alloc_elon(){
    Person *elon = malloc(sizeof(Person));

    if (!elon)
    {
        return NULL;
    }

    // Setting
    elon->name = "Elon";
    elon->active = true;
    elon->dimensions = 2;
    double pos[] = {4, 6, 6};
    memcpy(elon->pos, pos, sizeof(pos));
    elon->friend = NULL;

    return elon;
    
}

// Passing a whole struct as a copy in a function
void deactivate_person(Person p) {
    p.active = false;
}

// Passing a pointer in a function
void deactivate_person_ptr(Person *p){
    p->active = false;
}

/**
 * We will see:
 * - how to use structs along with functions
 *  - how to pass structs as arguments in functions
 *  - how to return structs from functions and get them (in 2 ways)
 *  - the difference between passing a struct as a copy and through a pointer
 * 
 * CREATING STRUCTs
 * 1. Either by creating and returning the struct
 * 2. Or use a pointer to create one (in the case of a Linked List for ex)
 * 
 * PASSING STRUCTS AS AGUMENTS
 * In C, arguments are always passed as "copy". Be it a copy of a variable or a pointer variable
 * So if we pass a struct as argument, we will pass a copy that's created by C.
 * The method will only modify the copy, not the original variable passed from main()
 * So if our intent is to modify and work with the original, we need to pass a pointer (a copy of the address)
 * 
 * The approach we will choose will depend on our scenario.
 */
int main() {

    printf("\n=== Structures & Functions ===\n");

    // one local variable that is of type Person
    Person bill = create_bill();

    // attach another struct through a pointer to the member friend (of type Person *)
    // concept of a Linked List
    bill.friend = alloc_elon();
    
    // active won't be changed since only the copy inside deactivate_person() is changed
    deactivate_person(bill);
    printf("bill.active = %d\n", bill.active);
    
    // passing the address of the original struct will allow deactivate to change it
    // main can pass it over and get it back updated
    deactivate_person_ptr(&bill);
    printf("bill.active = %d\n", bill.active);
    
    printf("\n");

    return EXIT_SUCCESS;
}