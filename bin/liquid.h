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
    int step;

    Layer *neurons;
    Synapse *synapses;
};
typedef struct Liquid Liquid;

/**
 * @brief Connects two layers of neurons.
 * @param layer1 The pre-synaptic layer.
 * @param layer2 The post-synaptic layer.
 * @param indegree The number of incoming connections per neuron in layer2
 * @param J Used to set the weight of the synapses. 
 * If J >= 0, the weight is sampled from a Gaussian distribution with mean J and standard deviation 0.7 * J. 
 * If J < 0, the weight is sampled from a Gaussian distribution with mean J and standard deviation 0.7 * (-J).
 * @param dt The time step.
 */
Synapse *connect_liquid(Layer *layer1, Layer *layer2, int indegree, float J, float dt);

Liquid *create_liquid(float dt, int n_exc, int n_inh, int n_ee, int n_ei, int n_ii, int n_ie);

void free_liquid(Liquid *liquid);

#endif

