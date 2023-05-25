#include <stdio.h>
#include <stdlib.h>
#include "liquid.h"
#include "neuron.h"
#include "synapse.h"
#include "visualize.h"
#include "random_utilities.h"
// #include <gtest/gtest.h>

int main()
{
    srand(time(NULL));

    Liquid liquid = create_liquid(0.1, 100, 80, 2, 2, 1, 1);

    free_liquid(liquid);
    
    // //creo il logger
    // NeuronLogger logger = create_logger(net.size * 10000);

    // //simulo
    // for (int i = 0; i < 10000; i++)
    // {
    //     simulate_neurons(&net, i, 0.01, &logger);
    //     simulate_synapses(&net, &syn, i, 0.01);
    // }

    // //Salvo su file
    // writeNeuronLogger("prova.txt", logger);

    // //Libero la memoria 
    // free_neuron_logger(&logger);

    return 0;
}
