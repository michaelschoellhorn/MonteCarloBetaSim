#include "random_distribution.h"
#include "electron.h"
#include "simulation.h"
#include "globals.h"

int main()
{
    simulation sim(OUTPUT_PATH + "coordinates.txt", OUTPUT_PATH + "energyGrid.txt");
    sim.run();
}
