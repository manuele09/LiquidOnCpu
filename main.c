#include <stdio.h>
#include <stdlib.h>
#include "neuron.h"
// #include <gtest/gtest.h>

int main()
{
    Neuron neurons = create_neurons(10);

    initialize_neurons(&neurons, 0, -1, -65.0f, -30.0f, 40.0f, 0.02f, 0.2f, -65.0f, 8.0f);

    for (int i = 0; i < 10000; i++)
        update_neurons(&neurons, i, 0.01);
    
    
    free_neurons(&neurons);

    return 0;
}
