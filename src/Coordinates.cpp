#include <cstdio>
#include <vector>
#include <utility>

#include "Parameters.hpp"
#include "Coordinates.hpp"

pair<int, vector<int>> Coordinates::Neighbours(int cell){
    lx_ = Parameters_.Lx;
    ly_ = Parameters_.Ly;
    size_=Parameters_.Total_Cells;

    int rx, ry;
    rx = cell%lx_;
    ry = cell/lx_;

    if(cell>size_-1){
        std::perror("Cell number cannot exceed total number of cells.");
    }

    vector<int> neighs;
    int no_of_neighs;

    neighs.clear();

    //Getting the neighbors of a "cell" based on the provided boundary conditions
    if(Parameters_.PBC_X==true){
        neighs.push_back((rx + lx_ - 1)%lx_ + lx_*ry);  //Minus-X neighbor (Right neighbor)
        neighs.push_back((rx + 1)%lx_ + lx_*ry);        //Plus-X neighbor (Left neighbor)
    }
    else if(Parameters_.PBC_X==false){
        if(rx!=0){
            neighs.push_back((rx + lx_ - 1)%lx_ + lx_*ry);
        }
        if(rx!=lx_-1){
            neighs.push_back((rx + 1)%lx_ + lx_*ry);
        }
    }

    if(Parameters_.PBC_Y==true){
        neighs.push_back(rx + ((ry + ly_ - 1)%ly_)*lx_); //Minus-Y neighbor (Bottom neighbor)
        neighs.push_back(rx + ((ry + 1)%ly_)*lx_);       //Plus-Y neighbor (Top neighbor)
    }
    else if(Parameters_.PBC_Y==false){
        if(ry!=0){
            neighs.push_back(rx + ((ry + ly_ - 1)%ly_)*lx_);
        }
        if(ry!=ly_-1){
            neighs.push_back(rx + ((ry + 1)%ly_)*lx_);
        }
    }

    no_of_neighs=neighs.size();

    if(no_of_neighs>4){
        std::perror("Each site can have a maximum of 4 neighbors. Check 'Neighbours' in Coordinates.cpp!");
    }

    return make_pair(no_of_neighs,neighs);
    
}