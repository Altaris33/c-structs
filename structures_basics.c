#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


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
 * Struct data type in C:
 * - 
 * 
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

    // Implementing the data in a raw manner
    char elon_name[] = "Elon Musk";
    bool elon_active = true;
    int elon_dimensions = 3;
    double elon_pos[] = {1, 2, 3};

    char bill_name[] = "Bill Gates";
    bool bill_active = true;
    int bill_dimensions = 2;
    double bill_pos[] = {3, 2, 1};

    // checking if we can calculate the distance between the two
    // i.e. if one of them is not active
    if (!bill_active || !elon_active)
    {
        printf("%s isn't active.\n", !bill_active ? bill_name : elon_name);
        return EXIT_FAILURE;
    }
    
    // check if both belong to the same universe (2D, 3D...)
    if (elon_dimensions != bill_dimensions)
    {
        printf("%s and %s are in different dimensions !\n", bill_name, elon_name);
        return EXIT_FAILURE;
    }

    printf("Distance between %s and %s is: %.1f\n", elon_name, bill_name,
                        calculate_distance(elon_dimensions, elon_pos, bill_pos));
    

    return EXIT_SUCCESS;
}