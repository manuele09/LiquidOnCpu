#ifndef _SYNAPSE_H
#define _SYNAPSE_H 1

#include <stdlib.h>
#include <math.h>
#include "neuron.h"

struct Synapse
{
    int *pre_neuron_idx;
    int *pre_location;
    int *post_neuron_idx;
    float *weight;
    float *gain;
    float *tau_syn;
    int num_synapses;
} Synaptic;
typedef struct Synapse Synapse;

Synapse create_synapses(int num_synapses)
{
    Synapse synaptic;
    synaptic.pre_neuron_idx = (int *)calloc(num_synapses, sizeof(int));
    synaptic.pre_location = (int *)calloc(num_synapses, sizeof(int));
    synaptic.post_neuron_idx = (int *)calloc(num_synapses, sizeof(int));
    synaptic.weight = (float *)calloc(num_synapses, sizeof(float));
    synaptic.gain = (float *)calloc(num_synapses, sizeof(float));
    synaptic.tau_syn = (float *)calloc(num_synapses, sizeof(float));

    synaptic.num_synapses = num_synapses;

    return synaptic;
}

Synapse connect(Neuron *layer1, Neuron *layer2, int *conn_matrix)
{
    int num_syn = 0;
    for (int i = 0; i < layer1->size; i++)
        for (int j = 0; j < layer2->size; j++)
            num_syn += conn_matrix[i * layer2->size + j];

    Synapse synapses = create_synapses(num_syn);
    int syn_index = 0;
    for (int i = 0; i < layer1->size; i++)
        for (int j = 0; j < layer2->size; j++)
        {
            if (conn_matrix[i * layer2->size + j] == 1)
            {
                synapses.pre_neuron_idx[syn_index] = layer1->id[i];
                synapses.pre_location[syn_index] = i;
                synapses.post_neuron_idx[syn_index] = layer2->id[j];

                synapses.gain[syn_index] = 1;
                synapses.weight[syn_index] = 1;
                synapses.tau_syn[syn_index] = 1;

                syn_index++;
            }
        }
    return synapses;
}

void set_pre_locations(Neuron neurons, Synapse synpase)
{
    for (int i = 0; i < synpase.num_synapses; i++)
    {
        for (int j = 0; j < neurons.size; j++)
        {
            if (neurons.id[j] == synpase.pre_neuron_idx[i])
            {
                synpase.pre_location[i] = j;
                break;
            }
        }
    }
}

void update_synapses(Neuron *neurons, Synapse *synapses, int step, float dt)
{
    for (int i = 0; i < neurons->size; i++)
    {
        float I_syn = 0.0f;

        for (int j = 0; j < synapses->num_synapses; j++)
        {
            int last_spike = neurons->last_spike[synapses->pre_location[j]];

            I_syn += synapses->weight[j] * exp(-(step - last_spike) * dt / synapses->tau_syn[j]);
        }
        neurons->I[i] = I_syn;
    }
}

void free_synapses(Synapse *synaptic)
{
    free(synaptic->pre_neuron_idx);
    free(synaptic->pre_location);
    free(synaptic->post_neuron_idx);
    free(synaptic->weight);
    free(synaptic->gain);
    free(synaptic->tau_syn);
}

#endif