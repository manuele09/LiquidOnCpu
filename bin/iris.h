#ifndef IRIS_H
#define IRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LogisticRegression.h"


#define MAX_LINE_LENGTH 100

/**
 * @brief Read the Iris dataset from file into input matrix and label matrix
 * 
 * @param filename 
 * @param input_matrix 
 * @param label_matrix 
 * @param num_samples Will contain the number of samples in the file
 */
void readIrisDataset(const char *filename, float **input_matrix, int **label_matrix, int *num_samples);

void test_iris();

#endif