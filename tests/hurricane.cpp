#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>


#include "HDF5Writer.h"
#include "HDF5Reader.h"

#include "GetPotGuard.hpp"




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
    // Ler os 48 arquivos QCLOUD no formanto bin
    // Salvar no formato HDF5  (sem compressão, SZIP, ZLIP, ZFP)
    // Gerar XDMF (HDF5+ZLIB) para visualizar no ParaView. 
    //* Teste padrão de compressão 1:

    // Montar uma tabela de comparação:
    // Metodo  |  Tamanho original |  Tamanho Comprimido | Taxa de Compressão
    // sem  
    // ZLIB
    // SZIP
    // ZFP (lossless)
    // ZFP (precisão) 

    const int size = 500*500*100;

    GetPot cl(argc, argv);
    if (cl.size() == 1 || cl.search("-h"))
    {
        std::cout<<"Usage: "<<argv[0]<<" -i <input> -o <output> -l <log_file> "<<std::endl;
        return 0;
    }

    if (!cl.search("-i"))
    {
        std::cout<<"Usage: "<<argv[0]<<" -i <input> -o <output> "<<std::endl;
        return 0;
    }

    std::string input = cl.next(std::string(""));

    if (!cl.search("-o"))
    {
        std::cout<<"Usage: "<<argv[0]<<" -i <input> -o <output> "<<std::endl;
        return 0;
    }

    std::string output = cl.next("");

    if (!cl.search("-l"))
    {
        std::cout<<"Usage: "<<argv[0]<<" -i <input> -o <output> "<<std::endl;
        return 0;
    }

    std::string logfile = cl.next("");

    

    std::ofstream log;

    log.open(logfile);
        
    float* dataset = new float[size]; 

    std::clock_t c_start = std::clock();
    read_hurricane_data(input.c_str(), dataset);
    std::clock_t c_end = std::clock();

    long time_elapsed_ms_read_to_dataset = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;


    c_start = std::clock();
    HDF5Writer hdf_cloud(output.c_str());
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