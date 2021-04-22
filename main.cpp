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
    
    eb_save_to_file(myDevice,"bella");


    Device* deviceRead = new Device;
    string svg=eb_read_from_file("device");
    deviceRead=eb_parse(svg);
    cout<<"svg letto da file ha i seguenti parametri: "<<endl;
    cout<<deviceRead->length_shaft<<" , "<<deviceRead->width_towtruck<<" , "<<deviceRead->width_platform<<" , "<<deviceRead->rotation<<" , "<<deviceRead->sliding<<endl;
    




    return 0;
}
