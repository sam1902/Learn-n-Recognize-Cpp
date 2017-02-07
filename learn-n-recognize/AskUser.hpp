//
//  AskUser.hpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 31/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#ifndef AskUser_hpp
#define AskUser_hpp

#include <iostream>
#include "Miscellaneous.hpp"

// Forward declaration
class Database;

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

string AskUser(string question);
bool AskYesNo(string question);
#endif /* AskUser_hpp */
