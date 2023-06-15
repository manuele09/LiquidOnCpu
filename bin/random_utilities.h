#ifndef _RANDOM_UTILITIES_H
#define _RANDOM_UTILITIES_H 1

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

/**
 * @brief Returns a number generated from a Gaussian Distribution.
 * 
 * @param mu Mean
 * @param sigma Standard Deviation
 * @return float 
 */
float GaussianDistribution(float mu, float sigma);

/**
 * @brief Returns a number generated from a Clipped Gaussian Distribution.
 * 
 * @param mu Mean
 * @param sigma Standard Deviation
 * @param minValue 
 * @param maxValue 
 * @return float 
 */
float GaussianDistributionClipped(float mu, float sigma, float minValue, float maxValue);

#endif