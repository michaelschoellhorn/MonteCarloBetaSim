# MonteCarloBetaSim
MonteCarlo simulation of an electron beam hitting solid matter. Physical features include moeller-, mott-scattering and the continuous slowing down approximation for modelling energy loss in cases with deflection under theta = 0.2 rad. The simulation can be used to model electrons with kinetic energy between ionisation energy and pair formation energy.

## Visualization
There are three different scripts for visualizing the paths of the electrons and the deposited energy in the medium. All plotting scripts need a working pathon3 installation aswell as the numpy and matplotlib packages to function properly.
For the visualization of the taken paths, one can run plot.py in the visualization directory after running the simulation. The paths of the electrons are color coded with their energy value.
plotgrid.py and plotheat.py both produce plots for the energy deposition. The first produces a 3D scatter plot, the second one a heatmap.
