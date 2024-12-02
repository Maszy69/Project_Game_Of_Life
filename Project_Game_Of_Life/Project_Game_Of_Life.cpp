#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem> // ou <experimental/filesystem> selon le support
#include <cstdlib>
#include <windows.h>
#include <shlobj.h> // Pour SHGetFolderPath
#include "Grille.h"
#include "Cellule.h"

// Fonction pour obtenir le chemin du dossier Downloads
std::string obtenirCheminDownloads() {
    wchar_t cheminWide[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, cheminWide))) {
        std::wstring cheminUtilisateurWide(cheminWide);
        std::string cheminUtilisateur(cheminUtilisateurWide.begin(), cheminUtilisateurWide.end());
        return cheminUtilisateur + "\\Downloads\\";
    }
    else {
        std::cerr << "Erreur : Impossible de localiser le dossier Téléchargements." << std::endl;
        exit(1);
    }
}


// Fonction principale
int main() {
    // Obtenir le chemin du dossier Téléchargements
    std::string cheminDownloads = obtenirCheminDownloads();

    // Chemin du fichier d'entrée et de sortie
    std::string cheminFichierEntree = cheminDownloads + "etat_initial.txt";
    std::string cheminFichierSortie = cheminDownloads + "jeu_out.txt";

    // Ouvrir le fichier de sortie
    std::ofstream fichierSortie(cheminFichierSortie);
    if (!fichierSortie) {
        std::cerr << "Erreur : Impossible de créer le fichier de sortie " << cheminFichierSortie << std::endl;
        return 1;
    }

    Grille grille(0, 0);
    grille.initialiserDepuisFichier(cheminFichierEntree);

    int maxIterations = 100;
    Grille ancienneGrille = grille;

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        // Sauvegarder l'état dans le fichier
        fichierSortie << "Iteration " << iteration << ":" << std::endl;
        grille.sauvegarderEtat(fichierSortie);

        // Afficher l'état actuel dans la console
        std::cout << "Iteration " << iteration << " : " << std::endl;
        grille.afficher();

        // Mettre à jour la grille
        ancienneGrille = grille;
        grille.mettreAJour();

        // Vérifier si l'état est stable
        if (grille.estStable(ancienneGrille)) {
            std::cout << "Automate stable. Fin de l'exécution." << std::endl;
            break;
        }
    }

    fichierSortie.close();
    std::cout << "Les résultats ont été enregistrés dans : " << cheminFichierSortie << std::endl;

    return 0;
}