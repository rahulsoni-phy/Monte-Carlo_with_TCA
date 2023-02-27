#include <math.h>
#include <cstdlib> //to call rand or srand
#include <ctime> //to call time
#include <vector>


#include "Parameters.hpp"
#include "Coordinates.hpp"
#include "Hamiltonian.hpp"

#define PI acos(-1.0)

void Hamiltonian::Initialize(){
    spin_ = Parameters_.Spin_mag; 
    size_ = Parameters_.Total_Cells;
}

vector<double> Hamiltonian::Random_Spin_Config(int cell){

    vector<double> stot_;

    stot_.resize(3);
    srand (static_cast <unsigned> (time(0))); //"seed" the random number generator

    float r1,r2,r3;
    r1 = static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX) ); //generate a random number from 0.0 to 1.0
    r2 = static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX) );
    r3 = static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX) );

    double phi_,theta_;

    phi_ = ((60.0*r1))*2.0*PI/60.0;
    theta_ = acos((30.0*r2)/(30.0));
    if(r3>0.5){
        theta_ = PI - theta_;
    }

    stot_[0] = spin_*sin(theta_)*cos(phi_);
    stot_[1] = spin_*sin(theta_)*sin(phi_);
    stot_[2] = spin_*cos(theta_);

    return stot_;
}


double Hamiltonian::Calculate_Energy(vector<vector<double>> stot_){
    
    double E_HUND,E_B,E_Total;
    E_HUND=0.0; E_B=0.0;

    int neigh_index;

    for(int cell=0;cell<size_;cell++){
        E_B += -Parameters_.B_mag*stot_[cell][2];

        auto neigh_pair = Coordinates_.Neighbours(cell);

        for(int neigh=0;neigh<neigh_pair.second.size();neigh++){
            neigh_index = neigh_pair.second[neigh];

            E_HUND += Parameters_.J_val*(stot_[cell][0]*stot_[neigh_index][0] 
                    + stot_[cell][1]*stot_[neigh_index][1] + stot_[cell][2]*stot_[neigh_index][2]);
        }
    }

    E_Total = E_B + E_HUND;

    return E_Total;
}