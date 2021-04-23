
#include "catch2/catch2.hpp"
#include "../include/device.h"


using namespace std;

TEST_CASE("init should create a new struct","[MyDevice]"){
   
    EbDevice* device = eb_init(400,160,300,-60,480);

    REQUIRE(device!=NULL);
}
/*
    some tests regarding the function eb_checkConstraints which check mechanical constraints
*/
TEST_CASE("check_constraints should return true if it is all right","[MyDevice]"){

    bool test=eb_checkConstraints(400,160,300,-60,480);

    REQUIRE(test==true);
}
TEST_CASE("check_constraints should return false if the length is negative ","[MyDevice]"){

    bool test=eb_checkConstraints(-400,160,300,-60,480);

    REQUIRE(test==false);
}
TEST_CASE("check_constraints should return false if the tow truck width is negative ","[MyDevice]"){

    bool test=eb_checkConstraints(400,-160,300,-60,480);

    REQUIRE(test==false);
}
TEST_CASE("check_constraints should return false if the platform width is negative ","[MyDevice]"){

    bool test=eb_checkConstraints(400,160,-300,-60,480);

    REQUIRE(test==false);
}
TEST_CASE("check_constraints should return false if the sliding is negative ","[MyDevice]"){

    bool test=eb_checkConstraints(400,160,300,-60,-480);

    REQUIRE(test==false);
}
TEST_CASE("check_constraints should return false if length of the shaft is less than than (std_platformHeight/2)+(std_towtruckHeight/2) ","[MyDevice]"){

    bool test=eb_checkConstraints(10,160,300,-60,480);

    REQUIRE(test==false);
}
TEST_CASE("check_constraints should return false if the angle of rotation is more than 80 degrees","[MyDevice]"){

    bool test=eb_checkConstraints(200,160,300,82,480);

    REQUIRE(test==false);
}
TEST_CASE("check_constraints should return false if the angle of rotation is less than -80 degrees","[MyDevice]"){

    bool test=eb_checkConstraints(7,160,300,-82,480);

    REQUIRE(test==false);
}

/*
    some tests regarding the function eb_drawConstraints which check draw constraints
*/
TEST_CASE("draw_constraints should return false if Yplatform is more than 1480, which means the device would be out of the sheet","[MyDevice]"){

    EbDevice* device = eb_init(1500,160,300,0,480);

    bool test=eb_drawConstraints(device);

    REQUIRE(test==false);
}
TEST_CASE("draw_constraints should return false if the coordinate x of the right extreme point is more than 2000","[MyDevice]"){

    EbDevice* device = eb_init(1500,160,1000,-80,700);

    bool test=eb_drawConstraints(device);

    REQUIRE(test==false);
}
TEST_CASE("draw_constraints should return false if the coordinate x of the left extreme point is less than 0","[MyDevice]"){

    EbDevice* device = eb_init(1500,160,1000,80,10);

    bool test=eb_drawConstraints(device);

    REQUIRE(test==false);
}

/*
    some tests regarding the set functions
    Sets a new parameter in the structure       
    if the new parameter is incompabile with other measures, RETURN 1, otherwise 0
*/
TEST_CASE("eb_set_lengthShaft should return 1 if the new length is incompatible with other measures","[MyDevice]"){

    EbDevice* device = eb_init(400,160,300,-60,300);
    double new_length_shaft=-10;

    REQUIRE(eb_set_lengthShaft(device, new_length_shaft)==1);
}
TEST_CASE("eb_set_lengthShaft should replace the new parameter, when the function return 0","[MyDevice]"){

    EbDevice* device = eb_init(400,160,300,-60,300);
    double new_length_shaft=450;

    if(eb_set_lengthShaft(device, new_length_shaft)==0){
        REQUIRE(device->length_shaft==450);
    }
}

TEST_CASE("eb_set_widthTowtruck should return 1 if the new width is incompatible with other measures","[MyDevice]"){

    EbDevice* device = eb_init(400,160,300,-60,300);
    double new_widthTowtruck=-10;

    REQUIRE(eb_set_widthTowtruck(device, new_widthTowtruck)==1);
}
TEST_CASE("eb_set_widthTowtruck should replace the new parameter, when the function return 0","[MyDevice]"){

    EbDevice* device = eb_init(400,160,300,-60,300);
    double new_widthTowtruck=200;

    if(eb_set_widthTowtruck(device, new_widthTowtruck)==0){
        REQUIRE(device->width_towtruck==200);
    }
}

TEST_CASE("eb_set_widthPlatform should return 1 if the new width is incompatible with other measures","[MyDevice]"){

    EbDevice* device = eb_init(400,160,300,-60,300);
    double new_widthPlatform=-10;

    REQUIRE(eb_set_widthPlatform(device, new_widthPlatform)==1);
}
TEST_CASE("eb_set_widthPlatform should replace the new parameter, when the function return 0","[MyDevice]"){

    EbDevice* device = eb_init(400,160,300,-60,300);
    double new_widthPlatform=350;

    if(eb_set_widthPlatform(device, new_widthPlatform)==0){
        REQUIRE(device->width_platform==350);
    }
}

TEST_CASE("eb_set_rotation should return 1 if the new rotation is incompatible with other measures","[MyDevice]"){

    EbDevice* device = eb_init(400,160,300,-60,300);
    double new_rotation=-90;

    REQUIRE(eb_set_rotation(device, new_rotation)==1);
}
TEST_CASE("eb_set_rotation should replace the new parameter, when the function return 0","[MyDevice]"){

    EbDevice* device = eb_init(400,160,300,-60,300);
    double new_rotation=30;

    if(eb_set_rotation(device, new_rotation)==0){
        REQUIRE(device->rotation==30);
    } 
}

TEST_CASE("eb_set_sliding should return 1 if the new sliding is incompatible with other measures","[MyDevice]"){

    EbDevice* device = eb_init(400,160,300,-60,300);
    double new_sliding=-90;

    REQUIRE(eb_set_sliding(device, new_sliding)==1);
}
TEST_CASE("eb_set_sliding should replace the new parameter, when the function return 0","[MyDevice]"){

    EbDevice* device = eb_init(400,160,300,-60,300);
    double new_sliding=100;

    if(eb_set_sliding(device, new_sliding)==0){
        REQUIRE(device->sliding==100);
    } 
}

/*
    test regarding the function eb_save_to_file
*/
TEST_CASE("eb_save_to_file should write a string in a file","[MyDevice]"){

    string stringToWrite="ciao";
    
    eb_save_to_file(stringToWrite,"filetest");

    REQUIRE(eb_read_from_file("filetest")==stringToWrite);
}