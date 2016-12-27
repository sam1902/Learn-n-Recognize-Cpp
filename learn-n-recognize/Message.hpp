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
#include <unistd.h>

#include "Database.hpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;

// ### General ###
string colorText(string inputText, int colorCode);
void ClearMessage();
void ExitMessage();
void CreditsMessage();
void Countdown(int seconds);
void MissingArgsMessage();

bool DoesSubjectExist();
void AskSubjectNameAndID(string* name, int* id, Database* db);

// ### OpenCV ###
void VersionMessage(string opencv_version);
// Haar
void ErrorLoadingHaarMessage();
void SuccessLoadingHaarMessage();
// LBPR
void ErrorLoadingLBPRMessage();
void SuccessLoadingLBPRMessage();
void InitEmptyLBPRMessage();
// Camera
void EmptyFrameMessage();
void ErrorOpeningCameraMessage();
// Mode transition
void LearningModeMessage();
// TODO :
//void ScanningModeMessage();
// ### File Loader ###
void InvalidDirectoryMessage(string path);
void FileFoundMessage(string filename, string path);
void FileNotFoundMessage(string filename, string path);

// ### Database ###
// Create
void ErrorCreateDBMessage(string error);
void SuccessCreateDBMessage();
// Access
void ErrorAccessDBMessage(string error);
void SuccessAccessDBMessage();

void ErrorExecuteQueryDBMessage(string query, string error);

bool IsNumber(string nbr);

#endif /* Message_hpp */
