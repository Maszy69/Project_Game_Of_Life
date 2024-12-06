#pragma once
// Classe représentant le jeu
class Jeu {
private:
    Grille grille;
    sf::RenderWindow fenetre;
    std::ofstream historique;
    int vitesseJeu;
    bool enPause;

public:
    Jeu(const std::string& cheminFichier, int tailleCellule, int largeurGrille, int hauteurGrille)
        : grille(largeurGrille, hauteurGrille),
        fenetre(sf::VideoMode(largeurGrille* tailleCellule, hauteurGrille* tailleCellule), "Jeu de la Vie"),
        vitesseJeu(100), enPause(false) {
        grille.initialiserDepuisFichier(cheminFichier);
        // Supprimer l'ancien historique
        std::remove((obtenirCheminDownloads() + "jeu_out.txt").c_str());
        historique.open(obtenirCheminDownloads() + "jeu_out.txt", std::ios::app);
    }

    void jouer() {
        while (fenetre.isOpen()) {
            sf::Event evenement;
            while (fenetre.pollEvent(evenement)) {
                if (evenement.type == sf::Event::Closed) fenetre.close();
                if (evenement.type == sf::Event::KeyPressed) {
                    if (evenement.key.code == sf::Keyboard::Q) fenetre.close();
                    else if (evenement.key.code == sf::Keyboard::Up) vitesseJeu = std::max(100, vitesseJeu - 100);
                    else if (evenement.key.code == sf::Keyboard::Down) vitesseJeu += 100;
                    else if (evenement.key.code == sf::Keyboard::G) grille.placerMotifAleatoire(glider());
                    else if (evenement.key.code == sf::Keyboard::B) grille.placerMotifAleatoire(block());
                    else if (evenement.key.code == sf::Keyboard::Space) enPause = !enPause; // Toggle pause

                }
                if (evenement.type == sf::Event::MouseButtonPressed && evenement.mouseButton.button == sf::Mouse::Left) {
                    grille.definirCelluleAvecSouris(evenement.mouseButton.x, evenement.mouseButton.y, 20);
                }
            }

            if (!enPause) {
                grille.mettreAJour(historique);
            }

            fenetre.clear(sf::Color::White);
            grille.afficher(fenetre, 20);
            fenetre.display();

            std::this_thread::sleep_for(std::chrono::milliseconds(vitesseJeu));
        }
        historique.close();
    }
};