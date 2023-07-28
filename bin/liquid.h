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
 * @param J The synaptic weight.
 * @param dt The time step.
 */
Synapse *connect_liquid(Layer *layer1, Layer *layer2, int indegree, double J, float dt);

Liquid *create_liquid(float dt, int n_exc, int n_inh, int n_ee, int n_ei, int n_ii, int n_ie);

void free_liquid(Liquid *liquid);

#endif
