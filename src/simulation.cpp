#include "simulation.h"

simulation::simulation(string coordFileName, string gridFileName)
{
    coordFile = ofstream(coordFileName); // open streams to files
    gridFile = ofstream(gridFileName);
    energyGrid = vector<vector<vector<double>>>(int(X_MAX / CELL_SIZE), vector<vector<double>>(int(Y_MAX / CELL_SIZE), vector<double>((int)Z_MAX / CELL_SIZE)));
}

int simulation::nextcoord(electron *e1, electron *e2)
{

    // Keep starting position for struck electron e2
    e2->x = e1->x;
    e2->y = e1->y;
    e2->z = e1->z;
    double energy = e1->E;
    double otheta = e1->theta; // old theta needed for transformation
    double ophi = e1->phi;     // old phi
    double p1;
    double p2;
    double theta1;
    double theta2;

    // get random phi and pathlenght
    double n_phi = rnPhi.get();
    double len = rnMeanFreePath.get() * pow(e1->E / 1.0, 2.0) / 50; // scattering length (scales with 1/E^2)

    // get momentum of e1 in target system
    double p = sqrt(pow(e1->E + me, 2) - me * me);
    double gamma; // Gamma factor
    double n_theta;

    // get new momenta and thetas from Mott or moeller scattering
    if (rnRatio.get() < 0.5) // mott scattering
    {
        n_theta = rnMott.get();
        theta1 = n_theta;
        p1 = p;
        p2 = 0;
    }
    else // moeller scattering
    {
        n_theta = rnMoeller.get();
        gamma = (e1->E + 2 * me) / sqrt(2 * me * (2 * me + e1->E));
        theta1 = atan2(sin(n_theta), gamma * (cos(n_theta) + 1));
        theta2 = atan2(sin(n_theta), gamma * (1 - cos(n_theta)));
        p1 = 2 * me * (e1->E + 2 * me) * p * cos(theta1) / (pow((e1->E + 2 * me), 2) - pow(p * cos(theta1), 2));
        p2 = 2 * me * (e1->E + 2 * me) * p * cos(theta2) / (pow((e1->E + 2 * me), 2) - pow(p * cos(theta2), 2));
    }

    // set new energies
    e1->E = (sqrt(p1 * p1 + me * me) - me) - 0.5 * len / e1->E;
    e2->E = (sqrt(p2 * p2 + me * me) - me);
    if (e2->E > 0.02)
    {
        e2->E = e2->E - 0.5 * len / e2->E;
    }
    else
    {
        e2->E = 0;
    }

    // stop if no energy left
    if (e1->E <= E_MIN)
    {
        return 0;
    }

    // Transform target angles into cartesian coordinates (x',y',z')
    double xn = len * cos(n_phi) * sin(theta1);
    double yn = len * sin(n_phi) * sin(theta1);
    double zn = len * cos(theta1);

    // Rotation of cartesian target system to previous direction of e1
    double dx = xn * cos(ophi) * cos(otheta) - yn * sin(ophi) + zn * cos(ophi) * sin(otheta);
    double dy = xn * sin(ophi) * cos(otheta) + yn * cos(ophi) + zn * sin(ophi) * sin(otheta);
    double dz = -xn * sin(otheta) + zn * cos(otheta);

    // New position and direction of e1
    e1->x += dx;
    e1->y += dy;
    e1->z += dz;
    e1->theta = acos(dz / len);
    e1->phi = atan2(dy, dx);

    // Transform target angles into cartesian coordinates for e2 and rotate
    if (p2 > 0)
    {
        xn = -len * cos(n_phi) * sin(theta2);
        yn = -len * sin(n_phi) * sin(theta2);
        zn = len * cos(theta2);

        dx = xn * cos(ophi) * cos(otheta) - yn * sin(ophi) + zn * cos(ophi) * sin(otheta);
        dy = xn * sin(ophi) * cos(otheta) + yn * cos(ophi) + zn * sin(ophi) * sin(otheta);
        dz = -xn * sin(otheta) + zn * cos(otheta);

        // Get direction of e2
        e2->theta = acos(dz / len);
        e2->phi = atan2(dy, dx);
    }

    // Stop if electron leaves detector
    if ((e1->x < 0) || (e1->x > X_MAX))
    {
        cout << "detector left at x:" << e1->x << endl;
        return 0;
    } // no data logging in this case!
    if ((e1->y < 0) || (e1->y > Y_MAX))
    {
        cout << "detector left at y:" << e1->y << endl;
        return 0;
    }
    if ((e1->z < 0) || (e1->z > Z_MAX))
    {
        cout << "detector left at z:" << e1->z << endl;
        return 0;
    }

    // Log position data
    coordFile << e1->x << " " << e1->y << " " << e1->z << " " << e1->E << "\n";
    if (e1->z < Z_MAX)
    {
        energyGrid[(int)e1->x / CELL_SIZE][(int)e1->y / CELL_SIZE][(int)e1->z / CELL_SIZE] += energy - e1->E - e2->E;
    }
    // return value 1 means success
    return 1;
}

void simulation::run()
{
    if (coordFile.is_open())
    {
        cout << "coordinate file successfully opened!" << endl;
        // loop over electrons to be traced
        for (int n = 0; n < N_ELEC; n++)
        {
            cout << "electron #" << n << endl;
            electrons.push_back(new electron(50.0, 50.0, 0.0, E_0, 0.0, 0.0)); // put a new electron on the stack
            while (!electrons.empty())                                         // loop over current traced electron and all secondaries
            {
                e1 = electrons.back();                                                      // get next electron from stack/list
                electrons.pop_back();                                                       // remove it from the stack/list
                coordFile << e1->x << " " << e1->y << " " << e1->z << " " << e1->E << "\n"; // log initial position and energy
                while (1)
                {
                    e2 = new electron(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
                    int ret = nextcoord(e1, e2); // propagate electron
                    if (ret == 0)
                    {
                        coordFile << endl; // to flush buffer and
                        break;             // break if electron left detector or E_electron<E_min
                    }
                    if (e2->E > E_MIN)
                        electrons.push_back(e2); // put secondary electron in list
                }
            }
        }
        coordFile.close();
        if (gridFile.is_open())
        {
            cout << "energy file successfully opened!";
            for (int i = 0; i != (int)X_MAX / CELL_SIZE; i++)
            {
                for (int j = 0; j != (int)Y_MAX / CELL_SIZE; j++)
                {
                    for (int k = 0; k != (int)Z_MAX / CELL_SIZE; k++)
                    {
                        gridFile << energyGrid[i][j][k] << " ";
                    }
                    gridFile << endl;
                }
            }
            gridFile.close();
        }
        else
        {
            cout << "energyGrid file can't be opened!" << endl;
        }
    }
    else
    {
        cout << "coordinate file can't be opened!" << endl;
    }
}
