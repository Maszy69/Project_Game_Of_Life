#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>

class Grille {
private:
    int lignes, colonnes;
    std::vector<std::vector<bool>> grilleActuelle;
    std::vector<std::vector<bool>> grilleSuivante;

    // Compte les voisins vivants autour de la cellule (x, y)
    int compterVoisinsVivants(int x, int y);


public:
    // Constructeur
    Grille(int lignes, int colonnes) : lignes(lignes), colonnes(colonnes) {
        grilleActuelle.resize(lignes, std::vector<bool>(colonnes, false));
        grilleSuivante.resize(lignes, std::vector<bool>(colonnes, false));
    }

};


