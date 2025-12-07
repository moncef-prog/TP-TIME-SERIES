#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <ctime>
#include <random>

#include"GaussianGenerator.h"
using namespace std;


GaussianGenerator::GaussianGenerator(){}
GaussianGenerator::GaussianGenerator(int seed) : TimeSeriesGenerator(seed){}
GaussianGenerator::GaussianGenerator(int seed, double moyenne, double ecart_type) : TimeSeriesGenerator(seed)
{
    this->moyenne = moyenne;
    this->ecart_type = ecart_type;
}

vector<double> GaussianGenerator::generateTimeSeries(int size){
    vector<double> series;
    series.resize(size);
    
    default_random_engine generator(seed);
    normal_distribution<double> distribution(moyenne, ecart_type);
    
    for (int i = 0; i < size; i++){
        series[i] = distribution(generator);
    }
    
    return series;
}