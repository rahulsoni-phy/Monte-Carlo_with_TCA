#include <vector>
#include <utility>
#include "Parameters.hpp"
#include "Coordinates.hpp"

#ifndef HAMILTONIAN_HPP
#define HAMILTONIAN_HPP

using namespace std;

class Hamiltonian
{
public:
    Hamiltonian(Parameters& Parameters__, Coordinates& Coordinates__):Parameters_(Parameters__), Coordinates_(Coordinates__){
        Initialize();
    }
    int lx_, ly_, size_;
    
    Parameters &Parameters_;
    Coordinates &Coordinates_;

    void Initialize();
    double Calculate_Energy();

};


#endif