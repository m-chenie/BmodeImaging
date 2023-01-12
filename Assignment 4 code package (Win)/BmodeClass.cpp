#include "BmodeClass.h"
#include<iostream>

using namespace std;

BmodeClass::BmodeClass()
{
    imparams = NULL;
    RFData = NULL;
    next = NULL;
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
    imparams = params; 
    RFData = data;
    line = numline;
    scanline = createScanline(imparams->getNumPixel()); // create scanline array
    beamform();
    
}

BmodeClass::~BmodeClass()
{
    deleteScanline();
}

float *BmodeClass::createScanline(int numPixel)
{
    // allocating memory for scanline array
    float *mem;
    mem = new float[numPixel];

    return mem;
}

void BmodeClass::beamform()
{
    float Preal = 0;
    float Pimag = 0;
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        Preal= 0;
        Pimag= 0;
        float tForward = imparams->getYPosition(line,i) / imparams->SOS; // calculate tForward

        for (int j = 0; j < imparams->getNumElement(); j++)
        {
            // calculate tBackward, tTotal and s
            float tBackward = sqrt(pow(imparams->getYPosition(line, i), 2) + pow(imparams->getXPosition(line,i) - imparams->getElementPosition(j), 2)) / imparams->SOS;
            float tTotal = tForward + tBackward;
            int s = floor(tTotal*imparams->FS); 
            // if the index s, is within range of numSample, then sum Preal and Pimag
            if (s < imparams->getNumSample()) {
                
                Preal += RFData->getRealRFData(j, s); 
                Pimag += RFData->getImagRFData(j, s);
            }
        }
       
        scanline[i] = sqrt(pow(Preal,2) + pow(Pimag,2)); // populate scanline array
       
    }
    
}

void BmodeClass::getScanline(float *data)
{
    // copying scanline into data
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        data[i] = scanline[i];
    }
    
}

void BmodeClass::deleteScanline()
{  
    delete[] scanline; // deleting scanline array
}