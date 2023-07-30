#include <stdio.h>
#include "neuron.h"
#include "synapse.h"
#include "liquid.h"
#include "iris.h"
#include "dataset.h"
#include "visualize.h"

int main(void)
{
    // printf("Prova: %f\n", 1 -((float)23 / 100));
    // exit(1);
    // define liquid structure
    float dt = 0.1;  // 0.1 ms
    int n_exc = 80;  // 80%
    int n_inh = 20;  // 20%
    float n_rec = 1; // 100% of excitatory neurons
    float input_outdegree = 0.7;

    // define input
    int num_feautures = 4;
    int num_classes = 3;

    float *input_matrix;
    int *label_matrix;
    int num_samples;


    readIrisDataset("../datasets/iris/iris.data", &input_matrix, &label_matrix, &num_samples);

    Dataset *dataset = create_dataset(input_matrix, label_matrix, num_samples, num_feautures, num_classes);

    split_dataset(dataset, 0.5);

    // exit(1);

    // print_dataset(dataset, true, true, true);

    float stim_interval = 40; // 300 ms
    float stim_length = 20;   // 50 ms
    float readout_delay = 1;  // 10 ms

    printf("readout delay: %f\n", readout_delay);

    int stim_interval_steps = (int)(stim_interval / dt);
    int stim_length_steps = (int)(stim_length / dt);
    int readout_delay_steps = (int)(readout_delay / dt);

    int steps = dataset->num_train_samples * stim_interval_steps - stim_length_steps - readout_delay_steps + 1;

    Liquid *liquid = create_liquid(dt, n_exc, n_inh, n_rec, 2, 2, 1, 1);
    create_input_layer(liquid, num_feautures, input_outdegree);
    NeuronLogger *logger = create_neuron_logger(liquid->neurons->n_neurons, steps);
    logger = NULL;

    float *liquid_output_train = (float *)calloc(dataset->num_train_samples * liquid->n_rec, sizeof(float));
    int epoch = -1;
    for (int i = 0; i < steps; i++)
    {

        if (i % stim_interval_steps == 0)
        {
            epoch++;
            set_input(liquid, &dataset->train_dataset[epoch * dataset->num_features], 5);
            printf("Epoch: %d\n", epoch); 
        }
        if ((i - stim_length_steps) % stim_interval_steps == 0)
            clear_input(liquid);
        if ((i - stim_length_steps - readout_delay_steps) % stim_interval_steps == 0)
            read_output(liquid, &liquid_output_train[epoch * liquid->n_rec], 1);

        simulate_neurons(liquid->neurons, liquid->dt, logger);
        simulate_synapses(liquid->synapses, liquid->dt);
    }

    // print_matrix_float(liquid_output_train, dataset->num_train_samples, liquid->n_rec);

    // construct LogisticRegression
    LogisticRegression classifier;
    LogisticRegression__construct(&classifier, dataset->num_train_samples, liquid->n_rec, dataset->num_classes);

    int n_epochs = 2000;
    for (epoch = 0; epoch < n_epochs; epoch++)
        for (int i = 0; i < dataset->num_train_samples; i++)
            LogisticRegression_train(&classifier, &liquid_output_train[i * liquid->n_rec], &dataset->train_labels[i * dataset->num_classes], 0.1);

    // testing on the training dataset
    float *train_prediction = (float *)calloc(dataset->num_train_samples * dataset->num_classes, sizeof(float));
    for (int i = 0; i < dataset->num_train_samples; i++)
        LogisticRegression_predict(&classifier, &liquid_output_train[i * liquid->n_rec], &train_prediction[i * dataset->num_classes]);


    float train_accuracy = accuracy(train_prediction, dataset->train_labels, dataset->num_train_samples, dataset->num_classes);
    printf("Accuracy: %.2f\%\n", train_accuracy * 100);
    // print_matrix_float(train_prediction, dataset->num_train_samples, dataset->num_classes);
    // print_matrix(dataset->train_labels, dataset->num_train_samples, dataset->num_classes);

    writeNeuronLogger("../logs/liquid.txt", logger);
    // free_neuron_logger(logger);
    LogisticRegression__destruct(&classifier);
    free_liquid(liquid);

    free_dataset(dataset);
    return 0;
}