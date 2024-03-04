cmake_minimum_required (VERSION 3.5.1)

### To use gcc/g++ on a Macintosh, you must set the Compilers
### here, not inside the project
##if(APPLE)
##       set(CMAKE_C_COMPILER "/usr/local/bin/gcc-7")
##       set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-7")
##endif()
### TODO: for now, we use CLang for Mac
###
### In order to create PALISADE's static libraries you should enable
### the BUILD_STATIC option. For that, you run "cmake .. -DBUILD_STATIC=ON".
### After having your link completed you will find static libs
### with the suffix "_static" in ./build/libs/.
### Examples: PALISADEpke_static.a, PALISADEcore_static.a, etc.
### After you run "make install" in your build directory, you can build your custom application.
### If you need your application to be linked statically, then run "cmake .. -DBUILD_STATIC=ON"

project(rabe CXX)
set(CMAKE_CXX_STANDARD 11)
option( BUILD_STATIC "Set to ON to include static versions of the library" OFF)

#本项目的头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

### 链接palisade库 ###
find_package(Palisade)

set( CMAKE_CXX_FLAGS ${PALISADE_CXX_FLAGS} )

#依赖
include_directories( ${OPENMP_INCLUDES} )
include_directories( ${PALISADE_INCLUDE} )
include_directories( ${PALISADE_INCLUDE}/third-party/include )
include_directories( ${PALISADE_INCLUDE}/core )
include_directories( ${PALISADE_INCLUDE}/pke )
### add directories for other PALISADE modules as needed for your project

link_directories( ${PALISADE_LIBDIR} )
link_directories( ${OPENMP_LIBRARIES} )

### 链接palisade-abe库 ###
find_package(PALISADEabe 1.11.0 REQUIRED)

include_directories( ${ABE_INCLUDE} )
link_directories( ${ABE_LIBDIR} )
link_libraries(PALISADEabe ${PALISADE_LIBRARIES} )
### 链接palisade-abe库 ###

if(BUILD_STATIC)
    set( CMAKE_EXE_LINKER_FLAGS "${PALISADE_EXE_LINKER_FLAGS} -static")
    link_libraries( ${PALISADE_STATIC_LIBRARIES} )
else()
    set( CMAKE_EXE_LINKER_FLAGS ${PALISADE_EXE_LINKER_FLAGS} )
    link_libraries( ${PALISADE_SHARED_LIBRARIES} )
endif()

### 添加生成的可执行文件路径 ###
### ADD YOUR EXECUTABLE(s) HERE
### add_executable( EXECUTABLE-NAME SOURCES )
###
### EXAMPLE:
add_executable(test src/main.cpp )
add_executable(testconfig src/config.cpp )

#将include目录添加到test目标的包含路径中
target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(testconfig PUBLIC ${CMAKE_SOURCE_DIR}/include)

### 设置可执行文件的输出路径为build/bin目录
set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(testconfig PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)