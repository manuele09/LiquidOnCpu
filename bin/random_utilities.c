#include "random_utilities.h"


float GaussianDistribution(float mu, float sigma)
{
    // These are uniform(0,1) random floats
    float u1 = (float)rand() / (float)RAND_MAX;
    float u2 = (float)rand() / (float)RAND_MAX;
    // Using Box-Muller transform to get two standard normally distributed numbers
    float randStdNormal = sqrt(-2.0 * log(u1)) *
                           sin(2.0 * M_PI * u2);

    // Scaling and shifting standard normal random numbers to get desired distribution
    float randNormal = mu + sigma * randStdNormal;

    return randNormal;
}

float GaussianDistributionClipped(float mu, float sigma, float minValue, float maxValue)
{
    float randNormal = 0;
    float u1, u2, randStdNormal;
    do
    {
        u1 = (float)rand() / (float)RAND_MAX;
        u2 = (float)rand() / (float)RAND_MAX;
        // Using Box-Muller transform to get two standard normally distributed numbers
        randStdNormal = sqrt(-2.0 * log(u1)) *
                               sin(2.0 * M_PI * u2);

        // Scaling and shifting standard normal random numbers to get desired distribution
        randNormal = mu + sigma * randStdNormal;
    } while ((randNormal < minValue) || (randNormal > maxValue));

    return randNormal;
}

