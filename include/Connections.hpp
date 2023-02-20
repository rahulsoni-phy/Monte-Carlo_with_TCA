#include <vector>
#include "Parameters.hpp"

#ifndef Connections_HPP
#define Connections_HPP

using namespace std;

class Connections
{
public:
    Connections(Parameters& Parameters__):Parameters_(Parameters__){
        Initialize();
    }
    int lx_, ly_, size_;
    vector<vector<pair<int, int>>> neighs;
    //double J_, B_, Spin_;

    Parameters &Parameters_;

    void Initialize();
    void Neighbours(int cell);

};


#endif
