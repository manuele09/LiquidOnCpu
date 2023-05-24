#include <stdio.h>
#include <stdlib.h>
#include "neuron.h"
#include "synapse.h"
#include "visualize.h"
#include "random_utilities.h"
// #include <gtest/gtest.h>

int main()
{
    srand(time(NULL));

    printf("Numero: %f\n", GaussianDistributionClipped(0, 1, 0, 10));

    int n_exc = 80;
    int n_inh = 20;
    
    //Alloco i Neuroni
    Neuron layer1 = create_neurons(5);
    Neuron layer2 = create_neurons(5);
    Neuron net = create_network(layer1, layer2);
    //visualize_neuron_layer(net);

    //Definisco la Connettività
    int *conn_mat = malloc(sizeof(int) * layer1.size * layer2.size);
    for (int i = 0; i < layer1.size; i++)
        for (int j = 0; j < layer2.size; j++)
            conn_mat[i * layer2.size + j] = 1;
    
    //Alloco le Sinapsi
    Synapse syn = connect(&layer1, &layer2, conn_mat);
    set_pre_locations(net, syn);
    //visualize_synapse(syn);
    
    //Imposto le correnti di input
    int *input = malloc(sizeof(int) * net.size);
    for (int i = 0; i < net.size; i++)
        input[i] = 56;
    set_input(net, input);

    //creo il logger
    NeuronLogger logger = create_logger(net.size * 10000);

    //simulo
    for (int i = 0; i < 10000; i++)
    {
        update_neurons(&net, i, 0.01, &logger);
        update_synapses(&net, &syn, i, 0.01);
    }

    //Salvo su file
    writeNeuronLogger("prova.txt", logger);

    //Libero la memoria 
    free_neurons(&layer1);
    free_neurons(&layer2);
    free_neurons(&net);
    free_synapses(&syn);
    free_neuron_logger(&logger);

    return 0;
}
