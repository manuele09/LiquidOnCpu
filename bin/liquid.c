#include "liquid.h"

Synapse connect_liquid(Neuron layer1, Neuron layer2, int indegree, double J, float dt)
{
    Synapse syn = create_synapses(layer2.size * indegree);
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
    return syn;
}

Liquid create_liquid(float dt, int n_exc, int n_inh, int n_ee, int n_ei, int n_ii, int n_ie)
{
    Liquid liquid;
    liquid.dt = dt;

    liquid.exc_neurons = create_neurons(n_exc);
    liquid.inh_neurons = create_neurons(n_inh);

    liquid.all_neurons = create_network(liquid.exc_neurons, liquid.inh_neurons);

    for (int i = 0; i < liquid.all_neurons.size; i++)
    {
        liquid.all_neurons.I_bias[i] = 0; // 32
        liquid.all_neurons.a[i] = 0.02;
        liquid.all_neurons.b[i] = 0.2;
        liquid.all_neurons.c[i] = -60;
        liquid.all_neurons.d[i] = 2;
        liquid.all_neurons.V[i] = -60;
        liquid.all_neurons.U[i] = 6;
    }

    liquid.ee_synapses = connect_liquid(liquid.exc_neurons, liquid.exc_neurons, n_ee, 10 * 5, dt);
    liquid.ei_synapses = connect_liquid(liquid.exc_neurons, liquid.inh_neurons, n_ei, 10 * 25, dt);

    liquid.ii_synapses = connect_liquid(liquid.inh_neurons, liquid.inh_neurons, n_ii, 10 * (-20), dt);
    liquid.ie_synapses = connect_liquid(liquid.inh_neurons, liquid.exc_neurons, n_ie, 10 * (-20), dt);

    
    

    Synapse temp1 = create_network_syn(liquid.ee_synapses, liquid.ei_synapses);
    Synapse temp2 = create_network_syn(temp1, liquid.ii_synapses);
    liquid.all_synapses = create_network_syn(temp2, liquid.ie_synapses);

    set_pre_locations(liquid.all_neurons, liquid.all_synapses);

    free_synapses(&temp1);
    free_synapses(&temp2);

    return liquid;
}

void simulate_liquid(Liquid liquid, int steps)
{
    NeuronLogger logger = create_logger(liquid.all_neurons.size * steps);
    for (int s = 0; s < steps; s++)
    {
        simulate_neurons(&liquid.all_neurons, s, liquid.dt, &logger);
        simulate_synapses(&liquid.all_neurons, &liquid.all_synapses, s, liquid.dt);
    }

    writeNeuronLogger("logs/liquid_neurons.txt", logger);
    free_neuron_logger(&logger);
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
