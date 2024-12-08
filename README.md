# GameOfLife

Ce projet implémente le célèbre "Jeu de la Vie" de John Conway en utilisant la bibliothèque SFML pour l'affichage graphique. Le jeu de la vie est un automate cellulaire où chaque cellule de la grille peut être vivante ou morte, et son état évolue en fonction de règles simples basées sur les cellules voisines.

## Fonctionnalités

- Initialisation de la grille à partir d'un fichier.
- Affichage graphique de la grille en utilisant SFML.
- Interaction avec la grille via la souris pour changer l'état des cellules.
- Possibilité de mettre en pause et de reprendre le jeu.
- Enregistrement de l'historique des états de la grille.
- Modification de la taille de la grille.
- Affichage des itérations du jeu à partir d'un fichier d'historique.

## Prérequis

- [SFML](https://www.sfml-dev.org/download.php) (Simple and Fast Multimedia Library)
- Un compilateur compatible avec C++14 (par exemple, g++, clang++, MSVC)

## Installation

1. Téléchargez et installez SFML en suivant les instructions sur le site officiel : [SFML Download](https://www.sfml-dev.org/download.php)

2. Clonez ce dépôt ou téléchargez les fichiers sources.

3. Assurez-vous que SFML est correctement configuré dans votre environnement de développement.

## Compilation

### Utilisation de Visual Studio Code

1. Créez un dossier `.vscode` dans le répertoire racine de votre projet.

2. Ajoutez un fichier `settings.json` dans le dossier `.vscode` avec le contenu suivant :
