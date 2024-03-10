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
#本项目的资源文件
include_directories(${PROJECT_SOURCE_DIR}/src)

### 链接palisade库 ###
find_package(Palisade)

set( CMAKE_CXX_FLAGS ${PALISADE_CXX_FLAGS} )
set( CMAKE_EXE_LINKER_FLAGS ${PALISADE_EXE_LINKER_FLAGS} )

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

#设置可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#查找当前目录下的所有源文件，并将名称保存到DIR_SRCS变量
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
#指定生成目标
add_executable(test ${DIR_SRCS})

### EXAMPLE:
#add_executable(test src/myconfig.cpp src/central_auth.cpp src/main.cpp  )
#add_executable(testconfig src/myconfig.cpp )

#将include目录添加到test目标的包含路径中，为编译器提供头文件搜索路径
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/include)
#target_include_directories(testconfig PUBLIC ${CMAKE_SOURCE_DIR}/include)

### 设置可执行文件的输出路径为build/bin目录
set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set_target_properties(testconfig PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)