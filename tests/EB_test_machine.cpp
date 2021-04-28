
#include "catch2/catch2.hpp"
#include "../include/EB_Device.h"
#include "../include/LBAMTTBiellaManovella.h"
#include "../include/EB_Machine.h"



using namespace std;

TEST_CASE("init should create a new struct EbMachine","[EbMachine]"){

    int n=2;
    double* dShaft = new double [n];
    double* stroke = new double [n];
    double* lenBiella = new double [n];
    double* wBiella = new double [n];
    double* hPistone = new double [n];
    double* dPistone = new double [n];
    double* angle = new double [n];

    for(int i=0;i<n;i++){
        dShaft[i] = 60;
        stroke[i] = 150;
        lenBiella[i] =  150;
        wBiella[i] = 30;
        hPistone[i] = 50;
        dPistone[i] = 75;
        angle[i] = 40;
    }

    double* sliding = new double [n];
    double* length_shaft = new double [n];
    double* width_towTruck = new double [n];
    double* width_platform = new double [n];
    double* rotation = new double [n];
    
    for(int i=0;i<n;i++){
        length_shaft[i]=350;
        width_towTruck[i]=100;
        width_platform[i]=150;
        rotation[i]=-30;
    }
    double XposMachine=100;

    EbMachine* machine = eb_machine_init(XposMachine, n, dShaft, stroke, lenBiella, wBiella, hPistone, dPistone, angle, length_shaft, width_towTruck, width_platform, rotation);

    REQUIRE(machine!=NULL);

}

/*
    some tests regarding the function eb_checkConstraints which check mechanical constraints
*/
TEST_CASE("check_constraints should return true if it is all right (XposMachine>0)","[EbMachine]"){

    double Xpos = 200;

    bool test=eb_checkConstraints_Machine(Xpos);
 
    REQUIRE(test==true);
}
TEST_CASE("check_constraints_angle should return true if the angle are good to go","[EbMachine]"){

    int n=2;
    double* angle = new double [n];

    angle[0]=200;  //va bene perchè è il primo device
    angle[1]=60;

    bool test=eb_checkConstraints_Machine_angle(angle,n);
 
    REQUIRE(test==true);
}
TEST_CASE("check_constraints should return false if position is negative","[EbMachine]"){

    double Xpos = -200;

    bool test=eb_checkConstraints_Machine(Xpos);

    REQUIRE(test==false);
}
TEST_CASE("check_constraints_angle should return false if angle>180 or angle<0 (not for the first LBAMTTdevice)","[EbMachine]"){

    int n=2;
    double* angle = new double [n];

    angle[0]=200;  //va bene perchè è il primo device
    angle[1]=200;

    bool test=eb_checkConstraints_Machine_angle(angle,n);
 
    REQUIRE(test==false);
}

/*
    some tests regarding the set functions
    Sets a new parameter in the structure       
    if the new parameter is incompabile with other measures, RETURN 1, otherwise 0
*/
TEST_CASE("eb_set_XposMachine should return 1 if the new position is not good","[EbMachine]"){

    EbMachine* machine = new EbMachine;
    double XposMachine=200;
    int n=1;
    double* dShaft = new double [n];
    double* stroke = new double [n];
    double* lenBiella = new double [n];
    double* wBiella = new double [n];
    double* hPistone = new double [n];
    double* dPistone = new double [n];
    double* angle = new double [n];

    for(int i=0;i<n;i++){
        dShaft[i] = 60;
        stroke[i] = 150;
        lenBiella[i] =  150;
        wBiella[i] = 30;
        hPistone[i] = 50;
        dPistone[i] = 75;
        angle[i] = 40;
    }
    double* sliding = new double [n];
    double* length_shaft = new double [n];
    double* width_towTruck = new double [n];
    double* width_platform = new double [n];
    double* rotation = new double [n];
    
    for(int i=0;i<n;i++){
        length_shaft[i]=350;
        width_towTruck[i]=100;
        width_platform[i]=150;
        rotation[i]=-30;
    }
    machine = eb_machine_init(XposMachine, n, dShaft, stroke, lenBiella, wBiella, hPistone, dPistone, angle, length_shaft, width_towTruck, width_platform, rotation);

    REQUIRE(eb_set_XposMachine(machine, -200)==1);

}

/*
    test regarding the function eb_machine_to_svg
*/
TEST_CASE("eb_machine_to_svg should return a string with the right code","[EbMachine]"){

    EbMachine* machine = new EbMachine;
    double XposMachine=200;
    int n=1;
    double* dShaft = new double [n];
    double* stroke = new double [n];
    double* lenBiella = new double [n];
    double* wBiella = new double [n];
    double* hPistone = new double [n];
    double* dPistone = new double [n];
    double* angle = new double [n];

    for(int i=0;i<n;i++){
        dShaft[i] = 60;
        stroke[i] = 150;
        lenBiella[i] =  150;
        wBiella[i] = 30;
        hPistone[i] = 50;
        dPistone[i] = 75;
        angle[i] = 40;
    }

    double* sliding = new double [n];
    double* length_shaft = new double [n];
    double* width_towTruck = new double [n];
    double* width_platform = new double [n];
    double* rotation = new double [n];
    
    for(int i=0;i<n;i++){
        length_shaft[i]=350;
        width_towTruck[i]=100;
        width_platform[i]=150;
        rotation[i]=-30;
    }

    machine = eb_machine_init(XposMachine, n, dShaft, stroke, lenBiella, wBiella, hPistone, dPistone, angle, length_shaft, width_towTruck, width_platform, rotation);
    

    eb_save_to_file(eb_machine_to_svg(machine,n),"machine");
    
    string check = eb_read_from_file("machine.svg");

    REQUIRE(eb_machine_to_svg(machine,n)==check);

}

