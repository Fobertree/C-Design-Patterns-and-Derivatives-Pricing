#include <random>
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;
const int seed{37};

double generateGaussian()
{
    // marsaglia polar method
    // one call to this function generates two R.V's. Can optimize by storing the extra
    static double spare;
    static bool hasSpare = false;
    // generate from N(0,1)
    if (hasSpare)
    {
        hasSpare = false;
        return spare;
    }
    float x, y, s;
    do
    {
        // RAND_MAX is constant stored in cstdlib
        x = rand() / ((double)RAND_MAX); // 0 to 1
        y = rand() / ((double)RAND_MAX);
        s = x * x + y * y;
    } while (0 < s && s < 1);

    x = x * sqrt((-2 * log(s)) / s);
    spare = y * s;
    hasSpare = true;

    return x * s;
}

double SimpleMonteCarlo1(double Expiry,
                         double Strike,
                         double Spot,
                         double Vol,
                         double r,
                         unsigned long NumberOfPaths)
{
    double variance = Vol * Vol * Expiry;
    double rootVariance = sqrt(variance);
    // correction term for the drift of the log
    double itoCorrection = -0.5 * variance; // -1/2 sigma^2 T

    double movedSpot = Spot * exp(r * Expiry + itoCorrection); // lhs
    double thisSpot;
    double runningSum = 0;

    for (unsigned long i = 0; i < NumberOfPaths; i++)
    {
        double thisGaussian = generateGaussian(); // N(0,1)
        // sigma * root T * N(0,1)
        // exponent property to create e^{lhs + rhs}
        thisSpot = movedSpot * exp(rootVariance * thisGaussian); // add in rhs of exp
        // thisSpot now represents all of everything in exp
        // (r-\frac{1}{2}\sigma^2)t + \sigma \sqrt{T} N(0,1)
        double thisPayoff = thisSpot - Strike; // E[P] - Strike
        thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
        runningSum += thisPayoff;
    }
    double mean = runningSum / NumberOfPaths;
    mean *= exp(-r * Expiry); // e^{-rT}
    return mean;
}

int main()
{
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPaths;
    cout << "\nEnter expiry:\n";
    cin >> Expiry;
    cout << "\nEnter strike:\n";
    cin >> Strike;

    cout << "\nEnter spot:\n";
    cin >> Spot;
    cout << "\nEnter vol:\n";
    cin >> Vol;

    cout << "\nr:\n";
    cin >> r;

    cout << "\nNumber of paths:\n";
    cin >> NumberOfPaths;

    double result = SimpleMonteCarlo1(Expiry,
                                      Strike,
                                      Spot,
                                      Vol,
                                      r,
                                      NumberOfPaths);

    cout << "\nthe price is " << result << "\n";

    double tmp;
    cin >> tmp;

    return 0;
}