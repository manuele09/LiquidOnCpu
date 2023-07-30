#include "iris.h"

void readIrisDataset(const char *filename, float **input_matrix, int **label_matrix, int *num_samples)
{
    float a, b, c, d;
    char label[40];

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }

    // Count the number of lines in the file to determine the number of samples
    *num_samples = 0;
    while (fscanf(fp, "%f,%f,%f,%f,%s\n", &a, &b, &c, &d, label) == 5)
        (*num_samples)++;
    fseek(fp, 0, SEEK_SET);

    // Allocate memory for input matrix and label matrix
(    *input_matrix) = (float *)calloc(*num_samples * 4, sizeof(float));
    *label_matrix = (int *)calloc(*num_samples * 3, sizeof(float));

    for (int i = 0; i < *num_samples; i++)
    {
        fscanf(fp, "%f,%f,%f,%f,%s\n", &a, &b, &c, &d, label);
        (*input_matrix)[i * 4] = a;
        (*input_matrix)[i * 4 + 1] = b;
        (*input_matrix)[i * 4 + 2] = c;
        (*input_matrix)[i * 4 + 3] = d;

        if (strcmp(label, "Iris-setosa") == 0)
            (*label_matrix)[i * 3] = 1;
        else if (strcmp(label, "Iris-versicolor") == 0)
            (*label_matrix)[i * 3 + 1] = 1;
        else if (strcmp(label, "Iris-virginica") == 0)
            (*label_matrix)[i * 3 + 2] = 1;
    }
    fclose(fp);
}


void test_iris()
{

    // float *input_matrix;
    // int *label_matrix;
    // int num_samples;
    // int train_samples;
    // int test_samples;
    // int n_in = 4;
    // int n_out = 3;
    // int n_epochs = 1;

    // // Read the Iris dataset from file into input matrix and label matrix
    // readIrisDataset("../datasets/iris/iris.data", input_matrix, label_matrix, &num_samples);
    // train_samples = (int)(0.5 * num_samples);
    // test_samples = num_samples - train_samples;

    // LogisticRegression classifier;
    // LogisticRegression__construct(&classifier, train_samples, n_in, n_out);

    // // train
    // for (int epoch = 0; epoch < n_epochs; epoch++)
    //     for (int i = 0; i < train_samples; i++)
    //         LogisticRegression_train(&classifier, input_matrix[i * n_in], label_matrix[i * n_out], 0.1);

    // // test
    // float test_Y[test_samples][n_out];
    // for (int i = 0; i < test_samples; i++)
    // {
    //     LogisticRegression_predict(&classifier, input_matrix[i + train_samples], test_Y[i]);
    //     for (int j = 0; j < n_out; j++)
    //     {
    //         printf("%f (%d); ", test_Y[i][j], label_matrix[i + train_samples][j]);
    //     }
    //     printf("\n");
    // }
    // // Free memory allocated for the Iris dataset
    // LogisticRegression__destruct(&classifier);
}