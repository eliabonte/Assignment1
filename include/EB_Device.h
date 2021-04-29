#ifndef EB_DEVICE_H
#define EB_DEVICE_H

#include <iostream>
#include <string.h>
#include <string>


using namespace std;

/**
 * 
 * A struct representing the device  
**/
struct EbDevice {
    double length_shaft;
    double width_towtruck;
    double width_platform;
    double rotation;
    double sliding;
};

/**
    A function initing a device
    @param length_shaft lunghezza asta
    @param width_towtruck larghezza carrello
    @param width_platform larghezza piattafotma
    @param rotation angolo di rotazione asta rispetto all'asse y, positivo rotazione in senso orario
    @param sliding scorrimento carrello sull'asse orizzontale
    @return puntatore alla struct EbDevice
**/
EbDevice* eb_init(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding);

/**
    A function checking mechanical costraints
    @param length_shaft lunghezza asta
    @param width_towtruck larghezza carrello
    @param width_platform larghezza piattafotma
    @param rotation angolo di rotazione asta rispetto all'asse y, positivo rotazione in senso orario
    @param sliding scorrimento carrello sull'asse orizzontale
    @return boolean, se ritorna true i vincoli meccanici sono rispettati
**/
bool eb_checkConstraints(double length_shaft, double width_towtruck, double width_platform, double rotation, double sliding);


/**
    A function checking costraints in relation to the svg draw
    @param eb_device puntatore alla struct EbDevice
    @return boolean, se ritorna true i vincoli riguardanti il disegno sono rispettati, il device è nel foglio
**/
bool eb_drawConstraints(EbDevice* eb_device);


/**
    A function which produce a string with svg code
    if with_measures is true the drawing will include measurements
    @param eb_device puntatore alla struct EbDevice
    @param with_measures è true se l'utente vuole disegno con misure
    @return string con codice svg
**/
string eb_to_svg(EbDevice* eb_device, bool with_measures);

/**
    A function which calculate coordinate X of CiR
    @param eb_device puntatore alla struct EbDevice
    @return coordinata x centro istantanea rotazione
**/
double eb_Xcir(EbDevice* eb_device);


/**
    A function which calculate coordinate X of the platform
    @param eb_device puntatore alla struct EbDevice
    @return coordinata x piattaforma
**/
double eb_Xplatform(EbDevice* eb_device);


/**
    A function which calculate coordinate Y of the platform
    @param eb_device puntatore alla struct EbDevice
    @return coordinata y piattaforma
**/
double eb_Yplatform(EbDevice* eb_device);


/**
    Sets a new length_shaft in the structure
    @param device puntatore alla struct EbDevice
    @param new_length_shaft nuova lunghezza
    @return 1,if the new length is incompabile with other measures, otherwise 0
**/
int eb_set_lengthShaft(EbDevice* device, double new_length_shaft);

/**
    Sets a new length_shaft in the structure
    @param device puntatore alla struct EbDevice
    @param new_width_towtruck nuova lunghezza
    @return 1,if the new length is incompabile with other measures, otherwise 0
**/
int eb_set_widthTowtruck(EbDevice* device, double new_width_towtruck);

/**
    Sets a new length_shaft in the structure
    @param device puntatore alla struct EbDevice
    @param new_width_platform nuova lunghezza
    @return 1,if the new length is incompabile with other measures, otherwise 0
**/
int eb_set_widthPlatform(EbDevice* device, double new_width_platform);

/**
    Sets a new length_shaft in the structure
    @param device puntatore alla struct EbDevice
    @param new_rotation nuova lunghezza
    @return 1,if the new length is incompabile with other measures, otherwise 0
**/
int eb_set_rotation(EbDevice* device, double new_rotation);

/**
    Sets a new length_shaft in the structure
    @param device puntatore alla struct EbDevice
    @param new_sliding nuova lunghezza
    @return 1,if the new length is incompabile with other measures, otherwise 0
**/
int eb_set_sliding(EbDevice* device, double new_sliding);


/**
    A function which write on a file svg
    @param stringToWrite stringa da salvare sul file
    @param filenmae nome del file dove salvare
**/
void eb_save_to_file(string stringToWrite, string filename);

/**
    function, which creates a struct from a SVG textual representation
    @param svg stringa con codice svg 
    @return puntatore a EbDevice con parametri letti dal file
**/
EbDevice* eb_parse(string svg);

/**
    A function which read from a file a string
    @param filename nome dal file da leggere
    @return stringa letta dal file
**/
string eb_read_from_file(string filename);

/**
    function which destroy the device
    @param device puntatore a EbDevice
    @return 0 se operazione è andata a buon fine, altrimenti 1
**/
int eb_destroy_device(EbDevice* device);

#endif //DEVICE_H
