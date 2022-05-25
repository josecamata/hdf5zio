#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>

#include <unistd.h>


#include "HDF5Writer.h"
#include "HDF5Reader.h"

void print_menu(const char* prog)
{
    std::cout<<"Usage: "<<prog<<" [OPTIONS] "<<std::endl;
    std::cout<<"Options:"<<std::endl;
    std::cout<<"   -i [filename]  : Input file name"<<std::endl;
    std::cout<<"   -o [filename]  : Output file name"<<std::endl;
    std::cout<<"   -l [filename]  : log file name"<<std::endl;
}


void read_hurricane_data(const char* file_path, float* dataset)
{
    int nx = 500;
    int ny = 500;
    int nz = 100;

    std::ifstream archive;

    archive.open(file_path, std::ios::binary);

    if(!archive.good())
    {
        std::cout<<"FAIL"<<std::endl;
        return;
    }
    int cont = 0;
    while(archive.read((char*)&dataset[cont], sizeof(float)))
    {
        cont++;
    }

    archive.close();

    // std::cout<<std::boolalpha<<(cont == ny*nx*nz)<<std::endl;

}

int main(int argc, char* argv[])
{


    const int size = 500*500*100;
    char c; 
    char *inputfile;
    char *outputfile;
    char  *logfile;
    
    if(argc == 1)
    {
        print_menu(argv[0]);
        return 0;
    }

    while( (c = getopt(argc, argv, "i:o:l:")) != -1)
    {
        switch(c)
        {
            case 'i':
                inputfile = optarg;
                break;
            case 'o':
                outputfile = optarg;
                break;
            case 'l':
                logfile = optarg;
                break;
            default:
                print_menu(argv[0]);
                return 0;
        }
    }
    

    std::ofstream log;

    log.open(logfile);
        
    float* dataset = new float[size]; 

    std::clock_t c_start = std::clock();
    read_hurricane_data(inputfile, dataset);
    std::clock_t c_end = std::clock();

    long time_elapsed_ms_read_to_dataset = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;


    c_start = std::clock();
    HDF5Writer hdf_cloud(outputfile);
    hdf_cloud.write(dataset, size, "dataset_cloud");
    c_end = std::clock();

    long time_elapsed_ms_write_to_dataset = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;

    log <<"Read dataset:\n"; 
    log << "CPU time used: " << time_elapsed_ms_read_to_dataset << " ms\n";
    log << "CPU time used: " << time_elapsed_ms_read_to_dataset / 1000.0 << " s\n";

    log <<"Write dataset:\n";
    log << "CPU time used: " << time_elapsed_ms_write_to_dataset << " ms\n";
    log << "CPU time used: " << time_elapsed_ms_write_to_dataset / 1000.0 << " s\n";
    log.close();
    
    delete [] dataset;

    return 0;
}

//     0              1                       2                               3                    4                    5
// ./hurricane [path para o raw] [nome de salvamento do arquivo] [path para salvar o arquivo] [arquivo de log] [tipo de compressao]