#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem> // ou <experimental/filesystem> selon le support
#include <cstdlib>
#include <windows.h>
#include <shlobj.h> // Pour SHGetFolderPath
#include "Cellule.h"

class Grille {
private:
    int largeur;
    int hauteur;
    std::vector<std::vector<Cellule>> cellules;

public:
    Grille(int largeur, int hauteur) : largeur(largeur), hauteur(hauteur) {
        cellules.resize(largeur, std::vector<Cellule>(hauteur));
    }

    void initialiserDepuisFichier(const std::string& cheminFichier) {
        std::ifstream fichier(cheminFichier);
        if (!fichier) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << std::endl;
            exit(1);
        }

        fichier >> hauteur >> largeur;
        cellules.resize(largeur, std::vector<Cellule>(hauteur));

        for (int y = 0; y < hauteur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                int etat;
                fichier >> etat;
                cellules[x][y].definirEtat(etat == 1);
            }
        }

        fichier.close();
    }

    void afficher() const {
        for (int y = 0; y < hauteur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                std::cout << (cellules[x][y].estVivante() ? "*" : ".");
            }
            std::cout << std::endl;
        }
    }

    void sauvegarderEtat(std::ofstream& fichier) const {
        fichier << hauteur << " " << largeur << std::endl;
        for (int y = 0; y < hauteur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                fichier << (cellules[x][y].estVivante() ? "1 " : "0 ");
            }
            fichier << std::endl;
        }
        fichier << "----------------------" << std::endl;
    }

    int compterVoisinsVivants(int x, int y) const {
        int compteur = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int nx = (x + i + largeur) % largeur;
                int ny = (y + j + hauteur) % hauteur;
                if (cellules[nx][ny].estVivante())
                    compteur++;
            }
        }
        return compteur;
    }

    void mettreAJour() {
        std::vector<std::vector<Cellule>> nouvelleGrille = cellules;

        for (int x = 0; x < largeur; ++x) {
            for (int y = 0; y < hauteur; ++y) {
                int voisinsVivants = compterVoisinsVivants(x, y);
                if (cellules[x][y].estVivante()) {
                    nouvelleGrille[x][y].definirEtat(voisinsVivants == 2 || voisinsVivants == 3);
                }
                else {
                    nouvelleGrille[x][y].definirEtat(voisinsVivants == 3);
                }
            }
        }

        cellules = nouvelleGrille;
    }

    bool estStable(const Grille& ancienneGrille) const {
        return cellules == ancienneGrille.cellules;
    }

    // Surcharge de l'opérateur ==
    bool operator==(const Grille& autre) const {
        return cellules == autre.cellules;
    }
};
