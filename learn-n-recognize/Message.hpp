//
//  Message.hpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 22/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#ifndef Message_hpp
#define Message_hpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using std::string;
using std::cout;
using std::endl;
#endif /* Message_hpp */

string colorText(string inputText, int colorCode);
void VersionMessage(string opencv_version);
void CreditsMessage();
void ErrorLoadingHaarMessage();
void MissingArgsMessage();
void EmptyFrameMessage();
void ExitMessage();
void InvalidDirectoryMessage(string path);
void FileFoundMessage(string filename, string path);
void FileNotFoundMessage(string filename, string path);
