#include <vector>
#include <utility>

#include "Parameters.hpp"
#include "Coordinates.hpp"

void Coordinates::Initialize(){
    lx_ = Parameters_.Lx;
    ly_ = Parameters_.Ly;
}

pair<int, vector<int>> Coordinates::Neighbours(int cell){

    int rx, ry;
    rx = cell%lx_;
    ry = cell/lx_;

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

    return make_pair(no_of_neighs,neighs);
    
}