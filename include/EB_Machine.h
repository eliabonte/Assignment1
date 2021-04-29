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
    @param XposMachine posizione iniziale machine
    @param n numero di coppie di device
    @param dShaft* array dinamico di parametri: diametro albero
    @param stroke* array dinamico di parametri: corsa pistone
    @param lenBiella* array dinamico di parametri: lunghezza biella
    @param wBiella*  array dinamico di parametri: larghezza biella
    @param hPistone*  array dinamico di parametri: altezza pistone
    @param dPistone*  array dinamico di parametri: diametro pistone
    @param angle* array dinamico di parametri: angolo in gradi della manovella (default 0.0, punto morto superiore)
    @param length_shaft* lunghezza asta
    @param width_towtruck* larghezza carrello
    @param width_platform* larghezza piattafotma
    @param rotation* angolo di rotazione asta rispetto all'asse y, positivo rotazione in senso orario
    @return puntatore alla machine; 
**/
EbMachine* eb_machine_init(double XposMachine, int n, double* dShaft, double* stroke, double* lenBiella, double* wBiella, double* hPistone, double* dPistone, double* angle,
                            double* length_shaft, double* width_towtruck, double* width_platform, double* rotation);

/**
    A function checking mechanical constraints (XposMachine) of the machine 
    @param XposMachine posizione iniziale machine
    @return true se vincoli sono rispettati, altrimenti false
**/
bool eb_checkConstraints_Machine(double XposMachine);

/**
    A function checking mechanical constraints of the machine 
    @param angle* array dinamico di parametri: angolo in gradi della manovella (default 0.0, punto morto superiore)
    @param n numero di coppie di device
    @return true se vincoli sono rispettati, altrimenti false
**/
bool eb_checkConstraints_Machine_angle(double* angle,int n);

/**
    A function which calculate the position of the towtruk
    @param cxShaft coordinata x centro albero motore
    @param stroke corsa pistone
    @param lenBiella lunghezza biella
    @param angle angolo in gradi della manovella
    @param hPistone altezza pistone
    @param wBiella  larghezza biella
    @return valore sliding carrello gru
**/
double eb_sliding(double cxShaft, double stroke, double lenBiella, double angle, double hPistone, double wBiella);

/**
    set new XposMachine
    @param machine puntatore a struct EbMachine
    @param XposMachine nuova posizione machine 
    @return 1,if the new length is incompabile with other measures, otherwise 0
**/
int eb_set_XposMachine(EbMachine* machine, double new_XposMachine);

/**
    set new biella manovella
    @param machine puntatore a struct EbMachine
    @param numDevice numero device da modificare
    @param choice tipo di parametro da modificare
    @param newparameter valore nuovo parametro 
    @return 1,if the new length is incompabile with other measures, otherwise 0
**/
int eb_set_biellaManovella(EbMachine* machine,int numDevice, char choice, double newparameter);

/**
    set new carrello gru
    @param machine puntatore a struct EbMachine
    @param numDevice numero device da modificare
    @param choice tipo di parametro da modificare
    @param newparameter valore nuovo parametro 
    @return 1,if the new length is incompabile with other measures, otherwise 0
**/
int eb_set_carrelloGru(EbMachine* machine,int numDevice, char choice, double newparameter);

/**
    A function which produce a string with svg code for the machine
    @param machine puntatore a struct EbMachine
    @param n numero di coppie di device
    @return stringa con codice svg della machine
**/
string eb_machine_to_svg(EbMachine* machine, int n);


/**
    New version of the function LBAMTTdeviceToStringSVG, readjusted for the machine
    Crea una stringa in codice SVG per la rappresentazione del device
    @param device puntatore a struttura da rappresentare
    @param cxShaft coordinata x del centro dell'albero nell'area di disegno
    @param cyShaft coordinata y del centro dell'albero nell'area di disegno
    @param quote flag: se vero include le quote delle misure del pezzo (default false)
    @param header flag: se vero include l'header per il file svg (default true)
    @return string deviceSVG;
*/
string eb_new_LBAMTTdeviceToStringSVG (LBAMTTdevice* device, double cxShaft, double cyShaft, bool header=true);

