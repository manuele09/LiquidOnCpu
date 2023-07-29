#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LogisticRegression.h"

void test_lr(void);

void LogisticRegression__construct(LogisticRegression *this, int N, int n_in, int n_out)
{
  int i, j;
  this->N = N;
  this->n_in = n_in;
  this->n_out = n_out;

  this->W = (float **)malloc(sizeof(float *) * n_out);
  this->W[0] = (float *)malloc(sizeof(float) * n_in * n_out);
  for (i = 0; i < n_out; i++)
    this->W[i] = this->W[0] + i * n_in;
  this->b = (float *)malloc(sizeof(float) * n_out);

  for (i = 0; i < n_out; i++)
  {
    for (j = 0; j < n_in; j++)
      this->W[i][j] = 0;
    this->b[i] = 0;
  }
}

void LogisticRegression__destruct(LogisticRegression *this)
{
  free(this->W[0]);
  free(this->W);
  free(this->b);
}

void LogisticRegression_train(LogisticRegression *this, float *x, int *y, float lr)
{
  int i, j;
  float *p_y_given_x = (float *)malloc(sizeof(float) * this->n_out); //will contain the prediction given x
  float *dy = (float *)malloc(sizeof(float) * this->n_out); //will contain the error between the prediction and the true label

  // Find the prediction for each output-classes
  //Is the same of calling LogisticRegression_predict
  for (i = 0; i < this->n_out; i++)
  {
    p_y_given_x[i] = 0;
    for (j = 0; j < this->n_in; j++)
    {
      p_y_given_x[i] += this->W[i][j] * x[j];
    }
    p_y_given_x[i] += this->b[i];
  }
  LogisticRegression_softmax(this, p_y_given_x);

  for (i = 0; i < this->n_out; i++)
  {
    //Error between the prediction and the true label
    dy[i] = y[i] - p_y_given_x[i];

    //Apply the gradient descent to each weight and bias
    for (j = 0; j < this->n_in; j++)
      this->W[i][j] += lr * dy[i] * x[j] / this->N;
    this->b[i] += lr * dy[i] / this->N;
  }

  free(p_y_given_x);
  free(dy);
}

void LogisticRegression_softmax(LogisticRegression *this, float *x)
{
  int i;
  float max = 0.0;
  float sum = 0.0;

  //Find the max value
  for (i = 0; i < this->n_out; i++)
    if (max < x[i])
      max = x[i];

  for (i = 0; i < this->n_out; i++)
  {
    x[i] = exp(x[i] - max); //Subtract max for numerical stability (this is equivalent to the version without the subtraction)
    sum += x[i];
  }

  for (i = 0; i < this->n_out; i++)
    x[i] /= sum;
}

void LogisticRegression_predict(LogisticRegression *this, float *x, float *y)
{
  int i, j;

  // Find the prediction for each output-classes
  for (i = 0; i < this->n_out; i++)
  {
    y[i] = 0;
    // Do the dot product between the weights and the input vector
    for (j = 0; j < this->n_in; j++)
    {
      y[i] += this->W[i][j] * x[j];
    }
    y[i] += this->b[i];
  }

  LogisticRegression_softmax(this, y);
}

void test_lr(void)
{
  int i, j, epoch;

  float learning_rate = 0.1;
  int n_epochs = 500;

  int train_N = 6;
  int test_N = 2;
  int n_in = 6;
  int n_out = 2;

  // training data
  float train_X[6][6] = {
      {1, 1, 1, 0, 0, 0},
      {1, 0, 1, 0, 0, 0},
      {1, 1, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 0},
      {0, 0, 1, 1, 0, 0},
      {0, 0, 1, 1, 1, 0}};

  int train_Y[6][2] = {
      {1, 0},
      {1, 0},
      {1, 0},
      {0, 1},
      {0, 1},
      {0, 1}};

  // construct LogisticRegression
  LogisticRegression classifier;
  LogisticRegression__construct(&classifier, train_N, n_in, n_out);

  // train
  for (epoch = 0; epoch < n_epochs; epoch++)
  {
    for (i = 0; i < train_N; i++)
    {
      LogisticRegression_train(&classifier, train_X[i], train_Y[i], learning_rate);
    }
    // learning_rate *= 0.95;
  }

  // test data
  float test_X[2][6] = {
      {1, 0, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 0}};

  float test_Y[2][2];

  // test
  for (i = 0; i < test_N; i++)
  {
    LogisticRegression_predict(&classifier, test_X[i], test_Y[i]);
    for (j = 0; j < n_out; j++)
    {
      printf("%f ", test_Y[i][j]);
    }
    printf("\n");
  }

  // destruct LogisticRegression
  LogisticRegression__destruct(&classifier);
}

