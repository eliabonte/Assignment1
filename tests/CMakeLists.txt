# Sources that contain the tests
add_executable(catch2Test catch2Main.cpp) # Just this one contains BOOST_TEST_MAIN
target_sources(catch2Test PRIVATE
        EB_test_machine.cpp
        EB_testDevice.cpp
        LBAMTTtestBiellaManovella.cpp
        LBAMTTtestCadSVG.cpp
	)

# Libraries used in the tests
target_link_libraries(catch2Test)

# Including headers
target_include_directories(catch2Test PRIVATE
        ../include) # Including this allows to simply write #include "funcs.h"

# Including sources
target_sources(catch2Test PRIVATE
        ../src/EB_Device.cpp
        ../src/LBAMTTBiellaManovella.cpp
        ../src/LBAMTTcadSVG.cpp
        ../src/EB_Machine.cpp)

#target_compile_options(catch2Test PRIVATE -Wa,-mbig-obj) # Solves assembler error of file too big
