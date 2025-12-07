#include "StepGenerator.h"
#include <random>
using namespace std;
#include"TimeSeriesGenerator.h"
StepGenerator::StepGenerator() : TimeSeriesGenerator() {}

StepGenerator::StepGenerator(int seed) : TimeSeriesGenerator(seed) {}

vector<double> StepGenerator::generateTimeSeries(int size) {
    vector<double> series;
    series.resize(size);
    
    if (size == 0) return series;

    series[0] = 0;
    
    default_random_engine generator(seed);
    uniform_int_distribution<int> valueDist(0, 100);
    uniform_real_distribution<double> probDist(0.0, 1.0);
    
    for (int i = 1; i < size; i++) {
        double prob = probDist(generator);
        
        if (prob < 0.5) {
            series[i] = valueDist(generator);
        } else {
            series[i] = series[i - 1];
        }
    }
    
    return series;
}