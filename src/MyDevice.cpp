
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
EbDevice* eb_init(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding){
    
    EbDevice* eb_device = new EbDevice;

    if(eb_checkConstraints(length_shaft,width_towtruck,width_platform,rotation,sliding)==false){
        return NULL;
    }
    else{
        eb_device -> length_shaft = length_shaft;
        eb_device -> width_towtruck = width_towtruck;
        eb_device ->  width_platform = width_platform;
        eb_device ->  rotation = rotation;  //angolo di rotazione è rispetto all'asse y, rotazione in senso orario se angolo positivo
        eb_device ->  sliding = sliding;
    }

    return eb_device;
}

/**
    A function checking mechanical constraints  
**/
bool eb_checkConstraints(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding){
    
    if(length_shaft < 0 || width_towtruck < 0 || width_platform < 0 || sliding < 0){
        return false;
    }
    if(length_shaft<((std_platformHeight/2)+(std_towtruckHeight/2))){   
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
bool eb_drawConstraints(EbDevice* eb_device){

    if(eb_Yplatform(eb_device) > 1480){   //vincolo in altezza
        return false;
    }
    if((eb_Xcir(eb_device) + (eb_device->width_towtruck/2)) > 2000 || (eb_Xplatform(eb_device)+(eb_device->width_platform/2)) > 2000){ //vincolo in larghezza(a dx)
        return false;
    }
    if((eb_Xplatform(eb_device) - ((eb_device->width_platform)/2)) < 0){ //vincolo in larghezza(a sx)
        return false;
    }      

    return true;
}

/**
    A function which produce a string with svg code  
**/
string eb_to_svg(EbDevice* eb_device){

    if(eb_drawConstraints(eb_device)==false){
        cout<<"ERROR 404: draw constraints exceeded"<<endl;
        exit(1);
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
    code+="<svg xmlns=\"http://www.w3.org/2000/svg\" style=\"background-color:white\" width=\"2000\" height=\"1500\">\n\n";
    
    /*
        carrello gru con spostamento orizzontale
    */
    code+="<g>\n";
    code+="<rect x = \""+to_string(sliding)+"\" y = \"60\" width = \"" + to_string(widthTt) +"\" height = \"40\" stroke = \"black\" stroke-width = \"3\" fill = \"yellow\"/>\n";
    code+="</g>\n\n";

    /*
        asta rotante, 
        angolo positivo --> asta ruota in senso orario(verso sx)
        angolo negativo --> asta ruota in senso antiorario(verso dx)
    */
    code+="<g transform  = \"rotate("+to_string(angle)+","+to_string(Xcir)+",80)\">\n";
    code+="<rect x = \""+to_string(Xcir-std_radius)+"\" y = \"80\" width = \"20\" height = \"" + to_string(length) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"orange\" />\n";
    code+="<circle cx = \""+to_string(Xcir)+"\" cy = \"80\" r = \"10\" stroke = \"black\" stroke-width = \"3\" fill = \"white\"/>\n";
    code+="</g>\n\n";

    /*
        piattaforma
    */
    code+="<g>\n";
    code+="<rect x = \""+to_string(Xplatform)+"\" y = \""+to_string(Yplatform)+"\" width = \""+to_string(widthPla)+"\" height = \"20\"  stroke = \"black\" stroke-width = \"3\" fill = \"black\" />\n";
    code+="</g>\n\n";

    code+="</svg>\n";

    return code;
}

/**
    A function which calculate coordinate X of CiR
**/
double eb_Xcir(EbDevice* eb_device){
    double Xcir;

    Xcir=eb_device->sliding + ((eb_device->width_towtruck)/2);

    return Xcir;
}

/**
    A function which calculate coordinate X of the platform
**/
double eb_Xplatform(EbDevice* eb_device){
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
double eb_Yplatform(EbDevice* eb_device){
    double Yplatform;
    double angle;
    double l = eb_device->length_shaft;

    angle=eb_device->rotation * (M_PI/180);  //necessario angolo in radianti nella funzione seno

    Yplatform=std_Ycir + l*cos(angle) - (std_platformHeight/2);

    return Yplatform;
}

/*
    Sets a new length_shaft in the structure       
    if the new length is incompabile with other measures, RETURN 1, otherwise 0
*/
int eb_set_lengthShaft(EbDevice* device, double new_length_shaft){ 

    if(eb_checkConstraints(new_length_shaft,device->width_towtruck,device->width_platform,device->rotation, device->sliding) == false){
        return 1;
    }

    device->length_shaft = new_length_shaft;

    return 0;
}

/*
    Sets a new width_towtruck in the structure       
    if the new width is incompabile with other measures, RETURN 1, otherwise 0
*/
int eb_set_widthTowtruck(EbDevice* device, double new_width_towtruck){ 

    if(eb_checkConstraints(device->length_shaft,new_width_towtruck,device->width_platform,device->rotation, device->sliding) == false){
        return 1;
    }

    device->width_towtruck = new_width_towtruck;

    return 0;
}

/*
    Sets a new width_platform in the structure       
    if the new width is incompabile with other measures, RETURN 1, otherwise 0
*/
int eb_set_widthPlatform(EbDevice* device, double new_width_platform){ 

    if(eb_checkConstraints(device->length_shaft,device->width_towtruck,new_width_platform,device->rotation, device->sliding) == false){
        return 1;
    }

    device->width_platform = new_width_platform;

    return 0;
}

/*
    Sets  rotation in the structure       
    if the new rotation is incompabile with other measures, RETURN 1, otherwise 0
*/
int eb_set_rotation(EbDevice* device, double new_rotation){ 

    if(eb_checkConstraints(device->length_shaft,device->width_towtruck,device->width_platform,new_rotation, device->sliding) == false){
        return 1;
    }

    device->rotation = new_rotation;

    return 0;
}

/*
    Sets  sliding in the structure       
    if the new sliding is incompabile with other measures, RETURN 1, otherwise 0
*/
int eb_set_sliding(EbDevice* device, double new_sliding){ 

    if(eb_checkConstraints(device->length_shaft,device->width_towtruck,device->width_platform, device->rotation, new_sliding) == false){
        return 1;
    }

    device->sliding = new_sliding;

    return 0;
}

/*
    A function which write on a file svg
*/
void eb_save_to_file(string stringToWrite, string filename){
   
    // Create and open a text file
    ofstream MyFile("../"+filename+".svg");

    // Write to the file
    MyFile << stringToWrite;

    // Close the file
    MyFile.close();
}

/*
    function, which creates a struct from a SVG textual representation
*/
EbDevice* eb_parse(string svg){
    
    double length_shaft;
    double width_towtruck;
    double width_platform;
    double rotation;
    double sliding;
    
    
    //getting sliding
    string element1 = eb_extractValue(svg,"rect x = \"","\"");
    sliding = stod(element1);


    //getting width_towtruck
    string element2 = eb_extractValue(svg,"rect x = \"400\" y = \"205\" width = \"","\"");
    width_towtruck = stod(element2);

    
    //getting rotation
    string element3 = eb_extractValue(svg,"g transform  = \"rotate(",",");
    rotation = stod(element3);
    
    //getting length_shaft
    string element4 = eb_extractValue(svg,"rect x = \"460\" y = \"230\" width = \"40\" height = \"","\"");
    length_shaft = stod(element4);

    //getting width_platform
    string element5 = eb_extractValue(svg,"rect x = \"620\" y = \"750\" width = \"","\"");
    width_platform = stod(element5);


    EbDevice* device = new EbDevice;

    device=eb_init(length_shaft,width_towtruck,width_platform,rotation,sliding);
    if(device==NULL){
        cout<<"ERROR 404: mechanical constraints exceeded"<<endl;
        exit(1);
    }
    return device;
}

/*
    function which extract a piece of a string
    function needed in eb_parse
*/
string eb_extractValue(string svg, string startingValue, string endingValue){
    size_t find1 = svg.find(startingValue) + startingValue.size();
    size_t find2= svg.find(endingValue, find1);
    string element = svg.substr(find1, find2-find1);
    return element;
} 

/*
    A function which read from a file a string
*/
string eb_read_from_file(string filename){
    ifstream t("../"+filename+".svg");
    stringstream buffer;
    buffer << t.rdbuf();
    string svg_string = buffer.str();

    return svg_string;
}