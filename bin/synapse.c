#include "synapse.h"
// Immaginiamo di voler connettere due popolazioni di neuroni:
// caso a: le due popolazioni sono distinte.
//   1) Creo le due popolazioni;
//   2) Faccio le opportune connessioni;
//   3) Ho finito.
//   L'oggetto sinapsi dovrà possedere i due indirizzi relativi alle popolazioni.

// caso b: le due popolazioni saranno fuse in un unica.
//   1) Creo le due popolazioni;
//   2) Faccio le opportune connessioni;
//   3) Unisco le due popolazioni;
//   4) Cambio i riferimenti all'interno della sinapsi.
//   L'oggetto sinapsi dovrà possedere l'indirizzo dell'unica popolazione finale.
//   I due indirizzi disponibili possono essere impostati coincidenti.

Synapse create_synapses(int n_synapses)
{
    Synapse synaptic;
    synaptic.pre_neuron_idx = (int *)calloc(n_synapses, sizeof(int));
    synaptic.post_neuron_idx = (int *)calloc(n_synapses, sizeof(int));

    synaptic.pre_layer = NULL;
    synaptic.post_layer = NULL;

    synaptic.pre_location = (int *)calloc(n_synapses, sizeof(int));
    synaptic.post_location = (int *)calloc(n_synapses, sizeof(int));

    synaptic.weight = (float *)calloc(n_synapses, sizeof(float));
    synaptic.gain = (float *)calloc(n_synapses, sizeof(float));
    synaptic.tau_syn = (float *)calloc(n_synapses, sizeof(float));
    synaptic.delay = (float *)calloc(n_synapses, sizeof(float));

    synaptic.n_synapses = n_synapses;

    return synaptic;
}

Synapse connect(Layer *pre_layer, Layer *post_layer, int *conn_matrix)
{
    int num_syn = 0;
    for (int i = 0; i < pre_layer->n_neurons; i++)
        for (int j = 0; j < post_layer->n_neurons; j++)
            num_syn += conn_matrix[i * post_layer->n_neurons + j];

    Synapse synapses = create_synapses(num_syn);

    synapses.pre_layer = pre_layer;
    synapses.post_layer = post_layer;

    int syn_index = 0;
    for (int i = 0; i < pre_layer->n_neurons; i++)
        for (int j = 0; j < post_layer->n_neurons; j++)
        {
            if (conn_matrix[i * post_layer->n_neurons + j] == 1)
            {
                synapses.pre_neuron_idx[syn_index] = pre_layer->id[i];
                synapses.pre_location[syn_index] = i;
                synapses.post_neuron_idx[syn_index] = post_layer->id[j];
                synapses.post_location[syn_index] = j;

                synapses.gain[syn_index] = 1;
                synapses.weight[syn_index] = 1;
                synapses.tau_syn[syn_index] = 1;
                synapses.delay[syn_index] = 0;

                syn_index++;
            }
        }
    return synapses;
}

// aggiungere controllo errori nel caso alcuni neuroni non siano trovati
void set_pre_locations(Layer pre_layer, Layer post_layer, Synapse synpase)
{
    for (int i = 0; i < synpase.n_synapses; i++)
    {
        for (int j = 0; j < pre_layer.n_neurons; j++)
        {
            if (pre_layer.id[j] == synpase.pre_neuron_idx[i])
            {
                synpase.pre_location[i] = j;
                break;
            }
        }
        for (int j = 0; j < post_layer.n_neurons; j++)
        {
            if (post_layer.id[j] == synpase.post_neuron_idx[i])
            {
                synpase.post_location[i] = j;
                break;
            }
        }
    }
}

void simulate_synapses(Layer *neurons, Synapse *synapses, int step, float dt)
{
    // For each neuron find the pre-synaptic current
    for (int i = 0; i < neurons->n_neurons; i++)
    {
        float I_syn = 0.0f;

        for (int j = 0; j < synapses->n_synapses; j++)
        {
            if (synapses->post_neuron_idx[j] != neurons->id[i])
                continue;

            int last_spike = neurons->last_spike[synapses->pre_location[j]];

            I_syn += synapses->weight[j] * exp(-(step - last_spike + synapses->delay[j]) * dt / synapses->tau_syn[j]);
        }
        neurons->I[i] = I_syn;
    }
}

Synapse combine_synapses(Synapse *syn1, Synapse *syn2)
{
    Layer *layers[4] = {syn1->pre_layer, syn2->pre_layer, syn1->post_layer, syn2->post_layer};
    int ids[4] = {layers[0]->layer_id, layers[1]->layer_id, layers[2]->layer_id, layers[3]->layer_id};

    Layer *unique_layers[4];
    int index = 0;
    int uniqueOccurrences = 0;
    // il count vale 1 solamente per la ultima occorrenza di un valore nell'array
    for (int i = 0; i < 4; i++)
    {
        int count = 1;
        for (int j = i + 1; j < 4; j++)
            if (ids[i] == ids[j])
            {
                count = 0; // Found a duplicate, reset count to 0
                break;
            }
        uniqueOccurrences += count;
        if (count == 1)
            unique_layers[index++] = layers[i];
    }

    if (uniqueOccurrences > 2)
    {
        printf("Combine synapses error: a syn obj can contain at most 2 different layers.\nHere there are %d\n", uniqueOccurrences);
        exit(1);
    }

    int total_s = syn1->n_synapses + syn2->n_synapses;
    Synapse syn_net;

    syn_net = create_synapses(total_s);

    if (uniqueOccurrences == 1) // Pre_layer and Post_layer are the same
    {
        syn_net.pre_layer = syn1->pre_layer;
        syn_net.post_layer = syn1->pre_layer;
    }
    else // There are two different layers
    {
        syn_net.pre_layer = unique_layers[0];
        syn_net.post_layer = unique_layers[1];
    }

    int net_id = 0;
    for (int i = 0; i < syn1->n_synapses; i++)
    {
        syn_net.pre_neuron_idx[net_id] = syn1->pre_neuron_idx[i];
        syn_net.post_neuron_idx[net_id] = syn1->post_neuron_idx[i];
        syn_net.weight[net_id] = syn1->weight[i];
        syn_net.gain[net_id] = syn1->gain[i];
        syn_net.tau_syn[net_id] = syn1->tau_syn[i];
        syn_net.delay[net_id] = syn1->delay[i];
        net_id++;
    }
    for (int i = 0; i < syn2->n_synapses; i++)
    {
        syn_net.pre_neuron_idx[net_id] = syn2->pre_neuron_idx[i];
        syn_net.post_neuron_idx[net_id] = syn2->post_neuron_idx[i];
        syn_net.weight[net_id] = syn2->weight[i];
        syn_net.gain[net_id] = syn2->gain[i];
        syn_net.tau_syn[net_id] = syn2->tau_syn[i];
        syn_net.delay[net_id] = syn2->delay[i];
        net_id++;
    }

    return syn_net;
}

void free_synapses(Synapse *synaptic)
{
    free(synaptic->pre_neuron_idx);
    free(synaptic->pre_location);
    free(synaptic->post_neuron_idx);
    free(synaptic->weight);
    free(synaptic->gain);
    free(synaptic->tau_syn);
    free(synaptic->delay);
}
