
#include "../include/device.h"
#include "iostream"

using namespace std;


/**
    A function initing a device 
**/
Device* eb_init(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding){
    /*
        some components' features are fixed --> shaft width, towtruck height, platform height 
    */
   double std_shaftWidth = 40;
   double std_towtruckHeight = 50;
   double std_platformHeight = 20;
    
    Device* eb_device = new Device;

    if(eb_checkCostraints(length_shaft,width_towtruck,width_platform,rotation,sliding)==false){
        eb_device==NULL;
    }
    else{
        eb_device -> length_shaft;
        eb_device -> width_towtruck;
        eb_device ->  width_platform;
        eb_device ->  rotation;
        eb_device ->  sliding;
    }

    return eb_device;
}

/**
    A function checking costraints  
**/
bool eb_checkCostraints(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding){
    
    /*
        some components' features are fixed --> shaft width, towtruck height, platform height 
    */
   double std_shaftWidth = 40;
   double std_towtruckHeight = 50;
   double std_platformHeight = 20;
    
    if(length_shaft < 0 || width_towtruck < 0 || width_platform < 0){
        return false;
    }

    if(rotation > 80 || rotation < -80){
        return false;
    }

    if(width_towtruck < std_shaftWidth){
        return false;
    }

    if(width_platform < std_shaftWidth){
        return false;
    }

    return true;
}


