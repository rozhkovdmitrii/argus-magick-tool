cmake_minimum_required(VERSION 3.18)
project(argus_challenge)

set(CMAKE_CXX_STANDARD 17)

find_package(ImageMagick COMPONENTS Magick++)
if (NOT ${ImageMagick_Magick++_FOUND})
  message(FATAL_ERROR "ImageMagick not found. Look at https://imagemagick.org/")
endif()

find_program(MAGICK_CONFIG "Magick++-config" ${ImageMagick_EXECUTABLE_DIR})
if (${MAGICK_CONFIG} STREQUAL "")
  message(FATAL_ERROR "MagickConfig not found. Look at https://imagemagick.org/")
endif()

execute_process(COMMAND "${MAGICK_CONFIG}" "--cxxflags" OUTPUT_VARIABLE MAGICK_CXX_FLAGS)
execute_process(COMMAND "${MAGICK_CONFIG}" "--ldflags" OUTPUT_VARIABLE MAGICK_LD_FLAGS)
string(STRIP "${MAGICK_CXX_FLAGS}" MAGICK_CXX_FLAGS)
string(STRIP "${MAGICK_LD_FLAGS}" MAGICK_LD_FLAGS)

message(STATUS "ImageMagick include dirs: ${ImageMagick_INCLUDE_DIRS}")
message(STATUS "ImageMagick libraries: ${ImageMagick_LIBRARIES}" )
message(STATUS "Magick cxx flags: ${MAGICK_CXX_FLAGS}")
message(STATUS "Magick ld flags: ${MAGICK_LD_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MAGICK_CXX_FLAGS} ${MAGICK_LD_FLAGS}")

add_subdirectory(Lib/rozhkovdmitrii-lib)
add_subdirectory(Lib/argus-lib)

add_executable(argus-magic-tool main.cpp App.cpp App.h)
target_include_directories(argus-magic-tool PRIVATE .)
target_link_libraries(argus-magic-tool argus-lib)


