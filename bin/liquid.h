#ifndef _LIQUID_H
#define _LIQUID_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "neuron.h"
#include "synapse.h"
#include "state_logger.h"
#include "random_utilities.h"

/**
 * @brief A liquid structure containing all neurons and synapses (exiting and inhibitory).
 * 
 */
struct Liquid
{
    float dt;
    Layer exc_neurons;
    Layer inh_neurons;
    Layer all_neurons;

    Synapse ee_synapses;
    Synapse ei_synapses;
    Synapse ii_synapses;
    Synapse ie_synapses;
    Synapse all_synapses;
};
typedef struct Liquid Liquid;

/**
 * @brief Connects two layers of neurons using the given parameters.
 * 
 * @param syn 
 * @param layer1 
 * @param layer2 
 * @param indegree // number of incoming connections per neuron in layer2
 * @param J 
 * @param dt 
 */
Synapse connect_liquid(Layer layer1, Layer layer2, int indegree, double J, float dt);

Liquid create_liquid(float dt, int n_exc, int n_inh, int n_ee, int n_ei, int n_ii, int n_ie);

void simulate_liquid(Liquid liquid, int steps);

void free_liquid(Liquid liquid);

#endif
