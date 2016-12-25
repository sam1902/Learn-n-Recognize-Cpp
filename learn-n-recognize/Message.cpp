//
//  Message.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 22/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include "Message.hpp"

string colorText(string inputText, int colorCode){
    return "\033[1;3" + std::to_string(colorCode) + "m" + inputText + "\033[0m";
}

// ### General ###

void ClearMessage(){
    // ############ ANSI ############
    // \033[2J      : escape char from top to bot
    // \033[1;1H    : set cursor at pos 1,1
    cout << "\033[2J" << "\033[1;1H";
}

void CreditsMessage(){
    cout << colorText("\t==> ", 1) << colorText("Learn'n'Recognize par Samuel Prevost dans le cadre du TPE", 7) << colorText(" <==\t", 1) << endl;
}

void ExitMessage(){
    cout << "Extinction imminante du programme" << endl;
}

void MissingArgsMessage(){
    cout << colorText("[+] ", 1) << "Arguments manquants" << endl
    << "Arguments: " << endl
    << "\t• Chemin vers la base de donnée\t"                    << endl
    << "\t• Chemin vers la Face Cascade\t"                      << endl
    << endl
    << "\t• Seuil de validité\t\t\t(0-100)"                     << endl
    << "\t• Identifiant de la caméra\t\t(Ex: 0)"                << endl
    << "\t• Coef d'agrandissement video\t\t(Ex: 1)"             << endl
    << endl;
}

// ### OpenCV ###
void VersionMessage(string opencv_version){
    cout << colorText("[+]", 2) << " OpenCV Version " << opencv_version << " chargé avec succes !"<< endl;
}

void EmptyFrameMessage(){
    cout << colorText("[+] ", 1) << "Aucune image capturé ! Break" << endl;
}

void ErrorLoadingHaarMessage(){
    cout << colorText("[+] ", 1) << "Erreur lors du chargement de la Face Cascade." << endl;
}

void SuccessLoadingHaarMessage(){
    cout << colorText("[+] ", 2) << " Chargement de la Face Cascade réussi ! " << endl;
}

void ErrorLoadingLBPRMessage(){
    cout << colorText("[+] ", 1) << "Erreur lors du chargement de LBPR." << endl;
}

void SuccessLoadingLBPRMessage(){
    cout << colorText("[+] ", 2) << " Chargement de LBPR réussi ! " << endl;
}

void ErrorOpeningCameraMessage(){
    cout << colorText("[+] ", 1) << "Erreur lors de l'ouverture du flux vidéo." << endl;
}

// ### File Loader ###

void InvalidDirectoryMessage(string path){
    cout << colorText("[+] ", 1) << "Erreur l'ouverture de " << path << endl;
}

void FileFoundMessage(string filename, string path){
    cout << colorText("[+]", 2) << filename << " a été trouvé dans " << path << endl;
}

void FileNotFoundMessage(string filename, string path){
    cout << colorText("[+] ", 1) << filename << " n'a pas été trouvé dans " << path << endl;
}

// #### Database ####

void ErrorAccessDBMessage(string error){
    cout << colorText("[+] ", 1) << " Impossible d'accèder à la base de données: " << error << endl;
}

void ErrorCreateDBMessage(string error){
    cout << colorText("[+] ", 1) << " Impossible de créer la base de données: " << error << endl;
}

void SuccessAccessDBMessage(){
    cout << colorText("[+] ", 2) << " Accès à la base de données réussi ! " << endl;
}

void SuccessCreateDBMessage(){
    cout << colorText("[+] ", 2) << " Création de la base de données réussi ! " << endl;
}

void ErrorExecuteQueryDBMessage(string query, string error){
    cout << colorText("[+] ", 1) << " Impossible d'exécuter la requète \"" << query << "\" : " << error << endl;
}
