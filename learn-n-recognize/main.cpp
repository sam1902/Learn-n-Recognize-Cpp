//
//  main.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 11/11/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#ifndef WIN32
    #include <sys/types.h>
#endif

#include <opencv2/face.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Message.hpp"
#include "Database.hpp"
#include "InputArgs.hpp"

using namespace std;
using namespace cv;
using namespace face;

/** Global variables */

// Text will be scaled depending on the face's size by this factor
float dynamic_text_scaling_factor = 3.3;
// Mode in which the program is currently running
// true:    scanning
// false:   learning
bool is_scanning_mode = true;

CascadeClassifier face_cascade;
string window_name = "Detection de visages";

int main(int argc, const char * argv[]){
    
    ExitMessage();
    exit(EXIT_SUCCESS);
    return 0;
}

