#include <iostream>
#include <iostream>
#include <string.h>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

#include "include/EB_Device.h"
#include "include/LBAMTTBiellaManovella.h"
#include "include/EB_Machine.h"



using namespace std;

void eb_printParameters(EbDevice* device);

void eb_draw_device();

void eb_draw_machine(int n);

void eb_comparaMachine();

void eb_caricaCarrelloGru();


int main() {
    
    int n ; //numero di coppie di device nella machine

    char choice1;
    char choice3;
    string svg;
    string nomefileCaricare;
    string nomefileSalvare;
    EbMachine* machineCaricata;
    string pat, svg_to_save;
    int n1;
    

    cout<<"Ben arrivato!!"<<endl;
    cout<<"Cosa vuoi fare??"<<endl;
    do{
        cout<<endl<<endl;
        cout<<"Possibili scelte: "<<endl;
        cout<<"1 -> costruire singolo device carrello-gru\n2 -> costruire machine composta da biella-manovella + carello-gru\n";
        cout<<"3 -> caricare da file una machine e salvarla su un file diverso\n4 -> controllare se due machine sono uguali\n";
        cout<<"5 -> caricare parametri di un carrello-gru da file già presente\naltro tasto per uscire"<<endl;
        cin>>choice1;

        switch (choice1){
            case '1':
                eb_draw_device();
            
            break;
            case '2':
                cout<<"Nella tua machine quante coppie di biella-manovella + carrelo-gru vuoi??"<<endl;
                cin>>n;
                eb_draw_machine(n);

            break;
            case '3':
                cout<<"Dimmi nome del file della machine da caricare (ricordati .svg):"<<endl;
                cin>>nomefileCaricare;
                svg = eb_read_from_file(nomefileCaricare);
                machineCaricata = eb_machine_parse(svg);
                cout<<"Dimmi nome del file dove salvare la machine:"<<endl;
                cin>>nomefileSalvare;

                pat = "g transform"; 
                n1 = eb_count_stringOccurences(pat, svg)/2;

                svg_to_save=eb_machine_to_svg(machineCaricata,n1);
                eb_save_to_file(svg_to_save,nomefileSalvare);

            break;
            case '4':
                eb_comparaMachine();
            break;
            case '5':
                eb_caricaCarrelloGru();
            break;
            default: 
                cout<<"Arrivederci e alla prossima!!"<<endl;
            break;
        }
    }while(choice1 == '1' || choice1 == '2' || choice1 == '3' || choice1 == '4' || choice1 == '5');
    
    return 0;
}

/**
    A function which print the 5 parameters of a device 
**/
void eb_printParameters(EbDevice* device){
    cout<<"5 fondamental parameters are: "<<endl;
    cout<<"Length shaft: "<<device -> length_shaft<<endl;
    cout<<"Width_towtruck: "<<device -> width_towtruck<<endl;
    cout<<"Width_platform: "<<device -> width_platform<<endl;
    cout<<"Angle of rotation: "<<device -> rotation<<endl;
    cout<<"Sliding: "<<device -> sliding<<endl;
}

