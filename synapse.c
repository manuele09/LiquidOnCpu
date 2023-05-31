#include "synapse.h"



Synapse create_synapses(int num_synapses)
{
    Synapse synaptic;
    synaptic.pre_neuron_idx = (int *)calloc(num_synapses, sizeof(int));
    synaptic.pre_location = (int *)calloc(num_synapses, sizeof(int));
    synaptic.post_neuron_idx = (int *)calloc(num_synapses, sizeof(int));
    synaptic.weight = (float *)calloc(num_synapses, sizeof(float));
    synaptic.gain = (float *)calloc(num_synapses, sizeof(float));
    synaptic.tau_syn = (float *)calloc(num_synapses, sizeof(float));
    synaptic.delay = (float *)calloc(num_synapses, sizeof(float));

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
                synapses.delay[syn_index] = 0;

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

void simulate_synapses(Neuron *neurons, Synapse *synapses, int step, float dt)
{
    for (int i = 0; i < neurons->size; i++)
    {
        float I_syn = 0.0f;

        for (int j = 0; j < synapses->num_synapses; j++)
        {
            int last_spike = neurons->last_spike[synapses->pre_location[j]];

            I_syn += synapses->weight[j] * exp(-(step - last_spike + synapses->delay[j]) * dt / synapses->tau_syn[j]);
            // if (step < 10 && j == 0 && i == 0);
            // printf("%d\n", synapses->delay[j]);
        }
        neurons->I[i] = I_syn;
    }
}

Synapse create_network_syn(Synapse syn1, Synapse syn2)
{
    int total_s = syn1.num_synapses + syn2.num_synapses;
    Synapse syn_net;

    syn_net = create_synapses(total_s);

    int net_id = 0;
    for (int i = 0; i < syn1.num_synapses; i++)
    {
        syn_net.pre_neuron_idx[net_id] = syn1.pre_neuron_idx[i];
        syn_net.post_neuron_idx[net_id] = syn1.post_neuron_idx[i];
        syn_net.weight[net_id] = syn1.weight[i];
        syn_net.gain[net_id] = syn1.gain[i];
        syn_net.tau_syn[net_id] = syn1.tau_syn[i];
        syn_net.delay[net_id] = syn1.delay[i];
        net_id++;
    }
    for (int i = 0; i < syn2.num_synapses; i++)
    {
        syn_net.pre_neuron_idx[net_id] = syn2.pre_neuron_idx[i];
        syn_net.post_neuron_idx[net_id] = syn2.post_neuron_idx[i];
        syn_net.weight[net_id] = syn2.weight[i];
        syn_net.gain[net_id] = syn2.gain[i];
        syn_net.tau_syn[net_id] = syn2.tau_syn[i];
        syn_net.delay[net_id] = syn2.delay[i];
        net_id++;
    }

    return syn_net;
}

void free_synapses(Synapse *synaptic)
{
    free(synaptic->pre_neuron_idx);
    free(synaptic->pre_location);
    free(synaptic->post_neuron_idx);
    free(synaptic->weight);
    free(synaptic->gain);
    free(synaptic->tau_syn);
    free(synaptic->delay);
}

