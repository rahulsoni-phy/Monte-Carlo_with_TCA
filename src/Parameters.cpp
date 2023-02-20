#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Parameters.hpp"

using namespace std;

void Parameters::Initialize(string input_file){
    string PBC_X_string,PBC_Y_string,SBC_X_string;
    string pbc_x_out, pbc_y_out, sbc_x_out;

    cout<<"-------------------------------------------"<<endl;
    cout<<"Reading the input file = "<<input_file<<endl;
    cout<<"-------------------------------------------"<<endl;

    PBC_X_string=matchstring2(input_file,"PBC_X");
    if(PBC_X_string=="True"){
        PBC_X=true;
        pbc_x_out="PBC";
    }
    else{
        PBC_X=false;
        pbc_x_out="OBC";
    }
    
    PBC_Y_string=matchstring2(input_file,"PBC_Y");
    if(PBC_Y_string=="True"){
        PBC_Y=true;
        pbc_y_out="PBC";
    }
    else{
        PBC_Y=false;
        pbc_y_out="OBC";
    }

    Lx = int(matchstring(input_file, "Cells_X"));
    Ly = int(matchstring(input_file, "Cells_Y"));
    N_Orbs = int(matchstring(input_file, "No_of_orbitals"));

    Total_Cells = Lx*Ly;
    Total_Sites = N_Orbs*Total_Cells;

    J_val = matchstring(input_file, "Coupling_Constant_J");
    B_mag = matchstring(input_file, "Magnetic_Field_B");

    Spin_mag = matchstring(input_file, "Spin_Magnitude");

    N_Eq = int(matchstring(input_file, "No_of_Equilibriation"));
    N_Avg = int(matchstring(input_file, "No_of_Averaging"));

    cout<<"Total number of unit cells = "<<Total_Cells<<endl;
    cout<<"Boundary conditions along-x = "<<pbc_x_out<<endl;
    cout<<"Boundary conditions along-y = "<<pbc_y_out<<endl;
    cout<<" "<<endl;
    
    cout<<"Ferromagnetic Coupling Constant = "<<J_val<<endl;
    cout<<"Magnitude of the External Field = "<<B_mag<<endl;
    cout<<"Magnitude of the Spin = "<<Spin_mag<<endl;
    cout<<" "<<endl;

    cout<<"Number of Equilibriation = "<<N_Eq<<endl;
    cout<<"Number of Averaging = "<<N_Avg<<endl;

    Temp_min = matchstring(input_file, "Min_Temperature");
    Temp_max = matchstring(input_file, "Max_Temperature");
    
    cout<<"-------------------------------------------"<<endl;
    cout<<"Finished reading the input file"<<endl;
    cout<<"-------------------------------------------"<<endl;

}


double Parameters::matchstring(string file, string match){

        string test;
        string line;
        ifstream inputfile(file);
        double amount;

        bool pass=false;

        while(getline(inputfile,line)){
                istringstream iss(line);

                if(getline(iss,test,'=') && pass == false){
                        if(iss >> amount && test == match){
                                pass = true;
                        }
                        else{pass == false;}
                        if(pass)
                                break;
                }
        }

        if(pass == false){
                string errorout = match;
                errorout += "= the argument is missing in the input file!";
                throw std::invalid_argument(errorout);
        }
   //     cout<< match <<" = "<< amount <<endl;
        return amount;
}


string Parameters::matchstring2(string file, string match){
        string line;
        ifstream inputfile(file);
        string amount;
        int offset;

        if(inputfile.is_open()){
                while(!inputfile.eof()){

                        getline(inputfile, line);

                        /* Referenced from https://cplusplus.com/forum/beginner/121556/ 
                         * https://stackoverflow.com/questions/12463750/ */

                        if((offset = line.find(match,0)) != string::npos){
                                amount = line.substr(offset + match.length() + 1);
                        }

                }
                inputfile.close();
        }
        else{cout << "Unable to open input file while in the Parameter class." << endl;}

        cout << match << " = " << amount << endl;
        return amount;
}