void eb_draw_device(){
    EbDevice* MyDevice = new EbDevice;
    double length_shaft;
    double width_towtruck;
    double width_platform;
    double rotation;
    double sliding;
    string errormsg="ERROR 404: mechanical constraints exceeded";

    
    cout<<"You are going to 'build' a really nice device..."<<endl<<"You must insert 5 fondamental parameters..."<<endl;
    cout<<"Length shaft: ";
    cin>>length_shaft;
    cout<<endl<<"Width towtruck: ";
    cin>>width_towtruck;
    cout<<endl<<"Width_platform: ";
    cin>>width_platform;
    cout<<endl<<"Rotation: ";
    cin>>rotation;
    cout<<endl<<"Sliding: ";
    cin>>sliding;
    cout<<endl;

    MyDevice=eb_init(length_shaft,width_towtruck,width_platform,rotation,sliding);
    if(MyDevice==NULL){
        cout<<errormsg<<endl;
        exit(1);
    }
        
    eb_printParameters(MyDevice);
    
    bool with_measures;
    string filename;
    cout<<"A file svg will be created now, tell me the name of your file: ";
    cin>>filename;
    cout<<endl;
    cout<<"Do you want the drawing with the measurements? No->0; Yes->1 ";
    cin>>with_measures;
    cout<<endl;
    if(eb_to_svg(MyDevice,with_measures)==""){
        cout<<"ERROR 404: draw constraints exceeded"<<endl;
        exit(1);
    }
    eb_save_to_file(eb_to_svg(MyDevice,with_measures),filename);
    cout<<"The file has been created succesfully!!Check it in your program's folder"<<endl;
    cout<<endl;
    
    char choice;
    cout<<"You can change parameters..."<<endl;
    do{
        cout<<"Press 1 to set a new length shaft, "<<endl;
        cout<<"Press 2 to set a new width towtruck, "<<endl;
        cout<<"Press 3 to set a new width platform, "<<endl;
        cout<<"Press 4 to set a new rotation, "<<endl;
        cout<<"Press 5 to set a new sliding, "<<endl;
        cout<<"Press any letter to keep last version of the device."<<endl;
        cin>>choice;

        double new_parameter;

        switch(choice){
            case '1':
                cout<<"Write a new length shaft: ";
                cin>>new_parameter;
                cout<<endl;
                eb_set_lengthShaft(MyDevice,new_parameter);
                if(eb_set_lengthShaft(MyDevice,new_parameter)==1){
                    cout<<"ATTENTION!The new parameter doesn't respect the mechanical constraints, so there will be no changes"<<endl;
                }
                else{
                    if(eb_to_svg(MyDevice,with_measures)==""){
                        cout<<"ERROR 404: draw constraints exceeded"<<endl;
                        exit(1);
                    }
                    cout<<"Do you want the drawing with the measurements? No->0; Yes->1 ";
                    cin>>with_measures;
                    eb_save_to_file(eb_to_svg(MyDevice,with_measures),filename);
                    cout<<"Nice! Check if the new device is good for you!"<<endl;
                    cout<<endl;
                }
                break;
            case '2':
                cout<<"Write a new width towtruck: ";
                cin>>new_parameter;
                cout<<endl;
                eb_set_widthTowtruck(MyDevice,new_parameter);
                if(eb_set_widthTowtruck(MyDevice,new_parameter)==1){
                    cout<<"ATTENTION!The new parameter doesn't respect the mechanical constraints, so there will be no changes"<<endl;
                }
                else{
                    if(eb_to_svg(MyDevice,with_measures)==""){
                        cout<<"ERROR 404: draw constraints exceeded"<<endl;
                        exit(1);
                    }
                    cout<<"Do you want the drawing with the measurements? No->0; Yes->1 ";
                    cin>>with_measures;
                    eb_save_to_file(eb_to_svg(MyDevice,with_measures),filename);
                    cout<<"Nice! Check if the new device is good for you!"<<endl;
                    cout<<endl;
                }
                break;
            case '3':
                cout<<"Write a new width platform: ";
                cin>>new_parameter;
                cout<<endl;
                eb_set_widthPlatform(MyDevice,new_parameter);
                if(eb_set_widthPlatform(MyDevice,new_parameter)==1){
                    cout<<"ATTENTION!The new parameter doesn't respect the mechanical constraints, so there will be no changes"<<endl;
                }
                else{
                    if(eb_to_svg(MyDevice,with_measures)==""){
                        cout<<"ERROR 404: draw constraints exceeded"<<endl;
                        exit(1);
                    }
                    cout<<"Do you want the drawing with the measurements? No->0; Yes->1 ";
                    cin>>with_measures;
                    eb_save_to_file(eb_to_svg(MyDevice,with_measures),filename);
                    cout<<"Nice! Check if the new device is good for you!"<<endl;
                    cout<<endl;
                }
                break;
            case '4':
                cout<<"Write a new rotation: ";
                cin>>new_parameter;
                cout<<endl;
                eb_set_rotation(MyDevice,new_parameter);
                if(eb_set_rotation(MyDevice,new_parameter)==1){
                    cout<<"ATTENTION!The new parameter doesn't respect the mechanical constraints, so there will be no changes"<<endl;
                    cout<<endl;
                }
                else{
                    if(eb_to_svg(MyDevice,with_measures)==""){
                        cout<<"ERROR 404: draw constraints exceeded"<<endl;
                        exit(1);
                    }
                    cout<<"Do you want the drawing with the measurements? No->0; Yes->1 ";
                    cin>>with_measures;
                    eb_save_to_file(eb_to_svg(MyDevice,with_measures),filename);
                    cout<<"Nice! Check if the new device is good for you!"<<endl;
                    cout<<endl;
                }
                break;
            case '5':
                cout<<"Write a new sliding: ";
                cin>>new_parameter;
                cout<<endl;
                eb_set_sliding(MyDevice,new_parameter);
                if(eb_set_sliding(MyDevice,new_parameter)==1){
                    cout<<"ATTENTION!The new parameter doesn't respect the mechanical constraints, so there will be no changes"<<endl;
                    cout<<endl;
                }
                else{
                    if(eb_to_svg(MyDevice,with_measures)==""){
                        cout<<"ERROR 404: draw constraints exceeded"<<endl;
                        exit(1);
                    }
                    cout<<"Do you want the drawing with the measurements? No->0; Yes->1 ";
                    cin>>with_measures;
                    eb_save_to_file(eb_to_svg(MyDevice,with_measures),filename);
                    cout<<"Nice! Check if the new device is good for you!"<<endl;
                    cout<<endl;
                }
                break;                
            default:
                cout<<"It's been a pleasure, see you soon"<<endl;
        }

    }while(choice=='1' || choice=='2' || choice=='3' || choice=='4'|| choice=='5');
}


