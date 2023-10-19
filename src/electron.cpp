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

/*
string electron::getPos(){
  return to_string(x)+", "+to_string(y)+", "+to_string(z)+"\n";
}
*/

int nextcoord(electron *e1, electron *e2) 
{
//log position
    //logfile << e1->getPos() << endl;
// Keep starting position of struck electron e2

    e2->x = e1->x;
    e2->y = e1->y;
    e2->z = e1->z;
    double otheta = e1->theta;  // old theta
    double ophi   = e1->phi;    // old phi
    double p1;
    double p2;
    double theta1;
    double theta2;

// calculate new coordinates
    double n_phi = rnPhi.get(); 
    double len= rnMeanFreePath.get()*pow(e1->E/1.0, 2.0)/50; // scattering length (scales with 1/E^2)
    
    double p = sqrt(pow(e1->E+me,2)-me*me);    // Momentum of e1 in target system
    double gamma;       // Gamma factor  
// transform angles into target system
// calculate new momenta and energies 
    double n_theta;
    if (rnRatio.get()<0.5) { // mott scattering
      n_theta = rnMott.get();
      theta1 = n_theta;
      p1 = p;
      p2 = 0;    
    }
    else {//moeller scattering
      n_theta = rnMoeller.get();
      gamma = (e1->E+2*me)/sqrt(2*me*(2*me+e1->E));
      theta1 = atan2(sin(n_theta),gamma*(cos(n_theta)+1));
      theta2 = atan2(sin(n_theta),gamma*(1-cos(n_theta)));
      p1 = 2*me*(e1->E+2*me)*p*cos(theta1)/(pow((e1->E+2*me),2)-pow(p*cos(theta1),2));
      p2 = 2*me*(e1->E+2*me)*p*cos(theta2)/(pow((e1->E+2*me),2)-pow(p*cos(theta2),2));
    }
    
    e1->E = (sqrt(p1*p1+me*me)-me)-0.5*len/e1->E;
    e2->E = (sqrt(p2*p2+me*me)-me);
    if (e2->E > 0.02) {
      e2->E = e2->E-0.5*len/e2->E;
    }
    else {
      e2->E = 0;
    }

// stop if no energy left
    if (e1->E <= E_MIN) {return 0;}
  
// transform into cartesian coordinates (x',y',z') 

    double xn = len * cos(n_phi)*sin(theta1);
    double yn = len * sin(n_phi)*sin(theta1);
    double zn = len * cos(theta1);
    
// Rotation of e1 relative to  previous direction of e1 

    double dx =  xn * cos(ophi)*cos(otheta) - yn * sin(ophi)+ zn* cos(ophi)*sin(otheta);
    double dy =  xn * sin(ophi)*cos(otheta) + yn * cos(ophi)+ zn* sin(ophi)*sin(otheta);
    double dz = -xn * sin(otheta)                           + zn* cos(otheta);
    
// New position and direction of e1

    e1->x += dx;
    e1->y += dy;
    e1->z += dz;
    e1->theta = acos(dz/len);
    e1->phi = atan2(dy,dx);

// Transformation of e2 relative to  previous direction of e1 

    if (p2 > 0) {
      xn = -len * cos(n_phi)*sin(theta2);
      yn = -len * sin(n_phi)*sin(theta2);
      zn =  len * cos(theta2);
      
      dx =  xn * cos(ophi)*cos(otheta) - yn * sin(ophi)+ zn* cos(ophi)*sin(otheta);
      dy =  xn * sin(ophi)*cos(otheta) + yn * cos(ophi)+ zn* sin(ophi)*sin(otheta);
      dz = -xn * sin(otheta)                           + zn* cos(otheta);

// Direction of e2

      e2->theta = acos(dz/len);
      e2->phi   = atan2(dy,dx);
    }

// stop if electron leaves detector
    if ((e1->x < 0) || (e1->x>X_MAX)) {cout << "detector left at x:" << e1->x << endl; return 0;} 
    if ((e1->y < 0) || (e1->y>Y_MAX)) {cout << "detector left at y:" << e1->y << endl; return 0;}

  // return value 1 means success
    return 1;
}

void elektron(void)
{
    //logfile.open("log.csv");
    vector<electron *> electrons;    // List of electron objects (see root User's guide)
    electron* e1;       // first electron (whose trajectory is followed)
    electron* e2;       // second electron (which is just produced and traced afterwards)

    // The cross section cannot be integrated to 0 degrees, 
    // a too small starting angle will never produce
    // branches, therefore 0.2 rad is a good compromise
    
  for (int n = 0; n < N_ELEC; n++) {
	  // loop for electrons
	  cout << "electron #" << n << endl;
	  electrons.push_back(new electron(50, 50 ,0 ,E_0, 0, 0));  // push new electron on stack
	  while (!electrons.empty()) {
	    e1 = electrons.back();              // pop next starting point from stack
	    electrons.pop_back();                           // remove it from the stack  
	    while (1) {
		    e2 = new electron(0, 0 ,0 ,0 , 0, 0);
		    int ret=nextcoord(e1, e2);
		    if (ret == 0) break;
		    if (e2->E > E_MIN) electrons.push_back(e2);     // put secondary electron on the stack
	    }  // end while
    }                                                                 
  }  // end for
  //logfile.close();
}
