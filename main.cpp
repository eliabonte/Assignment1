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

    cout << "I read this" << endl;
    cout << eb_read_from_file("device")<< endl;


    return 0;
}
