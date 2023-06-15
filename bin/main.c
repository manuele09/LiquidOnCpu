#include <stdio.h>
#include <stdlib.h>
#include "liquid.h"
#include "neuron.h"
#include "synapse.h"
#include "visualize.h"
#include "random_utilities.h"

int main()
{
    srand(time(NULL));

    Liquid liquid = create_liquid(0.1, 100, 80, 2, 2, 1, 1);

    double curr = 0.01;
    liquid.all_neurons.I_bias[0] = curr;
    liquid.all_neurons.I_bias[5] = curr;
    liquid.all_neurons.I_bias[10] = curr;
    liquid.all_neurons.I_bias[15] = curr;



    simulate_liquid(liquid, 100);




    

    return 0;
}
