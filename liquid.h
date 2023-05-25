#ifndef _LIQUID_H
#define _LIQUID_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "neuron.h"
#include "synapse.h"
#include "random_utilities.h"

struct Liquid
{
    float dt;
    Neuron exc_neurons;
    Neuron inh_neurons;
    Neuron all_neurons;

    Synapse ee_synapses;
    Synapse ei_synapses;
    Synapse ii_synapses;
    Synapse ie_synapses;
    Synapse all_synapses;
};
typedef struct Liquid Liquid;

void connect_liquid(Synapse syn, Neuron layer1, Neuron layer2, int indegree, double J, float dt)
{
    double delay = GaussianDistributionClipped(10, 20, 3, 200);
    double w, tau;
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

    int counter = 0;
    for (int i = 0; i < layer2.size; i++)
    {
        for (int j = 0; j < indegree; j++)
        {
            syn.pre_location[counter] = rand() % layer1.size;
            syn.pre_neuron_idx[counter] = layer1.id[syn.pre_location[counter]];
            syn.post_neuron_idx[counter] = layer2.id[i];
            syn.weight[counter] = w;
            syn.gain[counter] = 1;
            syn.tau_syn[counter] = tau;
            syn.delay[counter] = (int)(delay / dt);
            counter++;
        }
    }
}

Liquid create_liquid(float dt, int n_exc, int n_inh, int n_ee, int n_ei, int n_ii, int n_ie)
{
    Liquid liquid;
    liquid.dt = dt;

    liquid.exc_neurons = create_neurons(n_exc);
    liquid.inh_neurons = create_neurons(n_inh);

    liquid.ee_synapses = create_synapses(n_exc * n_ee);
    liquid.ei_synapses = create_synapses(n_inh * n_ei);
    liquid.ii_synapses = create_synapses(n_inh * n_ii);
    liquid.ie_synapses = create_synapses(n_exc * n_ie);

    connect_liquid(liquid.ee_synapses, liquid.exc_neurons, liquid.exc_neurons, n_ee, 10 * 5, dt);
    connect_liquid(liquid.ei_synapses, liquid.exc_neurons, liquid.inh_neurons, n_ei, 10 * 25, dt);
    connect_liquid(liquid.ii_synapses, liquid.inh_neurons, liquid.inh_neurons, n_ii, 10 * (-20), dt);
    connect_liquid(liquid.ie_synapses, liquid.inh_neurons, liquid.exc_neurons, n_ie, 10 * (-20), dt);

    liquid.all_neurons = create_network(liquid.exc_neurons, liquid.inh_neurons);

    return liquid;
}

void free_liquid(Liquid liquid)
{
    free_neurons(&liquid.all_neurons);
    free_neurons(&liquid.exc_neurons);
    free_neurons(&liquid.inh_neurons);

    free_synapses(&liquid.all_synapses);
    free_synapses(&liquid.ee_synapses);
    free_synapses(&liquid.ei_synapses);
    free_synapses(&liquid.ii_synapses);
    free_synapses(&liquid.ie_synapses);
}

#endif
