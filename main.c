#include <stdio.h>
#include <stdlib.h>
#include "neuron.h"
#include "synapse.h"
#include "visualize.h"
// #include <gtest/gtest.h>

int main()
{
    Neuron neurons1 = create_neurons(5);
    Neuron neurons2 = create_neurons(5);


    initialize_neurons(&neurons1, 0, -1, -65.0f, -30.0f, 40.0f, 0.02f, 0.2f, -65.0f, 8.0f);
    initialize_neurons(&neurons2, 0, -1, -65.0f, -30.0f, 40.0f, 0.02f, 0.2f, -65.0f, 8.0f);
    Neuron net = create_network(neurons1, neurons2);
    visualize_neuron_layer(net);
    
    int *conn_mat = malloc(sizeof(int) * neurons1.size * neurons2.size);
    for (int i = 0; i < neurons1.size; i++)
        for (int j = 0; j < neurons2.size; j++)
            conn_mat[i * neurons2.size + j] = 1;

    Synapse syn = connect(&neurons1, &neurons2, conn_mat);
    set_pre_locations(net, syn);
    visualize_synapse(syn);

    for (int i = 0; i < 10000; i++)
        update_neurons(&net, i, 0.01);

    for (int i = 0; i < 10000; i++)
        update_synapses(&net, &syn, i, 0.01);

    free_neurons(&neurons1);
    free_neurons(&neurons2);
    free_neurons(&net);
    free_synapses(&syn);

    return 0;
}
