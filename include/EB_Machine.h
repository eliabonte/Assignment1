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
EbMachine* eb_machine_init(double XposMachine, LBAMTTdevice** biellaManovella, EbDevice** carrelloGru, int n);

/*
    A function which calculate the position of the towtruk
*/
double eb_sliding(double cxShaft, double stroke, double lenBiella, double angle, double hPistone, double wBiella);

/*
    New version of the function LBAMTTdeviceToStringSVG, readjusted for the machine
*/
string eb_new_LBAMTTdeviceToStringSVG (LBAMTTdevice * device, double cxShaft, double cyShaft, bool header=true);

/**
    A function which produce a string with svg code for the machine
**/
string eb_machine_to_svg(EbMachine* machine, int n);

/*
    funzione che calcola la pos x degli alberi presenti nella machine
*/
double eb_cxShaft(EbDevice* CarrelloGru);

/*
    funzione che ritorna un puntatore all'array dinamico che contiente le pos y degli alberi presenti nella machine
*/
double* eb_yShafts(double YposMachine, int n, EbDevice** arrCarrelloGru,LBAMTTdevice** arrBiellaManovella);





#endif