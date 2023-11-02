#pragma once

#include <cmath>
#include "random_distribution.h"

// System constants
extern const string OUTPUT_PATH;

// Physical constants
extern const double pi; // pi
extern const double me; // electron mass [MeV]

// Simulation constants
extern const int N_ELEC;   // number of electrons
extern const double X_MAX; // x-size of the detector
extern const double Y_MAX; // y-size of the detector
extern const double E_0;   // energy of electrons
extern const double E_MIN; // minimum energy of electrons

// Init random number generators
extern RandomDistribution rnMeanFreePath; // mean free path 1E-16 as minimal evaluation value to prevent division through zero errors
extern RandomDistribution rnRatio;        // Ratio [0, 1) to decide between moeller and mott
extern RandomDistribution rnPhi;          // azimutal angle phi
// The cross sections aren't evaluated for theta<0.2 since this is the most common case and is already considered in the slowing down approximation
extern RandomDistribution rnMoeller; // moeller theta in c.m.
extern RandomDistribution rnMott;    // mott theta in c.m.
