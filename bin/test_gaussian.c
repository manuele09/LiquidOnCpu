#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "random_utilities.h"

// Function to find the minimum value in an array
float findMin(float arr[], int size) {
    float min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// Function to find the maximum value in an array
float findMax(float arr[], int size) {
    float max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Function to generate random samples and plot the distribution
void TestGaussian(float mean, float stddev, int num_samples) {
    // Seed the random number generator
    srand(time(NULL));

    // Store the generated samples in an array
    float samples[num_samples];
    for (int i = 0; i < num_samples; i++) {
        samples[i] = GaussianDistribution(mean, stddev);
    }

    // Print the samples and save them to a file
    FILE* fp = fopen("../gnuplot/samples.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < num_samples; i++) {
        fprintf(fp, "%f\n", samples[i]);
    }
    fclose(fp);

    // Calculate additional information
    float sum = 0.0;
    for (int i = 0; i < num_samples; i++) {
        sum += samples[i];
    }
    float calculated_mean = sum / num_samples;

    float sum_sq_diff = 0.0;
    for (int i = 0; i < num_samples; i++) {
        float diff = samples[i] - calculated_mean;
        sum_sq_diff += diff * diff;
    }
    float calculated_stddev = sqrt(sum_sq_diff / num_samples);

    float min_value = findMin(samples, num_samples);
    float max_value = findMax(samples, num_samples);

    // Create gnuplot script in C code
    FILE* gp = fopen("../gnuplot/plot_script.gp", "w");
    if (gp == NULL) {
        printf("Error creating gnuplot script file.\n");
        return;
    }
    fprintf(gp, "set terminal pngcairo enhanced size 800,600\n");
    fprintf(gp, "set output \"../gnuplot/distribution_plot.png\"\n");
    fprintf(gp, "set title \"Gaussian Distribution | Mean=%.2f | Stddev=%.2f | Min=%.2f | Max=%.2f\"\n",
            calculated_mean, calculated_stddev, min_value, max_value);
    fprintf(gp, "set xlabel \"Value\"\n");
    fprintf(gp, "set ylabel \"Frequency\"\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "binwidth=0.1\n");
    fprintf(gp, "bin(x,width)=width*floor(x/width)\n");
    fprintf(gp, "plot '../gnuplot/samples.txt' using (bin($1,binwidth)):(1.0) smooth freq with boxes title \"Samples\"\n");
    fclose(gp);

    // Use gnuplot to plot the distribution
    printf("Generating the plot...\n");
    system("gnuplot ../gnuplot/plot_script.gp");
    printf("Plot generated as \"distribution_plot.png\"\n");

    // Open the image file automatically (OS-specific commands)
    #ifdef __APPLE__ // macOS
        system("open ../gnuplot/distribution_plot.png");
    #elif _WIN32 // Windows
        system("start ../gnuplot/distribution_plot.png");
    #elif __linux__ // Linux
        system("open ../gnuplot/distribution_plot.png");
    #else
        printf("Automatic opening of the image not supported on this OS.\n");
    #endif
}

void TestGaussianClipped(float mean, float stddev, float min, float max, int num_samples) {
    // Seed the random number generator
    srand(time(NULL));

    // Store the generated samples in an array
    float samples[num_samples];
    for (int i = 0; i < num_samples; i++) {
        samples[i] = GaussianDistributionClipped(mean, stddev, min, max);
    }

        // Print the samples and save them to a file
    FILE* fp = fopen("../gnuplot/samples.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < num_samples; i++) {
        fprintf(fp, "%f\n", samples[i]);
    }
    fclose(fp);

    // Calculate additional information
    float sum = 0.0;
    for (int i = 0; i < num_samples; i++) {
        sum += samples[i];
    }
    float calculated_mean = sum / num_samples;

    float sum_sq_diff = 0.0;
    for (int i = 0; i < num_samples; i++) {
        float diff = samples[i] - calculated_mean;
        sum_sq_diff += diff * diff;
    }
    float calculated_stddev = sqrt(sum_sq_diff / num_samples);

    float min_value = findMin(samples, num_samples);
    float max_value = findMax(samples, num_samples);

    // Create gnuplot script in C code
    FILE* gp = fopen("../gnuplot/plot_script.gp", "w");
    if (gp == NULL) {
        printf("Error creating gnuplot script file.\n");
        return;
    }
    fprintf(gp, "set terminal pngcairo enhanced size 800,600\n");
    fprintf(gp, "set output \"../gnuplot/distribution_plot.png\"\n");
    fprintf(gp, "set title \"Gaussian Distribution | Mean=%.2f | Stddev=%.2f | Min=%.2f | Max=%.2f\"\n",
            calculated_mean, calculated_stddev, min_value, max_value);
    fprintf(gp, "set xlabel \"Value\"\n");
    fprintf(gp, "set ylabel \"Frequency\"\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "binwidth=0.1\n");
    fprintf(gp, "bin(x,width)=width*floor(x/width)\n");
    fprintf(gp, "plot '../gnuplot/samples.txt' using (bin($1,binwidth)):(1.0) smooth freq with boxes title \"Samples\"\n");
    fclose(gp);

    // Use gnuplot to plot the distribution
    printf("Generating the plot...\n");
    system("gnuplot ../gnuplot/plot_script.gp");
    printf("Plot generated as \"distribution_plot.png\"\n");

    // Open the image file automatically (OS-specific commands)
    #ifdef __APPLE__ // macOS
        system("open ../gnuplot/distribution_plot.png");
    #elif _WIN32 // Windows
        system("start ../gnuplot/distribution_plot.png");
    #elif __linux__ // Linux
        system("open ../gnuplot/distribution_plot.png");
    #else
        printf("Automatic opening of the image not supported on this OS.\n");
    #endif
}
