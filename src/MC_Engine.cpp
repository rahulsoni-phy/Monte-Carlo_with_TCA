#include <math.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include "Parameters.hpp"
#include "Coordinates.hpp"
#include "Hamiltonian.hpp"
#include "MC_Engine.hpp"

void MC_Engine::Initialize(){
    Neq_ = Parameters_.N_Eq;
    Nav_ = Parameters_.N_Avg;
    size_ = Parameters_.Total_Cells;

    Stot_old.resize(size_); Stot_save.resize(size_);
    for(int cell=0;cell<size_;cell++){
        Stot_old[cell].resize(size_);
        Stot_save[cell].resize(size_);
        for(int i=0;i<3;i++){
            Stot_old[cell][i] = 0.0;
            Stot_save[cell][i] = 0.0;
        }
    }

    vector<double> s_vec;

    for(int cell=0;cell<size_;cell++){
        s_vec = Hamiltonian_.Random_Spin_Config(cell);
        for(int i=0;i<3;i++){
            Stot_old[cell][i] = s_vec[i];
        }
    }
    
}

void MC_Engine::MC_engine(){
    vector<double> Temp_val, s_vec;
    double temp;
    double Avg_E,Avg_Mag_Total;
    double Avg_MagX,Avg_MagY,Avg_MagZ;
    double E_old,E_new,E_diff;
    double prob;
    float seed;

    for(int temp_ind=0;temp_ind<Temp_val.size();temp_ind++){
        temp = Temp_val[temp_ind];

        Avg_E = 0.0; Avg_MagX = 0.0; Avg_MagY = 0.0; Avg_MagZ = 0.0; Avg_Mag_Total = 0.0;

        for(int iters=0;iters<(Neq_+Nav_);iters++){
            for(int cell=0;cell<size_;cell++){

                E_old = Hamiltonian_.Calculate_Energy(Stot_old); //Getting the energy from the older spin configuration

                s_vec = Hamiltonian_.Random_Spin_Config(cell); //Making a random change in spin configuration of a single site
                for(int i=0;i<3;i++){
                    Stot_save[cell][i] = Stot_old[cell][i];
                    Stot_old[cell][i] = s_vec[i];
                }

                E_new = Hamiltonian_.Calculate_Energy(Stot_old); //Getting the energy from this newer spin configuration

                E_diff = E_new - E_old; //Calculating the difference in both old and new energy

                if(abs(E_diff/temp) < 8.0){
                    prob = exp(-1.0*(E_diff/temp));
                }
                else prob =0.0;

                srand (static_cast <unsigned> (time(0)));
                seed = static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX) );;
                
                if(E_diff <= 0.0){
                    Stot_save = Stot_new;
                }
                else {
                    if(prob > seed){
                        Stot_save = Stot_new;
                    }
                    else Stot_save = Stot_old;
                }

            }
        }
    }
}