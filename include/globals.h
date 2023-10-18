#pragma once

#include<cmath>
#include"random_distribution.h"



// constants
extern const double pi;   // pi
extern const double me;         // electron mass [MeV]

extern const int N_ELEC;           // number of electrons
extern const double X_MAX;        // x-size of the detector
extern const double Y_MAX;        // y-size of the detector
extern const double E_0;           // energy of electrons
extern const double E_MIN;       // minimum energy of electrons


//init random number generators
extern RandomDistribution rnMeanFreePath; //mean free path
extern RandomDistribution rnPhi;         //azimutal angle phi
extern RandomDistribution rnMoeller;     //moeller theta in c.m.
extern RandomDistribution rnMott;             //mott theta in c.m.
extern RandomDistribution rnRatio;          //Ratio [0, 1) to decide between moeller and mott
