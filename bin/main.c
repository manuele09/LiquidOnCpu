#include <stdio.h>
#include <stdlib.h>
#include "liquid.h"
#include "random_utilities.h"
#include "neuron.h"
#include "synapse.h"
#include "visualize.h"

int main()
{
    char *stringhe[10] = {"uno", "due", "tre", "due", "quattro", "cinque", "cinque", "quattro", "uno", "zero"};
    int ids[10] = {1, 2, 3, 2, 4, 5, 5, 4, 1, 0};

    char *unique_stringe[10];
    int uniqueOccurrences = 0;
    int index = 0;
    // il count vale 1 solamente per la ultima occorrenza di un valore nell'array
    for (int i = 0; i < 10; i++)
    {
        int count = 1;
        for (int j = i + 1; j < 10; j++)
            if (ids[i] == ids[j])
            {
                count = 0; // Found a duplicate, reset count to 0
                break;
            }
        uniqueOccurrences += count;
        if (count == 1)
            unique_stringe[index++] = stringhe[i];
    }

    for (int i = 0; i < index; i++)
        printf("%s\n", unique_stringe[i]);
    exit(1);
    srand(time(NULL));

    //create the neurons
    Layer layer1 = create_neurons(10, true);
    Layer layer2 = create_neurons(10, true);

    //create the connettivity matrix
    int *conn_matrix = malloc(sizeof(int) * 10 * 10);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            conn_matrix[i * 10 + j] = 1;

    //connect the layers
    Synapse syn1 = connect(&layer1, &layer2, conn_matrix);
    Synapse syn2 = connect(&layer2, &layer1, conn_matrix);

    //At this point we can simulate each separate object, 
    //ie the two neuron layers and the two synapses.

    //Instead we will simplify the final structure.
    Layer neurons = combine_layers(&layer1, &layer2);
    Synapse synapses = combine_synapses(&syn1, &syn2);


    return 0;
}
