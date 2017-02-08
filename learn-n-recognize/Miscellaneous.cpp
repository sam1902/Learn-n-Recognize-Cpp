//
//  Miscellaneous.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 07/02/2017.
//  Copyright © 2017 Samuel Prevost. All rights reserved.
//

#include "Miscellaneous.hpp"

std::string random_string(size_t length) {
    srand((unsigned)time(NULL));  //generate a seed by using the current time
    char str[length];
    str[length-1] = '\0';
    size_t i = 0;
    int r;
    
    for(i = 0; i < length-1; ++i) {
        for(;;) {
            r = rand() % 57 + 65; //interval between 65 ('A') and 65+57=122 ('z')
            if((r >= 65 && r <= 90) || (r >= 97 && r <= 122)) { // exclude '[' to '`'
                str[i] = (char)r;
                break;
            }
        }
    }
    
    return (std::string)str;
}

std::string timestamp(std::string format){
    // format example:
    // "%a, %d.%m.%Y %H:%M:%S"
    // Format: Mo, 15.06.2009 20:20:00
    
    std::time_t now = std::time(NULL);
    std::tm * ptm = std::localtime(&now);
    char buffer[128];
    
    std::strftime(buffer, 128, format.c_str(), ptm);
    std::string bufferStr = buffer;
    return bufferStr;
}

bool IsNumber(std::string nbr){
    char* ptr;
    strtol(nbr.c_str(), &ptr, 10);
    return *ptr == '\0' ? true : false;
}

std::string colorText(std::string inputText, int colorCode){
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
