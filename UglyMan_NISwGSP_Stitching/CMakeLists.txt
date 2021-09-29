cmake_minimum_required(VERSION 3.20)
project(image_stitching CXX)

include_directories(${CMAKE_SOURCE_DIR}/UglyMan_NISwGSP_Stitching/Debugger)
include_directories(${CMAKE_SOURCE_DIR}/UglyMan_NISwGSP_Stitching/Feature)
include_directories(${CMAKE_SOURCE_DIR}/UglyMan_NISwGSP_Stitching/Mesh)
include_directories(${CMAKE_SOURCE_DIR}/UglyMan_NISwGSP_Stitching/Stitching)
include_directories(${CMAKE_SOURCE_DIR}/UglyMan_NISwGSP_Stitching/Util)
include_directories(${CMAKE_SOURCE_DIR}/UglyMan_NISwGSP_Stitching/)


set(SOURCE_FILES
        UglyMan_NISwGSP_Stitching/Debugger/ColorMap.cpp
        UglyMan_NISwGSP_Stitching/Debugger/ErrorController.cpp
        UglyMan_NISwGSP_Stitching/Debugger/ImageDebugger.cpp
        UglyMan_NISwGSP_Stitching/Debugger/TimeCalculator.cpp

        UglyMan_NISwGSP_Stitching/Feature/FeatureController.cpp
        UglyMan_NISwGSP_Stitching/Feature/ImageData.cpp
        UglyMan_NISwGSP_Stitching/Feature/MultiImages.cpp

        UglyMan_NISwGSP_Stitching/Mesh/Mesh2D.cpp
        UglyMan_NISwGSP_Stitching/Mesh/MeshGrid.cpp
        UglyMan_NISwGSP_Stitching/Mesh/MeshOptimization.cpp

        UglyMan_NISwGSP_Stitching/Stitching/APAP_Stitching.cpp
        UglyMan_NISwGSP_Stitching/Stitching/NISwGSP_Stitching.cpp
        UglyMan_NISwGSP_Stitching/Stitching/Parameter.cpp

        UglyMan_NISwGSP_Stitching/Util/Blending.cpp
        UglyMan_NISwGSP_Stitching/Util/InputParser.cpp
        UglyMan_NISwGSP_Stitching/Util/Statistics.cpp
        UglyMan_NISwGSP_Stitching/Util/Transform.cpp
        )

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE ${CMAKE_SOURCE_DIR}/conanfile.txt
        BUILD *
        UPDATE ON
        SETTINGS ${settings}
        PROFILE ${CONAN_PROFILE})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(image_stitching_lib ${SOURCE_FILES})
target_link_libraries(image_stitching_lib ${CONAN_LIBS} ${CMAKE_SOURCE_DIR}/UglyMan_NISwGSP_Stitching/libs/libvl.so)

add_executable(exe UglyMan_NISwGSP_Stitching/main.cpp)
target_link_libraries(exe image_stitching_lib)