#ifndef TEST_GAUSSIAN_H_
#define TEST_GAUSSIAN_H_

float findMin(float arr[], int size);

float findMax(float arr[], int size);

void TestGaussian(float mean, float stddev, int num_samples);

void TestGaussianClipped(float mean, float stddev, float min, float max, int num_samples);

#endif