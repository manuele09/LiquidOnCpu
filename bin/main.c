#include <stdio.h>
#include <stdlib.h>
// #include "liquid.h"
#include "random_utilities.h"
#include "neuron.h"
#include "synapse.h"
#include "visualize.h"

int main()
{
    // srand(time(NULL));

    //create the neurons
    Layer *layer1 = create_neurons(10, true);
    // visualize_neuron_layer(layer1);
    Layer *layer2 = create_neurons(10, true);
    // visualize_neuron_layer(layer2);

    //create the connettivity matrix
    int *conn_matrix = malloc(sizeof(int) * 10 * 10);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            conn_matrix[i * 10 + j] = 1;

    //connect the layers
    Synapse *syn1 = connect(layer1, layer2, conn_matrix);
    // visualize_synapse(syn1);
    Synapse *syn2 = connect(layer2, layer1, conn_matrix);
    // visualize_synapse(syn2);

    //At this point we can simulate each separate object, 
    //ie the two neuron layers and the two synapses.

    //Instead we will simplify the final structure.
    Layer *layers[] = {layer1, layer2};
    Layer *neurons = combine_layers(layers, 2);
    // visualize_neuron_layer(neurons);

    Synapse *synapses_list[] = {syn1, syn2};
    Synapse *synapses = combine_synapses(synapses_list, 2);
    set_neurons_location(neurons, synapses);
    // visualize_synapse(synapses);

    float *bias_current = (float *)calloc(neurons->n_neurons, sizeof(float));
    // for (int i = 0; i < neurons->n_neurons; i++)
    //     bias_current[i] = 10.0f;
    bias_current[0] = 200;
    set_bias_current(neurons, bias_current);

    NeuronLogger *logger = create_neuron_logger(neurons->n_neurons, 1000);
    for (int i = 0; i < 1000; i++)
    {
        simulate_neurons(neurons, 0.1f, logger);
        simulate_synapses(synapses, 0.1f);

    }
    writeNeuronLogger("../logs/prova_log.txt", logger);


    return 0;
}


