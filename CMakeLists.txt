cmake_minimum_required(VERSION 3.10)
project(ProjetJeuDeDame LANGUAGES CXX)

# Configuration standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Activer les fonctionnalités automatiques de Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Trouver les modules Qt nécessaires
find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

# Fichiers de traduction
set(TS_FILES TraductionFR.ts TraductionEN.ts)
qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# Définir les fichiers source et d'en-tête
set(SOURCES
    main.cpp
    dames.cpp
    square.cpp
    checkerscontroller.cpp
    board.cpp
    imageicon.qrc
)

set(HEADERS
    dames.h
    square.h
    checkerscontroller.h
    board.h
)

set(UIS
    dames.ui
)

# Ajouter l'exécutable
add_executable(ProjetJeuDeDame ${SOURCES} ${HEADERS} ${UIS} ${QM_FILES})

# Lier les bibliothèques Qt nécessaires
target_link_libraries(ProjetJeuDeDame Qt5::Widgets)
