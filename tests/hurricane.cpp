#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

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

    std::cout<<std::boolalpha<<(cont == ny*nx*nz)<<std::endl;

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


    float m = +INFINITY;
    float M = -INFINITY;

    float* dataset = new float[500*500*100];
    
    read_hurricane_data(argv[1], dataset);

    for (size_t i = 0; i < 500*500*100; i++)
    {
        //if(dataset[i] != 0)
         //   std::cout<<dataset[i]<<std::endl;
        if(dataset[i] > M)
            M = dataset[i];
        if(dataset[i] < m)
            m = dataset[i];
    }

    HDF5Writer hdf_cloud(argv[2]);
    hdf_cloud.write(dataset, 500*500*100, "cloud");

    delete [] dataset;

    std::cout<<"\n\nM = "<<M<<std::endl;
    std::cout<<"m = "<<m<<std::endl;

    return 0;
}
