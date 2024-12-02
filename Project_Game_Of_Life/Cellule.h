#pragma once
class Cellule {
private:
    bool vivante;

public:
    Cellule() : vivante(false) {}

    void definirEtat(bool etat) {
        vivante = etat;
    }

    bool estVivante() const {
        return vivante;
    }

    // Surcharge de l'opérateur ==
    bool operator==(const Cellule& autre) const {
        return vivante == autre.vivante;
    }
};