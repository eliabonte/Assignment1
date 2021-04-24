#include <iostream>

#include "device.h"
#include <string.h>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

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
    string svg=eb_read_from_file("deviceToRead.svg");
    deviceRead=eb_parse(svg);
    if(deviceRead==NULL){
        cout<<errormsg<<endl;
        exit(1);
    }
    
    cout<<endl<<"Parameters of the svg load from file: "<<endl;
    cout<<deviceRead->length_shaft<<" , "<<deviceRead->width_towtruck<<" , "<<deviceRead->width_platform<<" , "<<deviceRead->rotation<<" , "<<deviceRead->sliding<<endl;
    
    return 0;
}
