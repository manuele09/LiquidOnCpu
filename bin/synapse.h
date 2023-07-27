#ifndef _SYNAPSE_H
#define _SYNAPSE_H 1

#include <stdlib.h>
#include <math.h>
#include "neuron.h"


/**
 * @brief The structure contains the synapses that connects two layers.
 * It contains a maximum of two different layers. It may also contain
 * one layer. In this case the two layers are set the same.
 * 
 */
struct Synapse
{
    int *pre_neuron_idx; //unique id of the presynaptic neuron
    int *post_neuron_idx; //unique id of the postsynaptic neuron

    Layer *pre_layer; //The presynaptic layer
    Layer *post_layer; //The postsynaptic layer

    int *pre_location; //Location of presynaptic neuron in the presynaptic layer (different from the id)
    int *post_location; //Location of presynaptic neuron in the presynaptic layer (different from the id)

    float *weight;
    float *gain;
    float *tau_syn; //questi parametri dovrebbero essere espressi in ms
    float *delay;

    int n_synapses;
};
typedef struct Synapse Synapse;

/**
 * @brief Create a void synapses object.
 * 
 * @param n_synapses 
 * @return Synapse 
 */
Synapse create_synapses(int n_synapses);

/**
 * @brief Connect two layers of neurons. The parameters of the synapse are set to default values:
 * gain = 1, weight = 1, tau_syn = 1, delay = 0. 
 * 
 * @param layer1 
 * @param layer2 
 * @param conn_matrix // Matrix of connections between neurons of layer1 and layer2
 * @return Synapse 
 */
Synapse connect(Layer *pre_layer, Layer *post_layer, int *conn_matrix);

/**
 * @brief Set the pre locations object. This function is used to set the index of the presynaptic neuron,
 * relative to the array of neurons, in the array of synapse.
 * 
 * @param neurons 
 * @param synpase 
 */
void set_pre_locations(Layer pre_layer, Layer post_layer, Synapse synpase);

/**
 * @brief Simulate the synapses (only one step).
 * 
 * @param neurons 
 * @param synapses 
 * @param step 
 * @param dt 
 */
void  simulate_synapses(Layer *neurons, Synapse *synapses, int step, float dt);

/**
 * @brief Create a network syn object. This function is used to create a synapse object that contains
 * the two synapses layers.
 * @attention The final network of synapses must have neurons from a maximum of two distinct layers.
 * @param syn1 
 * @param syn2 
 * @return Synapse 
 */
Synapse combine_synapses(Synapse *syn1, Synapse *syn2);

/**
 * @brief Free the memory allocated for the synapses.   
 * 
 * @param synaptic 
 */
void free_synapses(Synapse *synaptic);
#endif