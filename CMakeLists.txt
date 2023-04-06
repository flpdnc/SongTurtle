cmake_minimum_required(VERSION 3.15)
project(AudioGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFTW REQUIRED fftw3)
include_directories(${FFTW_INCLUDE_DIRS})

pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)
include_directories(${PORTAUDIO_INCLUDE_DIRS})

add_executable(AudioGame src/main.cpp src/player.cpp src/player.h src/item.cpp src/item.h src/audio.cpp src/audio.h)

target_link_libraries(AudioGame ${SDL2_LIBRARIES} ${FFTW_LIBRARIES} ${PORTAUDIO_LIBRARIES})

