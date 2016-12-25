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

// ### General ###
string colorText(string inputText, int colorCode);
void ClearMessage();
void ExitMessage();
void CreditsMessage();
void MissingArgsMessage();

// ### OpenCV ###
void VersionMessage(string opencv_version);
void ErrorLoadingHaarMessage();
void SuccessLoadingHaarMessage();
void ErrorLoadingLBPRMessage();
void SuccessLoadingLBPRMessage();
void EmptyFrameMessage();
void ErrorOpeningCameraMessage();

// ### File Loader ###
void InvalidDirectoryMessage(string path);
void FileFoundMessage(string filename, string path);
void FileNotFoundMessage(string filename, string path);

// ### Database ###
void ErrorAccessDBMessage(string error);
void ErrorCreateDBMessage(string error);
void SuccessAccessDBMessage();
void SuccessCreateDBMessage();
void ErrorExecuteQueryDBMessage(string query, string error);

#endif /* Message_hpp */
