#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

class Parameters{

    public:

    int Lx, Ly, N_Orbs;
    double J_val, B_mag;
    double Spin_mag;
    int Total_Cells, Total_Sites;
    double Temp_min, Temp_max;

    int N_Eq, N_Avg;

    bool PBC_X, PBC_Y;

    void Initialize(std::string input_file);
    double matchstring(std::string file, std::string match);
    std::string matchstring2(std::string file, std::string match);

};


#endif