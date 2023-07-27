#ifndef _SYNAPSE_H
#define _SYNAPSE_H 1

#include <stdlib.h>
#include <math.h>
#include "neuron.h"

#define WEIGHT 1
#define GAIN 20
#define TAU_SYN 3
#define DELAY 0

/**
 * @brief The structure contains the synapses that connects two layers.
 * It contains a maximum of two different layers. It may also contain
 * one layer. In this case the two layers are set the same.
 * 
 * The values pre_location and post_location are not valid if layer is NULL.
 */
struct Synapse
{
    int *synapse_id; //id of provenance.

    int *pre_neuron_idx; //unique id of the presynaptic neuron
    int *post_neuron_idx; //unique id of the postsynaptic neuron

    Layer *layer; //The layer address

    int *pre_location; //Location of presynaptic neuron in the presynaptic layer (different from the id)
    int *post_location; //Location of presynaptic neuron in the presynaptic layer (different from the id)

    float *weight;
    float *gain;
    float *tau_syn; //questi parametri dovrebbero essere espressi in ms
    float *delay;

    int synapse_family_id;
    int n_synapses;
};
typedef struct Synapse Synapse;

/**
 * @brief Create a void synapses object.
 * 
 * @param n_synapses 
 * @return Synapse 
 */
Synapse *create_synapses(int n_synapses, bool new_synapses_ids);

/**
 * @brief Connect two layers of neurons. The parameters of the synapse are set to default values:
 * gain = 1, weight = 1, tau_syn = 1, delay = 0. 
 * 
 * @param pre_layer Layer containing the presynaptic neurons.
 * @param post_layer Layer containing the postsynaptic neurons.
 * @param conn_matrix Matrix of connections between neurons of layer1 and layer2.
 * Must have dimensions: pre_layer->n_neurons, post_layer->n_neurons.
 * If there is a connection between the neuron i of layer1 and the neuron j of layer2, 
 * then conn_matrix[i * post_layer->n_neurons + j] = 1, else 0.
 * @return Synapse 
 * @attention The final synapse object cannot yet be utilized. It is necessary to set the pre and post locations.
 */
Synapse *connect(Layer *pre_layer, Layer *post_layer, int *conn_matrix);

/**
 * @brief Find the location of the presynaptic and postsynaptic neurons inside the layer, 
 * and set the pre_location and post_location parameters of the synapse.
 * 
 * @param layer An unique layer in wich are stored ALL the neurons of the network. 
 * @param synpase The synapse object to set.
 */
void set_neurons_location(Layer *layer, Synapse *synpase);

/**
 * @brief Simulate the synapses (only one step).
 * 
 * @param neurons 
 * @param synapses 
 * @param step 
 * @param dt 
 */
void simulate_synapses(Synapse *synapses, float dt);

/**
 * @brief Create a network syn object. This function is used to create a synapse object that contains
 * the two synapses layers.
 * @attention The final network of synapses must have neurons from a maximum of two distinct layers.
 * @param syn1 
 * @param syn2 
 * @return Synapse 
 */
Synapse *combine_synapses(Synapse **synapse, int num_synapse);

/**
 * @brief Free the memory allocated for the synapses.   
 * 
 * @param synaptic 
 */
void free_synapses(Synapse *synaptic);

void save_connectivity(Synapse *synapses, char *filename);

#endif