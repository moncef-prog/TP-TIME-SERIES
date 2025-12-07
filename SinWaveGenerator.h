#ifndef SINWAVEGENERATOR_H
#define SINWAVEGENERATOR_H


#include"TimeSeriesGenerator.h"

class SinWaveGenerator : public TimeSeriesGenerator {
    private:
        double amplitude;
        double frequence;
        double phase_initiale;
        
    public:
    SinWaveGenerator();
    SinWaveGenerator(int seed);
    SinWaveGenerator(int seed,double amplitude,double frequence,double phase_initiale);

    vector<double> generateTimeSeries(int) override;
};



#endif 