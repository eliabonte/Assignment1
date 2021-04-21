#ifndef DEVICE_H
#define DEVICE_H

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


/**
    A function which produce a string with svg code  
**/
string eb_to_svg(Device* eb_device);


/**
    A function which calculate coordinate X of CiR
**/
double eb_Xcir(Device* eb_device);


/**
    A function which calculate coordinate X of the platform
**/
double eb_xplatform(Device* eb_device);


/**
    A function which calculate coordinate Y of the platform
**/
double eb_Yplatform(Device* eb_device);



#endif //DEVICE_H
