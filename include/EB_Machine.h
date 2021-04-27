#ifndef EB_MACHINE_H
#define EB_MACHINE_H

#include "EB_Device.h"
#include "LBAMTTBiellaManovella.h"
#include <string>
#include <string.h>


using namespace std;

/*
    struct representing the machine
*/
struct EbMachine {
    double XposMachine;
    EbDevice** arrCarrelloGru;
    LBAMTTdevice** arrBiellaManovella;
};

/**
    A function initing a machine 
**/
EbMachine* eb_machine_init(double XposMachine, int n, double* dShaft, double* stroke, double* lenBiella, double* wBiella, double* hPistone, double* dPistone, double* angle,
                            double* length_shaft, double* width_towtruck, double* width_platform, double* rotation);

/*
    A function which calculate the position of the towtruk
*/
double eb_sliding(double cxShaft, double stroke, double lenBiella, double angle, double hPistone, double wBiella);

/**
    A function which produce a string with svg code for the machine
**/
string eb_machine_to_svg(EbMachine* machine, int n);

/*
    New version of the function LBAMTTdeviceToStringSVG, readjusted for the machine
*/
string eb_new_LBAMTTdeviceToStringSVG (LBAMTTdevice * device, double cxShaft, double cyShaft, bool header=true);

/*
    New version of the function eb_to_svg to create a svg for a "carrelloGru", readjusted for the machine
*/
string eb_new_to_svg(EbDevice* eb_device, double yShaft);

/*
    funzione che calcola la pos x degli alberi presenti nella machine
*/
double eb_cxShaft(EbDevice* CarrelloGru);

/*
    funzione che calcola la pos x degli alberi presenti nella machine
*/
double eb_cyShaft(EbDevice* carrelloGru, LBAMTTdevice* biellaManovella);





#endif