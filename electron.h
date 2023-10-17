#ifndef ELECTRON_H
#define ELECTRON_H

#include"random_distribution.h"
#include<fstream>



class electron{
public :
  electron(double x1, double y1, double z1, double E1 , double theta1, double phi1);
  ~electron();
  string getPos();
  double x;
  double y;
  double z;
  double E;
  double theta;
  double phi;
};


int nextcoord(electron *e1, electron *e2);


void elektron(void);


#endif