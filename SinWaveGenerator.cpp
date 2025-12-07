#include"TimeSeriesGenerator.h"
#include"SinWaveGenerator.h"


SinWaveGenerator::SinWaveGenerator(){}
SinWaveGenerator::SinWaveGenerator(int seed) : TimeSeriesGenerator(seed){}
SinWaveGenerator::SinWaveGenerator(int seed,double amplitude,double frequence,double phase_initiale) : TimeSeriesGenerator(seed)
{
    this->amplitude = amplitude;
    this->frequence = frequence;
    this->phase_initiale = phase_initiale;
}


vector<double> SinWaveGenerator::generateTimeSeries(int size){
    vector<double> series;
    series.resize(size);
    
    if (size == 0) return series;

    for (int i=0 ; i< size ; i++){
        series[i] = amplitude * sin(frequence * double(rand() % 100) + phase_initiale );
    }
    
    return series;
}