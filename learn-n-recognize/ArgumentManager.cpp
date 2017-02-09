//
//  ArgumentManager.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 24/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include "ArgumentManager.hpp"


ArgumentManager::ArgumentManager(int argc, const char * argv[]){
    // NB: strcmp() return 0 if the two string are the same, 0 is false so ! make it true so
    // if(!strcmp(str1, str2)) is the same as if(strcmp(str1, str2) == 0) is the same as
    // "if str1 and str2 are the same strings"
    
    
    // Check if the user requested to see the help message
    if(argc == 1){
        HelpMessage();
        ExitMessage();
        exit(EXIT_SUCCESS);
    }
    for (int i = 1; i < argc; i++) {
        if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "-help") || !strcmp(argv[i], "-aide")){
            HelpMessage();
            ExitMessage();
            exit(EXIT_SUCCESS);
        }
    }
    
    vector<string> arguements;
    if(!this->IsMandatoryArgs(argv, argc)){
        MissingArgsMessage();
        arguements = this->AskForArgs(argv[0]);
        
        program_path            =   arguements[0];
        database_path           =   arguements[1];
        recognizer_path         =   arguements[2];
        face_cascade_path       =   arguements[3];
        
        validity_threshold      =   stoi(arguements[4]);
        cameraID                =   stoi(arguements[5]);
        video_scaling_factor    =   stof(arguements[6]);
        
        save_path               =   arguements[7];
        
    }else{
        
        program_path = argv[0];
        
        for (int i = 1; i < argc; i++) {
            // Avoid 11: Segemntation fault
            if(i+1 > argc)
                break;
            
            // strcmp return 0 if equal, <0 or >0 if less or more
            if(!strcmp(argv[i], "-db") || !strcmp(argv[i], "-database")){
                database_path           =       trimmed(argv[i+1]);
                
            }else if(!strcmp(argv[i], "-rec") || !strcmp(argv[i], "-recognizer")){
                recognizer_path         =       trimmed(argv[i+1]);
                
            }else if(!strcmp(argv[i], "-haar")){
                face_cascade_path       =       trimmed(argv[i+1]);
                
            }else if(!strcmp(argv[i], "-validityThreshold") || !strcmp(argv[i], "-vt")){
                validity_threshold      =       stoi(trimmed(argv[i+1]));
                
            }else if(!strcmp(argv[i], "-cam") || !strcmp(argv[i], "-cameraID")){
                cameraID                =       stoi(trimmed(argv[i+1]));
                
            }else if(!strcmp(argv[i], "-scale")){
                video_scaling_factor    =       stoi(trimmed(argv[i+1]));
                
            }else if(!strcmp(argv[i], "-save") || !strcmp(argv[i], "-s")){
                save_path               =       trimmed(argv[i+1]);
            }
        }
    }
    
    if(face_cascade_path.size() < 5){
        ErrorNoFaceCascadeProvided();
        ExitMessage();
        exit(EXIT_SUCCESS);
    }
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
        ErrorNoFaceCascadeProvided();
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

bool ArgumentManager::IsMandatoryArgs(const char* argv[], int argc){
    bool isHaar = false, isSavePath = false;
    for (int i = 0; i < argc; i++) {
        if(!strcmp(argv[i], "-haar"))
            isHaar = true;
        else if(!strcmp(argv[i], "-save") || !strcmp(argv[i], "-s"))
            isSavePath = true;
    }
    return isHaar && isSavePath;
}
