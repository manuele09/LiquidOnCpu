#include "liquid.h"

Liquid *create_liquid(float dt, int n_exc, int n_inh, int n_ee, int n_ei, int n_ii, int n_ie)
{
    Liquid *liquid = (Liquid *)malloc(sizeof(Liquid));
    liquid->dt = dt;
    liquid->step = 0;
    liquid->n_exc = n_exc;
    liquid->n_inh = n_inh;

    // create the neurons
    Layer *exc_neurons = create_neurons(n_exc, true);
    Layer *inh_neurons = create_neurons(n_inh, true);

    // create the synapses
    Synapse *ee_synapses = connect_liquid(exc_neurons, exc_neurons, n_ee, 10 * 5, dt);
    Synapse *ei_synapses = connect_liquid(exc_neurons, inh_neurons, n_ei, 10 * 25, dt);
    Synapse *ii_synapses = connect_liquid(inh_neurons, inh_neurons, n_ii, 10 * (-20), dt);
    Synapse *ie_synapses = connect_liquid(inh_neurons, exc_neurons, n_ie, 10 * (-20), dt);

    // combine the neurons and the synapses in two single objects
    Layer *layers_array[] = {exc_neurons, inh_neurons};
    liquid->neurons = combine_layers(layers_array, 2);
    initialize_neurons(liquid->neurons, 0, -1, -60, 6, 0.02, 0.2, -60, 2);

    Synapse *synapses_array[] = {ee_synapses, ei_synapses, ii_synapses, ie_synapses};
    liquid->synapses = combine_synapses(synapses_array, 4);

    // set the location of the neurons in the synapses
    set_neurons_location(liquid->neurons, liquid->synapses);

    return liquid;
}

Synapse *connect_liquid(Layer *layer1, Layer *layer2, int indegree, float J, float dt)
{
    Synapse *syn = create_synapses(layer2->n_neurons * indegree, true);
    float delay, w, tau;

    int counter = 0;
    for (int i = 0; i < layer2->n_neurons; i++)
    {
        for (int j = 0; j < indegree; j++)
        {
            delay = GaussianDistributionClipped(10, 20, 3, 200);
            if (J >= 0)
            {
                w = GaussianDistributionClipped(J, 0.7 * J, 0, 100000);
                tau = 3;
            }
            else
            {
                w = GaussianDistributionClipped(J, 0.7 * (-J), -100000, 0);
                tau = 2;
            }
            syn->pre_location[counter] = rand() % layer1->n_neurons;
            syn->pre_neuron_idx[counter] = layer1->id[syn->pre_location[counter]];
            syn->post_neuron_idx[counter] = layer2->id[i];
            syn->weight[counter] = w;
            syn->gain[counter] = 1;
            syn->tau_syn[counter] = tau;
            syn->delay[counter] = (int)(delay / dt);
            counter++;
        }
    }
    return syn;
}

void set_input(Liquid *liquid, int *input, int input_size, int outdegree)
{
    for (int i = 0; i < input_size; i++)
        for (int j = 0; j < outdegree; j++)
            liquid->neurons->I_bias[rand() % liquid->neurons->n_neurons] += input[i];
}

void clear_input(Liquid *liquid)
{
    for (int i = 0; i < liquid->neurons->n_neurons; i++)
        liquid->neurons->I_bias[i] = 0;
}

float *read_output(Liquid *liquid, float tau)
{
    float *output = (float *)calloc(liquid->n_exc, sizeof(float));
    for (int i = 0; i < liquid->n_exc; i++)
        output[i] = exp((liquid->neurons->last_spike[i] - liquid->neurons->step) * liquid->dt / tau);
    return output;
}

void free_liquid(Liquid *liquid)
{
    free_neurons(liquid->neurons);
    free_synapses(liquid->synapses);
}
