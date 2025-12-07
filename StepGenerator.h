#ifndef STEPGENERATOR_H
#define STEPGENERATOR_H


#include"TimeSeriesGenerator.h"

class StepGenerator : public TimeSeriesGenerator {
    private:
        
    public:
    StepGenerator();
    StepGenerator(int seed);
    vector<double> generateTimeSeries(int size) override;
};



#endif 