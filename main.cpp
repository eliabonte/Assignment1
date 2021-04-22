#include <iostream>

#include "device.h"
#include <string.h>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

using namespace std;

/**
    A function which print the 5 parameters of a device 
**/
void eb_printParameters(EbDevice* device){
    cout<<"I 5 parametri principali di questo device sono: "<<endl;
    cout<<"Length shaft: "<<device -> length_shaft<<endl;
    cout<<"Width_towtruck: "<<device -> width_towtruck<<endl;
    cout<<"Width_platform: "<<device -> width_platform<<endl;
    cout<<"Angle of rotation: "<<device -> rotation<<endl;
    cout<<"Sliding: "<<device -> sliding<<endl;
}

int main() {

    EbDevice* myDevice = new EbDevice;

    myDevice=eb_init(200,130,300,-90,100);

    if(myDevice==NULL){
        cout<<"ERROR 404: mechanical constraints exceeded"<<endl;
        exit(1);
    }
    
    eb_printParameters(myDevice);
    
    /*
    eb_save_to_file(myDevice,"bella");

    
    EbDevice* deviceRead = new EbDevice;
    string svg=eb_read_from_file("device");
    deviceRead=eb_parse(svg);
    cout<<"svg letto da file ha i seguenti parametri: "<<endl;
    cout<<deviceRead->length_shaft<<" , "<<deviceRead->width_towtruck<<" , "<<deviceRead->width_platform<<" , "<<deviceRead->rotation<<" , "<<deviceRead->sliding<<endl;
    */
    return 0;
}
