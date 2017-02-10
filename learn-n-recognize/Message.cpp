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
    cout << colorText("\t==> ", RED) << colorText("Learn'n'Recognize par Samuel Prevost dans le cadre du TPE", WHITE) << colorText(" <==\t", RED) << endl;
}

void ExitMessage(){
    cout << colorText("Extinction imminante du programme", RED) << endl;
}

void MissingArgsMessage(){
    cout << colorText("[!] Arguments manquants !", RED) << endl;
}

void HelpMessage(){
    cout << "Bienvenu dans Learn'n'Recognize,"
    << endl
    << "Syntaxe: ./learn-n-recognize [options]"
    << endl
    << endl
    << "Liste des options :"
    << endl
    << endl
    << "-h , -help, -aide"
    << endl
    <<      "\tAffiche ce message d'aide."
    << endl
    << endl
    << "-i , -gui, -interface, -GUI"
    << endl
    <<      "\tAffiche une série de dialogue permettant le choix de chacun des arguments"
    << endl
    << endl
    << "-s, -save /chemin/vers/dossier"
    << endl
    << "\tChemin où sauvegarder les fichiers tel que la base de donnée (si non précédement fournis) ou le nouveau reconaisseur LBP (répertoire de l'executable par défaut)"
    << endl
    << endl
    << "-haar /chemin/vers/fichier/haar.xml"
    << endl
    <<      "\tChemin vers la Face Cascade (disponible à l'adresse : https://raw.githubusercontent.com/opencv/opencv/master/data/haarcascades/haarcascade_frontalface_default.xml) (téléchargement automatique par défaut)"
    << endl
    << endl
    << "-db , -database /chemin/vers/fichier/database.sqlite"
    << endl
    <<      "\tChemin vers la base de donnée (création automatique par défaut)"
    << endl
    << endl
    << "-rec, -recognizer /chemin/vers/fichier/LBPH.xml"
    << endl
    <<      "\tChemin vers le reconaisseur LBP (création automatique par défaut)"
    << endl
    << endl
    << "-vt, -validityThreshold 65"
    << endl
    <<      "\tSeuil de validité au delà duquel une détection est considéré comme trop hasardeuse (65 par défaut, en %) "
    << endl
    << endl
    << "-cam, -cameraID 0"
    << endl
    <<      "\tIdentifiant de la caméra à utilisé (0 par défaut) "
    << endl
    << endl
    << "-scale 1"
    << endl
    <<      "\tTaille de la vidéo affiché (par ratio, 1 par défaut) "
    << endl;
}

// ### OpenCV ###
void VersionMessage(string opencv_version){
    cout << colorText("[+]", GREEN) << " OpenCV Version " << opencv_version << " chargé avec succes !"<< endl;
}

void EmptyFrameMessage(){
    cout << colorText("[!] Aucune image capturé ! Break", YELLOW) << endl;
}

void ErrorLoadingHaarMessage(){
    cerr << colorText("[!] Erreur lors du chargement de la Face Cascade.", RED) << endl;
}

void ErrorNoFaceCascadeProvided(){
    cout << colorText("La Face Cascade est un élément essentiel au fonctionnement de ce programme, vous pouvez la téléchargée à l'adresse suivante:\n \thttps://raw.githubusercontent.com/opencv/opencv/master/data/haarcascades/haarcascade_frontalface_default.xml Taille: 930Ko\n\nCe fichier contient des données récoltées par des équipes scientifiques après plusieurs années de recherches et est utilisé afin de détecter la présence et la position d'un visage humain orienté verticalement face à la caméra.", YELLOW) << endl;
}

void SuccessLoadingHaarMessage(){
    cout << colorText("[+] ", GREEN) << "Chargement de la Face Cascade réussi !" << endl;
}

void ErrorLoadingLBPRMessage(){
    cerr << colorText("[!] Erreur lors du chargement de LBPR.", RED) << endl;
}

void SuccessLoadingLBPRMessage(){
    cout << colorText("[+] ", GREEN) << "Chargement de LBPR réussi ! " << endl;
}

void WarningInitEmptyLBPRMessage(){
    cout << colorText("[+] Initialisation d'un LBPR vide.", YELLOW) << endl;
}

void ErrorUpdateNotInitializedLBPR(){
    cerr << colorText("[+] ", YELLOW) << " Tentative d'update du LBPR vide, à la place le LBPR à été train. " << endl;
}

