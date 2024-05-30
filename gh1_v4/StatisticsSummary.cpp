// StatisticsSummary.cpp

#include "MCStatistics.h"
#include "StatisticsSummary.h"
#include "VecMeanStdDev.h"
#include "Normals.h"
#include  <cmath>

using namespace std;

StatisticsSummary::StatisticsSummary(double confLevel_)
    :
    Payoffs(0.0), confLevel(confLevel_)
{
}

void StatisticsSummary::DumpOneResult(double result)
{
    Payoffs.push_back(result);
}

vector<vector<double> > StatisticsSummary::GetResultsSoFar() const
{
    vector<vector<double> > Results(4);

	//increase size
    Results[0].resize(1);
    Results[0][0] = mean(Payoffs);
	
    Results[1].resize(1);
	Results[1][0] = stdDev(Payoffs);
	
    Results[2].resize(1);
	Results[2][0] = Results[1][0] / pow(Payoffs.size(), 0.5);
	
    double z;
    if (confLevel >= 0.5) {
        z = InverseCumulativeNormal(confLevel + (1 - confLevel) / 2);
    } else {
        z = InverseCumulativeNormal(1 - confLevel + confLevel / 2);
    };
    Results[3].resize(2);
	Results[3][0] = Results[0][0] - z * Results[2][0];
	Results[3][1] = Results[0][0] + z * Results[2][0];
    return Results;
}

StatisticsMC* StatisticsSummary::clone() const
{
    return new StatisticsSummary(*this);
}


void StatisticsSummary::reset(){
    Payoffs.clear();
}
