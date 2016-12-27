//
//  Message.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 22/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include "Message.hpp"

string colorText(string inputText, int colorCode){
    // 0: black
    // 1: red
    // 2: green
    // 3: yellow
    // 4: blue
    // 5: magenta
    // 6: cyan
    // 7: white
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

void Countdown(int seconds){
    for (int i = seconds; i > 0; i--) {
        cout << to_string(i) << "…" << endl;
        usleep(1000000);
    }
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

bool DoesSubjectExist(){
    char answ;
    do{
        cout << "Le sujet est-il déjà enregistré ? [y/n]" << endl;
        cin >> answ;
    } while( !cin.fail() && answ!='y' && answ!='n' );
    return answ=='y' ? true : false;
}

void AskSubjectNameAndID(string* name, int* id, Database* db){
    char answ;
    do{
        cout << "Connaissez-vous l'identifiant du sujet ? [y/n]" << endl;
        cin >> answ;
    } while( !cin.fail() && answ!='y' && answ!='n' );
    
    if(answ == 'y'){
        // ID is known
        string givenID;
        do{
            do{
                cout << "Quel est l'identifiant du sujet ?" << endl;
                cin >> givenID;
            } while( !cin.fail() && !IsNumber(givenID) );
            *id = stoi(givenID);
        } while( db->isSubjectIDValid(*id));
        
        *name = db->getSubjectName(*id);
    }else{
        // Name is known
        string givenName;
        do{
            do{
                cout << "Quel est le nom du sujet ?" << endl;
                cin >> givenName;
            } while( !cin.fail() );
            *name = givenName;
        } while( db->isSubjectNameValid(*name) );
        
        *id = db->getSubjectID(*name);
    }
}

bool IsNumber(string nbr){
    char* ptr;
    strtol(nbr.c_str(), &ptr, 10);
    return *ptr == '\0' ? true : false;

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

void InitEmptyLBPRMessage(){
    cout << colorText("[+] ", 3) << " Initialisation d'un LBPR vide. " << endl;
}

void ErrorOpeningCameraMessage(){
    cout << colorText("[+] ", 1) << "Erreur lors de l'ouverture du flux vidéo." << endl;
}

void LearningModeMessage(){
    cout << colorText("[+] ", 6) << "Vous allez entrer en mode apprentissage," << endl;
    cout << "veuillez positionner le sujet face à la caméra sans aucun autre visage" << endl;
    cout << "de manière à ce que le programme puisse assimiler son visage" << endl << endl;
    
    cout << colorText("[+] Début du compte à rebours", 1) << endl;
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
