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

/**
    A function checking mechanical constraints of the machine 
**/
bool eb_checkConstraints_Machine(double* angle,int n);

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
string eb_new_to_svg(EbDevice* eb_device, double yShaft, double dPistone);

/*
    funzione che calcola la pos x degli alberi presenti nella machine
*/
double eb_cxShaft(EbDevice* CarrelloGru);

/*
    funzione che calcola la pos x degli alberi presenti nella machine
*/
double eb_cyShaft(EbDevice* carrelloGru, LBAMTTdevice* biellaManovella, double Yshaft_prec);

/*
    funzione che calcola la pos y deglle piattaforme dei carreloGru della machine
*/
double new_eb_Yplatform(EbDevice* carrelloGru, double Yshaft_prec);

/*
    function, which creates a struct from a SVG textual representation
*/
EbMachine* eb_machine_parse(string svg, int n);

/*
    funzione che ritorna il pezzo di stringa relativa al device biella-manovella
*/
string eb_takeLBAMTTstring(string svg,size_t pos);

/*
    funzione che ritorna la posizione dove si è arrivati ad estrarre la stringa di LBAMTT
*/
size_t eb_posFinale_stringLBAMTT(string svg, size_t pos);

/*
    funzione che prende il pezzo di stringa relativa al device carrello-gru
*/
string eb_takeEBstring(string svg,size_t pos);
/*
    funzione che ritorna la posizione dove si è arrivati ad estrarre la stringa di EB
*/
size_t eb_posFinale_stringEB(string svg,size_t pos);


#endif