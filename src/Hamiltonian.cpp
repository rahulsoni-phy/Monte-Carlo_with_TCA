#include <math.h>
#include <cstdlib> //to call rand or srand
#include <ctime> //to call time
#include <vector>


#include "Parameters.hpp"
#include "Coordinates.hpp"
#include "Hamiltonian.hpp"

#define PI acos(-1.0)

void Hamiltonian::Initialize(){
    Spin_ = Parameters_.Spin_mag; 
    size_ = Parameters_.Total_Cells;

    srand (static_cast <unsigned> (time(0))); //"seed" the random number generator

    float r1,r2,r3;

    r1 = static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX) ); //generate a random number from 0.0 to 1.0
    r2 = static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX) );
    r3 = static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX) );


    Stot_.resize(3);
    for(int i=0;i<3;i++){
        Stot_[i].resize(size_);
    }

    Theta_.resize(size_);
    Phi_.resize(size_);

    for(int cell=0;cell<size_;cell++){

        Phi_[cell] = ((60.0*r1))*2.0*PI/60.0;
        Theta_[cell] = acos((30.0*r2)/(30.0));

        if(r3>0.5){
            Theta_[cell] = PI - Theta_[cell];
        }

        Stot_[0][cell] = Spin_*sin(Theta_[cell])*cos(Phi_[cell]);
        Stot_[1][cell] = Spin_*sin(Theta_[cell])*sin(Phi_[cell]);
        Stot_[2][cell] = Spin_*cos(Theta_[cell]);

    }
}


double Hamiltonian::Calculate_Energy(vector<vector<double>> stot_, vector<double> theta_, vector<double> phi_){
    
    double E_HUND,E_B;
    double E_Total;
    E_Total=0.0;

    int neigh_index;

    for(int cell=0;cell<size_;cell++){

        auto result = Coordinates_.Neighbours(cell);

        for(int neigh=0;neigh<result.second.size();neigh++){
            neigh_index = result.second[neigh];
        }

    }


    //Eng_JH = JH * ( sx[i]*(sx[j1] + sx[j2] + sx[j3] + sx[j4])
      //                      +   sy[i]*(sy[j1] + sy[j2] + sy[j3] + sy[j4])
        //                    +   sz[i]*(sz[j1] + sz[j2] + sz[j3] + sz[j4]) )
          //      Eng_B = -B * sz[i]
            //    E_old = Eng_JH + Eng_B
}