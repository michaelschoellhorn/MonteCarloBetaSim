#include "random_distribution.h"

using namespace std;

//utility functions
vector<double> linspace(double lower, double upper, int bins){
    double diff = (upper-lower)/double(bins);
    vector<double> x(bins+1);
    for (int i = 0; i < bins+1; i++){
        x[i] = lower + diff*i;
    }
    return x;
}


//distribution functions:
vector<double> mott(vector<double> v){
    vector<double> y(v.size());
    for (int i = 0; i!=v.size(); i++){
        y[i] = pow(cos(v[i]/2.0),2.0)/pow(sin(v[i]/2.0),4.0);
    }
    return y;
}


vector<double> moeller(vector<double> v){
    vector<double> y(v.size());
    for (int i = 0; i!=v.size(); i++){
        y[i] = pow(3.0+cos(v[i]),2.0)/pow(sin(v[i]),4.0);
    }
    return y;
}


vector<double> uniform(vector<double> v){
    vector<double> y(v.size());
    for (int i = 0; i!=v.size(); i++){
        y[i] = 1.0;
    }
    return y;
}


vector<double> expDecay(vector<double> v){
    vector<double> y(v.size());
    for (int i = 0; i!=v.size(); i++){
        y[i] = exp(-v[i]);
    }
    return y;
}


//RandomDistribution class definition
RandomDistribution::RandomDistribution(vector<double> (*dist_func)(vector<double>), double min, double max, int size)
    :generator(random_device()()), index(0), size(size) {
    //get P(y)
    x = linspace(min, max, 1000);
    vector<double> y = dist_func(x);
    distribution = discrete_distribution<int>(y.begin(), y.end()-1);

    index = 0;
    randomNumbers.reserve(size);
    for (int i = 0; i < size; ++i) {
        int randIndex = distribution(generator);
        randomNumbers.push_back(x[randIndex]);
    }
}


double RandomDistribution::get(){
    double out = randomNumbers.at(index);
    index++;
    if (size == index)
    {
        index = 0; //resetting index
        cout << "Generating new numbers" << endl;
        for (int i = 0; i < size; ++i) {
            int randIndex = distribution(generator);
            randomNumbers[i] = x[randIndex];
        }
    }
    return out;
}
