cmake_minimum_required(VERSION 2.6)
 
project(FreeBird)

#Setting the cmake module math
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")


#If we are generating the vrjuggler project for the cave
IF(VRJUGGLER)
set(SOURCES "${PROJECT_SOURCE_DIR}/src/")

# Recursive file search
file(
	GLOB_RECURSE 
	Source_File 
	${SOURCES}/*.h
	${SOURCES}/*.ih
	${SOURCES}/*.cpp
    )

#VRJuggler path config
set(INSTDIR "/net/bonne/exports/stk_bonne_fedora")
set(JUGGLER_DIR "${INSTDIR}/packages")
set(VJ_BASE_DIR "${JUGGLER_DIR}/usr")

#message(STATUS ${VJ_BASE_DIR})

#Speciefic compiling flags
ADD_DEFINITIONS("-m32 -g -Wall -fexceptions -pthread -Wall -DHAVE_CONFIG_H -DJUGGLER_DEBUG -Wno-unused-local-typedefs -Wno-deprecated -I${VJ_BASE_DIR}/include/ -I${VJ_BASE_DIR}/include/vrjuggler-2.2/ -I${VJ_BASE_DIR}/include/gadgeteer-1.2/ -I${VJ_BASE_DIR}/include/jccl-1.2/ -I${VJ_BASE_DIR}/include/vpr-2.0/ -I${VJ_BASE_DIR}/include/cppdom-0.7.10/ -I${VJ_BASE_DIR}/include/gmtl-0.5.4/")


#Setting the libs to link
set(CORELIBS 
  GL pthread vrj-2_2 vrj_ogl-2_2 gadget-1_2 jccl-1_2 vpr-2_0 cppdom-0_7_10 OpenThreads  osg osgDB osgUtil osgGA GLU GL m)


include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR} 	${OSG_INCLUDE_DIR} ${OSGDB_INCLUDE_DIR} ${OSGVIEWER_INCLUDE_DIR}
${OSGGA_INCLUDE_DIR})

#Specific linker flags
set(CMAKE_EXE_LINKER_FLAGS "-m32 -L -Wall")

#Creating the library
add_library(FreeBirdLib ${Source_File})

#Adding the specific link directory
LINK_DIRECTORIES( ${LINK_DIRECTORIES} ${VJ_BASE_DIR}/lib)

#Adding the exefile
add_executable(FreeBird program/freebird.cpp)
TARGET_LINK_LIBRARIES(FreeBird FreeBirdLib ${CORELIBS})

#Config file for launching sim/cave/run
set(INIT ${INSTDIR}/bin/site_init_vj2.2.0.sh)
set(EXE "FreeBird")
configure_file(${CMAKE_SOURCE_DIR}/cmake/FreeBirdLauncher.sh.in  ${CMAKE_BINARY_DIR}/FreeBirdLauncher.sh )  

#Link to data file
add_custom_command(
    TARGET FreeBird POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/data ${PROJECT_BINARY_DIR}/data
)
ELSE()

ENDIF()


 


