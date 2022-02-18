#include "teste/joao_teste.h"
#include "teste/xdmf_teste.h"
#include "teste/zfp_test.h"
#include "teste/zfp_test_prec.h"
#include "teste/config_file_test.h"

int main(int argc, char** argv){

    // * Teste padrão de compressão 1:
    //testePadrao();

    // * Teste padrão de compressão 2 (com xdmf):
    //testeXdmf();

    // * Teste padrão de compressão 3 (zfp):
    //zfp_test();

    // * Teste padrão de compressão 4 (zfp com precision 5)
    //zfp_test_prec();

    // * Teste padrão de compressão 5 (config file)
    config_file_test();

    return 0;
}