
cmake_minimum_required(VERSION 3.10.0)
project(ProjetJeuDeDame CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES TraductionFR.ts TraductionEN.ts)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

find_package(Qt5Widgets REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-Wall -Wpedantic)
endif()

add_executable(ProjetJeuDeDame main.cpp
    dames.ui dames.h dames.cpp
    square.h square.cpp
    checkerscontroller.cpp checkerscontroller.h
    board.cpp board.h
   imageicon.qrc ${QM_FILES})
target_link_libraries(ProjetJeuDeDame Qt5::Widgets)




