#ifndef _VISUALIZE_H
#define _VISUALIZE_H 1

#include "neuron.h"
#include "synapse.h"

void visualize_neuron_layer(Layer *layer);

void visualize_synapse(Synapse *syn);

void print_matrix(int *matrix, int x, int y);


#endif