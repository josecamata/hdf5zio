#ifndef FB2EB310_95D2_4818_A9AB_461498963E17
#define FB2EB310_95D2_4818_A9AB_461498963E17

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

void generation(int* vect, int size){
    int r;

    for(int i = 0; i < size; i++){
        r = -0.25 + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(800-(-0.25))));
        vect[i] = r;
    }
}


void testCOrdenacaoInteiro(int number, int dataBase, int size){
    string num = std::to_string(number); //Transforma o número em string

}

void createDir(string name){
    string dir = "/home/joaovictor/Documents/Testes_Diretorio/";

    dir.append(name);

    mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void autoTestAux(){

}

void autoTest(int qtd){
    string name1 = "InteiroS_Compressao";
    string name2 = "InteiroC_Compressao";
    string name3 = "DoubleS_Compressao";
    string name4 = "DoubleC_Compressao";
    string name5 = "FloatS_Compressao";
    string name6 = "FloatC_Compressao";

    for(int i = 0; i < qtd; i++){
        string number = std::to_string(i);
        
    }



}

#endif /* FB2EB310_95D2_4818_A9AB_461498963E17 */
