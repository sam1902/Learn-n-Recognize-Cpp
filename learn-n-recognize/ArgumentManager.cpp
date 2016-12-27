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
    if(argc < 6){
        MissingArgsMessage();
        arguements = this->AskForArgs(argv[0]);
    }else{
        for (int i = 0; i < argc; i++) {
            // You could also allocate argc-slots to arguments but meh that's only 7 args
            arguements.push_back(argv[i]);
        }
    }
    database_path           =   arguements[1];
    recognizer_path         =   arguements[2];
    face_cascade_path       =   arguements[3];
    
    validity_threshold      =   stoi(arguements[4]);
    cameraID                =   stoi(arguements[5]);
    video_scaling_factor    =   stof(arguements[6]);
}

vector<string> ArgumentManager::AskForArgs(const char* argv_zero){
    vector<string> argv(7);
    argv[0] = argv_zero;
    cout << "Veuillez entrer les arguments:" << endl;
    cout << "\tChemin vers la base de donnée ?" << endl;
    cin >> argv[1];
    cout << "\tChemin vers le reconaisseur LBP ( n si aucun)?" << endl;
    cin >> argv[2];
    cout << "\tChemin vers la Face Cascade ?" << endl;
    cin >> argv[3];
    cout << "\tSeuil de validité au delà duquel le visage détecté est considéré comme valide en % ? (65 à 75 recommendé)" << endl;
    cin >> argv[4];
    cout << "\tIdentifiant de la caméra à utiliser ? (0 recommendé)" << endl;
    cin >> argv[5];
    cout << "\tTaille de la video affiiché ? (1 recommandé) ?" << endl;
    cin >> argv[6];
    
    return argv;
    // vector<string> to char** []
    // BE CAREFUL ! SEGMENTATION FAULT 11 IS WATCHING YOU !
//    for (int i = 0; i < newArgvStr.size(); i++) {
//        *argv[i] = newArgvStr[i].c_str();
//    }
}

