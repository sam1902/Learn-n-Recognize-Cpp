//
//  Message.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 22/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include "Message.hpp"

#include "Database.hpp"

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
        *id = AskExistingSubjectID(db);
        
        *name = db->getSubjectName(*id);
    }else{
        // Name is known
        *name = AskExistingSubjectName(db);
        
        *id = db->getSubjectID(*name);
    }
}

int AskExistingSubjectID(Database* db){
    string givenID;
    int id;
    while(!db->isSubjectIDValid(id)){
        do{
            cout << "Quel est l'identifiant du sujet ?" << endl;
            cin >> givenID;
        } while( !cin.fail() && !IsNumber(givenID) && givenID == "-1");
        id = stoi(givenID);
    }
    return id;
}

string AskNewSubjectName(Database* db){
    string givenName;
    string name;
    while(db->isSubjectNameValid(name)) {
        do{
            cout << "Quel est le nom du nouveau sujet ?" << endl;
            getline(cin, givenName);
        } while( !cin.fail() && !(givenName.size()>0) && givenName == "-1");
        name = givenName;
    }
    return name;
}

string AskExistingSubjectName(Database* db){
    string givenName;
    string name;
    while(!db->isSubjectNameValid(name)) {
        do{
            cout << "Quel est le nom du sujet déjà existant ?" << endl;
            getline(cin, givenName);
        } while( !cin.fail() && !(givenName.size()>0) && givenName == "-1");
        name = givenName;
    }
    return name;
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
    cout << colorText("[!] Aucune image capturé ! Break", 1) << endl;
}

void ErrorLoadingHaarMessage(){
    cout << colorText("[!] Erreur lors du chargement de la Face Cascade.", 1) << endl;
}

void SuccessLoadingHaarMessage(){
    cout << colorText("[+] ", 2) << "Chargement de la Face Cascade réussi !" << endl;
}

void ErrorLoadingLBPRMessage(){
    cout << colorText("[!] Erreur lors du chargement de LBPR.", 1) << endl;
}

void SuccessLoadingLBPRMessage(){
    cout << colorText("[+] ", 2) << "Chargement de LBPR réussi ! " << endl;
}

void WarningInitEmptyLBPRMessage(){
    cout << colorText("[+] Initialisation d'un LBPR vide.", 3) << endl;
}

void ErrorUpdateNotInitializedLBPR(){
    cout << colorText("[+] ", 3) << " Tentative d'update du LBPR vide, à la place le LBPR à été train. " << endl;
}

void ErrorOpeningCameraMessage(){
    cout << colorText("[!] Erreur lors de l'ouverture du flux vidéo.", 1) << endl;
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

string AskWhereToSaveRecognizer(){
    string dir;
    cout << "Où souhaitez-vous sauvegarder le reconaisseur LBP ? " << endl;
    cout << "(indiquez un répertoire dans le format suivant: /chemin/vers/repertoireSansSlash )" << endl;
    getline(cin, dir);
    return dir;
}
// ### File Loader ###

void InvalidDirectoryMessage(string path){
    cout << colorText("[!] Erreur l'ouverture de ", 1) << path << endl;
}

void FileFoundMessage(string filename, string path){
    cout << colorText("[+]", 2) << filename << " a été trouvé dans " << path << endl;
}

void FileNotFoundMessage(string filename, string path){
    cout << colorText("[!] ", 1) << filename << colorText(" n'a pas été trouvé dans ", 1) << path << endl;
}

// #### Database ####

void ErrorAccessDBMessage(string error){
    cout << colorText("[!] Impossible d'accèder à la base de données:", 1) << error << endl;
}

void ErrorCreateDBMessage(string error){
    cout << colorText("[!] Impossible de créer la base de données:", 1) << error << endl;
}

void SuccessAccessDBMessage(){
    cout << colorText("[+] ", 2) << "Accès à la base de données réussi ! " << endl;
}

void SuccessCreateDBMessage(){
    cout << colorText("[+] ", 2) << "Création de la base de données réussi ! " << endl;
}

void ErrorInsertSubjectDBMessage(string error){
    cout << colorText("[!] Impossible d'ajouter le sujet à la base de données:", 1) << error << endl;
}

void ErrorExecuteQueryDBMessage(string query, string error){
    cout << colorText("[!] Impossible d'exécuter la requète", 1) << " \"" << query << "\" : " << error << endl;
}
