#include <vector>
#include "Parameters.hpp"
#include "Coordinates.hpp"
#include "Hamiltonian.hpp"

#ifndef MC_ENGINE_HPP
#define MC_ENGINE_HPP

using namespace std;

class MC_Engine
{
public:
    MC_Engine(Parameters& Parameters__, Coordinates& Coordinates__, Hamiltonian& Hamiltonian__):
    Parameters_(Parameters__), Coordinates_(Coordinates__), Hamiltonian_(Hamiltonian__){
        Initialize();
    }

    int Neq_, Nav_, size_;
    vector<vector<double>> Stot_old, Stot_new, Stot_save;

    Parameters &Parameters_;
    Coordinates &Coordinates_;
    Hamiltonian &Hamiltonian_;

    void Initialize();
    void MC_engine();
    vector<double> Temperature_Reading(string file_temp_in);


};


#endif