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


     /* Struct declaration */
    struct Person {
        // members of the struct
        char *name;
        bool active;
        int dimensions;
        double pos[MAX_DIMENSIONS];    // flexible array member
    };

    /* Using a struct */
    // 1. Declare a variable typed by the name of the declared struct
    //.   Here elon and bill are both structs of type Person
    struct Person elon, bill;

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