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
#include "Header.h"
#include "Jeu.h"
#include "Header_2.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    const std::string cheminFichier = obtenirCheminDownloads() + "etat_initial.txt";
    const std::string cheminHistorique = obtenirCheminDownloads() + "jeu_out.txt";

    int largeurGrille = 10, hauteurGrille = 10;

    std::ifstream fichierTest(cheminFichier);
    if (!fichierTest) {
        std::ofstream fichier(cheminFichier);
        fichier << "10 10" << std::endl;
        std::cout << "Fichier cree avec des dimensions par defaut (10x10)." << std::endl;
    }
    else {
        fichierTest >> hauteurGrille >> largeurGrille;
    }

    int choix = 0;

    while (choix != 4) {
        std::cout << "=== Menu ===" << std::endl;
        std::cout << "1. Jouer" << std::endl;
        std::cout << "2. Modifier la taille de la grille" << std::endl;
        std::cout << "3. Afficher les iterations" << std::endl;
        std::cout << "4. Quitter" << std::endl;

        do {
            std::cout << "Veuillez entrer votre choix (1, 2, 3 ou 4) : ";
            std::cin >> choix;

            if (choix < 1 || choix > 4) {
                std::cout << "Choix invalide. Veuillez entrer un choix valide." << std::endl;
            }
        } while (choix < 1 || choix > 4);

        switch (choix) {
        case 1: {
            Jeu jeu(cheminFichier, 20, largeurGrille, hauteurGrille);
            jeu.jouer();
            break;
        }
        case 2:
            modifierTailleGrille(cheminFichier, largeurGrille, hauteurGrille);
            afficherInterfaceModifierGrille(cheminFichier, largeurGrille, hauteurGrille, 20);
            break;
        case 3:
            afficherIterations(cheminHistorique);
            break;
        case 4:
            std::cout << "Au revoir !" << std::endl;
            break;
        }
    }

    return 0;
}

