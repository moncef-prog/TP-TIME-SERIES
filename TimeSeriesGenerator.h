#ifndef TIMESERIESGENERATOR_H
#define TIMESERIESGENERATOR_H

#include <vector>
using namespace std;

class TimeSeriesGenerator{
    protected: 
     int seed;


    public:
        TimeSeriesGenerator();

        TimeSeriesGenerator(int seed);

        vector<double> virtual generateTimeSeries(int);

        void PrintTimeSeries(const vector<double>& v);
        int getSeed();
};







#endif