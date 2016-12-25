//
//  ArgumentManager.hpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 24/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#ifndef ArgumentManager_hpp
#define ArgumentManager_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Message.hpp"

using namespace std;

class ArgumentManager {
    
public:
    // Path to where the SQLite database containing name and id is
    string database_path;
    // Path to where the LBP recognizer archive is
    string recognizer_path;
    // Path to haar cascade XML file
    string face_cascade_path;
    
    // Threshold after which the program will consider the
    // guessed name as valid, about 65% - 75% is normal
    int validity_threshold;
    // ID of the used camera,
    // usualy 0 if only one cam is connected
    int cameraID;
    // Scaling factor of the displayed live video stream
    float video_scaling_factor;
    
    ArgumentManager(int argc, const char * argv[]);
    
    bool AskForArgs(int argc, const char** argv[]);
};

#endif /* ArgumentManager_hpp */
