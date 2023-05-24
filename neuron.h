#ifndef _NEURON_H
#define _NEURON_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// #define MAX_SPIKE_TIMES 50
//  considerando la simulazione delle sinapsi, è possible usare un approccio
//  event driven: se un determinato neurone non emmette spike, invece di calcoare
//  il contributo in corrente degli spike passati, basta moltiplicare il valore vecchio
//  per una costante (e^-dt). Questo presuppone che si conservi in memoria in locazioni distinte
//  il contributo in corrente da parte di ciascun neurone presinaptico, perchè un nuerone può
//  spikare, altri no.

struct Neuron
{
    float *V;        // membrane potential
    float *U;        // recovery variable
    float *I;        // input current
    float *I_bias;        // bias current
    float *a;        // parameter
    float *b;        // parameter
    float *c;        // parameter
    float *d;        // parameter
    int *last_spike; // timestamp of last spike emitted
    int *id;
    int size;
};
typedef struct Neuron Neuron;

struct NeuronLogger
{
    int *step;
    float *V; // membrane potential
    float *I; // input current
    float *I_bias; // bias current
    int *id;
    int counter;
    int size;
};
typedef struct NeuronLogger NeuronLogger;

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
    fprintf(fp, "Step  Id  V  I  I_Bias\n");
    for (int i = 0; i < logger.counter; i++)
        fprintf(fp, "%d  %d  %f  %f  %f\n", logger.step[i], logger.id[i], logger.V[i], logger.I[i], logger.I_bias[i]);
    fclose(fp);
}

// suppone che si chiami la initialize_neurons
Neuron create_neurons(size_t num_neurons)
{
    static int global_id = 0;
    Neuron neurons;

    neurons.V = (float *)calloc(num_neurons, sizeof(float));
    neurons.U = (float *)calloc(num_neurons, sizeof(float));
    neurons.I = (float *)calloc(num_neurons, sizeof(float));
    neurons.I_bias = (float *)calloc(num_neurons, sizeof(float));
    neurons.a = (float *)calloc(num_neurons, sizeof(float));
    neurons.b = (float *)calloc(num_neurons, sizeof(float));
    neurons.c = (float *)calloc(num_neurons, sizeof(float));
    neurons.d = (float *)calloc(num_neurons, sizeof(float));
    neurons.last_spike = (int *)calloc(num_neurons, sizeof(int));
    neurons.id = (int *)calloc(num_neurons, sizeof(int));
    neurons.size = num_neurons;

    for (int i = 0; i < num_neurons; i++)
        neurons.id[i] = global_id++;

    return neurons;
}

Neuron create_network(Neuron layer1, Neuron layer2)
{
    int total_n = layer1.size + layer2.size;
    Neuron network;

    network = create_neurons(total_n);

    int net_id = 0;
    for (int i = 0; i < layer1.size; i++)
    {
        network.V[net_id] = layer1.V[i];
        network.U[net_id] = layer1.U[i];
        network.I[net_id] = layer1.I[i];
        network.I_bias[net_id] = layer1.I_bias[i];
        network.a[net_id] = layer1.a[i];
        network.b[net_id] = layer1.b[i];
        network.c[net_id] = layer1.c[i];
        network.d[net_id] = layer1.d[i];
        network.last_spike[net_id] = layer1.last_spike[i];
        network.id[net_id] = layer1.id[i];
        net_id++;
    }
    for (int i = 0; i < layer2.size; i++)
    {
        network.V[net_id] = layer2.V[i];
        network.U[net_id] = layer2.U[i];
        network.I[net_id] = layer2.I[i];
        network.I_bias[net_id] = layer2.I_bias[i];
        network.a[net_id] = layer2.a[i];
        network.b[net_id] = layer2.b[i];
        network.c[net_id] = layer2.c[i];
        network.d[net_id] = layer2.d[i];
        network.last_spike[net_id] = layer2.last_spike[i];
        network.id[net_id] = layer2.id[i];
        net_id++;
    }

    return network;
}

void update_neurons(Neuron *neurons, int step, float dt, NeuronLogger *logger)
{
    for (int i = 0; i < neurons->size; ++i)
    {
        float V = neurons->V[i];
        float U = neurons->U[i];
        float I = neurons->I[i];
        float I_bias = neurons->I_bias[i];

        if (V >= 30.0f)
        {
            neurons->V[i] = neurons->c[i];
            neurons->U[i] += neurons->d[i];
            neurons->last_spike[i] = step;
        }
        else
        {
            neurons->V[i] += dt * (0.04f * V * V + 5.0f * V + 140.0f - U + I + I_bias);
            neurons->U[i] += dt * neurons->a[i] * (neurons->b[i] * V - U);

            if (logger != NULL)
            {
                logger->step[logger->counter] = step;
                logger->V[logger->counter] = neurons->V[i];
                logger->I[logger->counter] = neurons->I[i];
                logger->I_bias[logger->counter] = neurons->I_bias[i];
                logger->id[logger->counter] = neurons->id[i];
                logger->counter++;
            }
        }
    }
}

/**
 * @brief Initialize the initial potential, current, and parameters (a, b, c, d) for a range of neurons.
 *
 * @param neurons Pointer to the Neuron array.
 * @param start_idx The start index of neurons to be initialized.
 * @param end_idx The end index of neurons to be initialized. If -1, initialize all neurons starting from start_idx.
 * @param init_v The initial value for membrane potential.
 * @param init_I The initial value for input current.
 * @param init_a The initial value for parameter a.
 * @param init_b The initial value for parameter b.
 * @param init_c The initial value for parameter c.
 * @param init_d The initial value for parameter d.
 */
void initialize_neurons(Neuron *neurons, int start_idx, int end_idx, float init_v, float init_u, float init_I, float init_a, float init_b, float init_c, float init_d)
{
    // Validate the end index
    if (end_idx == -1 || end_idx >= neurons->size)
    {
        end_idx = neurons->size - 1;
    }

    // Initialize the initial potential, current, and parameters for the specified range of neurons
    for (int i = start_idx; i <= end_idx; i++)
    {
        neurons->V[i] = init_v;
        neurons->U[i] = init_u;
        neurons->I[i] = init_I;
        neurons->a[i] = init_a;
        neurons->b[i] = init_b;
        neurons->c[i] = init_c;
        neurons->d[i] = init_d;
        neurons->last_spike[i] = -1;
    }
}

void free_neurons(Neuron *neurons)
{
    free(neurons->V);
    free(neurons->U);
    free(neurons->I);
    free(neurons->I_bias);
    free(neurons->a);
    free(neurons->b);
    free(neurons->c);
    free(neurons->d);
    free(neurons->last_spike);
    free(neurons->id);
}

void free_neuron_logger(NeuronLogger *logger)
{
    free(logger->V);
    free(logger->I);
    free(logger->I_bias);
    free(logger->id);
    free(logger->step);
}

#endif
