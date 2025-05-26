#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()  {
    // Randomly generate the rainfall amount for a five-year period
    float rainfallYear[5][12];
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 12; j++) {
            rainfallYear[i][j] = (rand() % 501);
        }
    }

    // Calculate the total rainfall for each year
    float totalRainfall[5] = {0};
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 12; j++) {
            totalRainfall[i] += rainfallYear[i][j];
        }
    }

    // Calculate the average rainfall for each year
    float averageRainfall[5];
    for (int i = 0; i < 5; i++) {
        averageRainfall[i] = totalRainfall[i] / 12.0f;
    }

    // Calculate the average rainfall per month
    float averageMonthlyRainfall[12] = {0};
    for (int j = 0; j < 12; j++) {
        for (int i = 0; i < 5; i++) {
            averageMonthlyRainfall[j] += rainfallYear[i][j];
        }
        averageMonthlyRainfall[j] /= 5.0f;
    }

    // Display the results
    printf("Yearly Rainfall Data:\n");
    for (int i = 0; i < 5; i++) {
        printf("Year %d: Total Rainfall = %.2f, Average Rainfall = %.2f\n", 
               i + 1, totalRainfall[i], averageRainfall[i]);
    }
    printf("\nMonthly Average Rainfall Data:\n");
    for (int j = 0; j < 12; j++) {
        printf("Month %d: Average Rainfall = %.2f\n", j + 1, averageMonthlyRainfall[j]);
    }
    printf("\nRainfall Data for Each Year:\n");
    printf("Year/Month: ");
    for (int j = 0; j < 12; j++) {
        printf("%d ", j + 1);
    }
    printf("\n");
    for (int i = 0; i < 5; i++) {
        printf("Year %d: ", i + 1);
        for (int j = 0; j < 12; j++) {
            printf("%.2f ", rainfallYear[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
