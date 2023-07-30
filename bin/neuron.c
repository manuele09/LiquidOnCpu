#include "neuron.h"
//Modifica: permettere di inserire manualmente l'id del layer
Layer *create_neurons(size_t num_neurons, bool new_neurons_ids)
{
    static int global_id = 0;
    static int global_layer_id = 0;
    Layer *neurons = (Layer *)calloc(1, sizeof(Layer));

    neurons->n_neurons = num_neurons;
    neurons->layer_id = global_layer_id++;
    neurons->step = 0;

    neurons->id = (int *)calloc(num_neurons, sizeof(int));
    neurons->neuron_layer_id = (int *)calloc(num_neurons, sizeof(int));

    if (new_neurons_ids)
        for (int i = 0; i < num_neurons; i++)
        {
            neurons->id[i] = global_id++;
            neurons->neuron_layer_id[i] = neurons->layer_id;
        }

    neurons->last_spike = (int *)calloc(num_neurons, sizeof(int));
    neurons->V = (float *)calloc(num_neurons, sizeof(float));
    neurons->U = (float *)calloc(num_neurons, sizeof(float));
    neurons->I = (float *)calloc(num_neurons, sizeof(float));
    neurons->I_bias = (float *)calloc(num_neurons, sizeof(float));
    neurons->a = (float *)calloc(num_neurons, sizeof(float));
    neurons->b = (float *)calloc(num_neurons, sizeof(float));
    neurons->c = (float *)calloc(num_neurons, sizeof(float));
    neurons->d = (float *)calloc(num_neurons, sizeof(float));

    initialize_neurons(neurons, 0, -1, -65.0f, -30.0f, 0.02f, 0.2f, -65.0f, 8.0f);
    return neurons;
}

void initialize_neurons(Layer *neurons, int start_idx, int end_idx, float init_v, float init_u, float init_a, float init_b, float init_c, float init_d)
{
    if (end_idx == -1 || end_idx >= neurons->n_neurons)
        end_idx = neurons->n_neurons - 1;

    if (start_idx < 0 || start_idx > end_idx)
    {
        printf("Invalid start or end index: start=%d, end=%d.\n", start_idx, end_idx);
        exit(1);
    }

    for (int i = start_idx; i <= end_idx; i++)
    {
        neurons->V[i] = init_v;
        neurons->U[i] = init_u;
        neurons->a[i] = init_a;
        neurons->b[i] = init_b;
        neurons->c[i] = init_c;
        neurons->d[i] = init_d;
    }
}

Layer *combine_layers(Layer **layers, int num_layers)
{
    // TODO: eliminare vecchi layer, altrimenti sarebbe inconsistente avere più
    // neuroni con lo stesso id in memoria.

    int total_n = 0;
    for (int i = 0; i < num_layers; i++)
        total_n += layers[i]->n_neurons;

    Layer *network;

    network = create_neurons(total_n, false);

    int index = 0;
    for (int l = 0; l < num_layers; l++)
    {
        for (int i = 0; i < layers[l]->n_neurons; i++)
        {
            network->U[index] = layers[l]->U[i];
            network->V[index] = layers[l]->V[i];
            network->I[index] = layers[l]->I[i];
            network->I_bias[index] = layers[l]->I_bias[i];
            network->a[index] = layers[l]->a[i];
            network->b[index] = layers[l]->b[i];
            network->c[index] = layers[l]->c[i];
            network->d[index] = layers[l]->d[i];
            network->id[index] = layers[l]->id[i];
            network->neuron_layer_id[index] = layers[l]->neuron_layer_id[i];
            index++;
        }
        free_neurons(layers[l]);
    }
    return network;
}

void simulate_neurons(Layer *neurons, float dt, NeuronLogger *logger)
{
    for (int i = 0; i < neurons->n_neurons; ++i)
    {
        float V = neurons->V[i];
        float U = neurons->U[i];
        float I = neurons->I[i];
        float I_bias = neurons->I_bias[i];

        if (V >= 30.0f)
        {
            neurons->V[i] = neurons->c[i];
            neurons->U[i] += neurons->d[i];
            neurons->last_spike[i] = neurons->step;
        }
        else
        {
            neurons->V[i] += dt * (0.04f * V * V + 5.0f * V + 140.0f - U + I + I_bias);
            neurons->U[i] += dt * neurons->a[i] * (neurons->b[i] * V - U);
        }

        if (logger != NULL)
        {
            logger->step[logger->counter] = neurons->step;
            logger->V[logger->counter] = neurons->V[i];
            logger->I[logger->counter] = neurons->I[i];
            logger->I_bias[logger->counter] = neurons->I_bias[i];
            logger->id[logger->counter] = neurons->id[i];
            logger->layer_id[logger->counter] = neurons->neuron_layer_id[i];
            logger->counter++;
        }
    }
    neurons->step++;
}

void set_bias_current(Layer *neuron, float *currents)
{
    for (int i = 0; i < neuron->n_neurons; i++)
        neuron->I_bias[i] = currents[i];
}

void free_neurons(Layer *neurons)
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
    free(neurons->neuron_layer_id);
}
