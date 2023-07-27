#ifndef _NEURON_H
#define _NEURON_H 1
#include "state_logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Implements the Izikevich neuron model. This structure contains n_neurons neurons.
 * The memory storage is optimized for GPU computation. All values of a certain parameter are stored
 * in a single array.
 */
struct Layer
{
    int *id;       // unique id for each neuron
    int *neuron_layer_id; //the layer id of provenience of the neuron, can be different from the layer id of the layer.
                          //The layer of provenience may not exists anymore. Storing the layer id of provenience
                          //is useful to keep track of the layer composition of the final (combined) layer.
    int *last_spike; // timestamp of last spike emitted
    
    float *V;        // membrane potential
    float *U;        // recovery variable
    float *I;        // input current
    float *I_bias;   // bias current
    float *a;        // parameter
    float *b;        // parameter
    float *c;        // parameter
    float *d;        // parameter

    int n_neurons; // number of neurons
    int step;      // current simulation step
    int layer_id; //unique id for each layer
};
typedef struct Layer Layer;



/**
 * @brief Create a Layer (unique id) containing num_neurons neurons.
 * Each neuron is identified by a unique id.
 * They are initialized with default values.
 *
 * @param num_neurons
 * @param new_layer If true doesn't assigne new indexes to neurons. Usefule when creating a layer
 * to merge two existing.
 * @return Layer
 */
Layer *create_neurons(size_t num_neurons, bool new_neurons_ids);

/**
 * @brief Set the initial potential, current, recovery and
 * parameters (a, b, c, d) for a range of neurons in a Layer,
 * where the start_idx end end_idx are inclusive.
 * @attention The indexes refers only to the position of the neurons in the Layer,
 * not to the unique ids of the neurons.
 * 
 * @param neurons The Layer containing the neurons.
 * @param start_idx The start index of neurons to be initialized.
 * @param end_idx The end index of neurons to be initialized. If -1, initialize all neurons starting from start_idx.
 * @param init_v The initial value for membrane potential.
 * @param init_I The initial value for input current.
 * @param init_a The initial value for parameter a.
 * @param init_b The initial value for parameter b.
 * @param init_c The initial value for parameter c.
 * @param init_d The initial value for parameter d.
 * @return void
 */
void initialize_neurons(Layer *neurons, int start_idx, int end_idx, float init_v, float init_u, float init_a, float init_b, float init_c, float init_d);

/**
 * @brief Combine two layers of neurons into a single layer.
 *
 * @param layer1
 * @param layer2
 * @return Layer
 */
Layer *combine_layers(Layer **layers, int num_layers);

/**
 * @brief Simulate the neurons for one time step.
 *
 * @param neurons
 * @param step
 * @param dt
 * @param logger May be null if no logging is needed.
 */
void simulate_neurons(Layer *neurons, float dt, NeuronLogger *logger);

/**
 * @brief Uses an input currents vector to set the input bias currents for the neurons.
 *
 * @param neuron A neuron object.
 * @param currents An array of input currents.
 */
void set_bias_current(Layer *neuron, float *currents);

/**
 * @brief Free the memory allocated for the neurons.
 *
 * @param neurons
 */
void free_neurons(Layer *neurons);


#endif
