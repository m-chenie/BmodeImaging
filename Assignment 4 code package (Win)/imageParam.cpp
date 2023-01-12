#include "imageParam.h"

using namespace std;

imageParam::imageParam()
{
    numElement = 128;
    numSample = 3338;
    numScanline = 127;
    elementPosition = genElementPosition(); // creating elementPosition array
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition); // creating scanlinePosition array
}

imageParam::~imageParam()
{
    deletePositionArray();
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
    // create/allocate memory for elementPosition
    float *elementPosition = new float[numElement];
    // populating elementPosition
    for (int n = 0; n < numElement; n++)
    {
        elementPosition[n] = (n - ((numElement-1.0)/2.0)) * PITCH;
    }
    return elementPosition;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
    // getting input from user
    cout << "Enter imaging depth: ";
    cin >> desiredDepth;
    cout << "Enter number of pixels: ";
    cin >> numPixel;

    float2 **scanlinePosition = new float2*[numScanline]; // allocate memory for scanlinePosition
    float diff = desiredDepth/(numPixel-1); // calculate difference between each depth of scanline, in y-direction

    for (int m = 0; m <= numScanline; m++)
    {
        scanlinePosition[m] = new float2[numPixel]; // allocate memory for scanlinePosition
        float x = (m - ((numScanline-1.0)/2.0)) * PITCH; // calculation for x depth
        for (int n = 0; n < numPixel; n++)
        {   
            // populating scanlinePosition
            scanlinePosition[m][n].x = x;
            scanlinePosition[m][n].y = n*diff;
        }
        
    }
    return scanlinePosition;
}

float imageParam::getXPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].x;
}

float imageParam::getYPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].y;
}

float imageParam::getElementPosition(int element)
{
    return elementPosition[element];
}

int imageParam::getNumElement()
{
    return numElement;
}

int imageParam::getNumSample()
{
    return numSample;
}

int imageParam::getNumScanline() 
{
    return numScanline;
}

int imageParam::getNumPixel() 
{
    return numPixel;
}

void imageParam::deletePositionArray()
{
    // deleting scanlinePosition and elementPosition
    for (int i = 0; i < numScanline; i++)
    {
        delete[] scanlinePosition[i];
    }
    
    delete[] scanlinePosition;
    delete[] elementPosition;
}









