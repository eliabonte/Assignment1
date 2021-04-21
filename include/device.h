#ifndef DEVICE_H
#define DEVICE_H

#include <string.h>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>


using namespace std;

/**
 * 
 * A struct representing the device  
**/
struct Device {
    double length_shaft;
    double width_towtruck;
    double width_platform;
    double rotation;
    double sliding;
};

/**
    A function initing a device 
**/
Device* eb_init(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding);


/**
    A function checking mechanical costraints  
**/
bool eb_checkConstraints(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding);


/**
    A function checking costraints in relation to the svg draw
**/
bool eb_drawConstraints(Device* eb_device);


/*
    A function which produce a string with svg code  
*/
string eb_to_svg(Device* eb_device);


/**
    A function which calculate coordinate X of CiR
**/
double eb_Xcir(Device* eb_device);


/**
    A function which calculate coordinate X of the platform
**/
double eb_Xplatform(Device* eb_device);


/**
    A function which calculate coordinate Y of the platform
**/
double eb_Yplatform(Device* eb_device);


/*
    A function which write on a file svg
*/
void eb_save_to_file(Device* eb_device);



#endif //DEVICE_H
