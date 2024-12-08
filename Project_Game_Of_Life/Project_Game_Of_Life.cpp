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

// Fonction principale du programme
int main() {
    // Initialiser le générateur de nombres aléatoires avec l'heure actuelle
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Définir les chemins des fichiers d'état initial et d'historique
    const std::string cheminFichier = obtenirCheminDownloads() + "etat_initial.txt";
    const std::string cheminHistorique = obtenirCheminDownloads() + "jeu_out.txt";

    // Définir les dimensions par défaut de la grille
    int largeurGrille = 10, hauteurGrille = 10;

    // Vérifier si le fichier d'état initial existe
    std::ifstream fichierTest(cheminFichier);
    if (!fichierTest) {
        // Si le fichier n'existe pas, le créer avec des dimensions par défaut
        std::ofstream fichier(cheminFichier);
        fichier << "10 10" << std::endl;
        std::cout << "Fichier cree avec des dimensions par defaut (10x10)." << std::endl;
    }
    else {
        // Si le fichier existe, lire les dimensions de la grille
        fichierTest >> hauteurGrille >> largeurGrille;
    }

    int choix = 0;

    // Boucle principale du menu
    while (choix != 4) {
        // Afficher le menu
        std::cout << "=== Menu ===" << std::endl;
        std::cout << "1. Jouer" << std::endl;
        std::cout << "2. Modifier la taille de la grille" << std::endl;
        std::cout << "3. Afficher les iterations" << std::endl;
        std::cout << "4. Quitter" << std::endl;

        // Demander à l'utilisateur de faire un choix
        do {
            std::cout << "Veuillez entrer votre choix (1, 2, 3 ou 4) : ";
            std::cin >> choix;

            if (choix < 1 || choix > 4) {
                std::cout << "Choix invalide. Veuillez entrer un choix valide." << std::endl;
            }
        } while (choix < 1 || choix > 4);

        // Exécuter l'action correspondant au choix de l'utilisateur
        switch (choix) {
        case 1: {
            // Lancer le jeu
            Jeu jeu(cheminFichier, 20, largeurGrille, hauteurGrille);
            jeu.jouer();
            break;
        }
        case 2:
            // Modifier la taille de la grille
            modifierTailleGrille(cheminFichier, largeurGrille, hauteurGrille);
            afficherInterfaceModifierGrille(cheminFichier, largeurGrille, hauteurGrille, 20);
            break;
        case 3:
            // Afficher les itérations du jeu à partir du fichier d'historique
            afficherIterations(cheminHistorique);
            break;
        case 4:
            // Quitter le programme
            std::cout << "Au revoir !" << std::endl;
            break;
        }
    }

    return 0;
}
