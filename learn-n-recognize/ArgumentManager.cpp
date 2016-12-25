//
//  ArgumentManager.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 24/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include "ArgumentManager.hpp"


ArgumentManager::ArgumentManager(int argc, const char * argv[]){
    if(argc < 5){
        MissingArgsMessage();
        if(!this->AskForArgs(argc, &argv))
            exit(EXIT_FAILURE);
    }
    database_path           =   argv[1];
    face_cascade_path       =   argv[2];
    
    validity_threshold      =   stoi(argv[3]);
    cameraID                =   stoi(argv[4]);
    video_scaling_factor    =   stof(argv[5]);
}

bool ArgumentManager::AskForArgs(int argc, const char** argv[]){
    vector<string> newArgvStr(6);
    newArgvStr[0] = *argv[0];
    cout << "Veuillez entrer les arguments:" << endl;
    cout << "\tChemin vers la base de donnée ?" << endl;
    cin >> newArgvStr[1];
    cout << "\tChemin vers la Face Cascade ?" << endl;
    cin >> newArgvStr[2];
    cout << "\tSeuil de validité au delà duquel le visage détecté est considéré comme valide en % ? (65 à 75 recommendé)" << endl;
    cin >> newArgvStr[3];
    cout << "\tIdentifiant de la caméra à utiliser ? (0 recommendé)" << endl;
    cin >> newArgvStr[4];
    cout << "\tTaille de la video affiiché ? (1 recommandé) ?" << endl;
    cin >> newArgvStr[5];
    
    // vector<string> to char** []
    for (int i = 0; i < newArgvStr.size(); i++) {
        *argv[i] = newArgvStr[i].c_str();
    }
    return true;
}

