//
//  InputArgs.hpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 24/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#ifndef InputArgs_hpp
#define InputArgs_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Message.hpp"

using namespace std;
#endif /* InputArgs_hpp */

class InputArgs {
    
public:
    // Path to where the database will be loaded from and saved in
    // Must be a folder with images or an xml file named "recognized.xml" in it.
    string database_path;
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
    
    InputArgs(int argc, const char * argv[]);
    
    bool AskForArgs(int argc, const char** argv[]);
};
