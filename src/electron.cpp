//This class describes the scattering of electrons in matter
#include"electron.h"

using namespace std;


electron::electron(double x1, double y1, double z1, double E1 , double theta1, double phi1) {
  x=x1;
  y=y1;
  z=z1; 
  E=E1; 
  theta=theta1; 
  phi=phi1;}


electron::~electron(){}
