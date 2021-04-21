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
    A function checking costraints  
**/
bool eb_checkCostraints(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding);




#endif //DEVICE_H
