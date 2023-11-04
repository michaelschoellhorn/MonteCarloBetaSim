#include "globals.h"

// System constants
extern const string OUTPUT_PATH = "../../visualization/";

// Physical constants
const double pi = M_PI;  // pi
const double me = 0.511; // electron mass [MeV]

// Simulation constants
const int N_ELEC = 400;     // number of electrons
const double X_MAX = 100;  // x-size of the detector
const double Y_MAX = 100;  // y-size of the detector
const double E_0 = 30;     // energy of electrons
const double E_MIN = 0.02; // minimum energy of electrons

// Init random number generators
RandomDistribution rnMeanFreePath(*expDecay, 1E-16, 10.0, 1024); // mean free path 1E-16 as minimal evaluation value to prevent division through zero errors
RandomDistribution rnRatio(*uniform, 0.0, 1.0, 2048);            // Ratio [0, 1) to decide between moeller and mott
RandomDistribution rnPhi(*uniform, 0.0, 2 * M_PI, 1024);         // azimutal angle phi
// The cross sections aren't evaluated for theta<0.2 since this is the most common case and is already considered in the slowing down approximation
RandomDistribution rnMoeller(*moeller, 0.2, M_PI_2, 1024); // moeller theta in c.m.
RandomDistribution rnMott(*mott, 0.2, M_PI, 1024);         // mott theta in c.m.
