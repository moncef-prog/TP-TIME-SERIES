#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include"TimeSeriesDataset.h"



using namespace std;

TimedSeriesDataset::TimedSeriesDataset(){}
TimedSeriesDataset::TimedSeriesDataset(bool znormalize,
        bool isTrain,
        vector<double> data,
        vector<int> labels,
        int maxLength,
        int numberOfSamples)
  {
        this->isTrain= isTrain;
        this->data = data;
        this->labels = labels;
        this->maxLength= maxLength;
        this->numberOfSamples = numberOfSamples; 
  }           
        
void TimedSeriesDataset::znormalization(){
    
    if(this->znormalize == false){
        return;
    }

    
    for (int s = 0; s < numberOfSamples; s++) {
        int start = s * maxLength;
        int end   = start + maxLength;
        double sum = 0.0;
        for (int i = start; i < end; i++){
            sum += data[i];
        }
        double mean = sum / maxLength;
        double var = 0.0;
        for (int i = start; i < end; i++){
            var += (data[i] - mean) * (data[i] - mean);
        }
            
        double std = sqrt(var / maxLength);
        if (std == 0) std = 1e-8;
        for (int i = start; i < end; i++)
            data[i] = (data[i] - mean) / std;
    }

}

double TimedSeriesDataset::euclidian_distance(const vector<double>& a, const vector<double>& b) {
    if (a.size() != b.size()) {
        throw invalid_argument("euclidian_distance: les vecteurs n'ont pas la même taille");
    }

    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        double diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}


double TimedSeriesDataset::dtw_distance(const vector<double>& a, const vector<double>& b) {
    const size_t n = a.size();
    const size_t m = b.size();

    if (n == 0 || m == 0) {
        throw invalid_argument("dtw_distance: une des series est vide");
    }

    const double INF = numeric_limits<double>::infinity();


    vector<double> prev(m + 1, INF);
    vector<double> curr(m + 1, INF);

    prev[0] = 0.0; // 
    for (size_t i = 1; i <= n; ++i) {
        curr[0] = INF; 

        for (size_t j = 1; j <= m; ++j) {
            double cost = fabs(a[i - 1] - b[j - 1]);

            
            double m1 = prev[j];     
            double m2 = curr[j - 1];
            double m3 = prev[j - 1]; 
            double bestPrev = min(min(m1, m2), m3);

            curr[j] = cost + bestPrev;
        }

        prev.swap(curr);
        fill(curr.begin(), curr.end(), INF);
    }

    return prev[m];
}