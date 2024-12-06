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
#include "Grille.h"
#include "Cellule.h"

// Classe représentant une cellule
class Cellule {
private:
    bool vivante = false;
    bool obstacle = false;

public:
    void definirEtat(bool etat) {
        if (!obstacle) vivante = etat;
    }

    void definirObstacle(bool estObstacle) { obstacle = estObstacle; }
    bool estVivante() const { return vivante; }
    bool estObstacle() const { return obstacle; }
};