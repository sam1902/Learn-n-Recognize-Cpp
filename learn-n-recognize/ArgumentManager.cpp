//
//  ArgumentManager.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 24/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include "ArgumentManager.hpp"


ArgumentManager::ArgumentManager(int argc, const char * argv[]){
    vector<string> arguements;
    if(argc < 7){
        MissingArgsMessage();
        arguements = this->AskForArgs(argv[0]);
    }else{
        for (int i = 0; i < argc; i++) {
            // You could also allocate argc-slots to arguments but meh that's only 8 args
            arguements.push_back(argv[i]);
        }
    }
    database_path           =   arguements[1];
    recognizer_path         =   arguements[2];
    face_cascade_path       =   arguements[3];
    
    validity_threshold      =   stoi(arguements[4]);
    cameraID                =   stoi(arguements[5]);
    video_scaling_factor    =   stof(arguements[6]);
    
    save_path               =   arguements[7];
}

vector<string> ArgumentManager::AskForArgs(const char* argv_zero){
    vector<string> argv(8);
    argv[0] = argv_zero;
    cout << "Veuillez entrer les arguments:" << endl;
    
    argv[1] = trimmed(AskUser("\tChemin vers la base de donnée (n si aucun) ?\n"));
    if(argv[1] == "n")
        argv[1] = "";
    
    argv[2] = trimmed(AskUser("\tChemin vers le reconaisseur LBP (n si aucun)?\n"));
    if(argv[2] == "n")
        argv[2] = "";
    
    argv[3] = trimmed(AskUser("\tChemin vers la Face Cascade ?\n"));
    if(argv[3].size()<5){
        // Say goodbye
        cout << colorText("La Face Cascade est un élément essentiel au fonctionnement de ce programme, vous pouvez la téléchargée à l'adresse suivante:\n \thttps://raw.githubusercontent.com/opencv/opencv/master/data/haarcascades/haarcascade_frontalface_default.xml Taille: 930Ko\n\nCe fichier contient des données récoltées par des équipes scientifiques après plusieurs années de recherches et est utilisé afin de détecter la présence et la position d'un visage humain orienté verticalement face à la caméra.", 3) << endl;
        ExitMessage();
        exit(EXIT_SUCCESS);
    }
    
    do {
        argv[4] = AskUser("\tSeuil de validité au delà duquel le visage détecté est considéré comme valide en % ? (65 par défaut, n pour défaut)?\n");
        if(argv[4] == "n"){
            argv[4] = "65";
            break;
        }
    } while (!IsNumber(argv[4]));
    
    
    do {
        argv[5] = AskUser("\tIdentifiant de la caméra à utiliser ? (0 par défaut, n pour défaut)\n");
        if(argv[5] == "n"){
            argv[5] = "0";
            break;
        }
    } while (!IsNumber(argv[5]));
    
    do {
        argv[6] = AskUser("\tTaille de la video affiiché ? (1 recommandé, n pour défaut) ?\n");
        if(argv[6] == "n"){
            argv[6] = "0";
            break;
        }
    } while (!IsNumber(argv[6]));
    
    argv[7] = trimmed(AskUser("\tVeuillez fournir l'adresse d'un dossier\n\tafin d'y sauvegarder les nouveaux fichiers:\n"));
    
    return argv;
    // vector<string> to char** []
    // BE CAREFUL ! SEGMENTATION FAULT 11 IS WATCHING YOU !
//    for (int i = 0; i < newArgvStr.size(); i++) {
//        *argv[i] = newArgvStr[i].c_str();
//    }
}

