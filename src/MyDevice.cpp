
#include "../include/device.h"
#include <iostream>
#include <string.h>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

using namespace std;

/*
    some components' features are fixed --> shaft width, towtruck height, platform height 
*/
    const double std_shaftWidth = 20;
    const double std_towtruckHeight = 40;
    const double std_platformHeight = 20;

    const double std_Ycir=80;
    const double std_radius=10;
    const double std_YtowTruck=60;
/*
    centro di istantanea rotazione --> punto attorno al quale l'asta ruota, corrisponde al
    centro della coppia rotoidale che unisce asta e carrello --> Ycir è fissa, Xcir varia in
    funzione dello spostamento del carrello lungo x
*/


/**
    A function initing a device 
**/
Device* eb_init(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding){
    
    Device* eb_device = new Device;

    if(eb_checkConstraints(length_shaft,width_towtruck,width_platform,rotation,sliding)==false){
        eb_device==NULL;
    }
    else{
        eb_device -> length_shaft;
        eb_device -> width_towtruck;
        eb_device ->  width_platform;
        eb_device ->  rotation;  //angolo di rotazione è rispetto all'asse y, rotazione in senso orario se angolo positivo
        eb_device ->  sliding;
    }

    return eb_device;
}

/**
    A function checking mechanicalconstraints  
**/
bool eb_checkConstraints(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding){
    
    /*
        vincoli meccanici di cotruzione 
    */
    if(length_shaft < 0 || width_towtruck < 0 || width_platform < 0){
        return false;
    }
    if(rotation > 80 || rotation < -80){      //angoli max = +- 80 --> limite "fisico" max
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
    A function checking costraints in relation to the svg draw
**/
bool eb_drawConstraints(Device* eb_device){

    if(eb_Yplatform(eb_device) > 1480){   //vincolo in altezza
        return false;
    }
    if((eb_Xcir(eb_device) + (eb_device->length_shaft) + (eb_device->width_platform/2)) > 2000){ //vincolo in larghezza(a dx)
        return false;
    }
    if((eb_Xcir(eb_device) < (eb_device->length_shaft) + (eb_device->width_platform/2))){ //vincolo in larghezza(a sx)
        return false;
    }      

    return true;
}

/**
    A function which produce a string with svg code  
**/
string eb_to_svg(Device* eb_device){

    if(eb_drawConstraints(eb_device)==false){
        throw invalid_argument("you didn't respect draw contraints. Your device doesn't fit in the svg file!");
    }

    /*parametri device*/
    double sliding=eb_device->sliding;
    double length=eb_device->length_shaft;
    double angle=eb_device->rotation; 
    double widthPla=eb_device->width_platform;
    double widthTt=eb_device->width_towtruck;

    /*variabili utili*/
    double Xcir=eb_Xcir(eb_device);
    double Xplatform=eb_Xplatform(eb_device);
    double Yplatform=eb_Yplatform(eb_device);


    string code="";

    code+="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    code+="<svg xmlns=\"http://www.w3.org/2000/svg\"  width = \"2000\" height = \"1500\">\n\n";
    
    /*
        carrello gru con spostamento orizzontale
    */
    code+="<g>\n";
    code+="<rect x = \""+to_string(sliding)+"\" y = \"60\" width = \"" + to_string(widthTt) +"\" height = \"40\" stroke = \"black\" stroke-width = \"3\" fill = \"yellow\"/>\n";
    code+="</g>\n";

    /*
        asta rotante, 
        angolo positivo --> asta ruota in senso orario(verso sx)
        angolo negativo --> asta ruota in senso antiorario(verso dx)
    */
    code+="<g transform  = \"rotate(\""+to_string(angle)+"\",\""+to_string(Xcir)+"\",80)\">\n";
    code+="<rect x = \""+to_string(Xcir-std_radius)+"\" y = \"80\" width = \"20\" height = \"" + to_string(length) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"orange\" />\n";
    code+="<circle cx = \""+to_string(Xcir)+"\" cy = \"80\" r = \"10\" stroke = \"black\" stroke-width = \"3\" fill = \"white\"/>\n";
    code+="</g>\n";

    /*
        piattaforma
    */
    code+="<g>\n";
    code+="<rect x = \""+to_string(Xplatform)+"\" y = \""+to_string(Yplatform)+"\" width = \""+to_string(widthPla)+"\" height = \"20\"  stroke = \"black\" stroke-width = \"3\" fill = \"black\" />\n";
    code+="</g>\n";

    code+="</svg\n";

    return code;
}

/**
    A function which calculate coordinate X of CiR
**/
double eb_Xcir(Device* eb_device){
    double Xcir;

    Xcir=eb_device->sliding + ((eb_device->width_towtruck)/2);

    return Xcir;
}

/**
    A function which calculate coordinate X of the platform
**/
double eb_Xplatform(Device* eb_device){
    double Xplatform;
    double Xcir=eb_Xcir(eb_device);
    double angle;
    double l = eb_device->length_shaft;

    angle=eb_device->rotation * (M_PI/180);  //necessario angolo in radianti nella funzione seno

    Xplatform=Xcir - l*sin(angle) - ((eb_device->width_platform)/2);

    return Xplatform;
}

/**
    A function which calculate coordinate Y of the platform
**/
double eb_Yplatform(Device* eb_device){
    double Yplatform;
    double angle;
    double l = eb_device->length_shaft;

    angle=eb_device->rotation * (M_PI/180);  //necessario angolo in radianti nella funzione seno

    Yplatform=std_Ycir + l*cos(angle) - (std_platformHeight/2);

    return Yplatform;
}

/*
    A function which write on a file svg
*/
void eb_save_to_file(Device* eb_device){
    
    // Create and open a text file
    ofstream ebFile("ebDevice.svg");
    
    string string_to_write = eb_to_svg(eb_device);
    
    // Write to the file
    ebFile << string_to_write;
    
    // Close the file
    ebFile.close();

}
