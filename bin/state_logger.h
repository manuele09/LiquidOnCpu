#ifndef _STATE_LOGGER_H
#define _STATE_LOGGER_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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
    int *layer_id; // id of the layer the neuron belongs to
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
NeuronLogger *create_neuron_logger(size_t n_neurons, size_t steps);

void writeNeuronLogger(char *file_name, NeuronLogger *logger);

void free_neuron_logger(NeuronLogger *logger);

#endif