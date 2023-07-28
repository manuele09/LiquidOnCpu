#include <stdio.h>
#include "neuron.h"
#include "synapse.h"
#include "liquid.h"

int main(void)
{
    Liquid *liquid = create_liquid(0.1, 100, 25, 10, 10, 10, 10);
    int steps = 1000;
    NeuronLogger *logger = create_neuron_logger(liquid->neurons->n_neurons, steps);
    for (int i = 0; i < steps; i++)
    {
        // printf("Step %d\n", liquid->neurons->step);
        simulate_neurons(liquid->neurons, liquid->dt, logger);
        simulate_synapses(liquid->synapses, liquid->dt);
    }

    writeNeuronLogger("../logs/liquid.txt", logger);

    return 0;
}