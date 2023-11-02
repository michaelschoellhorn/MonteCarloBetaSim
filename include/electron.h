#pragma once

#include"globals.h"
#include"random_distribution.h"
#include<fstream>



class electron{
  public :
    electron(double x1, double y1, double z1, double E1 , double theta1, double phi1);
    ~electron();
    //string getPos();
    double x;
    double y;
    double z;
    double E;
    double theta;
    double phi;
};

class simulation{
  public:
    simulation(string outputFileName);
    int nextcoord(electron *e1, electron *e2);
    void run();
    ofstream outputFile;
    vector<electron *> electrons;      // List of electron pointers to keep track of all electrons
    electron* e1;                      // electron which trajectory is currently followed
    electron* e2;                      // target electron which may be produced and put in the list for later
};