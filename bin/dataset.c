#include "dataset.h"

Dataset *create_dataset(float *dataset, int *labels, int num_samples, int num_features, int num_classes)
{
    Dataset *d = (Dataset *)malloc(sizeof(Dataset));
    d->dataset = dataset;
    d->labels = labels;
    d->num_samples = num_samples;
    d->num_features = num_features;
    d->num_classes = num_classes;

    d->train_dataset = NULL;
    d->train_labels = NULL;
    d->test_dataset = NULL;
    d->test_labels = NULL;

    return d;
}

void split_dataset(Dataset *dataset, float train_ratio)
{
    int train_samples = (int)(train_ratio * dataset->num_samples);
    int test_samples = dataset->num_samples - train_samples;

    dataset->train_dataset = (float *)calloc(train_samples * dataset->num_features, sizeof(float));
    dataset->train_labels = (int *)calloc(train_samples * dataset->num_classes, sizeof(int));
    dataset->test_dataset = (float *)calloc(test_samples * dataset->num_features, sizeof(float));
    dataset->test_labels = (int *)calloc(test_samples * dataset->num_classes, sizeof(int));

    int *indexs = (int *)calloc(dataset->num_samples, sizeof(float));
    for (int i = 0; i < dataset->num_samples; i++)
        indexs[i] = i;

    // shuffle indexs
    for (int i = 0; i < dataset->num_samples; i++)
    {
        int j = rand() % dataset->num_samples;
        int temp = indexs[i];
        indexs[i] = indexs[j];
        indexs[j] = temp;
    }

    for (int i = 0; i < train_samples; i++)
    {
        for (int j = 0; j < dataset->num_features; j++)
            dataset->train_dataset[i * dataset->num_features + j] = dataset->dataset[indexs[i] * dataset->num_features + j];
        for (int j = 0; j < dataset->num_classes; j++)
            dataset->train_labels[i * dataset->num_classes + j] = dataset->labels[indexs[i] * dataset->num_classes + j];
    }

    for (int i = 0; i < test_samples; i++)
    {
        for (int j = 0; j < dataset->num_features; j++)
            dataset->test_dataset[i * dataset->num_features + j] = dataset->dataset[indexs[i + train_samples] * dataset->num_features + j];
        for (int j = 0; j < dataset->num_classes; j++)
            dataset->test_labels[i * dataset->num_classes + j] = dataset->labels[indexs[i + train_samples] * dataset->num_classes + j];
    }

    dataset->num_train_samples = train_samples;
    dataset->num_test_samples = test_samples;
}

float cross_entropy(float *prediction, int *target, int num_samples, int num_classes)
{
    float loss = 0;
    for (int i = 0; i < num_samples; i++)
    {
        for (int j = 0; j < num_classes; j++)
        {
            loss += -target[i * num_classes + j] * log(prediction[i * num_classes + j]);
        }
    }
    return loss;
}

float accuracy(float *prediction, int *target, int num_samples, int num_classes)
{
    int wrong_predictions = 0;
    float max;
    int max_index;
    for (int i = 0; i < num_samples; i++)
    {
        max = -1;
        for (int j = 0 ; j < num_classes; j++)
            if (prediction[i * num_classes + j] > max)
            {
                max = prediction[i * num_classes + j];
                max_index = j;
            }

        wrong_predictions += 1 ? target[i * num_classes + max_index] == 0 : 0;
    }
    return 1 - ((float)wrong_predictions / num_samples);
    // return wrong_predictions;
}

void print_dataset(Dataset *dataset, bool print_all, bool print_train, bool print_test)
{

    if (print_all)
    {
        printf("Complete Dataset:\n");
        for (int i = 0; i < dataset->num_samples; i++)
        {
            printf("%4d) ", i);
            for (int j = 0; j < dataset->num_features; j++)
                printf("%.2f ", dataset->dataset[i * dataset->num_features + j]);
            for (int j = 0; j < dataset->num_classes; j++)
                printf("%d ", dataset->labels[i * dataset->num_classes + j]);
            printf("\n");
        }
    }

    if (print_train)
    {
        printf("Train Dataset:\n");
        for (int i = 0; i < dataset->num_train_samples; i++)
        {
            printf("%4d) ", i);
            for (int j = 0; j < dataset->num_features; j++)
                printf("%.2f ", dataset->train_dataset[i * dataset->num_features + j]);
            for (int j = 0; j < dataset->num_classes; j++)
                printf("%d ", dataset->train_labels[i * dataset->num_classes + j]);
            printf("\n");
        }
    }

    if (print_test)
    {
        printf("Test Dataset:\n");
        for (int i = 0; i < dataset->num_test_samples; i++)
        {
            printf("%4d) ", i);
            for (int j = 0; j < dataset->num_features; j++)
                printf("%.2f ", dataset->test_dataset[i * dataset->num_features + j]);
            for (int j = 0; j < dataset->num_classes; j++)
                printf("%d ", dataset->test_labels[i * dataset->num_classes + j]);
            printf("\n");
        }
    }
}

void free_dataset(Dataset *dataset)
{
    if (dataset == NULL)
        return;
    if (dataset->dataset != NULL)
        free(dataset->dataset);
    if (dataset->labels != NULL)
        free(dataset->labels);
    if (dataset->train_dataset != NULL)
        free(dataset->train_dataset);
    if (dataset->train_labels != NULL)
        free(dataset->train_labels);
    if (dataset->test_dataset != NULL)
        free(dataset->test_dataset);
    if (dataset->test_labels != NULL)
        free(dataset->test_labels);
    // free(dataset);
}