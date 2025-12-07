#ifndef KNN_H
#define KNN_H

#include <string>
#include "TimeSeriesDataset.h"


class KNN {
public:
    
    KNN(int k, const std::string& similarity_measure);

    
    int predict(const TimedSeriesDataset& trainSet,
                const TimedSeriesDataset& testSet,
                int testIndex) const;

    
    double evaluate(const TimedSeriesDataset& trainSet,
                    const TimedSeriesDataset& testSet) const;

private:
    int k;
    std::string similarity_measure;
};

#endif 