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

const double std_YposMachine = 100;


EbMachine* eb_machine_init(double XposMachine, LBAMTTdevice** biellaManovella,  EbDevice** carrelloGru, int n){
    
    EbMachine* eb_machine = new EbMachine;
    eb_machine->XposMachine=XposMachine;

    eb_machine->arrBiellaManovella = biellaManovella;  //array dinamico di puntatori alla struct LBAMTTdevice
    eb_machine->arrCarrelloGru = carrelloGru; //array dinamico di puntatori alla struct EbDevice

    return eb_machine;
}

double eb_sliding(double cxShaft, double stroke, double lenBiella, double angle, double hPistone, double wBiella){
    double sliding;
    double L1 = stroke/2; //lunghezza manovella
    double L2 = lenBiella;  
    double q = PI/2 - angle * PI / 180.0; //angolo manovella in radianti

    double distShaftPist = sqrt(pow(L2, 2) - pow(L1 * cos(q), 2)) + L1 * sin(q) - wBiella*7/10;

    sliding = cxShaft + distShaftPist + hPistone;


    return sliding;

}
string eb_new_LBAMTTdeviceToStringSVG (LBAMTTdevice * device, double cxShaft, double cyShaft, bool header){

    //controllo sia stato passato un device
    if(device == NULL) return "";

    double cxBiella, cyBiella; //coordinate centro coppia biella-manovella
    double cxPistone, cyPistone; //coordinate cetro coppia biella-pistone
    double L1 = device->stroke/2; //lunghezza manovella
    double L2 = device->lenBiella;  
    double q = PI/2 - device->angle * PI / 180.0; //angolo manovella in radianti
    double theta = atan2(-L1 * cos(q) / L2, sqrt(pow(L2, 2) - pow(L1 * cos(q), 2)) / L2); //angolo biella in radianti
    
    cxBiella = cxShaft + L1 * cos(q);
    cyBiella = cyShaft + L1 * sin(q);
    cxPistone = cxShaft;
    cyPistone = cyShaft + sqrt(pow(L2, 2) - pow(L1 * cos(q), 2)) + L1 * sin(q);

    string deviceSVG = "";
 
    deviceSVG += "<g transform = \"rotate(-90,"+to_string(cxShaft)+","+to_string(cyShaft)+")\">\n\n";

    //biella
    deviceSVG += LBAMTTrectSVG(cxBiella, cyBiella - device->wBiella/2, 
                               L2, device->wBiella, 
                               "blue", 
                               90 - theta * 180 / PI, cxBiella, cyBiella);
    deviceSVG += "\n"; 

    //pistone
    deviceSVG += LBAMTTrectSVG(cxPistone - device->dPistone/2, cyPistone - device->wBiella*7/10, 
                               device->dPistone, device->hPistone, 
                               "red");
    deviceSVG += "\n"; 

    //manovella
        //cerchio albero
    deviceSVG += LBAMTTcircleSVG(cxShaft, cyShaft, 
                                 device->dShaft*7/10, 
                                 "green");
    deviceSVG += "\n"; 
        //cerchio coppia biella-manovella
    deviceSVG += LBAMTTcircleSVG(cxBiella, cyBiella, 
                                 device->wBiella*7/10, 
                                 "green");
    deviceSVG += "\n"; 
        //rettangolo che collega i due cerchi
    deviceSVG += LBAMTTrectSVG(cxShaft, cyShaft - device->wBiella*7/10, 
                               L1, device->wBiella*7/5, 
                               "green", 
                               q * 180 / PI, cxShaft, cyShaft);
    deviceSVG += "\n"; 

    //albero
    deviceSVG += LBAMTTcircleSVG(cxShaft, cyShaft, 
                                 device->dShaft/2, 
                                 "gray");
    deviceSVG += "\n"; 

    //coppie biella
        //manovella
    deviceSVG += LBAMTTcircleSVG(cxBiella, cyBiella, 
                                 device->wBiella/2, 
                                 "Blue");
    deviceSVG += "\n"; 
        //pistone
    deviceSVG += LBAMTTcircleSVG(cxPistone, cyPistone, 
                                 device->wBiella/2, 
                                 "Blue");
    deviceSVG += "\n"; 

    deviceSVG += "</g>\n"; 
    
    return deviceSVG;
}

string eb_machine_to_svg(EbMachine* machine, int n){

    string machine_svg="";
    string biellaManovella_svg1;
    string carrelloGru_svg1;

    double cxShaft1 = machine->XposMachine + machine->arrBiellaManovella[0]->dShaft/2;
    double cyShaft1 = std_YposMachine + machine->arrBiellaManovella[0]->dShaft/2;

    biellaManovella_svg1 = eb_new_LBAMTTdeviceToStringSVG(machine->arrBiellaManovella[0],cxShaft1,cyShaft1);
    carrelloGru_svg1= eb_to_svg(machine->arrCarrelloGru[0],false,true);
    
    if(biellaManovella_svg1 == "" || carrelloGru_svg1 == ""){
        return "";
    }

    machine_svg = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\n"
                  "<svg xmlns=\"http://www.w3.org/2000/svg\" style=\"background-color:white\" width=\"1500\" height=\"1000\" >\n\n";
    
    if(n>1){
        double* xShafts = new double [n];
        xShafts [0] = machine->XposMachine;
        double* yShafts = eb_yShafts(std_YposMachine, n, machine->arrCarrelloGru, machine->arrBiellaManovella);
        for(int i=1;i<=n;i++){
            xShafts[i] = eb_cxShaft(machine->arrCarrelloGru[i-1]);
            machine_svg += eb_new_LBAMTTdeviceToStringSVG(machine->arrBiellaManovella[i],xShafts[i],yShafts[i]); 
            machine_svg += eb_to_svg(machine->arrCarrelloGru[i],false,true);
        }
        delete [] xShafts;
        delete [] yShafts;
    }
    else{
        machine_svg += biellaManovella_svg1;
        machine_svg += carrelloGru_svg1;
    }
    machine_svg += "</svg>";

    return  machine_svg;
}

double eb_cxShaft(EbDevice* carrelloGru){

    double xPlatform = eb_Xplatform(carrelloGru);

    double cxShaft = xPlatform + carrelloGru->width_platform/2;

    return cxShaft;
}

double eb_cyShaft(EbDevice* carrelloGru, LBAMTTdevice* biellaManovella){

    double yPlatform = eb_Yplatform(carrelloGru);

    double cyShaft = yPlatform - biellaManovella->dShaft*7/10;
    
    return cyShaft;
}

/*
    funzione che ritorna un puntatore all'array dinamico che contiente le pos y degli alberi presenti nella machine
*/
double* eb_yShafts(double YposMachine, int n, EbDevice** arrCarrelloGru,LBAMTTdevice** arrBiellaManovella){
    double* yShafts;
    yShafts = new double [n];
    yShafts[0] = YposMachine;
    for(int i=1; i<n; i++){
        yShafts[i]=eb_cyShaft(arrCarrelloGru[i-1],arrBiellaManovella[i]);
    }

    return yShafts;
}