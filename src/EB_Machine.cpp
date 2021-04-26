#include "../include/EB_Machine.h"
#include "../include/EB_Device.h"
#include "../include/LBAMTTBiellaManovella.h"
#include <iostream>
#include <string.h>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

using namespace std;


EbMachine* eb_machine_init(double xpos, EbDevice* carrelloGru, LBAMTTdevice* biellaManovella, int n){
    
    EbMachine* eb_machine = new EbMachine;
    eb_machine->xpos=xpos;

    eb_machine->arrBiellaManovella = new LBAMTTdevice* [n];  //array dinamico di puntatori alla struct LBAMTTdevice
    eb_machine->arrCarrelloGru = new EbDevice* [n]; //array dinamico di puntatori alla struct EbDevice
   
    double sliding = eb_sliding(xpos,biellaManovella->stroke,biellaManovella->lenBiella, biellaManovella->angle, biellaManovella->wBiella);

    eb_machine->arrBiellaManovella[0]=LBAMTTinitDevice(biellaManovella->angle,biellaManovella->dPistone,biellaManovella->dShaft,biellaManovella->hPistone,biellaManovella->lenBiella,biellaManovella->stroke,biellaManovella->wBiella);
    eb_machine->arrCarrelloGru[0]=eb_init(carrelloGru->length_shaft,carrelloGru->width_towtruck,carrelloGru->width_platform,sliding,carrelloGru->rotation);


    return eb_machine;
}

double eb_sliding(double posShaft, double stroke, double lenBiella, double angle, double wBiella){
    double sliding;
    double L1 = stroke/2; //lunghezza manovella
    double L2 = lenBiella;  
    double q = PI/2 - angle * PI / 180.0; //angolo manovella in radianti
    sliding = (posShaft + sqrt(pow(L2, 2) - pow(L1 * cos(q), 2)) + L1 * sin(q)) + wBiella*7/10;

}