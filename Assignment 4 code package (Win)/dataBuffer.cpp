#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    numElement = 0; 
    numSample = 0;
    scanline = 0;
    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;

    dataMatrix = createDataMatrix(); // creating dataMatrix
    loadRFData(dataMatrix, imagFile, realFile); // call function to load data from files and populate dataMatrix
} 

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // call to function that deletes dataMatrix
}

complex **dataBuffer::createDataMatrix()
{
    // allocate memory for RFData
    complex **RFData;
    RFData = new complex*[numElement];
    for (int i = 0; i < numElement; i++)
    {
        RFData[i] = new complex[numSample];
    }

    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    // populate RFData
    for (int i = 0; i < numElement; i++)
    {
        for (int j = 0; j < numSample; j++)
        {
            char imag[20];
            char real[20];
            imagFile->getline(imag, 20); // getting data from imageFile
            realFile->getline(real, 20); // getting data from realFile
            RFData[i][j].imag = atof(imag); // populating imag part
            RFData[i][j].real = atof(real); // populating real part
        }
        
    }
    return 0;
}

float dataBuffer::getRealRFData(int element,int sample)
{
    return dataMatrix[element][sample].real; 
}
float dataBuffer::getImagRFData(int element,int sample)
{
    return dataMatrix[element][sample].imag;
}

void dataBuffer::deleteDataMatrix()
{
    // deleting dataMatrix
    for (int i = 0; i < numElement; i++)
    {
        delete[] dataMatrix[i];
    }

    delete[] dataMatrix;
}




