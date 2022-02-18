#include "teste/joao_teste.h"
#include "teste/xdmf_teste.h"
#include "teste/zfp_test.h"
#include "teste/zfp_test_prec.h"
#include "teste/config_file_test.h"
#include <GetPotGuard.hpp>


int main(int argc, char** argv){

    GetPot ifile("../config/config2.pot");

    int ct = ifile("compression_type", 0);

    int zfp_mode = 5;
    uint prec = 0;

    if (ct == 3) { // ZFP
        zfp_mode = ifile("zfp_mode", 5);

        if (zfp_mode == 2) { // zfp mode precision
            prec = ifile("zfp_precision", 5);
        }
    }

    // * Teste padrão de compressão 1:
    //testePadrao();

    // * Teste padrão de compressão 2 (com xdmf):
    //testeXdmf(ct, zfp_mode, prec);

    // * Teste padrão de compressão 3 (zfp):
    //zfp_test();

    // * Teste padrão de compressão 4 (zfp com precision 5)
    //zfp_test_prec();

    // * Teste padrão de compressão 5 (config file)
    config_file_test(ct, zfp_mode, prec);

    return 0;
}