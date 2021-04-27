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


EbMachine* eb_machine_init(double XposMachine, int n, double* dShaft, double* stroke, double* lenBiella, double* wBiella, double* hPistone, double* dPistone, double* angle,
                            double* length_shaft, double* width_towtruck, double* width_platform, double* rotation){
    
    EbMachine* eb_machine = new EbMachine;
    LBAMTTdevice** arrBiellaManovella = new LBAMTTdevice* [n];  //array dinamico di puntatori alla struct LBAMTTdevice
    EbDevice** arrCarrelloGru = new EbDevice* [n];  //array dinamico di puntatori alla struct EbDevice

    eb_machine->XposMachine=XposMachine;

    //inizializzazione devices biella-manovella
    for(int i=0;i<n;i++){
        arrBiellaManovella[i]=LBAMTTinitDevice(dShaft[i],stroke[i],lenBiella[i],wBiella[i],hPistone[i],dPistone[i],angle[i]);
    }
   
    double* sliding = new double [n];
    double* xShafts = new double [n];
    xShafts[0]=eb_machine->XposMachine;

    //definisco vettore delle x dei centri degli alberi nella machine, degli sliding del carrello e arrCarrelloGru
    for(int i=0;i<n;i++){
        if(i>0){
            xShafts[i] = eb_cxShaft(arrCarrelloGru[i-1]);
        }
        sliding[i] = eb_sliding(xShafts[i], arrBiellaManovella[i]->stroke,arrBiellaManovella[i]->lenBiella,arrBiellaManovella[i]->angle,arrBiellaManovella[i]->hPistone,arrBiellaManovella[i]->wBiella);
        
        arrCarrelloGru[i]=eb_init(length_shaft[i],width_towtruck[i],width_platform[i],rotation[i],sliding[i]);
    }

    
    eb_machine->arrBiellaManovella = arrBiellaManovella;  
    eb_machine->arrCarrelloGru = arrCarrelloGru; 

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

string eb_machine_to_svg(EbMachine* machine, int n){

    string machine_svg="";
    double* xShafts = new double [n];
    double* yShafts = new double [n];

    xShafts[0]=machine->XposMachine;
    yShafts[0]=std_YposMachine;

    //definisco vettore delle x e y dei centri degli alberi nella machine
    for(int i=1;i<n;i++){
        xShafts[i] = eb_cxShaft(machine->arrCarrelloGru[i-1]);
        yShafts[i] = eb_cyShaft(machine->arrCarrelloGru[i-1],machine->arrBiellaManovella[i]);
    }

    /*
        creo la stringa machine_svg
    */
    machine_svg += "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\n"
                  "<svg xmlns=\"http://www.w3.org/2000/svg\" style=\"background-color:white\" width=\"1500\" height=\"1000\" >\n\n";
    for(int i=0;i<n;i++){
        machine_svg += eb_new_LBAMTTdeviceToStringSVG(machine->arrBiellaManovella[i],xShafts[i],yShafts[i]); 
        machine_svg += eb_new_to_svg(machine->arrCarrelloGru[i],yShafts[i]);
    }

    machine_svg += "</svg>";

    return  machine_svg;
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

string eb_new_to_svg(EbDevice* eb_device, double yShaft){
    const double std_shaftWidth = 20;
    const double std_towtruckHeight = 40;
    const double std_platformHeight = 20;
    const double std_radius=10;

    double Ycir = yShaft;
    double YtowTruck = Ycir-std_towtruckHeight/2;
    
    if(eb_drawConstraints(eb_device)==false){
        return "";
    }
    
    /*parametri device*/
    double sliding=eb_device->sliding;
    double length=eb_device->length_shaft;
    double angle=eb_device->rotation; 
    double widthPla=eb_device->width_platform;
    double widthTt=eb_device->width_towtruck;

    /*variabili utili*/
    double Xcir=eb_Xcir(eb_device);
    double Xplatform=eb_Xplatform(eb_device);

    double angleGru=eb_device->rotation * (M_PI/180);  //necessario angolo in radianti nella funzione seno
    double Yplatform=Ycir + eb_device->length_shaft*cos(angleGru) - (std_platformHeight/2);

    string code="";
    
    /*
        carrello gru con spostamento orizzontale
    */
    code+="<g>\n";
    code+="<rect x = \""+to_string(sliding)+"\" y = \""+to_string(YtowTruck)+"\" width = \"" + to_string(widthTt) +"\" height = \""+to_string(std_towtruckHeight)+"\" stroke = \"black\" stroke-width = \"3\" fill = \"yellow\"/>\n";
    code+="</g>\n\n";

    /*
        asta rotante, 
        angolo positivo --> asta ruota in senso orario(verso sx)
        angolo negativo --> asta ruota in senso antiorario(verso dx)
    */
    code+="<g transform  = \"rotate("+to_string(angle)+","+to_string(Xcir)+","+to_string(Ycir)+")\">\n";
    code+="<rect x = \""+to_string(Xcir-std_radius)+"\" y = \""+to_string(Ycir)+"\" width = \""+to_string(std_shaftWidth)+"\" height = \"" + to_string(length) + "\" stroke = \"black\" stroke-width = \"3\" fill = \"orange\" />\n";
    code+="<circle cx = \""+to_string(Xcir)+"\" cy = \""+to_string(Ycir)+"\" r = \""+to_string(std_radius)+"\" stroke = \"black\" stroke-width = \"3\" fill = \"white\"/>\n";
    code+="</g>\n\n";

    /*
        piattaforma
    */
    code+="<g>\n";
    code+="<rect x = \""+to_string(Xplatform)+"\" y = \""+to_string(Yplatform)+"\" width = \""+to_string(widthPla)+"\" height = \"20\"  stroke = \"black\" stroke-width = \"3\" fill = \"black\" />\n";
    code+="</g>\n\n";

    return code;
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
