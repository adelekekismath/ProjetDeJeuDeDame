# Projet De Jeu De Dame

Ce dépôt contient un projet de jeu de dames implémenté principalement en C++. Il s'agit d'une application interactive avec une interface utilisateur graphique (UI) pour jouer aux dames.

## Table des matières

- [À propos](#à-propos)
- [Fonctionnalités](#fonctionnalités)
- [Structure du projet](#structure-du-projet)
- [Installation](#installation)

## À propos

Le **Projet De Jeu De Dame** est une implémentation du jeu de dames utilisant le langage C++. Le jeu est conçu pour permettre aux joueurs de s'affronter via une interface graphique. 

## Fonctionnalités

- Jeu interactif de dames pour deux joueurs.
- Interface utilisateur graphique.
- Prise en charge de différentes langues (français et anglais).

## Structure du projet

Le projet est organisé en plusieurs fichiers et dossiers :

- **`main.cpp`** : Point d'entrée principal de l'application.
- **`board.cpp` et `board.h`** : Contient la logique et les structures du plateau de jeu.
- **`checkerscontroller.cpp` et `checkerscontroller.h`** : Gère les interactions et la logique de jeu.
- **`dames.cpp` et `dames.h`** : Interface utilisateur et logique principale.
- **`square.cpp` et `square.h`** : Gestion des cases du plateau.
- **`TraductionFR.ts` et `TraductionEN.ts`** : Fichiers pour la gestion des traductions.
- **`icones`** : Ressources d'icônes pour l'interface graphique.

## Installation

1. Clonez ce dépôt sur votre machine locale :
   ```bash
   git clone https://github.com/adelekekismath/ProjetDeJeuDeDame.git
2. Assurez-vous d'avoir un compilateur C++ installé (comme GCC ou MSVC).
3. Utilisez CMake pour configurer et générer les fichiers de build :
   ```bash
   mkdir build && cd build
   cmake ..
   make
4. Exécutez l'application générée.
