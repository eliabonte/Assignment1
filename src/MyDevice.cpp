
#include "../include/device.h"
#include <iostream>
#include <string.h>

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
   double std_towtruckHeight = 40;
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

/**
    A function which produce a string with svg code  
**/
string eb_to_svg(Device* eb_device){
    string code="";

    code+="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    code+="<svg xmlns=\"http://www.w3.org/2000/svg\"  width = \"1000\" height = \"900\">\n\n";
    
    /*
        carrello gru con spostamento orizzontale
    */
    code+="<g>\n";
    code+="<rect x = \"400\" y = \"205\" width = \"" + to_string(eb_device->width_towtruck) +"\" height = \"40\" stroke = \"black\" stroke-width = \"3\" fill = \"yellow\"/>\n";
    code+="<text x = \"450\" y = \"170\" fill = \"black\"> tow truck </text>\n";
    code+="<line x1 = \"400\" y1 = \"180\" x2 = \"560\" y2 = \"180\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
    code+="</g>\n";

    /*
        asta rotante
    */
    code+="<g transform  = \"rotate(\""+to_string(eb_device->rotation)+"\",480,230)\">\n";
    code+="<rect x =   \"460\" y = \"230\" width = \"40\" height = \"" + to_string(eb_device->length_shaft) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"orange\" />\n";
    code+="<text x = \"620\" y = \"500\" fill = \"black\"> shaft </text>\n";
    code+="<line x1 = \"600\" y1 = \"230\" x2 = \"600\" y2 = \"830\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
    code+="<text x = \"390\" y = \"490\" fill = \"black\"> rotation </text>\n";
    code+="<line x1 = \"370\" y1 = \"500\" x2 = \"460\" y2 = \"500\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
    code+="<circle cx = \"480\" cy = \"230\" r = \"10\" stroke = \"black\" stroke-width = \"3\" fill = \"white\"/>\n";
    code+="<circle cx = \"480\" cy = \"830\" r = \"10\" stroke = \"black\" stroke-width = \"3\" fill = \"white\"/>\n";
    code+="</g>\n";

    /*
        piattaforma
    */
    code+="<g>\n";
    code+="<rect x = \"620\" y = \"750\" width = \""+to_string(eb_device->width_platform)+"\" height = \"20\"  stroke = \"black\" stroke-width = \"3\" fill = \"black\" />\n";
    code+="<text x = \"750\" y = \"820\" fill = \"black\"> platform </text>\n";
    code+="<line x1 = \"620\" y1 = \"790\" x2 = \"940\" y2 = \"790\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
    code+="</g>\n";

    /*
        quota spostamento carrelo
    */
    code+="<g>\n";
    code+="<text x = \"330\" y = \"220\" fill = \"black\"> sliding </text>\n";
    code+="<line x1 = \"300\" y1 = \"230\" x2 = \"400\" y2 = \"230\"  stroke = \"black\" stroke-width  = \"2\"/>\n";
    code+="</g>\n";

    code+="</svg\n";

    return code;
    }