void eb_draw_machine(int n){

    double XposMachine;
    cout<<"Dimmi la posizione iniziale x della tua machine: ";
    cin>>XposMachine;
    cout<<endl;
     
    double* dShaft = new double [n];
    double* stroke = new double [n];
    double* lenBiella = new double [n];
    double* wBiella = new double [n];
    double* hPistone = new double [n];
    double* dPistone = new double [n];
    double* angle = new double [n];

    cout<<endl;
    cout<<"Definisci ora i parametri per "<<n<<" bielle-manovelle: ";
    for(int i=0;i<n;i++){
        cout<<endl<<"Diametro albero motore per device num ( "<<i+1<<" ): ";
        cin>>dShaft[i];
        cout<<endl<<"Corsa del pistone per device num ( "<<i+1<<" ): ";
        cin>>stroke[i];
        cout<<endl<<"Lunghezza biella per device num ( "<<i+1<<" ): ";
        cin>>lenBiella[i];
        cout<<endl<<"Larghezza biella per device num ( "<<i+1<<" ): ";
        cin>>wBiella[i];
        cout<<endl<<"Altezza pistone per device num ( "<<i+1<<" ): ";
        cin>>hPistone[i];
        cout<<endl<<"Larghezza pistone per device num ( "<<i+1<<" ): ";
        cin>>dPistone[i];
        cout<<endl<<"Angolo manovella per device num( "<<i+1<<" ): ";
        cin>>angle[i];
    }
    cout<<endl;

    double* sliding = new double [n];
    double* length_shaft = new double [n];
    double* width_towTruck = new double [n];
    double* width_platform = new double [n];
    double* rotation = new double [n];

    cout<<"Definisci ora i parametri per "<<n<<" carrelo-gru: "<<endl;
    for(int i=0;i<n;i++){
        cout<<"Length shaft per device num ( "<<i+1<<" ): ";
        cin>>length_shaft[i];
        cout<<endl<<"Width towtruck per device num ( "<<i+1<<" ): ";
        cin>>width_towTruck[i];
        cout<<endl<<"Width_platform per device num ( "<<i+1<<" ): ";
        cin>>width_platform[i];
        cout<<endl<<"Rotation per device num ( "<<i+1<<" ): ";
        cin>>rotation[i];
    }
    
    EbMachine* eb_machine;
    eb_machine = eb_machine_init(XposMachine, n, dShaft, stroke, lenBiella, wBiella, hPistone, dPistone, angle, length_shaft, width_towTruck, width_platform, rotation);
    if(eb_machine==NULL){
        cout<<"ERROR 404!!!"<<endl;
        exit(1);
    }

    if(eb_machine_to_svg(eb_machine,n)==""){
        cout<<"ERROR 808: ci sono stati alcuni problemi nel disegno"<<endl;
        exit(1);
    }
    string filename;
    cout<<"Dimmi nome del file dove vuoi salvare la tua machine: "<<endl;
    cin>>filename;

    eb_save_to_file(eb_machine_to_svg(eb_machine,n),filename);
    cout<<endl;
    cout<<"The file has been created succesfully!!Check it in your program's folder"<<endl;
    cout<<endl;
}

void eb_comparaMachine(){
    string file1, file2;
    string pat;
    string svg1, svg2;
    EbMachine* eb_machine1 = new EbMachine;
    EbMachine* eb_machine2 = new EbMachine;
    pat = "g transform"; 

    cout<<"Dimmi nome del file della prima machine(ricordati .svg):"<<endl;
    cin>>file1;
    svg1=eb_read_from_file(file1);    
    eb_machine1= eb_machine_parse(svg1);
    int n1 = eb_count_stringOccurences(pat, svg1)/2;

    cout<<"Dimmi nome del file della seconda machine(ricordati .svg):"<<endl;
    cin>>file2;
    svg2=eb_read_from_file("machine2.svg");    
    eb_machine2= eb_machine_parse(svg2);
    int n2 = eb_count_stringOccurences(pat, svg2)/2;
    
    if(eb_machine_are_equal(eb_machine1,n1,eb_machine2,n2)==true){
        cout<<"Le sono machine uguali!!"<<endl;
    }
    else{   
        cout<<"NOPE!! Machine diverse!"<<endl;
    }
}

void eb_caricaCarrelloGru(){
    EbDevice* MyDevice = new EbDevice;
    EbDevice* deviceRead = new EbDevice;
    string fileToRead;
    cout<<endl<<"Tell me the name(and extension) of the file you want to load and create a struct Device: ";
    cin>>fileToRead;
    string svg=eb_read_from_file(fileToRead);
    deviceRead=eb_parse(svg);
    if(deviceRead==NULL){
        cout<<"errormsg"<<endl;
        exit(1);
    }
    
    cout<<endl<<"Parameters of the \"carrello-gru\" load from file: "<<endl;
    eb_printParameters(deviceRead);
    eb_destroy_device(MyDevice);
}