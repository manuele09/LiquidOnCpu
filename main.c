#include <stdio.h>
#include <stdlib.h>
#include "neuron.h"
#include "synapse.h"
// #include <gtest/gtest.h>

int main()
{
    Neuron neurons1 = create_neurons(10);
    Neuron neurons2 = create_neurons(10);

    initialize_neurons(&neurons1, 0, -1, -65.0f, -30.0f, 40.0f, 0.02f, 0.2f, -65.0f, 8.0f);
    initialize_neurons(&neurons2, 0, -1, -65.0f, -30.0f, 40.0f, 0.02f, 0.2f, -65.0f, 8.0f);

    for (int i = 0; i < 10000; i++)
        update_neurons(&neurons1, i, 0.01);
    
    int* conn_mat = malloc(sizeof(int)*10*10);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            conn_mat[i*10+j] = 1;

    Synapse syn = connect(&neurons1, &neurons2, conn_mat);
    
    free_neurons(&neurons1);
    free_neurons(&neurons2);
    free_synapses(&syn);

    return 0;
}
