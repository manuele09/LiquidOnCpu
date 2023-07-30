#ifndef DATASET_H
#define DATASET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
//Dataset for logistic regression
struct Dataset
{
    float *dataset;
    int *labels;

    int num_samples;
    int num_features;
    int num_classes;

    float *train_dataset;
    int *train_labels;

    float *test_dataset;
    int *test_labels;

    int num_train_samples;
    int num_test_samples;
};
typedef struct Dataset Dataset;

//aggiungere normalizzazione

Dataset *create_dataset(float *dataset, int *labels, int num_samples, int num_features, int num_classes);

void split_dataset(Dataset *dataset, float train_ratio);

float cross_entropy(float *prediction, int *target, int num_samples, int num_classes);

float accuracy(float *prediction, int *target, int num_samples, int num_classes);

void print_dataset(Dataset *dataset, bool print_all, bool print_train, bool print_test);

void free_dataset(Dataset *dataset);
#endif