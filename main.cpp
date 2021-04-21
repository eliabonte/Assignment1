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

    myDevice=eb_init(400,180,300,60,350);

    return 0;
}
