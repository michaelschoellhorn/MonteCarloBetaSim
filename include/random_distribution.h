#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

vector<double> linspace(double lower, double upper, int bins);

vector<double> mott(vector<double> v);

vector<double> moeller(vector<double> v);

vector<double> uniform(vector<double> v);

vector<double> expDecay(vector<double> v);

class RandomDistribution
{
private:
    vector<double> randomNumbers;
    int index;
    int size;
    default_random_engine generator;
    discrete_distribution<int> distribution;
    vector<double> x;

public:
    RandomDistribution(vector<double> (*dist_func)(vector<double>), double min, double max, int size);
    double get();
};