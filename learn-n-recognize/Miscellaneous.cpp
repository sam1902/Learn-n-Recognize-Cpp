//
//  Miscellaneous.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 07/02/2017.
//  Copyright © 2017 Samuel Prevost. All rights reserved.
//

#include "Miscellaneous.hpp"

std::string random_string(size_t length){
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
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
