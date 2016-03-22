cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

SET(CMAKE_PREFIX_PATH "/usr/local/opt/opencv3" CACHE PATH "OpenCV install prefix")
project( StitchingOpencv )

# Version number
set ( StitchingOpencv_VERSION_MAJOR 1 )
set ( StitchingOpencv_VERSION_MINOR 0 )

find_package( OpenCV 3.1.0 COMPONENTS highgui cudaimgproc video imgcodecs REQUIRED )
find_package( Boost 1.6.0 COMPONENTS program_options REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
add_executable( stitch stitch.cpp )
target_link_libraries( stitch ${OpenCV_LIBRARIES} )
target_link_libraries( stitch ${Boost_LIBRARIES} )

target_compile_features( stitch PRIVATE cxx_range_for )
