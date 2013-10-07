cmake_minimum_required(VERSION 2.6)
 
project(FreeBird)


set(SOURCES "${PROJECT_SOURCE_DIR}/src/")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")


file(
	GLOB_RECURSE 
	Source_File 
	${SOURCES}/*.h
	${SOURCES}/*.ih
	${SOURCES}/*.cpp
    )


find_package(OpenSceneGraph REQUIRED)
find_package(osgDB REQUIRED)
find_package(osgViewer REQUIRED)
find_package(osgGA REQUIRED)
find_package(OpenGL REQUIRED)
FIND_PACKAGE (X11 REQUIRED)

set(CORELIBS ${GLEW_LIBRARY} ${OPENGL_LIBRARIES}  
  ${OSG_LIBRARY} 
  ${OSGDB_LIBRARY} 
  ${OSGVIEWER_LIBRARY}
  ${OSGGA_LIBRARY}
${X11_Xxf86vm_LIB} ${X11_Xrandr_LIB} ${X11_Xi_LIB} pthread )

include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR} 	${OSG_INCLUDE_DIR} ${OSGDB_INCLUDE_DIR} ${OSGVIEWER_INCLUDE_DIR}
${OSGGA_INCLUDE_DIR})

add_library(FreeBirdLib ${Source_File})


add_executable(FreeBird program/freebird.cpp)
TARGET_LINK_LIBRARIES(FreeBird FreeBirdLib ${CORELIBS})


add_custom_command(
    TARGET FreeBird POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/data ${PROJECT_BINARY_DIR}
)



	


 