void ErrorOpeningCameraMessage(){
    cerr << colorText("[!] Erreur lors de l'ouverture du flux vidéo.", RED) << endl;
}

void LearningModeMessage(){
    cout << colorText("[+] Vous allez entrer en mode apprentissage", CYAN) << endl;
    cout << "\tVeuillez positionner le sujet face à la caméra sans aucun autre visage" << endl;
    cout << "\tde manière à ce que le programme puisse assimiler son visage" << endl << endl;
    
    cout << colorText("[!] Début du compte à rebours", RED) << endl;
}

void ScanningModeMessage(){
    cout << colorText("[+] Vous allez entrer en mode scan", CYAN) << endl;
    cout << "\tVeuillez positionner le(s) sujet(s) face à la caméra" << endl;
    cout << "\tde manière à ce que le programme déssine un carré autour du/des visage(s)." << endl;
    cout << "\t Si le LBPR est vide, aucun nom ne sera afficher. Passez en mode apprentissage (l) pour y remédier." << endl << endl;
    
    cout << colorText("[!] Début du compte à rebours", YELLOW) << endl;
}

void SuccessSavingLBPRMessage(string pathToLBPR){
    cout << colorText("[+] ", GREEN) << "Sauvegarde du reconaisseur LBP réussi ! Il se trouve à l'adresse : " << endl << pathToLBPR << endl;
}

void NotBeenImprovedSavingLBPR(){
    cout << colorText("[+] Le LBPH n'a pas été sauvegardé, car aucune modification ne lui a été apportée.", YELLOW) << endl;
}
// ### File Loader ###

void InvalidDirectoryMessage(string path){
    cerr << colorText("[!] Erreur l'ouverture de ", RED) << path << endl;
}

void FileFoundMessage(string filename, string path){
    cout << colorText("[+]", GREEN) << filename << " a été trouvé dans " << path << endl;
}

void FileNotFoundMessage(string filename, string path){
    cerr << colorText("[!] ", RED) << filename << colorText(" n'a pas été trouvé dans ", RED) << path << endl;
}

// #### Database ####

void ErrorAccessDBMessage(string error){
    cerr << colorText("[!] Impossible d'accèder à la base de données:", RED) << error << endl;
}

void ErrorCreateDBMessage(string error){
    cerr << colorText("[!] Impossible de créer la base de données:", RED) << error << endl;
}

void SuccessAccessDBMessage(){
    cout << colorText("[+] ", GREEN) << "Accès à la base de données réussi ! " << endl;
}

void SuccessCreateDBMessage(string pathToDB){
    cout << colorText("[+] ", GREEN) << "Création de la base de données réussi ! Il se trouve à l'adresse : " << endl << pathToDB << endl;
}

void SuccessFindSubject(){
    cout << colorText("[+] ", GREEN) << "Le sujet à été trouvé ! " << endl;
}

void DisplayIDSubject(string id){
    cout << colorText("[+] ", GREEN) << "L'identifiant du sujet est: " << id << endl;
}

void DisplayNameSubject(string name){
    cout << colorText("[+] ", GREEN) << "Le nom du sujet est: " << name << endl;
}

void InvalidIDSubjet(){
    cout << colorText("[!] L'identifiant du sujet est introuvable !", RED) << endl;
}

void ErrorInsertSubjectDBMessage(string error){
    cerr << colorText("[!] Impossible d'ajouter le sujet à la base de données:", RED) << error << endl;
}

void SuccessInsertSubjectMessage(string subjectName, string subjectID){
    cout << colorText("[+] ", GREEN) << "Enregistrement du sujet réussi !" << endl << "Nom:\t\t\t" << subjectName << endl << "Identifiant:\t\t" << subjectID << endl;
}

void ErrorExecuteQueryDBMessage(string query, string error){
    cerr << colorText("[!] Impossible d'exécuter la requète", RED) << " \"" << query << "\" : " << error << endl;
}

// ### cURL ###

void ErrorDownloadingFile(string url, string status){
    cerr << colorText("[!] Impossible de télécharger le fichier à l'adresse ", RED) << url << " : " << endl << status << endl;
}

void SuccessDownloadingFile(string url, string outfilename, string status){
    cout << colorText("[+] ", GREEN) << "Téléchargement du fichier réussi !" << endl << "URL: " << url << endl << "Fichier de sortie: " << outfilename << endl << "Status de la requête: " << status << endl << endl;
}
