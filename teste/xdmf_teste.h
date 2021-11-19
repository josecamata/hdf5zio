#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "HDF5Writer.h"
#include "HDF5Reader.h"
 
// The number of cells in the X, Y dimensions
#define NX 800
#define NY 700
void write_hdf5_data(CompressionType compression, char fileName[])
{
    // Create the coordinate data.
    float *x = (float *) malloc((NX+1)*(NY+1) * sizeof(float));
    float *y = (float *) malloc((NX+1)*(NY+1) * sizeof(float));
    int ndx = 0;
    for (int j = 0; j < NY+1; j++)
    {
        float yt = j*1.0 / NY;
        float angle = yt * M_PI;
        for (int i = 0; i < NX+1; i++)
        {
            float xt = i*1.0 / NX;
            float R = (1.-xt)*2. + xt*5.;
 
            x[ndx] = R * cos(angle);
            y[ndx] = R * sin(angle);
            ndx++;
        }
    }
 
    // Create the scalar data.
    float *pressure = (float *) malloc(NX*NY * sizeof(float));
 
    for (int j = 0; j < NY; j++)
    {
        for (int i = 0; i < NX; i++)
        {
            int ndx = j * NX + i;
            pressure[ndx] = (float) j;
        }
    }

    float *velocityx = (float *) malloc((NX+1)*(NY+1) * sizeof(float));
 
    for (int j = 0; j < NY+1; j++)
    {
        for (int i = 0; i < NX+1; i++)
        {
            int ndx = j * (NX+1) + i;
            velocityx[ndx] = (float) i;
        }
    }

    HDF5Writer w(fileName);
    w.setCompression(compression);
 
    // Write the data file.
 
    /* Write separate coordinate arrays for the x and y coordinates. */
    w.write(x, (NX + 1)*(NY + 1), "/X");
    w.write(y, (NX + 1)*(NY + 1), "/Y");
    
    // Write the scalar data.
    w.write(pressure, NY*NX, "/Pressure");
    w.write(velocityx, (NX + 1)*(NY + 1), "/VelocityX");

    w.close();

    // Free the data.
    free(x);
    free(y);
    free(pressure);
    free(velocityx);
}
 
void write_xdmf_xml()
{
    FILE *xmf = 0;
 
    /*
     * Open the file and write the XML description of the mesh..
     */
    xmf = fopen("xdmf2d.xmf", "w");
    fprintf(xmf, "<?xml version=\"1.0\" ?>\n");
    fprintf(xmf, "<!DOCTYPE Xdmf SYSTEM \"Xdmf.dtd\" []>\n");
    fprintf(xmf, "<Xdmf Version=\"2.0\">\n");
    fprintf(xmf, " <Domain>\n");
    fprintf(xmf, "   <Grid Name=\"mesh1\" GridType=\"Uniform\">\n");
    fprintf(xmf, "     <Topology TopologyType=\"2DSMesh\" NumberOfElements=\"%d %d\"/>\n", NY+1, NX+1);
    fprintf(xmf, "     <Geometry GeometryType=\"X_Y\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", (NY+1), (NX+1));
    fprintf(xmf, "        xdmf2d.h5:/X\n");
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", (NY+1), (NX+1));
    fprintf(xmf, "        xdmf2d.h5:/Y\n");
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Geometry>\n");
    fprintf(xmf, "     <Attribute Name=\"Pressure\" AttributeType=\"Scalar\" Center=\"Cell\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", NY, NX);
    fprintf(xmf, "        xdmf2d.h5:/Pressure\n");
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Attribute>\n");
    fprintf(xmf, "     <Attribute Name=\"VelocityX\" AttributeType=\"Scalar\" Center=\"Node\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", NY+1, NX+1);
    fprintf(xmf, "        xdmf2d.h5:/VelocityX\n");
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Attribute>\n");
    fprintf(xmf, "   </Grid>\n");
    fprintf(xmf, " </Domain>\n");
    fprintf(xmf, "</Xdmf>\n");
    fclose(xmf);
}
 
void testeXdmf()
{
    std::string temp;
    std::cout << "Defina a compressão:\n";
    std::cout << "(NOCOMPRESSION, SZIP, ZLIB)\n";
    std::cin >> temp;
    if (temp == "NOCOMPRESSION") {
        write_hdf5_data(NOCOMPRESSION, "xdmf2d.h5");
        write_xdmf_xml();
    } else if (temp == "SZIP") {
        write_hdf5_data(SZIP, "comSZIP.h5");    
    } else {
        write_hdf5_data(ZLIB, "comZLIB.h5");
    }
}