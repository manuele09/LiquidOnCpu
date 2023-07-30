#include "visualize.h"

void visualize_neuron_layer(Layer *layer)
{
    printf("-------------------------------------|\n");
    printf("%-9s | %-25s|\n", "Layer id", "total number of neurons");
    printf("%-9d | %-25d|\n", layer->layer_id, layer->n_neurons);

    // Print column headers
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-25s | %-9s | %-9s | %-9s | %-9s | %-9s | %-9s | %-9s | %-9s | %-9s | %-15s\n",
           "Layer id (of provenance)", "Neuron id", "A", "B", "C", "D", "V", "I", "I_bias", "U", "Last Spike(step)");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < layer->n_neurons; i++)
    {
        printf("%-25d | %-9d | %-9.2f | %-9.2f | %-9.2f | %-9.2f | %-9.2f | %-9.2f | %-9.2f | %-9.2f | %-15d\n",
               layer->neuron_layer_id[i], layer->id[i], layer->a[i], layer->b[i], layer->c[i], layer->d[i], layer->V[i], layer->I[i], layer->I_bias[i], layer->U[i], layer->last_spike[i]);
    }
    printf("\n\n");
}

void visualize_synapse(Synapse *syn)
{
    printf("----------------------------------------------|\n");
    printf("%-18s | %-25s|\n", "Synapse family id", "total number of synapses");
    printf("%-18d | %-25d|\n", syn->synapse_family_id, syn->n_synapses);

    // Print column headers
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-27s | %-10s | %-11s | %-12s | %-14s | %-8s | %-8s | %-8s | %-8s\n",
           "Synapse id (of provenance)", "Pre Index", "Post Index", "Pre Location", "Post Location", "Weight", "Gain", "Tau_syn", "Delay");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < syn->n_synapses; i++)
    {
        printf("%-27d | %-10d | %-11d | %-12d | %-14d | %-8f | %-8f | %-8f | %-8f\n",
               syn->synapse_id[i], syn->pre_neuron_idx[i], syn->post_neuron_idx[i], syn->pre_location[i], syn->post_location[i], syn->weight[i], syn->gain[i], syn->tau_syn[i], syn->delay[i]);
    }
    printf("\n\n");
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

void print_matrix_float(float *matrix, int x, int y)
{
    printf("Matrice  delle connessioni:\n");
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
            printf("%.2f ", matrix[i * y + j]);
        printf("\n");
    }
    printf("\n");
}