/*
    test regarding the function eb_parse
*/
TEST_CASE("eb_machine_parse should return NULL, if the measures read from file don't respect the mechanical constraints","[EbMachine]"){

    string svg = eb_read_from_file("tests/wrongmachine.svg");

    EbMachine* machine= eb_machine_parse(svg);

    REQUIRE(machine==NULL);

}
TEST_CASE("eb_machine_parse should create a struct from a svg file","[EbMachine]"){

    string svg = eb_read_from_file("machine.svg");

    EbMachine* machine1= eb_machine_parse(svg);
    string pat = "g transform"; 

    string svg1=eb_read_from_file("machine.svg");    
    
    int n1 = eb_count_stringOccurences(pat, svg1)/2;

    EbMachine* machine2 = new EbMachine;
    double XposMachine=200;
    int n=1;
    double* dShaft = new double [n];
    double* stroke = new double [n];
    double* lenBiella = new double [n];
    double* wBiella = new double [n];
    double* hPistone = new double [n];
    double* dPistone = new double [n];
    double* angle = new double [n];

    for(int i=0;i<n;i++){
        dShaft[i] = 60;
        stroke[i] = 150;
        lenBiella[i] =  150;
        wBiella[i] = 30;
        hPistone[i] = 50;
        dPistone[i] = 75;
        angle[i] = 40;
    }

    double* sliding = new double [n];
    double* length_shaft = new double [n];
    double* width_towTruck = new double [n];
    double* width_platform = new double [n];
    double* rotation = new double [n];
    
    for(int i=0;i<n;i++){
        length_shaft[i]=350;
        width_towTruck[i]=100;
        width_platform[i]=150;
        rotation[i]=-30;
    }

    machine2 = eb_machine_init(XposMachine, n, dShaft, stroke, lenBiella, wBiella, hPistone, dPistone, angle, length_shaft, width_towTruck, width_platform, rotation);
    
    REQUIRE(eb_machine_are_equal(machine1,n1,machine2,n)==true);

}

TEST_CASE("eb_machine_are equal should return true if two machines are the same","[EbMachine]"){

    EbMachine* eb_machine = new EbMachine;
    double XposMachine = 200;
    int n=1; //numero di coppie di device nella machine
    
    
    double* dShaft = new double [n];
    double* stroke = new double [n];
    double* lenBiella = new double [n];
    double* wBiella = new double [n];
    double* hPistone = new double [n];
    double* dPistone = new double [n];
    double* angle = new double [n];

    for(int i=0;i<n;i++){
        dShaft[i] = 60;
        stroke[i] = 150;
        lenBiella[i] =  150;
        wBiella[i] = 30;
        hPistone[i] = 50;
        dPistone[i] = 75;
        angle[i] = 40;
    }

    double* sliding = new double [n];
    double* length_shaft = new double [n];
    double* width_towTruck = new double [n];
    double* width_platform = new double [n];
    double* rotation = new double [n];
    
    for(int i=0;i<n;i++){
        length_shaft[i]=350;
        width_towTruck[i]=100;
        width_platform[i]=150;
        rotation[i]=-30;
    }
    
    
    eb_machine = eb_machine_init(XposMachine, n, dShaft, stroke, lenBiella, wBiella, hPistone, dPistone, angle, length_shaft, width_towTruck, width_platform, rotation);
    
    eb_save_to_file(eb_machine_to_svg(eb_machine,n),"tests/machine1");
    eb_save_to_file(eb_machine_to_svg(eb_machine,n),"tests/machine2");

    EbMachine* eb_machine1 = new EbMachine;
    EbMachine* eb_machine2 = new EbMachine;
    string pat = "g transform"; 

    string svg1=eb_read_from_file("tests/machine1.svg");    
    eb_machine1= eb_machine_parse(svg1);
    int n1 = eb_count_stringOccurences(pat, svg1)/2;

    string svg2=eb_read_from_file("tests/machine2.svg");    
    eb_machine2= eb_machine_parse(svg2);
    int n2 = eb_count_stringOccurences(pat, svg2)/2;

    REQUIRE(eb_machine_are_equal(eb_machine1,n1,eb_machine2,n)==true);

}

TEST_CASE("eb_destroy_machine should delete the machine","[EbMachine]"){
    EbMachine* eb_machine = new EbMachine;
    double XposMachine = 200;
    int n=1; //numero di coppie di device nella machine
    
    
    double* dShaft = new double [n];
    double* stroke = new double [n];
    double* lenBiella = new double [n];
    double* wBiella = new double [n];
    double* hPistone = new double [n];
    double* dPistone = new double [n];
    double* angle = new double [n];

    for(int i=0;i<n;i++){
        dShaft[i] = 60;
        stroke[i] = 150;
        lenBiella[i] =  150;
        wBiella[i] = 30;
        hPistone[i] = 50;
        dPistone[i] = 75;
        angle[i] = 40;
    }

    double* sliding = new double [n];
    double* length_shaft = new double [n];
    double* width_towTruck = new double [n];
    double* width_platform = new double [n];
    double* rotation = new double [n];
    
    for(int i=0;i<n;i++){
        length_shaft[i]=350;
        width_towTruck[i]=100;
        width_platform[i]=150;
        rotation[i]=-30;
    }
    
    
    eb_machine = eb_machine_init(XposMachine, n, dShaft, stroke, lenBiella, wBiella, hPistone, dPistone, angle, length_shaft, width_towTruck, width_platform, rotation);

    
    REQUIRE(eb_destroy_machine(eb_machine,n)==0); 

}