#include <Random1.h>
#include <cstdlib>
#include <cmath>

// some math functions are not properly defined in Visual C++ 6.0 (VC++6) compiler.
#if !defined(_MSC_VER)
// this means code is not compiled with a visual C++ compiler
using namespace std;
#endif

double GetOneGaussianBySummation()
{
    double result = 0;

    for (unsigned long j = 0; j < 12; j++)
        result += rand() / static_cast<double>(RAND_MAX);

    result -= 6.0; // result will be around 6. 0.5 * 12

    return result; // return mean of 0?
}

double GetOneGaussianByBoxMuller()
{
    double result;

    double x;
    double y;

    double sizeSquared;
    do
    {
        x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
        y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
        sizeSquared = x * x + y * y;
    } while (sizeSquared >= 1.0);

    result = x * sqrt(-2 * log(sizeSquared) / sizeSquared);

    return result;
}