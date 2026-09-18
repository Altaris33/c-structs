#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define LEN 10

typedef struct Sample
{
    double temperature;
    time_t timestamp;
} Sample;

int rand_range_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

double rand_range(double min, double max, int decimal_digits) {
    double scale_factor = pow(10, decimal_digits);
    int scaled_min = round(min * scale_factor);
    int scaled_max = round(max * scale_factor);
    return rand_range_int(scaled_min, scaled_max) / scale_factor; 
}

double get_temperature() {
    return rand_range(20, 25, 1);
}


int main() {

    printf("\n=== Arrays of Structure ===\n");

    /* Let's build a temperature logger: it logs temperature along with its timestamp 
    * To store the data, we will build a struct that stores:
    * 1. the temperature
    * 2. the timestamp in UTC
    * We will then build an array of this struct
    */
    
    // Create the array of the defined struct
    Sample samples[LEN];

    // Populate the array with data
    for (int i = 0; i < LEN; i++)
    {
        printf("Sample %d\n", i);

        samples[i].timestamp = time(NULL);
        samples[i].temperature = get_temperature();

        sleep(1);
    }

    /* print timestamp, time offset from first sample, temperature */
    printf("\ntimestamp, time offset, temperature\n");

    for (int i = 0; i < LEN; i++)
    {
        printf("%lld, %lld, %5.1f\n", 
                samples[i].timestamp,
                samples[i].timestamp - samples[0].timestamp,
                samples[i].temperature);
    }
    

    printf("\n");
       
    return EXIT_SUCCESS;
}

