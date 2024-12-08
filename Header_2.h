#pragma once
#include <SFML/Graphics.hpp>
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

// Fonction pour modifier la taille de la grille
void modifierTailleGrille(const std::string& cheminFichier, int& largeur, int& hauteur) {
    std::cout << "Entrez la nouvelle largeur de la grille : ";
    std::cin >> largeur;
    std::cout << "Entrez la nouvelle hauteur de la grille : ";
    std::cin >> hauteur;

    std::ofstream fichier(cheminFichier);
    fichier << hauteur << " " << largeur << std::endl;
}

// Fonction pour afficher l'interface de modification de la grille
void afficherInterfaceModifierGrille(const std::string& cheminFichier, int largeur, int hauteur, int tailleCellule) {
    Grille grille(largeur, hauteur);
    grille.initialiserDepuisFichier(cheminFichier);

    sf::RenderWindow fenetre(sf::VideoMode(largeur * tailleCellule, hauteur * tailleCellule), "Modifier la Grille");
    while (fenetre.isOpen()) {
        sf::Event evenement;
        while (fenetre.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed) fenetre.close();
            if (evenement.type == sf::Event::MouseButtonPressed && evenement.mouseButton.button == sf::Mouse::Left) {
                grille.definirCelluleAvecSouris(evenement.mouseButton.x, evenement.mouseButton.y, tailleCellule);
            }
        }

        fenetre.clear(sf::Color::White);
        grille.afficher(fenetre, tailleCellule);
        fenetre.display();
    }

    grille.sauvegarder(cheminFichier);
}

// Fonction pour afficher les itérations du jeu à partir d'un fichier d'historique
void afficherIterations(const std::string& cheminHistorique) {
    std::ifstream fichier(cheminHistorique);
    if (!fichier) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << cheminHistorique << std::endl;
        return;
    }

    std::string ligne;
    while (std::getline(fichier, ligne)) {
        std::cout << ligne << std::endl;
    }
}