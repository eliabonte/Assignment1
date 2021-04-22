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

    myDevice=eb_init(200,130,300,-60,350);

    eb_printParameters(myDevice);
    
    eb_save_to_file(myDevice,"bella");

    /*
    Device* deviceRead = new Device;
    string svg=eb_read_from_file("device");
    deviceRead=eb_parse(svg);
    cout<<"svg letto da file ha i seguenti parametri: "<<endl;
    cout<<deviceRead->length_shaft<<" , "<<deviceRead->width_towtruck<<" , "<<deviceRead->width_platform<<" , "<<deviceRead->rotation<<" , "<<deviceRead->sliding<<endl;
    
*/



    return 0;
}
