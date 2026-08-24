#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_DIMENSIONS 3

/**
 * This program will calculate the distance between two objects (persons)
 * 
 * The concept (or object of person) here is:
 * - a collection of various data types
 * 
 * Calculating the distance between two objects:
 * - in a cartesian 2D system ->  sqrt( pow(x2 - x1) + pow(y2 - y1) ),
 * since each person has its x and y position points
 * 
 * 
 * Let's try to implement the program without using a Struct
 * 
 * First version : we create each field for our objects manually 
 *      Our data is not structured and can get messy as the program grows
 * 
 * Second version: Using structs
 * Struct data type in C:
 * - through the use of the struct keyword, C allows us to create structured data types
 * - each structure is made up of "members" (independent variables)
 * - we can think of members all the data components, packaged together -> struct
 */


// smart function which will calculate the distance, in a versatile way
// by taking the number of dimensions into account
// we use variable length arrays to pass in the number of dimensions
// this is useful here, because we can pass the number of elements for each array, using a parameter
// and not a fixed value

/* Struct declaration */
// Standard way
struct PersonStruct {
    // members of the struct
    char *name;
    bool active;
    int dimensions;
    double pos[MAX_DIMENSIONS];    // flexible array member
};

/* Alternative: using typedef */
// Defining a new type of structure called/aliased as "Person"
// This kind of declaration is called an anonymous structure
typedef struct {
    char *name;
    bool active;
    int dimensions;
    double pos[MAX_DIMENSIONS];  
} PersonAnon;  // structure alias

// A better way is by giving a "tag" to the structure
// By giving it the same name as its alias at the end (good practise)
// It's also good practise to name the tag and alias identically 
typedef struct Person { // structure tag
    char *name;
    bool active;
    int dimensions;
    double pos[MAX_DIMENSIONS];   
    struct Person *friend;      // we can define a member that is of the type of the structure itself
} Person; // structure alias -> will alias the structure by its tag defined above

// Nested structures
// A structure can hold another one as member
typedef struct Motorcycle {
    char *model;
    double speed;
    Person owner;
} Motorcycle;

double calculate_distance(int dimensions, double a[dimensions], double b[dimensions])
{
    double square_distance = 0;
    for (int i = 0; i < dimensions; i++)
    {
        square_distance += pow(a[i] - b[i], 2);
    }
    return sqrt(square_distance);
}


int main() {

    printf("\n=== Structuring Data ===\n");

    /* Using a struct */
    // 1. Declare a variable typed by the name of the declared struct
    //.   Here elon and bill are both structs of type Person
    Person elon, bill;

    Motorcycle moto;
    moto.model = "honda";
    moto.speed = 300;
    moto.owner.name = "Captain";

    // 2. Access and set members from a struct (in write mode)
    elon.name = "Elon Musk";
    elon.active = true;
    elon.dimensions = 3;
    elon.pos[0] = 1;
    elon.pos[1] = 2;
    elon.pos[2] = 3;

    bill.name = "Bill Gates";
    bill.active = true;
    bill.dimensions = 3;
    bill.pos[0] = 3;
    bill.pos[1] = 2;
    bill.pos[2] = 1;

    // checking if we can calculate the distance between the two
    // i.e. if one of them is not active
    // access an individual member in read mode
    if (!bill.active || !elon.active)
    {
        printf("%s isn't active.\n", !bill.active ? bill.name : elon.name);
        return EXIT_FAILURE;
    }
    
    // check if both belong to the same universe (2D, 3D...)
    if (elon.dimensions != bill.dimensions)
    {
        printf("%s and %s are in different dimensions !\n", bill.name, elon.name);
        return EXIT_FAILURE;
    }

    printf("Distance between %s and %s is: %.1f\n", elon.name, bill.name,
                        calculate_distance(elon.dimensions, elon.pos, bill.pos));

    return EXIT_SUCCESS;
}