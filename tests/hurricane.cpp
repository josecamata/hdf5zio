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

        if(std::isnan(dataset[cont]))
        {
            dataset[cont] = 0.0f;
            //lsstd::cout<<"NAN"<<std::endl;
        }
        else{
            if(dataset[cont] < 0.0f || dataset[cont] > 1.0f)
            {
                dataset[cont] = 0.0f;
            }
        }
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
    char  *begin_range;
    char *end_range;
    int  setup_begin = 0;
    
    if(argc == 1)
    {
        print_menu(argv[0]);
        return 0;
    }

    while( (c = getopt(argc, argv, "i:o:l:be")) != -1)
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
            case 'b':
                begin_range = optarg;
                setup_begin = 1;
                break;
            case 'e':
                end_range = optarg;
                break;
            default:
                print_menu(argv[0]);
                return 0;
        }
    }
    

    std::ofstream log;

    log.open(logfile);
        
    float begin = -MAXFLOAT;
    if(setup_begin)
    {
        begin = atof(begin_range);
    }
    float end = MAXFLOAT;
    if(end_range)
    {
        end = atof(end_range);
    }

    float* dataset = new float[size]; 

    std::clock_t c_start = std::clock();
    read_hurricane_data(inputfile, dataset);
    std::clock_t c_end = std::clock();


    long time_elapsed_ms_read_to_dataset = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;


    c_start = std::clock();
    HDF5Writer hdf_cloud(outputfile);
    hdf_cloud.write(dataset, size, "dataset_cloud");
    c_end = std::clock();

    HDF5Reader hdf_cloudreader(outputfile);
    float* database = new float[size];
    hdf_cloudreader.read(database, size, "dataset_cloud");

    long time_elapsed_ms_write_to_dataset = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;

    log << "COMPRESSION: " << hdf_cloud.getCompression() << "\n";
    log << "Difference (after compression - before compression): \n";
    log << "Size: " << size << "\n";
    log << "\n-------------------------------------\n\n";
    log << "DATASET DIFFERENCE\n";
    float diff = 0;
    double diff_avg = 0;
    double avg = 0;
    for (size_t i = 0; i < size; i++) {
        diff = database[i] - dataset[i];
        if (!std::isnan(dataset[i])) {
            avg      += dataset[i];
            diff_avg += fabs(diff);
        }
    }
    diff_avg = diff_avg / (float) size;
    avg = avg / size;
    
    double variance = 0;
    for (size_t i = 0; i < size; i++) {
        if (!std::isnan(dataset[i])) {
            variance += (dataset[i] - avg)*(dataset[i] - avg);
        } 
    }
    variance = variance / size;
    
    log << "Diff Average: " << diff_avg << "\n";
    log << "Average: " << avg << "\n";
    log << "Variance: " << variance << "\n";
    log << "Deviation: " << avg << " +- " << sqrt(variance) << "\n";
    log << "\n-------------------------------------\n";

    log <<"Read dataset:\n"; 
    log << "CPU time used: " << time_elapsed_ms_read_to_dataset << " ms\n";
    log << "CPU time used: " << time_elapsed_ms_read_to_dataset / 1000.0 << " s\n";

    log <<"Write dataset:\n";
    log << "CPU time used: " << time_elapsed_ms_write_to_dataset << " ms\n";
    log << "CPU time used: " << time_elapsed_ms_write_to_dataset / 1000.0 << " s\n";
    log.close();
    
    delete [] dataset;
    delete [] database;

    return 0;
}

//     0              1                       2                               3                    4                    5
// ./hurricane [path para o raw] [nome de salvamento do arquivo] [path para salvar o arquivo] [arquivo de log] [tipo de compressao]