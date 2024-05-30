// RandomMain3.cpp

#include <iostream>
#include "SimpleMC8.h"
#include "ParkMiller.h"
#include "Vanilla3.h"
#include "MCStatistics.h"
#include "ConvergenceTable.h"
#include "StatisticsSummary.h"
#include "VecMeanStdDev.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

int main()
{
    // srand(time(NULL));
    // unsigned long baseSeed = rand();
    unsigned long baseSeed = 1;

    double Expiry = 0.5;
    double Strike = 100;
    double Spot = 95;
    double Vol = 0.2;
    double r = 0.06;
    unsigned long NumberOfPaths = 1000000;
    double confLevel = 0.95;

    PayOffCall thePayOff(Strike);
    VanillaOption theOption(thePayOff, Expiry);

    ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);

    // ==================================================
    cout << "\nWe have the following parameters:\n";
    cout << "Expiry          = " << Expiry << "\n";
    cout << "Strike          = " << Strike << "\n";
    cout << "Spot            = " << Spot << "\n";
    cout << "Vol             = " << Vol << "\n";
    cout << "r               = " << r << "\n";
    cout << "NumberOfPaths   = " << NumberOfPaths << "\n";
    cout << "ConfLevel alpha = " << confLevel << "\n";
    cout << "Base seed       = " << baseSeed << "\n";

    // ==================================================
    StatisticsSummary gatherer3(confLevel);
    RandomParkMiller generator3(baseSeed);

    SimpleMonteCarlo6(theOption,
                      Spot,
                      VolParam,
                      rParam,
                      NumberOfPaths,
                      gatherer3,
                      generator3);

    vector<vector<double>> results3 = gatherer3.GetResultsSoFar();

    cout << "\nFor the call price the results are: \n";
    cout << "averaged discounted payoff | std of discounted payoffs | std of averaged discounted payoffs | lower alpha% confidence limit | upper alpha% confidence limit |\n";

    for (unsigned long i = 0; i < results3.size(); i++)
    {
        for (unsigned long j = 0; j < results3[i].size(); j++)
        {
            cout << results3[i][j] << " | ";
        }
    }
    cout << "\n";
    
    // ==================================================
    // waiting for user to enter anything
    double tmp2;
    //cin >> tmp2;

    return 0;
}
