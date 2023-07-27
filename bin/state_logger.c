#include "neuron.h"
#include "state_logger.h"

NeuronLogger create_logger(size_t size)
{
    NeuronLogger logger;

    logger.step = (int *)calloc(size, sizeof(float));
    logger.V = (float *)calloc(size, sizeof(float));
    logger.I = (float *)calloc(size, sizeof(float));
    logger.I_bias = (float *)calloc(size, sizeof(float));
    logger.id = (int *)calloc(size, sizeof(int));

    logger.counter = 0;
    logger.size = size;

    return logger;
}

void writeNeuronLogger(char *file_name, NeuronLogger logger)
{
    FILE *fp = fopen(file_name, "w");
    if (fp == NULL)
    {
        printf("Error opening file %s\n", file_name);
        exit(1);
    }
    fprintf(fp, "Step  Id  V  I  I_Bias\n");
    for (int i = 0; i < logger.counter; i++)
        fprintf(fp, "%d  %d  %f  %f  %f\n", logger.step[i], logger.id[i], logger.V[i], logger.I[i], logger.I_bias[i]);
    fclose(fp);
}

//free_logger