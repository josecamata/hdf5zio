#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>

#include "HDF5Writer.h"
#include "HDF5Reader.h"

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
/*
    GetPot cl(argc, argv);
    if (cl.size() == 1 || cl.search("-h"))
    {
        std::cout<<"Usage: "<<argv[0]<<" -i <input> -o <output> "<<std::endl;
        return 0;
    }

    if (!cl.search("-i"))
    {
        std::cout<<"Usage: "<<argv[0]<<" -i <input> -o <output> "<<std::endl;
        return 0;
    }

    const std::string input = cl.next(std::string(""));

    if (!cl.search("-o"))
    {
        std::cout<<"Usage: "<<argv[0]<<" -i <input> -o <output> "<<std::endl;
        return 0;
    }

    const std::string output = cl.next(std::string(""));

    */


    std::ofstream log_file;

    // log_file.open(argv[4]);

    // std::cout<<argv[4]<<std::endl;

    std::clock_t c_start = std::clock();

    float* dataset = new float[500*500*100]; //std::cout<<"\n\n"<<argv[1]<<std::endl;

    read_hurricane_data(argv[1], dataset);

    std::clock_t c_end = std::clock();

    long time_elapsed_ms_read_to_dataset = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;

    std::string file_name(argv[3]);
    file_name = file_name.append(argv[2]);

    const char* fileName = file_name.c_str();

    c_start = std::clock();

    if(strcmp(argv[5], "0") == 0)
    {
        //std::cout<<"78"<<std::endl;
        HDF5Writer hdf_cloud(fileName);
        hdf_cloud.write(dataset, 500*500*100, "dataset_cloud");
    }
    else if(strcmp(argv[5], "1") == 0)
    {
        //std::cout<<"84"<<std::endl;
        HDF5Writer hdf_cloud(fileName);
        hdf_cloud.setCompression(SZIP); /* std::cout<<"---"<<std::endl; */
        hdf_cloud.write(dataset, 500*500*100, "dataset_cloud_szip");
    }
    else if(strcmp(argv[5], "2") == 0)
    {
        //if(dataset[i] != 0)
         //   std::cout<<dataset[i]<<std::endl;
        if(dataset[i] > M)
            M = dataset[i];
        if(dataset[i] < m)
            m = dataset[i];
    }
    c_end = std::clock();

    // std::cout<<argv[4]<<std::endl;

    HDF5Writer hdf_cloud(argv[2]);
    hdf_cloud.write(dataset, 500*500*100, "cloud");

    delete [] dataset;

    delete dataset;/* std::cout<<"106"<<std::endl; */

    // log_file<<"Read dataset:\n"; std::cout<<"111"<<std::endl;
    // log_file << "CPU time used: " << time_elapsed_ms_read_to_dataset << " ms\n";
    // log_file << "CPU time used: " << time_elapsed_ms_read_to_dataset / 1000.0 << " s\n";

    // log_file<<"Write dataset:\n";
    // log_file << "CPU time used: " << time_elapsed_ms_write_to_dataset << " ms\n";
    // log_file << "CPU time used: " << time_elapsed_ms_write_to_dataset / 1000.0 << " s\n";
    // std::cout<<"115"<<std::endl;
    return 0;
}

//     0              1                       2                               3                    4                    5
// ./hurricane [path para o raw] [nome de salvamento do arquivo] [path para salvar o arquivo] [arquivo de log] [tipo de compressao]