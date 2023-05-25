#ifndef _VISUALIZE_H
#define _VISUALIZE_H 1

#include "neuron.h"
#include "synapse.h"

void visualize_neuron_layer(Neuron layer)
{
    printf("Totale Neuroni: %d\n", layer.size);
    for (int i = 0; i < layer.size; i++)
    {
        printf("Neurone: %d\n", layer.id[i]);
        printf("A: %f, B: %f, C: %f, D: %f, V: %f, I: %f, U: %f\n", layer.a[i], layer.b[i], layer.c[i], layer.d[i], layer.V[i], layer.I[i], layer.U[i]);
        printf("Last Spike (step): %d\n", layer.last_spike[i]);
        printf("\n\n");
    }
}

void visualize_synapse(Synapse syn)
{
    printf("Totale Sinapsi: %d\n", syn.num_synapses);
    for (int i = 0; i < syn.num_synapses; i++)
    {
        printf("Pre: %d, Post: %d\n", syn.pre_neuron_idx[i], syn.post_neuron_idx[i]);
        printf("W: %f, G: %f, Tau: %f, Delay: %f\n", syn.weight[i], syn.gain[i], syn.tau_syn[i], syn.delay[i]);
        printf("\n\n");
    }
}

void print_matrix(int *matrix, int x, int y)
{
    printf("Matrice  delle connessioni:\n");
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
            printf("%d ", matrix[i * y + j]);
        printf("\n");
    }
    printf("\n");
}


#endif