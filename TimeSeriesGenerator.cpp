#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>



#include"TimeSeriesGenerator.h"
using namespace std;

TimeSeriesGenerator::TimeSeriesGenerator() {}

TimeSeriesGenerator::TimeSeriesGenerator(int seed) {
    this->seed = seed;
}
vector<double> TimeSeriesGenerator::generateTimeSeries(int size){
    vector<double> series;
    series.resize(size);
    
    for (int i = 0; i < size; i++){
        series[i] = rand() % 100;
    }
    
    return series;
}

void TimeSeriesGenerator::PrintTimeSeries(const vector<double>& v){
    for (int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

int TimeSeriesGenerator::getSeed(){
        return this->seed;
}


