#ifndef LOGISTICREGRESSION_H
#define LOGISTICREGRESSION_H

typedef struct {
  int N; //Number of samples, is mandatory to only if you are doing training.
  int n_in; //Input dimension 
  int n_out; //Output dimension (number of classes) 
  float **W; //Matrix of weights (n_out x n_in)
  float *b; //Vector of biases (n_out)
} LogisticRegression;

/**
 * @brief Construct a new Logistic Regression object
 * 
 * @param this The pointer to the LogisticRegression object.
 * @param N Number of samples, is mandatory to only if you are doing training.
 * @param n_in Input dimension.
 * @param n_out Output dimension (number of classes).
 */
void LogisticRegression__construct(LogisticRegression *this, int N, int n_in, int n_out);

/**
 * @brief Frees the memory allocated for the LogisticRegression object.
 * 
 * @param this The pointer to the LogisticRegression object.
 */
void LogisticRegression__destruct(LogisticRegression *this);

/**
 * @brief Trains the Logistic Regression model.
 * 
 * @param this The pointer to the LogisticRegression object.
 * @param x The input vector of n_in elements.
 * @param y The output vector (n_out elements), that contains the true labels.
 * @param lr The learning rate.
 */
void LogisticRegression_train(LogisticRegression *this, float *x, int *y, float lr);

/**
 * @brief Computes the softmax of the input vector.
 * This function is called by LogisticRegression_predict, so it is not necessary to call it explicitly.
 * 
 * @param this The pointer to the LogisticRegression object.
 * @param x The vector, where the result will be stored. This vector
 * must be of size n_out. Each entry usually is the dot product between the
 * weights of the Logistic Regression model and the input vector.
 */
void LogisticRegression_softmax(LogisticRegression *this, float *x);

/**
 * @brief Predicts the output of the Logistic Regression model.
 * 
 * @param this The pointer to the LogisticRegression object.
 * @param x The input vector, of size n_in.
 * @param y The output vector, of size n_out, where the result will be stored.
 */
void LogisticRegression_predict(LogisticRegression *this, float *x, float *y);

/**
 * @brief Tests the Logistic Regression model. The code contains
 * a simple example of Logistic Regression.
 * 
 */
void test_lr(void);

#endif
