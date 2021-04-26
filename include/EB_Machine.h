#ifndef EB_MACHINE_H
#define EB_MACHINE_H

#include "EB_Device.h"
#include "LBAMTTBiellaManovella.h"


using namespace std;

/*
    struct representing the machine
*/
struct EbMachine {
    double xpos;
    EbDevice** arrCarrelloGru;
    LBAMTTdevice** arrBiellaManovella;
};

/**
    A function initing a machine 
**/
EbMachine* eb_machine_init(double xpos, EbDevice** carrelloGru, LBAMTTdevice** biellaManovella, int n);

/**
    A function which produce a string with svg code
    if with_measures is true the drawing will include measurements   
**/
string eb_machine_to_svg(EbDevice* eb_device, bool with_measures);



#endif