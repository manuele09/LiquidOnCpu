#include "synapse.h"
#include <stdlib.h>
#include <unistd.h>

Synapse *create_synapses(int n_synapses, bool new_synapses_ids)
{
    static int synapse_global_id = 0;

    Synapse *synaptic = (Synapse *)calloc(1, sizeof(Synapse));
    synaptic->synapse_family_id = synapse_global_id++;

    synaptic->synapse_id = (int *)calloc(n_synapses, sizeof(int));
    synaptic->pre_neuron_idx = (int *)calloc(n_synapses, sizeof(int));
    synaptic->post_neuron_idx = (int *)calloc(n_synapses, sizeof(int));

    if (new_synapses_ids)
        for (int i = 0; i < n_synapses; i++)
            synaptic->synapse_id[i] = synaptic->synapse_family_id;

    synaptic->layer = NULL;

    synaptic->pre_location = (int *)calloc(n_synapses, sizeof(int));
    synaptic->post_location = (int *)calloc(n_synapses, sizeof(int));

    synaptic->weight = (float *)calloc(n_synapses, sizeof(float));
    synaptic->gain = (float *)calloc(n_synapses, sizeof(float));
    synaptic->tau_syn = (float *)calloc(n_synapses, sizeof(float));
    synaptic->delay = (float *)calloc(n_synapses, sizeof(float));

    synaptic->n_synapses = n_synapses;

    return synaptic;
}

Synapse *connect(Layer *pre_layer, Layer *post_layer, int *conn_matrix)
{
    // Find the total number of synapses
    int num_syn = 0;
    for (int i = 0; i < pre_layer->n_neurons; i++)
        for (int j = 0; j < post_layer->n_neurons; j++)
            num_syn += conn_matrix[i * post_layer->n_neurons + j];

    Synapse *synapses = create_synapses(num_syn, true);

    int syn_index = 0;
    for (int i = 0; i < pre_layer->n_neurons; i++)
        for (int j = 0; j < post_layer->n_neurons; j++)
        {
            // There is a connection between the neuron i and the neuron j
            if (conn_matrix[i * post_layer->n_neurons + j] == 1)
            {
                // Set the ids of the pre and post neurons
                synapses->pre_neuron_idx[syn_index] = pre_layer->id[i];
                synapses->post_neuron_idx[syn_index] = post_layer->id[j];

                // Set the default values of the synapse
                synapses->gain[syn_index] = 1;
                synapses->weight[syn_index] = 1;
                synapses->tau_syn[syn_index] = 1;
                synapses->delay[syn_index] = 0;

                syn_index++;
            }
        }
    return synapses;
}

void set_neurons_location(Layer *layer, Synapse *synpase)
{
    int found;
    synpase->layer = layer;
    for (int i = 0; i < synpase->n_synapses; i++)
    {
        found = 0;

        // Find the locations of the pre and post neurons of the j-th synapse
        for (int j = 0; j < layer->n_neurons; j++)
        {
            if (found == 2)
                break;
            // Find pre location
            if (layer->id[j] == synpase->pre_neuron_idx[i])
            {
                synpase->pre_location[i] = j;
                found++;
            }
            // Find post location
            if (layer->id[j] == synpase->post_neuron_idx[i])
            {
                synpase->post_location[i] = j;
                found++;
            }
        }

        if (found != 2)
        {
            printf("Error: pre (%d) or post (%d) neuron not found in the layer.\n", synpase->pre_neuron_idx[i], synpase->post_neuron_idx[i]);
            exit(1);
        }
    }
}

void simulate_synapses(Synapse *synapses, float dt)
{
    // For each neuron find the pre-synaptic current
    Layer *neurons = synapses->layer;
    int step = neurons->step;
    for (int i = 0; i < neurons->n_neurons; i++)
    {
        float I_syn = 0.0f;

        for (int j = 0; j < synapses->n_synapses; j++)
        {
            if (synapses->post_neuron_idx[j] != neurons->id[i])
                continue;
            int last_spike = neurons->last_spike[synapses->pre_location[j]];

            // printf("Step: %d\n", step);
            // printf("Neuron %d, Spike: %d\n", i, last_spike);
            I_syn += synapses->weight[j] * exp(-(step - last_spike + synapses->delay[j]) * dt / synapses->tau_syn[j]);
        }
        neurons->I[i] = I_syn;
        printf("%d %f\n",i, I_syn);
    }
}

Synapse *combine_synapses(Synapse **synapse, int num_synapse)
{
    int total_s = 0;
    for (int i = 0; i < num_synapse; i++)
        total_s += synapse[i]->n_synapses;

    Synapse *syn_net;
    syn_net = create_synapses(total_s, false);

    int index = 0;
    for (int l = 0; l < num_synapse; l++)
    {
        for (int i = 0; i < synapse[l]->n_synapses; i++)
        {
            syn_net->pre_neuron_idx[index] = synapse[l]->pre_neuron_idx[i];
            syn_net->post_neuron_idx[index] = synapse[l]->post_neuron_idx[i];

            syn_net->weight[index] = synapse[l]->weight[i];
            syn_net->gain[index] = synapse[l]->gain[i];
            syn_net->tau_syn[index] = synapse[l]->tau_syn[i];
            syn_net->delay[index] = synapse[l]->delay[i];
            syn_net->synapse_id[index] = synapse[l]->synapse_id[i];
            index++;
        }
        free(synapse[l]);
    }


    return syn_net;
}

void free_synapses(Synapse *synaptic)
{
    free(synaptic->synapse_id);
    free(synaptic->layer);
    free(synaptic->pre_neuron_idx);
    free(synaptic->post_neuron_idx);
    free(synaptic->pre_location);
    free(synaptic->post_location);
    free(synaptic->weight);
    free(synaptic->gain);
    free(synaptic->tau_syn);
    free(synaptic->delay);
}
