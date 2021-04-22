
#include "catch2/catch2.hpp"
#include "../include/device.h"
#include <stdexcept>

using namespace std;

TEST_CASE("init should create a new struct","[MyDevice]"){
   
    Device* device = eb_init(400,160,300,-60,480);

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
TEST_CASE("check_constraints should return false if the angle of rotation is more than 80 degrees","[MyDevice]"){

    bool test=eb_checkConstraints(400,160,300,82,480);

    REQUIRE(test==false);
}
TEST_CASE("check_constraints should return false if the angle of rotation is less than -80 degrees","[MyDevice]"){

    bool test=eb_checkConstraints(400,160,300,-82,480);

    REQUIRE(test==false);
}

/*
    some tests regarding the function eb_drawConstraints which check draw constraints
*
TEST_CASE("draw_constraints should return false if Yplatform is more than 1480, which means the device would be out of the sheet","[MyDevice]"){

    bool test=eb_checkConstraints(400,160,300,-82,480);

    REQUIRE(test==false);
}
*/


