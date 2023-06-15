#include "neuron.h"

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



void initialize_neurons(Neuron *neurons, int start_idx, int end_idx, float init_v, float init_u, float init_a, float init_b, float init_c, float init_d)
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
        neurons->a[i] = init_a;
        neurons->b[i] = init_b;
        neurons->c[i] = init_c;
        neurons->d[i] = init_d;
        neurons->last_spike[i] = -1;
    }
}

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

    initialize_neurons(&neurons, 0, -1, -65.0f, -30.0f, 0.02f, 0.2f, -65.0f, 8.0f);
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


void simulate_neurons(Neuron *neurons, int step, float dt, NeuronLogger *logger)
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

void set_input(Neuron neuron, int *currents)
{
    for (int i = 0; i < neuron.size; i++)
        neuron.I_bias[i] = currents[i];
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
