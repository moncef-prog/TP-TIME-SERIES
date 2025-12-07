#ifndef GAUSSIANGENERATOR_H
#define GAUSSIANGENERATOR_H

#include "TimeSeriesGenerator.h" 

class GaussianGenerator : public TimeSeriesGenerator{
    private:
        int moyenne;
        int ecart_type;

    public:
        GaussianGenerator();
        GaussianGenerator(int seed);
        GaussianGenerator(int seed, double moyenne, double ecart_type);

        vector<double> generateTimeSeries(int) override;


};






#endif 