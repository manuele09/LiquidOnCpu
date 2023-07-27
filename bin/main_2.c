#include <stdio.h>
#include <stdlib.h>
// #include "liquid.h"
#include "random_utilities.h"
#include "neuron.h"
#include "synapse.h"
#include "visualize.h"
#include <unistd.h>

int maina()
{
    
    Layer *layer1 = create_neurons(1, true);
    Layer *layer2 = create_neurons(1, true);

    int *conn_matrix = malloc(sizeof(int) * 1 * 1);
    conn_matrix[0] = 1;

    Synapse *syn = connect(layer1, layer2, conn_matrix);

    Layer *layers[] = {layer1, layer2};
    Layer *neurons = combine_layers(layers, 2);

    set_neurons_location(neurons, syn);

    float *bias_current = (float *)calloc(neurons->n_neurons, sizeof(float));
    bias_current[0] = 20;
    set_bias_current(neurons, bias_current);

    NeuronLogger *logger = create_neuron_logger(neurons->n_neurons, 1000);
    for (int i = 0; i < 1000; i++)
    {
        simulate_neurons(neurons, 0.1f, logger);
        simulate_synapses(syn, 0.1f);

    }
    writeNeuronLogger("../logs/prova_log.txt", logger);
    visualize_synapse(syn);

    save_connectivity(syn, "../logs/conn.txt");
    //Prossimo passo: aggiustare i parametri.
    //Fare la prova con due neuroni

    return 0;
}


