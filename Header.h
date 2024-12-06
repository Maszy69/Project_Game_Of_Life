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

// Fonction pour convertir std::wstring en std::string
std::string wstringToString(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

// Fonction pour obtenir le chemin du dossier Downloads
std::string obtenirCheminDownloads() {
    wchar_t cheminWide[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, cheminWide))) {
        return wstringToString(cheminWide) + "\\Downloads\\";
    }
    else {
        throw std::runtime_error("Erreur : Impossible de localiser le dossier Telechargements.");
    }
}

// Déclarations des fonctions pour les motifs
std::vector<std::vector<int>> glider();
std::vector<std::vector<int>> block();