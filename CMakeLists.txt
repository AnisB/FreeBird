cmake_minimum_required(VERSION 2.6)
 
project(FreeBird)

#Setting the cmake module math
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
set(ENGINE "${PROJECT_SOURCE_DIR}/src/engine")


#If we are generating the vrjuggler project for the cave
IF(VRJUGGLER)


ADD_DEFINITIONS(-D VRJUGGLER)
set(IO "${PROJECT_SOURCE_DIR}/src/io/vrjuggler")
# Recursive file search
file(
	GLOB_RECURSE 
	Source_File 
	${ENGINE}/*.h
	${ENGINE}/*.ih
	${ENGINE}/*.cpp
	${IO}/*.h
	${IO}/*.ih
	${IO}/*.cpp
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


include_directories(${IO} ${ENGINE} ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR} 	${OSG_INCLUDE_DIR} ${OSGDB_INCLUDE_DIR} ${OSGVIEWER_INCLUDE_DIR}
${OSGGA_INCLUDE_DIR})

#Specific linker flags
set(CMAKE_EXE_LINKER_FLAGS "-m32 -L -Wall")

#Creating the library
add_library(FreeBirdLib ${Source_File})

#Adding the specific link directory
LINK_DIRECTORIES( ${LINK_DIRECTORIES} ${VJ_BASE_DIR}/lib)

#Adding the exefile
add_executable(FreeBird program/vrjuggler/freebird.cpp)
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

IF(TESS)
	ADD_DEFINITIONS(-D TESS)
ENDIF()
ADD_DEFINITIONS(-D OSG)

set(IO "${PROJECT_SOURCE_DIR}/src/io/osg")
# Recursive file search
file(
	GLOB_RECURSE 
	Source_File 
	${ENGINE}/*.h
	${ENGINE}/*.ih
	${ENGINE}/*.cpp
	${IO}/*.h
	${IO}/*.ih
	${IO}/*.cpp
    )

find_package(OpenSceneGraph REQUIRED)
find_package(osgDB REQUIRED)
find_package(osgViewer REQUIRED)
find_package(osgGA REQUIRED)
find_package(osgUtil REQUIRED)
find_package(OpenGL REQUIRED)
FIND_PACKAGE (X11 REQUIRED)
FIND_PACKAGE (OpenThreads REQUIRED)

set(CORELIBS ${GLEW_LIBRARY} ${OPENGL_LIBRARIES}  
  ${OSG_LIBRARY} 
  ${OSGDB_LIBRARY} 
  ${OSGVIEWER_LIBRARY}
  ${OSGGA_LIBRARY}
  ${OSGUTIL_LIBRARY}
${X11_Xxf86vm_LIB} ${X11_Xrandr_LIB} ${X11_Xi_LIB} pthread ${OPENTHREADS_LIBRARY})

include_directories(${ENGINE} ${IO} ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR}   ${OSG_INCLUDE_DIR} ${OSGDB_INCLUDE_DIR} ${OSGVIEWER_INCLUDE_DIR} ${OSGUTIL_INCLUDE_DIR}
${OSGGA_INCLUDE_DIR})

add_library(FreeBirdLib ${Source_File})


add_executable(FreeBird program/osg/freebird.cpp)
TARGET_LINK_LIBRARIES(FreeBird FreeBirdLib ${CORELIBS})


add_custom_command(
    TARGET FreeBird POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/data ${PROJECT_BINARY_DIR}
) 
ENDIF()


 


