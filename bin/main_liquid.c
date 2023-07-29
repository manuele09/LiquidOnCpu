#include <stdio.h>
#include "neuron.h"
#include "synapse.h"
#include "liquid.h"

int main(void)
{
    float dt = 0.1; //0.1 ms

    float stim_interval = 40; //300 ms          
    float stim_length = 10; //50 ms
    float readout_delay = 1; //10 ms

    int stim_interval_steps = (int)(stim_interval / dt);
    int stim_length_steps = (int)(stim_length / dt);
    int readout_delay_steps = (int)(readout_delay / dt);

    int times = 3;
    int steps = times * stim_interval_steps - stim_length_steps - readout_delay_steps + 1;

    int n_exc = 80; //80%
    int n_inh = 20; //20%
    float n_rec = 1; //100% of excitatory neurons

    int input_size = 4;
    float input_outdegree = 1; 
    float input[] = {10, 10, 20, 30};

    float *output;

    Liquid *liquid = create_liquid(0.1, n_exc, n_inh, n_rec, 10, 10, 10, 10);
    create_input_layer(liquid, input_size, input_outdegree);
    NeuronLogger *logger = create_neuron_logger(liquid->neurons->n_neurons, steps);

    for (int i = 0; i < steps; i++)
    {
        if (i % stim_interval_steps == 0)
            set_input(liquid, input);
        if ((i - stim_length_steps) % stim_interval_steps  == 0)
            clear_input(liquid);
        if ((i - stim_length_steps - readout_delay_steps) % stim_interval_steps  == 0)
            output = read_output(liquid, 0.1);

        simulate_neurons(liquid->neurons, liquid->dt, logger);
        simulate_synapses(liquid->synapses, liquid->dt);
    }

    for (int i = 0; i < liquid->n_rec; i++)
    {
        printf("Output %d: %f\n", i, output[i]);
    }

    writeNeuronLogger("../logs/liquid.txt", logger);

    return 0;
}