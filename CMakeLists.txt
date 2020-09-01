cmake_minimum_required(VERSION 3.5)

project(qtsamples LANGUAGES CXX VERSION 1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DEFAULT_SAMPLES_DIR "/home/victor/Downloads/musicradar-female-vocal-samples")
option(USE_SIMPLE_AUDIO_PLAYBACK "use simple QAudio play() method" ON)
configure_file(SamplesConfig.h.in SamplesConfig.h)

set(CMAKE_INSTALL_PREFIX "~/.local")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "~/.local/include")
#find_package(cpp-ipfs-api)
# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)
set(SOURCES
    Singleton.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    samplemanager.cpp
    samplemanager.h
    soundsample.cpp
    soundsample.h
    identity.h
    soundsampletablemodel.cpp
    soundsampletablemodel.h
    samplessummarytablemodel.cpp
    samplessummarytablemodel.h
    wavfile.cpp
    wavfile.h)
if(ANDROID)
  add_library(qtsamples SHARED
 ${SOURCES}
    mainwindow.ui
  )
else()
  add_executable(qtsamples
      ${SOURCES}
    mainwindow.ui
  )
endif()
set(CMAKE_LIBRARY_PATH ~/.local/lib)
set(CMAKE_EXE_LINKER_FLAGS -Llibipfs-api.a)
target_link_libraries(qtsamples PRIVATE Qt5::Widgets Qt5::Multimedia )
