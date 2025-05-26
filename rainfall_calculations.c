#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_YEARS 5
#define MAX_MONTHS 12

int main()  {
    // Randomly generate the rainfall amount for a five-year period
    float rainfallYear[MAX_YEARS][MAX_MONTHS];
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < MAX_YEARS; i++) {
        for (int j = 0; j < MAX_MONTHS; j++) {
            rainfallYear[i][j] = (rand() % 501);
        }
    }

    // Calculate the total rainfall for each year
    float totalRainfall[MAX_YEARS] = {0};
    for (int i = 0; i < MAX_YEARS; i++) {
        for (int j = 0; j < MAX_MONTHS; j++) {
            totalRainfall[i] += rainfallYear[i][j];
        }
    }

    // Calculate the average rainfall for each year
    float averageRainfall[MAX_YEARS];
    for (int i = 0; i < MAX_YEARS; i++) {
        averageRainfall[i] = totalRainfall[i] / MAX_MONTHS;
    }

    // Calculate the average rainfall per month
    float averageMonthlyRainfall[MAX_MONTHS] = {0};
    for (int j = 0; j < MAX_MONTHS; j++) {
        for (int i = 0; i < MAX_YEARS; i++) {
            averageMonthlyRainfall[j] += rainfallYear[i][j];
        }
        averageMonthlyRainfall[j] /= MAX_YEARS;
    }

    // Display the results
    printf("Yearly Rainfall Data:\n");
    for (int i = 0; i < MAX_YEARS; i++) {
        printf("Year %d: Total Rainfall = %.2f, Average Rainfall = %.2f\n", 
               i + 1, totalRainfall[i], averageRainfall[i]);
    }
    printf("\nMonthly Average Rainfall Data:\n");
    for (int j = 0; j < MAX_MONTHS; j++) {
        printf("Month %d: Average Rainfall = %.2f\n", j + 1, averageMonthlyRainfall[j]);
    }
    printf("\nRainfall Data for Each Year:\n");
    printf("Year/Month: ");
    for (int j = 0; j < MAX_MONTHS; j++) {
        printf("%d ", j + 1);
    }
    printf("\n");
    for (int i = 0; i < MAX_YEARS; i++) {
        printf("Year %d: ", i + 1);
        for (int j = 0; j < MAX_MONTHS; j++) {
            printf("%.2f ", rainfallYear[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
