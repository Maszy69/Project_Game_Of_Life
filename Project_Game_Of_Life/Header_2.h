#pragma once
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
#include "Header.h"
#include "Jeu.h"


// Fonction pour créer des motifs
std::vector<std::vector<int>> glider() {
    return { {0, 1, 0}, {0, 0, 1}, {1, 1, 1} };
}
std::vector<std::vector<int>> block() {
    return { {1, 1}, {1, 1} };
}

// Fonction pour modifier la taille de la grille
void modifierTailleGrille(const std::string& cheminFichier, int& largeurGrille, int& hauteurGrille) {
    std::cout << "Entrez la largeur de la grille : ";
    std::cin >> largeurGrille;
    std::cout << "Entrez la hauteur de la grille : ";
    std::cin >> hauteurGrille;

    std::ofstream fichier(cheminFichier);
    fichier << hauteurGrille << " " << largeurGrille << std::endl;
}

// Fonction pour afficher les itérations
void afficherIterations(const std::string& cheminHistorique) {
    std::ifstream fichier(cheminHistorique);
    if (!fichier) {
        std::cout << "Aucune iteration precedente enregistree." << std::endl;
        return;
    }

    std::string ligne;
    std::cout << "Iterations de la dernière partie : " << std::endl;
    while (std::getline(fichier, ligne)) {
        if (ligne.find("Etat de la grille :") != std::string::npos) {
            std::cout << ligne << std::endl;
            while (std::getline(fichier, ligne) && ligne != "-----------------------------------") {
                std::cout << ligne << std::endl;
            }
            std::cout << "-----------------------------------" << std::endl;
        }
    }
}

// Fonction pour afficher l'interface de modification de la grille
void afficherInterfaceModifierGrille(const std::string& cheminFichier, int& largeurGrille, int& hauteurGrille, int tailleCellule) {
    Grille grille(largeurGrille, hauteurGrille);
    grille.initialiserDepuisFichier(cheminFichier);

    sf::RenderWindow fenetre(sf::VideoMode(largeurGrille * tailleCellule, hauteurGrille * tailleCellule), "Modifier la Grille");

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
