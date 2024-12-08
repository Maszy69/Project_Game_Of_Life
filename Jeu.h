#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include "Grille.h"

// Classe représentant le jeu
class Jeu {
private:
    Grille grille; // Grille du jeu de la vie
    sf::RenderWindow fenetre; // Fenêtre SFML pour afficher la grille
    std::ofstream historique; // Fichier pour enregistrer l'historique des états de la grille
    int vitesseJeu; // Vitesse du jeu (intervalle de temps entre les mises à jour)
    bool enPause; // Indicateur de pause du jeu

public:
    // Constructeur de la classe Jeu
    Jeu(const std::string& cheminFichier, int tailleCellule, int largeurGrille, int hauteurGrille)
        : grille(largeurGrille, hauteurGrille),
        fenetre(sf::VideoMode(largeurGrille* tailleCellule, hauteurGrille* tailleCellule), "Jeu de la Vie"),
        vitesseJeu(100), enPause(false) {
        // Initialiser la grille à partir d'un fichier
        grille.initialiserDepuisFichier(cheminFichier);
        // Supprimer l'ancien historique
        std::remove((obtenirCheminDownloads() + "jeu_out.txt").c_str());
        // Ouvrir le fichier d'historique en mode ajout
        historique.open(obtenirCheminDownloads() + "jeu_out.txt", std::ios::app);
    }

    // Méthode pour démarrer le jeu
    void jouer() {
        // Boucle principale du jeu
        while (fenetre.isOpen()) {
            sf::Event evenement;
            // Gérer les événements de la fenêtre
            while (fenetre.pollEvent(evenement)) {
                if (evenement.type == sf::Event::Closed) fenetre.close();
                if (evenement.type == sf::Event::KeyPressed) {
                    if (evenement.key.code == sf::Keyboard::Q) fenetre.close();
                    else if (evenement.key.code == sf::Keyboard::Up) vitesseJeu = std::max(100, vitesseJeu - 100);
                    else if (evenement.key.code == sf::Keyboard::Down) vitesseJeu += 100;
                    else if (evenement.key.code == sf::Keyboard::G) grille.placerMotifAleatoire(glider());
                    else if (evenement.key.code == sf::Keyboard::B) grille.placerMotifAleatoire(block());
                    else if (evenement.key.code == sf::Keyboard::Space) enPause = !enPause; // Mettre en pause ou reprendre le jeu
                }
                if (evenement.type == sf::Event::MouseButtonPressed && evenement.mouseButton.button == sf::Mouse::Left) {
                    grille.definirCelluleAvecSouris(evenement.mouseButton.x, evenement.mouseButton.y, 20);
                }
            }

            // Mettre à jour la grille si le jeu n'est pas en pause
            if (!enPause) {
                grille.mettreAJour(historique);
            }

            // Effacer la fenêtre
            fenetre.clear(sf::Color::White);
            // Afficher la grille
            grille.afficher(fenetre, 20);
            // Afficher la fenêtre
            fenetre.display();

            // Attendre un certain temps avant la prochaine mise à jour
            std::this_thread::sleep_for(std::chrono::milliseconds(vitesseJeu));
        }
        // Fermer le fichier d'historique
        historique.close();
    }
};