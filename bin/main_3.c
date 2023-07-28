#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "test_gaussian.h"

int mainc() {

    TestGaussian(1, 100, 500000);
    // TestGaussianClipped(0, 1, -3, 3, 500000);

    return 0;
}
