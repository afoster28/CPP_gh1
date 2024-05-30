// StatisticsSummary.h
#ifndef CONFLIMITS_H
#define CONFLIMITS_H

#include "MCStatistics.h"
#include<vector>

class StatisticsSummary : public StatisticsMC
{

public:

    StatisticsSummary(double confLevel_);
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double> > GetResultsSoFar() const;
    virtual StatisticsMC* clone() const;
    virtual void reset();

private:

    std::vector<double> Payoffs;
    double confLevel;

};

#endif
