#include <vector>

#include "Parameters.hpp"
#include "Coordinates.hpp"
#include "Hamiltonian.hpp"

void Hamiltonian::Initialize(){
    lx_ = Parameters_.Lx;
    ly_ = Parameters_.Ly;
    size_=Parameters_.Total_Cells;
}

double Hamiltonian::Calculate_Energy(){
    
}