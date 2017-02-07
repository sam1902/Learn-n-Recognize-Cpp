//
//  Message.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 22/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include "Message.hpp"

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
    cout << colorText("Extinction imminante du programme", 1) << endl;
}

void Countdown(int seconds){
    for (int i = seconds; i > 0; i--) {
        cout << to_string(i) << "…" << endl;
        usleep(1000000);
    }
}

void MissingArgsMessage(){
    cout << colorText("[!] ", 1) << "Arguments manquants" << endl
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
    cout << colorText("[!] Aucune image capturé ! Break", 3) << endl;
}

void ErrorLoadingHaarMessage(){
    cerr << colorText("[!] Erreur lors du chargement de la Face Cascade.", 1) << endl;
}

void SuccessLoadingHaarMessage(){
    cout << colorText("[+] ", 2) << "Chargement de la Face Cascade réussi !" << endl;
}

void ErrorLoadingLBPRMessage(){
    cerr << colorText("[!] Erreur lors du chargement de LBPR.", 1) << endl;
}

void SuccessLoadingLBPRMessage(){
    cout << colorText("[+] ", 2) << "Chargement de LBPR réussi ! " << endl;
}

void WarningInitEmptyLBPRMessage(){
    cout << colorText("[+] Initialisation d'un LBPR vide.", 3) << endl;
}

void ErrorUpdateNotInitializedLBPR(){
    cerr << colorText("[+] ", 3) << " Tentative d'update du LBPR vide, à la place le LBPR à été train. " << endl;
}

void ErrorOpeningCameraMessage(){
    cerr << colorText("[!] Erreur lors de l'ouverture du flux vidéo.", 1) << endl;
}

void LearningModeMessage(){
    cout << colorText("[+] Vous allez entrer en mode apprentissage", 6) << endl;
    cout << "\tVeuillez positionner le sujet face à la caméra sans aucun autre visage" << endl;
    cout << "\tde manière à ce que le programme puisse assimiler son visage" << endl << endl;
    
    cout << colorText("[!] Début du compte à rebours", 1) << endl;
}

void ScanningModeMessage(){
    cout << colorText("[+] Vous allez entrer en mode scan", 6) << endl;
    cout << "\tVeuillez positionner le(s) sujet(s) face à la caméra" << endl;
    cout << "\tde manière à ce que le programme déssine un carré autour du/des visage(s)." << endl;
    cout << "\t Si le LBPR est vide, aucun nom ne sera afficher. Passez en mode apprentissage (l) pour y remédier." << endl << endl;
    
    cout << colorText("[!] Début du compte à rebours", 3) << endl;
}
// ### File Loader ###

void InvalidDirectoryMessage(string path){
    cerr << colorText("[!] Erreur l'ouverture de ", 1) << path << endl;
}

void FileFoundMessage(string filename, string path){
    cout << colorText("[+]", 2) << filename << " a été trouvé dans " << path << endl;
}

void FileNotFoundMessage(string filename, string path){
    cerr << colorText("[!] ", 1) << filename << colorText(" n'a pas été trouvé dans ", 1) << path << endl;
}

// #### Database ####

void ErrorAccessDBMessage(string error){
    cerr << colorText("[!] Impossible d'accèder à la base de données:", 1) << error << endl;
}

void ErrorCreateDBMessage(string error){
    cerr << colorText("[!] Impossible de créer la base de données:", 1) << error << endl;
}

void SuccessAccessDBMessage(){
    cout << colorText("[+] ", 2) << "Accès à la base de données réussi ! " << endl;
}

void SuccessCreateDBMessage(){
    cout << colorText("[+] ", 2) << "Création de la base de données réussi ! " << endl;
}

void SuccessFindSubject(){
    cout << colorText("[+] ", 2) << "Le sujet à été trouvé ! " << endl;
}

void DisplayIDSubject(string id){
    cout << colorText("[+] ", 2) << "L'identifiant du sujet est: " << id << endl;
}

void DisplayNameSubject(string name){
    cout << colorText("[+] ", 2) << "Le nom du sujet est: " << name << endl;
}

void InvalidIDSubjet(){
    cout << colorText("[!] L'identifiant du sujet est introuvable !", 1) << endl;
}

void ErrorInsertSubjectDBMessage(string error){
    cerr << colorText("[!] Impossible d'ajouter le sujet à la base de données:", 1) << error << endl;
}

void ErrorExecuteQueryDBMessage(string query, string error){
    cerr << colorText("[!] Impossible d'exécuter la requète", 1) << " \"" << query << "\" : " << error << endl;
}
