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
    Sets a new length_shaft in the structure       
    if the new length is incompabile with other measures, RETURN 1, otherwise 0
*/
int eb_set_lengthShaft(Device* device, double new_length_shaft);

/*
    Sets a new width_towtruck in the structure       
    if the new width is incompabile with other measures, RETURN 1, otherwise 0
*/
int eb_set_widthTowtruck(Device* device, double new_width_towtruck);

/*
    Sets a new width_platform in the structure       
    if the new width is incompabile with other measures, RETURN 1, otherwise 0
*/
int eb_set_widthPlatform(Device* device, double new_width_platform);

/*
    Sets  rotation in the structure       
    if the new rotation is incompabile with other measures, RETURN 1, otherwise 0
*/
int eb_set_rotation(Device* device, double new_rotation);

/*
    Sets  sliding in the structure       
    if the new sliding is incompabile with other measures, RETURN 1, otherwise 0
*/
int eb_set_sliding(Device* device, double new_sliding);


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
void eb_save_to_file(Device* eb_device, string filename);


Device* eb_parse(string svg);



#endif //DEVICE_H
