#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "HDF5Writer.h"
#include "HDF5Reader.h"

// Número de células nas dimensões X e Y
#define NX 800
#define NY 700
void writeHdf5Data(CompressionType compression, char fileName[])
{
    // Create the coordinate data.
    float *x = (float *)malloc((NX + 1) * (NY + 1) * sizeof(float));
    float *y = (float *)malloc((NX + 1) * (NY + 1) * sizeof(float));
    int ndx = 0;
    for (int j = 0; j < NY + 1; j++)
    {
        float yt = j * 1.0 / NY;
        float angle = yt * M_PI;
        for (int i = 0; i < NX + 1; i++)
        {
            float xt = i * 1.0 / NX;
            float R = (1. - xt) * 2. + xt * 5.;

            x[ndx] = R * cos(angle);
            y[ndx] = R * sin(angle);
            ndx++;
        }
    }

    // Create the scalar data.
    float *pressure = (float *)malloc(NX * NY * sizeof(float));

    for (int j = 0; j < NY; j++)
    {
        for (int i = 0; i < NX; i++)
        {
            int ndx = j * NX + i;
            pressure[ndx] = (float)j;
        }
    }

    float *velocityx = (float *)malloc((NX + 1) * (NY + 1) * sizeof(float));

    for (int j = 0; j < NY + 1; j++)
    {
        for (int i = 0; i < NX + 1; i++)
        {
            int ndx = j * (NX + 1) + i;
            velocityx[ndx] = (float)i;
        }
    }

    HDF5Writer w(fileName);
    w.setCompression(compression);

    // Write the data file.

    /* Write separate coordinate arrays for the x and y coordinates. */
    w.write(x, (NX + 1) * (NY + 1), "/X");
    w.write(y, (NX + 1) * (NY + 1), "/Y");

    // Write the scalar data.
    w.write(pressure, NY * NX, "/Pressure");
    w.write(velocityx, (NX + 1) * (NY + 1), "/VelocityX");

    w.close();

    // Free the data.
    free(x);
    free(y);
    free(pressure);
    free(velocityx);
}

void writeXdmfXml(char xmfFileName[], char h5FileName[])
{
    FILE *xmf = 0;
    xmf = fopen(xmfFileName, "w");

    fprintf(xmf, "<?xml version=\"1.0\" ?>\n");
    fprintf(xmf, "<!DOCTYPE Xdmf SYSTEM \"Xdmf.dtd\" []>\n");
    fprintf(xmf, "<Xdmf Version=\"2.0\">\n");
    fprintf(xmf, " <Domain>\n");
    fprintf(xmf, "   <Grid Name=\"mesh1\" GridType=\"Uniform\">\n");
    fprintf(xmf, "     <Topology TopologyType=\"2DSMesh\" NumberOfElements=\"%d %d\"/>\n", NY + 1, NX + 1);
    fprintf(xmf, "     <Geometry GeometryType=\"X_Y\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", (NY + 1), (NX + 1));
    fprintf(xmf, "        %s:/X\n", h5FileName);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", (NY + 1), (NX + 1));
    fprintf(xmf, "        %s:/Y\n", h5FileName);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Geometry>\n");
    fprintf(xmf, "     <Attribute Name=\"Pressure\" AttributeType=\"Scalar\" Center=\"Cell\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", NY, NX);
    fprintf(xmf, "        %s:/Pressure\n", h5FileName);
    fprintf(xmf, "       </DataItem>\n");
    fprintf(xmf, "     </Attribute>\n");
    fprintf(xmf, "     <Attribute Name=\"VelocityX\" AttributeType=\"Scalar\" Center=\"Node\">\n");
    fprintf(xmf, "       <DataItem Dimensions=\"%d %d\" NumberType=\"Float\" Precision=\"4\" Format=\"HDF\">\n", NY + 1, NX + 1);
    fprintf(xmf, "        %s:/VelocityX\n", h5FileName);
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
        writeHdf5Data(NOCOMPRESSION, "xdmf2d.h5");
        writeXdmfXml("xdmf2d.xmf", "xdmf2d.h5");
    }
    else if (temp == "SZIP") {
        writeHdf5Data(SZIP, "comSZIP.h5");
        writeXdmfXml("comSZIP.xmf", "comSZIP.h5");
    }
    else {
        writeHdf5Data(ZLIB, "comZLIB.h5");
        writeXdmfXml("comZLIB.xmf", "comZLIB.h5");
    }
}