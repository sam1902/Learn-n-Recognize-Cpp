//
//  AskUser.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 31/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include "AskUser.hpp"

string AskUser(string question){
    string result;
    std::cout << question;
    while(!std::getline(std::cin, result)){
        std::cerr << "Entrée invalide, veuillez réessayer:" << std::endl;
    }
    return result;
}

bool AskYesNo(string question){
    string result;
    do{
        result = AskUser(question);
    }while(
           (result != "N" && result != "No" && result != "n" && result != "no") &&
           (result != "Y" && result != "Yes" && result != "y" && result != "yes")
           );
    
    // Check if the result contain the y/Y letter
    return (
            (result.find("Y") != std::string::npos) ||
            (result.find("y") != std::string::npos)
            ) ? true : false;
}
