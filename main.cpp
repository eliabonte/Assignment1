#include <iostream>

#include "include/EB_Device.h"
#include "include/LBAMTTBiellaManovella.h"
#include "include/EB_Machine.h"


using namespace std;

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

int main() {
    
    EbMachine* eb_machine = new EbMachine;
    double XposMachine = 200;
    int n =2 ; //numero di coppie di device nella machine
    LBAMTTdevice** arrBiellaManovella;
    EbDevice** arrCarrelloGru;

    arrBiellaManovella = new LBAMTTdevice* [n];
    arrCarrelloGru = new EbDevice* [n];

    double dShaft = 60;
    double stroke = 150;
    double lenBiella = 150;
    double wBiella = 30;
    double hPistone = 50;
    double dPistone = 75;
    double angle = 30;

    arrBiellaManovella[0] = LBAMTTinitDevice(dShaft,stroke,lenBiella,wBiella,hPistone,dPistone,angle);
    arrBiellaManovella[1] = LBAMTTinitDevice(dShaft,stroke,lenBiella,wBiella,hPistone,dPistone,angle);

    double* sliding = new double [n];

    double length_shaft = 350;
    double width_towTruch = 100;
    double width_platform = 150;
    double rotation = -30;

    double* xShafts = new double [n];
    xShafts[0] = XposMachine;
   
    for(int i=0;i<n;i++){
        if(i>0){
            xShafts[i] = eb_cxShaft(arrCarrelloGru[i-1]);
        }
        sliding[i] = eb_sliding(xShafts[i] + arrBiellaManovella[i]->dShaft/2,arrBiellaManovella[i]->stroke,arrBiellaManovella[i]->lenBiella,arrBiellaManovella[i]->angle,arrBiellaManovella[i]->hPistone,arrBiellaManovella[i]->wBiella);
        arrCarrelloGru[i] = eb_init(length_shaft,width_towTruch,width_platform,rotation,sliding[i]);
    }

    eb_machine = eb_machine_init(XposMachine, arrBiellaManovella, arrCarrelloGru,1);

    string svg = eb_machine_to_svg(eb_machine,n);
    eb_save_to_file(svg,"machine");


    delete [] sliding;
    delete [] arrBiellaManovella;
    delete [] arrCarrelloGru;
    
    
    /*
    device = LBAMTTinitDevice(dShaft, stroke, lenBiella, wBiella, hPistone, dPistone, angle);
    if(device == NULL) cout << "errore parametri" << endl;
    else{
        //cout << LBAMTTtoStringSVG(device);
        LBAMTTsaveToFile(LBAMTTdeviceToStringSVG(device, 400, 200, false),"prova-biella-manovella1.svg");
        LBAMTTsetAngle(device, 300);
        LBAMTTsaveToFile(LBAMTTdeviceToStringSVG(device, 400, 200, false),"prova-biella-manovella2.svg");
    }

    //LBAMTTsaveToFile(LBAMTTdeviceToStringSVG(LBAMTTdeviceFromStringSVG(LBAMTTloadFromFile("prova-biella-manovella1.svg")), 400, 200, true), "copia-biella-manovella1.svg");


    /*
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

    EbDevice* deviceRead = new EbDevice;
    string fileToRead;
    cout<<endl<<"Tell me the name(and extension) of the file you want to load and create a struct Device: ";
    cin>>fileToRead;
    string svg=eb_read_from_file(fileToRead);
    deviceRead=eb_parse(svg);
    if(deviceRead==NULL){
        cout<<errormsg<<endl;
        exit(1);
    }
    
    cout<<endl<<"Parameters of the svg load from file: "<<endl;
    eb_printParameters(deviceRead);
    */
    return 0;
}