/**
    New version of the function eb_to_svg, readjusted for the machine
    Crea una stringa in codice SVG per la rappresentazione del device
    @param eb_device puntatore alla struct EbDevice
    @param yShaft coordinata y dell'albero motore
    @param dPistone diametro pistone
    @return string con codice svg
**/
string eb_new_to_svg(EbDevice* eb_device, double yShaft, double dPistone);

/**
    funzione che calcola la pos x degli alberi presenti nella machine
    @param CarrelloGru puntatore alla struct EbDevice
    @return coordinata x albero motore
**/
double eb_cxShaft(EbDevice* CarrelloGru);

/*
    funzione che calcola la pos x degli alberi presenti nella machine
*/
/**
    funzione che calcola la pos y degli alberi presenti nella machine
    @param CarrelloGru puntatore alla struct EbDevice
    @param biellaManovella puntatore alla struct LBAMTTdevice
    @param Yshaft_prec coordinata y albero motore precedente
    @return coordinata y albero motore corrente
**/
double eb_cyShaft(EbDevice* carrelloGru, LBAMTTdevice* biellaManovella, double Yshaft_prec);

/**
    funzione che calcola la pos y deglle piattaforme dei carreloGru della machine
    @param CarrelloGru puntatore alla struct EbDevice
    @param Yshaft_prec coordinata y albero motore precedente
    @return coordinata y piattaforma
**/
double new_eb_Yplatform(EbDevice* carrelloGru, double Yshaft_prec);

/**
    function, which creates a struct from a SVG textual representation
    @param svg stringa svg
    @return puntatore alla struct EbMachine appena creata 
**/
EbMachine* eb_machine_parse(string svg);

/**
    funzione che estrae un pezzo di stringa relativa al device biella-manovella
    @param svg stringa con codice svg
    @param pos posizione nella stringa da cui partire per estrarre il pezzo di stringa
    @return stringa di codice svg relativa al device biella-manovella
**/
string eb_takeLBAMTTstring(string svg,size_t pos);

/**
    funzione che calcola la posizione dove si è arrivati ad estrarre la stringa di LBAMTT
    @param svg stringa con codice svg
    @param pos posizione nella stringa da cui partire
    @return posizione dove si è arrivata nella stringa svg
**/
size_t eb_posFinale_stringLBAMTT(string svg, size_t pos);

/**
    funzione che estrae un pezzo di stringa relativa al device carrello-gru 
    @param svg stringa con codice svg
    @param pos posizione nella stringa da cui partire per estrarre il pezzo di stringa
    @return stringa di codice svg relativa al device carrello-gru
**/
string eb_takeEBstring(string svg,size_t pos);

/**
    funzione che calcola la posizione dove si è arrivati ad estrarre la stringa di EB
    @param svg stringa con codice svg
    @param pos posizione nella stringa da cui partire
    @return  posizione dove si è arrivata nella stringa svg
**/
size_t eb_posFinale_stringEB(string svg,size_t pos);

/**
    destroy machine
    @param machine puntatore a EbMachine
    @param n numero di coppie di device
    @return 0 se operazione è andata a buon fine, altrimenti 1
**/
int eb_destroy_machine(EbMachine* machine, int n);

/**
    function which checks if the two machines are the same
    @param machine1 puntatore a EbMachine
    @param n1 numero di coppie di device nella machine 1
    @param machine2 puntatore a EbMachine
    @param n2 numero di coppie di device nella machine 2
    @return true se le machine sono uguali
**/
bool eb_machine_are_equal(EbMachine* machine1, int n1, EbMachine* machine2, int n2);

/**
    function which checks if two LBAMTT devices are the same
    @param device1 puntatore a LBAMTTdevice
    @param device2 puntatore a LBAMTTdevice
    @return true se i device sono uguali
**/
bool eb_devicesLBAMTT_are_equal(LBAMTTdevice* device1, LBAMTTdevice* device2);

/**
    function which checks if two EB devices are the same
    @param device1 puntatore a EBdevice
    @param device2 puntatore a EBdevice
    @return true se i device sono uguali
**/
bool eb_devicesEB_are_equal(EbDevice* device1, EbDevice* device2);

/**
    funzione che ritorna il numero di ripetizioni di stringa in una stringa più lunga
    serve per calcolare il numero di coppie di device presenti in una stringa svg di un machine
    @param pat stringa da cercare e contare
    @param txt stringa dove ricercare pat
    @return numero di ripetizioni
**/
int eb_count_stringOccurences(string &pat, string &txt);


#endif