#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "test_gaussian.h"
#include "LogisticRegression.h"

#define MAX_LINE_LENGTH 100

void readIrisDataset(const char *filename, float ***input_matrix, int ***label_matrix, int *num_samples)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }

    // Count the number of lines in the file to determine the number of samples
    *num_samples = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        (*num_samples)++;
    }
    // Allocate memory for input matrix and label matrix
    *input_matrix = (float **)malloc(*num_samples * sizeof(float *));
    *label_matrix = (int **)malloc(*num_samples * sizeof(float *));
    for (int i = 0; i < *num_samples; i++)
    {
        (*input_matrix)[i] = (float *)malloc(4 * sizeof(float));
        (*label_matrix)[i] = (int *)malloc(3 * sizeof(float));
    }

    // Rewind the file pointer to the beginning
    fseek(fp, 0, SEEK_SET);

    // Read data from the file and store in the allocated matrices
    int i = 0;
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL && i < *num_samples)
    {
        // Read the four feature values
        sscanf(line, "%f,%f,%f,%f,%*[^,\n]", &((*input_matrix)[i][0]),
               &((*input_matrix)[i][1]), &((*input_matrix)[i][2]), &((*input_matrix)[i][3]));

        // Read the label and convert it into a one-hot encoded format
        char label[20];
        sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%19[^,\n]", label);
        if (strcmp(label, "Iris-setosa") == 0)
        {
            (*label_matrix)[i][0] = 1;
            (*label_matrix)[i][1] = 0;
            (*label_matrix)[i][2] = 0;
        }
        else if (strcmp(label, "Iris-versicolor") == 0)
        {
            (*label_matrix)[i][0] = 0;
            (*label_matrix)[i][1] = 1;
            (*label_matrix)[i][2] = 0;
        }
        else if (strcmp(label, "Iris-virginica") == 0)
        {
            (*label_matrix)[i][0] = 0;
            (*label_matrix)[i][1] = 0;
            (*label_matrix)[i][2] = 1;
        }
        else
        {
            // Unknown label, set all to 0
            (*label_matrix)[i][0] = 0;
            (*label_matrix)[i][1] = 0;
            (*label_matrix)[i][2] = 0;
        }

        i++;
    }

    fclose(fp);
}

// Function to free memory allocated for the Iris dataset
void freeIrisDataset(float **input_matrix, int **label_matrix, int num_samples)
{
    for (int i = 0; i < num_samples; i++)
    {
        free(input_matrix[i]);
        free(label_matrix[i]);
    }
    free(input_matrix);
    free(label_matrix);
}

int main()
{

    float **input_matrix;
    int **label_matrix;
    int num_samples;
    int train_samples;
    int test_samples;
    int n_in = 4;
    int n_out = 3;
    int n_epochs = 10;

    // Read the Iris dataset from file into input matrix and label matrix
    readIrisDataset("../datasets/iris/iris.data", &input_matrix, &label_matrix, &num_samples);
    train_samples = (int)(0.5 * num_samples);
    test_samples = num_samples - train_samples;

    LogisticRegression classifier;
    LogisticRegression__construct(&classifier, train_samples, n_in, n_out);

    // train
    for (int epoch = 0; epoch < n_epochs; epoch++)
        for (int i = 0; i < train_samples; i++)
            LogisticRegression_train(&classifier, input_matrix[i], label_matrix[i], 0.1);

    // test
    float test_Y[test_samples][n_out];
    for (int i = 0; i < test_samples; i++)
    {
        LogisticRegression_predict(&classifier, input_matrix[i + train_samples], test_Y[i]);
        for (int j = 0; j < n_out; j++)
        {
            printf("%f ", test_Y[i][j]);
        }
        printf("\n");
    }
    // Free memory allocated for the Iris dataset
    LogisticRegression__destruct(&classifier);
    freeIrisDataset(input_matrix, label_matrix, num_samples);

    return 0;
}
