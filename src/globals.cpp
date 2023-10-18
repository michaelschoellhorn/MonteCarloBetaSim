#include "globals.h"


// constants
const double pi = M_PI;   // pi
const double me = 0.511;         // electron mass [MeV]

const int N_ELEC = 1;           // number of electrons
const double X_MAX = 100;        // x-size of the detector
const double Y_MAX = 100;        // y-size of the detector
const double E_0 = 20;           // energy of electrons
const double E_MIN = 0.02;       // minimum energy of electrons


//init random number generators
RandomDistribution rnMeanFreePath(*expDecay, 0.0, 10.0, 1024); //mean free path
RandomDistribution rnPhi(*uniform, 0.0, 2*M_PI, 1024);         //azimutal angle phi
RandomDistribution rnMoeller(*moeller, 0.2, M_PI_2, 1024);     //moeller theta in c.m.
RandomDistribution rnMott(*mott, 0.2, M_PI, 1024);             //mott theta in c.m.
RandomDistribution rnRatio(*uniform, 0.0, 1.0, 2048);          //Ratio [0, 1) to decide between moeller and mott