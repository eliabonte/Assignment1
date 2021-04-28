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
    double XposMachine; //poszione iniziale della machine, coordinate centro primo albero 
    EbDevice** arrCarrelloGru; //array dinamico di puntatori a struct EbDevice
    LBAMTTdevice** arrBiellaManovella; //array dinamico di puntatori a struct LBAMTTdevice
};

/**
    A function initing a machine 
**/
EbMachine* eb_machine_init(double XposMachine, int n, double* dShaft, double* stroke, double* lenBiella, double* wBiella, double* hPistone, double* dPistone, double* angle,
                            double* length_shaft, double* width_towtruck, double* width_platform, double* rotation);

/**
    A function checking mechanical constraints (XposMachine) of the machine 
**/
bool eb_checkConstraints_Machine(double XposMachine);
/**
    A function checking mechanical constraints of the machine 
**/
bool eb_checkConstraints_Machine_angle(double* angle,int n);

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
EbMachine* eb_machine_parse(string svg);

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

/*
    destroy machine
*/
int eb_destroy_machine(EbMachine* machine, int n);

/*
    function which checks if the two machines are the same
*/
bool eb_machine_are_equal(EbMachine* machine1, int n1, EbMachine* machine2, int n2);

/*
    function which checks if  two LBAMTT devices are equal
*/
bool eb_devicesLBAMTT_are_equal(LBAMTTdevice* device1, LBAMTTdevice* device2);

/*
    function which checks if two EB devices are equal
*/
bool eb_devicesEB_are_equal(EbDevice* device1, EbDevice* device2);

/*
    funzione che ritorna il numero di coppie di device n presenti in una machine, lette da file svg
*/
int eb_count_stringOccurences(string &pat, string &txt);


#endif