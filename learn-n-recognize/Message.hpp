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
#include <cstdlib>
#include <unistd.h>
#include "Miscellaneous.hpp"

using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::to_string;

// ### General ###
void ClearMessage();
void ExitMessage();
void CreditsMessage();
void Countdown(int seconds);
void MissingArgsMessage();

// ### OpenCV ###
void VersionMessage(string opencv_version);
// Haar
void ErrorLoadingHaarMessage();
void SuccessLoadingHaarMessage();
// LBPR
void ErrorLoadingLBPRMessage();
void SuccessLoadingLBPRMessage();
void WarningInitEmptyLBPRMessage();
void ErrorUpdateNotInitializedLBPR();
void SuccessSavingLBPRMessage(string pathToLBPR);
// Camera
void EmptyFrameMessage();
void ErrorOpeningCameraMessage();
// Mode transition
void LearningModeMessage();
void ScanningModeMessage();

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
void SuccessFindSubject();
void DisplayIDSubject(string id);
void DisplayNameSubject(string name);
void InvalidIDSubjet();
// Insert
void ErrorInsertSubjectDBMessage(string error);
void SuccessInsertSubjectMessage(string subjectName, string subjectID);
void ErrorExecuteQueryDBMessage(string query, string error);


#endif /* Message_hpp */
