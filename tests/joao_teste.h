#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <string.h>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "Sorting.h"
#include "HDF5Writer.h"
// #include "HDF5Reader.h"

using namespace std;

void generation(int* vect, int size){
    int r;

    for(int i = 0; i < size; i++){
        r = -0.25 + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(800-(-0.25))));
        vect[i] = r;
    }
}

void testePadrao(){

//     string OBS = "Tempo total = tempo de escrita + tempo de fechamento, não considerando, assim, o tempo de ordenação do database";
//     string FILETITLE = "C_Ordenacao_Inteiro.txt";
//     string TITLE = "Compressão com Tipo Inteiro com ordenação";
//     string path = "/home/joaovictor/Documents/Repositories/GETEngComp/hdf5zio/Results/";
//     path.append(FILETITLE);
//     fstream FILE;
//     FILE.open(path, ios::out);

    char name0[] = "testNC.h5";
    char name1[] = "testSZIP.h5";
    char name2[] = "testZLIB.h5";
    int size = 1000;

    //int *database = new int[size];
    unique_ptr<int> database(new int[size]);

    generation(database.get(), size);

    heapSort(database.get(), size);

/**************************************************************/

    // FILE<<TITLE<<endl;
    // FILE<<endl;

    // FILE<<"Tamanho do database: "<<size<<endl;
    // FILE<<endl;
/**************************************************************/

    HDF5Writer myFile0(name0);
    myFile0.setCompression(NOCOMPRESSION);

    // auto start = std::chrono::steady_clock::now();

    myFile0.write(database.get(), size, "Compression Test");

    myFile0.close();

    //auto end = std::chrono::steady_clock::now();

    // std::chrono::duration<float> elapsed_seconds = end-start;
    // FILE<<"NC: " << elapsed_seconds.count()<<" segundos" <<endl;
    // FILE<<endl;

/*************************************************************/

    HDF5Writer myFile1(name1);
    myFile1.setCompression(SZIP);

    // start = std::chrono::steady_clock::now();

    myFile1.write(database.get(), size, "Compression Test");

    myFile1.close();

    // end = std::chrono::steady_clock::now();

    // elapsed_seconds = end-start;
    // FILE<<"SZIP: " << elapsed_seconds.count()<<" segundos" <<endl;
    // FILE<<endl;

/**************************************************************/

    HDF5Writer myFile2(name2);
    myFile2.setCompression(ZLIB);

    // start = std::chrono::steady_clock::now();

    myFile2.write(database.get(), size, "Compression Test");

    myFile2.close();

    // end = std::chrono::steady_clock::now();

    // elapsed_seconds = end-start;
    // FILE<<"ZLIB: " << elapsed_seconds.count() <<" segundos"<<endl;
    // FILE<<endl;

// /***************************************************************/

//     cout<<endl;
//     delete[] database;



//     FILE<<OBS<<endl;

//     FILE.close();

//     cout<<"Finished"<<endl;
}
