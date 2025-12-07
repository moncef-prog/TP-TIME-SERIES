#include "KNN.h"

#include <vector>
#include <algorithm>   
#include <map>        
#include <stdexcept>   
#include <cctype>      
#include <cmath>       


static std::string toLower(const std::string& s) {
    std::string r = s;
    for (char& c : r) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return r;
}

KNN::KNN(int k, const std::string& similarity_measure)
    : k(k), similarity_measure(toLower(similarity_measure))
{
    if (k <= 0) {
        throw std::invalid_argument("KNN: k doit etre > 0");
    }

    
    if (this->similarity_measure != "euclidian" &&
        this->similarity_measure != "euclidean" &&
        this->similarity_measure != "dtw") {
        throw std::invalid_argument("KNN: mesure de similarite inconnue (utiliser 'euclidian' ou 'dtw')");
    }
}

int KNN::predict(const TimedSeriesDataset& trainSet,
                 const TimedSeriesDataset& testSet,
                 int testIndex) const
{
    int nTrain = trainSet.getNumberOfSamples();
    int nTest  = testSet.getNumberOfSamples();

    if (nTrain == 0) {
        throw std::runtime_error("KNN::predict: dataset d'entrainement vide");
    }
    if (testIndex < 0 || testIndex >= nTest) {
        throw std::out_of_range("KNN::predict: index d'echantillon de test invalide");
    }

    int Ltrain = trainSet.getMaxLength();
    int Ltest  = testSet.getMaxLength();

    if (Ltrain != Ltest) {
        throw std::runtime_error("KNN::predict: train et test n'ont pas la meme longueur de serie");
    }

    int seriesLength = Ltrain;

    
    const std::vector<double>& trainData  = trainSet.getData();
    const std::vector<int>&    trainLabel = trainSet.getLabels();
    const std::vector<double>& testData   = testSet.getData();

    
    int startTest = testIndex * seriesLength;
    std::vector<double> seqTest(
        testData.begin() + startTest,
        testData.begin() + startTest + seriesLength
    );

    
    std::vector<std::pair<double, int>> distances;
    distances.reserve(nTrain);

    for (int i = 0; i < nTrain; ++i) {
        int startTrain = i * seriesLength;
        std::vector<double> seqTrain(
            trainData.begin() + startTrain,
            trainData.begin() + startTrain + seriesLength
        );

        double d = 0.0;
        if (similarity_measure == "euclidian" || similarity_measure == "euclidean") {
            d = euclidian_distance(seqTrain, seqTest);
        } else if (similarity_measure == "dtw") {
            d = dtw_distance(seqTrain, seqTest);
        }

        distances.push_back(std::make_pair(d, i));
    }

    
    std::sort(distances.begin(), distances.end(),
              [](const std::pair<double,int>& a, const std::pair<double,int>& b) {
                  return a.first < b.first;
              });

  
    int effectiveK = k;
    if (effectiveK > nTrain) {
        effectiveK = nTrain;
    }

    
    std::map<int, int> votes; 
    for (int i = 0; i < effectiveK; ++i) {
        int idxNeighbor = distances[i].second;
        int label = trainLabel[idxNeighbor];
        votes[label]++;
    }

    
    int bestLabel = -1;
    int bestCount = -1;
    for (const auto& p : votes) {
        if (p.second > bestCount) {
            bestCount = p.second;
            bestLabel = p.first;
        }
    }

    return bestLabel;
}

double KNN::evaluate(const TimedSeriesDataset& trainSet,
                     const TimedSeriesDataset& testSet) const
{
    int nTest = testSet.getNumberOfSamples();
    if (nTest == 0) {
        throw std::runtime_error("KNN::evaluate: dataset de test vide");
    }

    const std::vector<int>& testLabels = testSet.getLabels();

    int correct = 0;

    
    for (int i = 0; i < nTest; ++i) {
        int predicted = predict(trainSet, testSet, i);
        int trueLabel = testLabels[i];

        if (predicted == trueLabel) {
            ++correct;
        }
    }

    
    return static_cast<double>(correct) /
           static_cast<double>(nTest);
}