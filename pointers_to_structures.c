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

/**
 * In this small program we will:
 * - show how to use pointers with structs
 * - show different ways of creating and managing structs, through pointers
 * - many ways of accessing structs members using either standard notations or pointer-related notations
 */
int main() {

    printf("\n=== Pointers to Structures ===\n");

    // Explicit initialization  
    Person bill = {
        .name = "Bill Gates",
        .active = true,
        .dimensions = 3,
        .pos = {3, 2, 1},

    };

    // Creating a pointer to the struct using the address of operator
    Person *firstPerson = &bill;

    // Different ways of accessing the struct
    // 1. Accessing the struct directly
    printf("Person name: %s\n", bill.name);

    // 2. Accessing the struct through a pointer, by the mean of the indirection operator (star operator)
    // We must enclose the indirection in parentheses so that it takes precedence 
    // over the accessing of the struct field
    // In other word, the indirection happens first -> (*pointerToPerson)
    // Then, we access a member of the structure -> (*pointerToPerson).name
    printf("Person name: %s\n", (*firstPerson).name);

    // 3. Most common method: Accessing the struct through a pointer using the arrow operator
    printf("Person name: %s\n", firstPerson->name);
    printf("Person active: %d\n", firstPerson->active);
    printf("Person dimensions: %d\n", firstPerson->dimensions);
    printf("Person position: %.1f %.1f %.1f\n",
        firstPerson->pos[0],
        firstPerson->pos[1],
        firstPerson->pos[2]);

    // the dot (.) notation is used to access the struct directly
    // while the arrow (->) operator is used to access the struct through a pointer

    // 4. Principle of the Single Linked List
    // We currently have declared a member from our struct Person
    // as a pointer of Person itself (see typedef above)

    // So, we can allocate a portion of memory to store a struct of type Person
    // and storing this portion to the member friend in the pointer pointerToPerson
    firstPerson->friend = malloc(sizeof(Person));
    firstPerson->friend->name = "Elon Musk";
    firstPerson->friend->active = false;

    // Go through the list
    // This is not a common practise, but just to show how we can walk through the list manually
    firstPerson->friend->friend = malloc(sizeof(Person));
    firstPerson->friend->friend->name = "Captain";

    // 5. Allocate an array of a struct using a pointer
    int num = 10;
    // returns a 10 element array of type Person, stored in this pointer
    Person *manyPersons = malloc(num * sizeof(Person));

    // accessing an element using the square bracket notation
    manyPersons[0].name = "Mario";
    manyPersons[0].friend = &bill;

    // accessing another element using a pointer arithmetic instead
    // Here: we increment the address so that it points to the second element of the array
    //.      (manyPersons + 1) will therefore give us another address, that of the second elem
    (manyPersons + 1)->name = "Luigi";

    // let's now print the second elem name
    printf("manyPersons[1].name = %s\n", manyPersons[1].name);
    

    printf("\n");

    return EXIT_SUCCESS;
}