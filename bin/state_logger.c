#include "neuron.h"
#include "state_logger.h"

NeuronLogger *create_neuron_logger(size_t n_neurons, size_t steps)
{
    size_t size = n_neurons * steps;
    NeuronLogger *logger = (NeuronLogger *)malloc(sizeof(NeuronLogger));

    logger->step = (int *)calloc(size, sizeof(float));
    logger->V = (float *)calloc(size, sizeof(float));
    logger->I = (float *)calloc(size, sizeof(float));
    logger->I_bias = (float *)calloc(size, sizeof(float));
    logger->id = (int *)calloc(size, sizeof(int));
    logger->layer_id = (int *)calloc(size, sizeof(int));

    logger->counter = 0;
    logger->size = size;

    return logger;
}

void writeNeuronLogger(char *file_name, NeuronLogger *logger)
{
    if (logger == NULL)
        return;
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", file_name);
        exit(1);
    }
    fprintf(fp, "Step  Layer_ID Id  V  I  I_Bias\n");
    for (int i = 0; i < logger->counter; i++)
    {
        fprintf(fp, "%d  %d %d  %f  %f  %f\n", logger->step[i], logger->layer_id[i], logger->id[i], logger->V[i], logger->I[i], logger->I_bias[i]);
    }
    fclose(fp);
    free(logger);
}

void free_neuron_logger(NeuronLogger *logger)
{
    free(logger->step);
    free(logger->V);
    free(logger->I);
    free(logger->I_bias);
    free(logger->id);
    free(logger->layer_id);
}
