#ifndef TIMESERIESDATASET_H
#define TIMESERIESDATASET_H


using namespace std;
#include<vector>
class TimedSeriesDataset{
    private:
        bool znormalize;
        bool isTrain;
        vector<double> data;
        vector<int> labels;
        int maxLength;
        int numberOfSamples;

    public:
        TimedSeriesDataset();
        TimedSeriesDataset(bool znormalize,
        bool isTrain,
        vector<double> data,
        vector<int> labels,
        int maxLength,
        int numberOfSamples);

        void znormalization();
        double euclidian_distance(const std::vector<double>& a, const std::vector<double>& b);
        double dtw_distance(int sampleIdx1, int sampleIdx2) const;

        const std::vector<double>& getData() const { return data; }
        const std::vector<int>& getLabels() const { return labels; }
};



#endif