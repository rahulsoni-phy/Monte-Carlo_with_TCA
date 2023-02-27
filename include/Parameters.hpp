#include<string>

#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

using namespace std;

class Parameters{

    public:

    int Lx, Ly, N_Orbs;
    double J_val, B_mag;
    double Spin_mag;
    int Total_Cells, Total_Sites;
    string Temp_file;

    int N_Eq, N_Avg;

    bool PBC_X, PBC_Y;

    void Initialize(string input_file);
    double matchstring(string file, string match);
    string matchstring2(string file, string match);

};


#endif