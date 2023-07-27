#include <stdio.h>
#include <stdlib.h>
// #include "liquid.h"
#include "random_utilities.h"
#include "neuron.h"
#include "synapse.h"
#include "visualize.h"

int main()
{
    srand(time(NULL));

    //create the neurons
    Layer *layer1 = create_neurons(10, true);
    Layer *layer2 = create_neurons(10, true);

    //create the connettivity matrix
    int *conn_matrix = malloc(sizeof(int) * 10 * 10);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            conn_matrix[i * 10 + j] = 1;

    //connect the layers
    Synapse *syn1 = connect(layer1, layer2, conn_matrix);
    Synapse *syn2 = connect(layer2, layer1, conn_matrix);

    //At this point we can simulate each separate object, 
    //ie the two neuron layers and the two synapses.

    //Instead we will simplify the final structure.
    Layer *neurons = combine_layers(layer1, layer2);
    Synapse *synapses = combine_synapses(syn1, syn2);


    return 0;
}
