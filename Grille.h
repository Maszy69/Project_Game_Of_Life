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

// Classe représentant la grille
class Grille {
private:
    int largeur;
    int hauteur;
    std::vector<std::vector<Cellule>> cellules;

public:
    Grille(int largeur, int hauteur) : largeur(largeur), hauteur(hauteur), cellules(hauteur, std::vector<Cellule>(largeur)) {}

    void initialiserDepuisFichier(const std::string& cheminFichier) {
        std::ifstream fichier(cheminFichier);
        if (!fichier) throw std::runtime_error("Erreur : Impossible d'ouvrir le fichier " + cheminFichier);

        fichier >> hauteur >> largeur;
        cellules.resize(hauteur, std::vector<Cellule>(largeur)); // Ajuster la taille de la grille

        for (int y = 0; y < hauteur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                int etat;
                fichier >> etat;
                cellules[y][x].definirEtat(etat == 1);
            }
        }
    }

    void afficher(sf::RenderWindow& fenetre, int tailleCellule) const {
        for (int y = 0; y < hauteur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                sf::RectangleShape rectangle(sf::Vector2f(tailleCellule - 1, tailleCellule - 1));
                rectangle.setPosition(x * tailleCellule, y * tailleCellule);
                rectangle.setFillColor(cellules[y][x].estVivante() ? sf::Color::Green : sf::Color::Black);
                fenetre.draw(rectangle);
            }
        }
    }

    void definirCelluleAvecSouris(int x, int y, int tailleCellule) {
        int cellX = x / tailleCellule;
        int cellY = y / tailleCellule;
        if (cellX >= 0 && cellX < largeur && cellY >= 0 && cellY < hauteur) {
            cellules[cellY][cellX].definirEtat(!cellules[cellY][cellX].estVivante());
        }
    }

    void mettreAJour(std::ofstream& historique) {
        std::vector<std::vector<Cellule>> nouvelleGrille = cellules;

        for (int y = 0; y < hauteur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                if (cellules[y][x].estObstacle()) continue;

                int voisinsVivants = compterVoisinsVivants(x, y);
                nouvelleGrille[y][x].definirEtat(cellules[y][x].estVivante() ? (voisinsVivants == 2 || voisinsVivants == 3) : (voisinsVivants == 3));
            }
        }

        cellules = std::move(nouvelleGrille);
        enregistrerHistorique(historique);
    }

    void enregistrerHistorique(std::ofstream& historique) const {
        historique << "Etat de la grille :\n";
        for (const auto& ligne : cellules) {
            for (const auto& cellule : ligne) {
                historique << (cellule.estVivante() ? 1 : 0) << " ";
            }
            historique << "\n";
        }
        historique << "-----------------------------------\n";
    }

    int compterVoisinsVivants(int x, int y) const {
        int compteur = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                int nx = (x + i + largeur) % largeur;
                int ny = (y + j + hauteur) % hauteur;
                compteur += cellules[ny][nx].estVivante();
            }
        }
        return compteur;
    }

    void sauvegarder(const std::string& cheminFichier) {
        std::ofstream fichier(cheminFichier);
        fichier << hauteur << " " << largeur << std::endl;
        for (const auto& ligne : cellules) {
            for (const auto& cellule : ligne) {
                fichier << (cellule.estVivante() ? 1 : 0) << " ";
            }
            fichier << std::endl;
        }
    }

    void placerMotifAleatoire(const std::vector<std::vector<int>>& motif) {
        int xOffset = std::rand() % largeur;
        int yOffset = std::rand() % hauteur;
        placerMotif(motif, xOffset, yOffset);
    }

    void placerMotif(const std::vector<std::vector<int>>& motif, int xOffset, int yOffset) {
        for (int y = 0; y < motif.size(); ++y) {
            for (int x = 0; x < motif[y].size(); ++x) {
                if (motif[y][x] == 1) {
                    int xPos = (xOffset + x) % largeur;
                    int yPos = (yOffset + y) % hauteur;
                    cellules[yPos][xPos].definirEtat(true);
                }
            }
        }
    }
};
