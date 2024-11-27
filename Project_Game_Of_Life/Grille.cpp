#include <iostream>
#include <vector>
#include <cstdlib>
#include "Grille.h"

    int Grille::compterVoisinsVivants(int x, int y)
    {
        int compteur = 0;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Ignorer la cellule elle-même
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes && grilleActuelle[nx][ny]) {
                    ++compteur;
                }
            }
        }
        return compteur;
    }
