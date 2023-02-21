#include <vector>
#include <utility>
#include "Parameters.hpp"

#ifndef COORDINATES_HPP
#define COORDINATES_HPP

using namespace std;

class Coordinates
{
public:
    Coordinates(Parameters& Parameters__):Parameters_(Parameters__){
        Initialize();
    }
    int lx_, ly_, size_;
    
    Parameters &Parameters_;

    void Initialize();
    pair<int, vector<int>> Neighbours(int cell);

};


#endif
