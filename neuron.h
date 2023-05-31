#ifndef _NEURON_H
#define _NEURON_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief A basic neuron model, based on Izikevich.
 *
 */
struct Neuron
{
    float *V;        // membrane potential
    float *U;        // recovery variable
    float *I;        // input current
    float *I_bias;   // bias current
    float *a;        // parameter
    float *b;        // parameter
    float *c;        // parameter
    float *d;        // parameter
    int *last_spike; // timestamp of last spike emitted
    int *id;         // unique id for each neuron
    int size;        // number of neurons
};
typedef struct Neuron Neuron;

/**
 * @brief A logger for neuron data.
 *
 */
struct NeuronLogger
{
    int *step;
    float *V;      // membrane potential
    float *I;      // input current
    float *I_bias; // bias current
    int *id;       // unique id for each neuron
    int counter;
    int size; // number of neurons times number of steps
};
typedef struct NeuronLogger NeuronLogger;

/**
 * @brief Create a logger object.
 * 
 * @param size number of neurons times number of steps
 * @return NeuronLogger 
 */
NeuronLogger create_logger(size_t size);

void writeNeuronLogger(char *file_name, NeuronLogger logger);

/**
 * @brief Create a neurons object, containing num_neurons neurons.
 *
 * @param num_neurons
 * @return Neuron
 */
Neuron create_neurons(size_t num_neurons);

/**
 * @brief Initialize the initial potential, current, and parameters (a, b, c, d) for a range of neurons.
 *
 * @param neurons Pointer to the Neuron array.
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
void initialize_neurons(Neuron *neurons, int start_idx, int end_idx, float init_v, float init_u, float init_a, float init_b, float init_c, float init_d);

/**
 * @brief Create a network object, containing two layers of neurons.
 *
 * @param layer1
 * @param layer2
 * @return Neuron
 */
Neuron create_network(Neuron layer1, Neuron layer2);

/**
 * @brief Simulate the neurons for one time step.
 *
 * @param neurons
 * @param step
 * @param dt
 * @param logger May be null if no logging is needed.
 */
void simulate_neurons(Neuron *neurons, int step, float dt, NeuronLogger *logger);

/**
 * @brief Uses an input currents vector to set the input bias currents for the neurons.
 *
 * @param neuron A neuron object.
 * @param currents An array of input currents.
 */
void set_input(Neuron neuron, int *currents);

/**
 * @brief Free the memory allocated for the neurons.
 *
 * @param neurons
 */
void free_neurons(Neuron *neurons);

/**
 * @brief Free the memory allocated for the neuron logger.
 *
 * @param logger
 */
void free_neuron_logger(NeuronLogger *logger);

#endif
