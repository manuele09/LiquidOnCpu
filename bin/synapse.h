#ifndef _SYNAPSE_H
#define _SYNAPSE_H 1

#include <stdlib.h>
#include <math.h>
#include "neuron.h"
// #define MAX_SPIKE_TIMES 50
//  considerando la simulazione delle sinapsi, è possible usare un approccio
//  event driven: se un determinato neurone non emmette spike, invece di calcoare
//  il contributo in corrente degli spike passati, basta moltiplicare il valore vecchio
//  per una costante (e^-dt). Questo presuppone che si conservi in memoria in locazioni distinte
//  il contributo in corrente da parte di ciascun neurone presinaptico, perchè un nuerone può
//  spikare, altri no.

struct Synapse
{
    int *pre_neuron_idx;
    int *pre_location;
    int *post_neuron_idx;
    float *weight;
    float *gain;
    float *tau_syn; //questi parametri dovrebbero essere espressi in ms
    float *delay;
    int num_synapses;
};
typedef struct Synapse Synapse;

/**
 * @brief Create a synapses object.
 * 
 * @param num_synapses 
 * @return Synapse 
 */
Synapse create_synapses(int num_synapses);

/**
 * @brief Connect two layers of neurons. The parameters of the synapse are set to default values:
 * gain = 1, weight = 1, tau_syn = 1, delay = 0. 
 * 
 * @param layer1 
 * @param layer2 
 * @param conn_matrix // Matrix of connections between neurons of layer1 and layer2
 * @return Synapse 
 */
Synapse connect(Neuron *layer1, Neuron *layer2, int *conn_matrix);

/**
 * @brief Set the pre locations object. This function is used to set the index of the presynaptic neuron,
 * relative to the array of neurons, in the array of synapse.
 * 
 * @param neurons 
 * @param synpase 
 */
void set_pre_locations(Neuron neurons, Synapse synpase);

/**
 * @brief Simulate the synapses (only one step).
 * 
 * @param neurons 
 * @param synapses 
 * @param step 
 * @param dt 
 */
void simulate_synapses(Neuron *neurons, Synapse *synapses, int step, float dt);

/**
 * @brief Create a network syn object. This function is used to create a synapse object that contains
 * the two synapses layers.
 * 
 * @param syn1 
 * @param syn2 
 * @return Synapse 
 */
Synapse create_network_syn(Synapse syn1, Synapse syn2);

/**
 * @brief Free the memory allocated for the synapses.   
 * 
 * @param synaptic 
 */
void free_synapses(Synapse *synaptic);
#endif