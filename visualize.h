#ifndef _VISUALIZE_H
#define _VISUALIZE_H 1

#include "neuron.h"
#include "synapse.h"

void visualize_neuron_layer(Neuron layer)
{
    printf("Totale Neuroni: %d\n", layer.size);
    for (int i = 0; i < layer.size; i++)
    {
        printf("Neurone: %d\n", layer.id[i]);
        printf("A: %f, B: %f, C: %f, D: %f, V: %f, I: %f, U: %f\n", layer.a[i], layer.b[i], layer.c[i], layer.d[i], layer.V[i], layer.I[i], layer.U[i]);
        printf("Last Spike (step): %d\n", layer.last_spike[i]);
        printf("\n\n");
    }
}

void visualize_synapse(Synapse syn)
{
    printf("Totale Sinapsi: %d\n", syn.num_synapses);
    for (int i = 0; i < syn.num_synapses; i++)
    {
        printf("Pre: %d, Post: %d\n", syn.pre_neuron_idx[i], syn.post_neuron_idx[i]);
        printf("W: %f, G: %f, Tau: %f\n", syn.weight[i], syn.gain[i], syn.tau_syn[i]);
        printf("\n\n");
    }
}

// void print_matrix(int *matrix, int x, int y)
// {
//     printf("Matrice  delle connessioni:\n");
//     for (int i = 0; i < x; i++)
//     {
//         for (int j = 0; j < y; j++)
//             printf("%d ", matrix[i * y + j]);
//         printf("\n");
//     }
//     printf("\n");
// }

// void graph_v(NeuronLogger *logger, int i)
// {
//     if (i >= logger->n_neurons)
//     {
//         printf("Indice fuori soglia\n");
//         exit(1);
//     }
//     FILE *gp = popen("gnuplot -persist", "w"); // open gnuplot

//     fprintf(gp, "set xlabel 'Time (ms)'\n");
//     fprintf(gp, "set ylabel 'Voltage (mV)'\n");
//     fprintf(gp, "set yrange [-85:50]\n");
//     fprintf(gp, "set title 'Neuron %d'\n", i);
//     fprintf(gp, "plot '-' with lines\n");

//     for (int s = 0; s < logger->steps; s++)
//     {
//         fprintf(gp, "%d %f\n", s, logger->v[s * logger->n_neurons + i]);
//     }
//     fprintf(gp, "e\n"); // end of data for gnuplot
//     fflush(gp);         // flush gnuplot buffer
//     pclose(gp);         // close gnuplot */
// }
// void graph_I(NeuronLogger *logger, int i)
// {
//     if (i >= logger->n_neurons)
//     {
//         printf("Indice fuori soglia\n");
//         exit(1);
//     }
//     FILE *gp = popen("gnuplot -persist", "w"); // open gnuplot

//     fprintf(gp, "set xlabel 'Time (ms)'\n");
//     fprintf(gp, "set ylabel 'Current (A)'\n");
//     fprintf(gp, "set title 'Neuron %d'\n", i);
//     fprintf(gp, "plot '-' with lines\n");

//     for (int s = 0; s < logger->steps; s++)
//     {
//         fprintf(gp, "%d %f\n", s, logger->I[s * logger->n_neurons + i]);
//     }
//     fprintf(gp, "e\n"); // end of data for gnuplot
//     fflush(gp);         // flush gnuplot buffer
//     pclose(gp);         // close gnuplot */
// }

// void graph_spikes(NeuronLogger *logger, int i)
// {
//     if (i >= logger->n_neurons)
//     {
//         printf("Indice fuori soglia\n");
//         exit(1);
//     }
//     FILE *gp = popen("gnuplot -persist", "w"); // open gnuplot

//     fprintf(gp, "set xlabel 'Time (ms)'\n");
//     fprintf(gp, "set ylabel 'Spikes (A)'\n");
//     fprintf(gp, "set title 'Neuron %d'\n", i);
//     fprintf(gp, "plot '-' with p pointtype 7 pointsize 0.5 \n");

//     for (int s = 0; s < logger->steps; s++)
//     {
//         if (logger->spikes[s * logger->n_neurons + i] == 1)
//             fprintf(gp, "%d %d\n", s, logger->spikes[s * logger->n_neurons + i]);
//     }
//     fprintf(gp, "e\n"); // end of data for gnuplot
//     fflush(gp);         // flush gnuplot buffer
//     pclose(gp);         // close gnuplot */
// }
// float get_logger_dim(NeuronLogger *logger)
// {
//     float dim = sizeof(float) * 2 * logger->steps * logger->n_neurons;
//     printf("Il Logger occupa %.3f Megabytes\n", dim / 1000000);
//     return dim;
// }

#endif