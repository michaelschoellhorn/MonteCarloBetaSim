#pragma once

#include <fstream>
#include "globals.h"
#include "random_distribution.h"
#include "electron.h"

class simulation
{
public:
    simulation(string coordFileName, string gridFileName);
    int nextcoord(electron *e1, electron *e2);
    void run();
    ofstream coordFile;
    ofstream gridFile;
    vector<electron *> electrons;              // List of electron pointers to keep track of all electrons
    electron *e1;                              // electron which trajectory is currently followed
    electron *e2;                              // target electron which may be produced and put in the list for later
    vector<vector<vector<double>>> energyGrid; // energy deposition grid, has DIM X_MAX/CELL_SIZE x Y_MAX/CELL_SIZE x Z_MAX/CELL_SIZE
};