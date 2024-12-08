#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <windows.h>
#include <shlobj.h>
#include <locale>
#include <codecvt>
#include <ctime>
#include <cstdio> // Pour std::remove

// Classe repr�sentant une cellule
class Cellule {
private:
    bool vivante = false; // Indique si la cellule est vivante
    bool obstacle = false; // Indique si la cellule est un obstacle

public:
    // D�finir l'�tat de la cellule (vivante ou morte)
    void definirEtat(bool etat) {
        if (!obstacle) vivante = etat;
    }

    // D�finir si la cellule est un obstacle
    void definirObstacle(bool estObstacle) { obstacle = estObstacle; }

    // V�rifier si la cellule est vivante
    bool estVivante() const { return vivante; }

    // V�rifier si la cellule est un obstacle
    bool estObstacle() const { return obstacle; }
};