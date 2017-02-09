//
//  Miscellaneous.hpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 07/02/2017.
//  Copyright © 2017 Samuel Prevost. All rights reserved.
//

#ifndef Miscellaneous_hpp
#define Miscellaneous_hpp

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <ctime>
#include <unistd.h>
#include <locale>

std::string random_string(size_t length);
std::string timestamp(std::string format);

bool IsNumber(std::string nbr);
void Countdown(int seconds);

// 0: black
// 1: red
// 2: green
// 3: yellow
// 4: blue
// 5: magenta
// 6: cyan
// 7: white
std::string colorText(std::string inputText, int colorCode);

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

// trim from start (copying)
static inline std::string ltrimmed(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrimmed(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trimmed(std::string s) {
    trim(s);
    return s;
}

#endif /* Miscellaneous_hpp */
