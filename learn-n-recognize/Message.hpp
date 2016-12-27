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
#include <stdlib.h>
#include <unistd.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;

// Forward declaration
class Database;

// ### General ###
string colorText(string inputText, int colorCode);
void ClearMessage();
void ExitMessage();
void CreditsMessage();
void Countdown(int seconds);
void MissingArgsMessage();

bool DoesSubjectExist();
void AskSubjectNameAndID(string* name, int* id, Database* db);
int AskExistingSubjectID(Database* db);
string AskNewSubjectName(Database* db);
string AskExistingSubjectName(Database* db);

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
// Camera
void EmptyFrameMessage();
void ErrorOpeningCameraMessage();
// Mode transition
void LearningModeMessage();
void ScanningModeMessage();
// Save LBPR file
string AskWhereToSaveRecognizer();

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
// Insert
void ErrorInsertSubjectDBMessage(string error);

void ErrorExecuteQueryDBMessage(string query, string error);

bool IsNumber(string nbr);

#endif /* Message_hpp */
