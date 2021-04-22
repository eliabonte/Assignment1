#include <iostream>

#include "device.h"
#include <string.h>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

using namespace std;

int main() {

    Device* myDevice = new Device;

    myDevice=eb_init(400,160,300,-60,480);

    cout<<"creo un file svg del mio device con parametri: "<<endl;
    cout<<myDevice->length_shaft<<" , "<<myDevice->width_towtruck<<" , "<<myDevice->width_platform<<" , "<<myDevice->rotation<<" , "<<myDevice->sliding<<endl;
    
    cout<<"Xcir: "<<eb_Xcir(myDevice)<<endl;
    cout<<"Xplatform: "<<eb_Xplatform(myDevice)<<endl;
    cout<<"Yplatform: "<<eb_Yplatform(myDevice)<<endl;
    
    eb_save_to_file(myDevice,"bella");

    cout<<"cambio adesso la rotzione e poi creo nuovo file: -60 -> 30"<<endl;

    eb_set_rotation(myDevice,30);
    eb_save_to_file(myDevice,"bellax2");




    return 0;
}
