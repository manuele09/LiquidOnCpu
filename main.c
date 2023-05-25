#include <stdio.h>
#include <stdlib.h>
#include "liquid.h"
#include "neuron.h"
#include "synapse.h"
#include "visualize.h"
#include "random_utilities.h"
// #include <gtest/gtest.h>

int main()
{
    srand(time(NULL));

    Liquid liquid = create_liquid(0.1, 100, 80, 2, 2, 1, 1);
    
    simulate_liquid(liquid, 100);

    free_liquid(liquid);


    return 0;
}
