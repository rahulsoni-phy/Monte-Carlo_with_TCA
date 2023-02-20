
#include "Parameters.hpp"
#include "Connections.hpp"

void Connections::Initialize(){
    lx_ = Parameters_.Lx;
    ly_ = Parameters_.Ly;

    neighs.clear();

}

void Connections::Neighbours(int cell){

    int rx, ry;
    rx = cell%lx_;
    ry = cell/lx_;

    //Getting the neighbors of a "cell"
    if(Parameters_.PBC_X==true){
        neighs[cell].push_back(make_pair( (rx+1)%lx_ , ry)); //Plus-X neighbor (Right neighbor)
        neighs[cell].push_back(make_pair( (rx+lx_-1)%lx_, ry)); //Minus-X neighbor (Left neighbor)
    }
    if(Parameters_.PBC_X=false){
        if(rx!=lx_-1){
            neighs[cell].push_back(make_pair(rx+1, ry)); //Plus-X neighbor (Right neighbor)
        }
        if(rx!=0){
            neighs[cell].push_back(make_pair(rx-1, ry)); //Minus-X neighbor (Left neighbor)
        }
    }

    if(Parameters_.PBC_Y==true){
        neighs[cell].push_back(make_pair(rx, (ry+1)%ly_ )); //Plus-Y neighbor (Top neighbor)
        neighs[cell].push_back(make_pair(rx, (ry+ly_-1)%ly_ )); //Minus-Y neighbor (Bottom neighbor)
    }
    if(Parameters_.PBC_Y==false){
        if(ry!=ly_-1){
            neighs[cell].push_back(make_pair(rx, ry+1)); //Plus-Y neighbor (Top neighbor)
        }
        if(ry!=0){
            neighs[cell].push_back(make_pair(rx, ry-1)); //Minus-Y neighbor (Bottom neighbor)
        }
    }

}