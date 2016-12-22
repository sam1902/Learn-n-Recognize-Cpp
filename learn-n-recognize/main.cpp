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

using namespace std;
using namespace cv;
using namespace face;

void detectAndDisplay( Mat frame );
bool lookForFile(const char* filename, const char* path);

/** Global variables */

// Path to where the database will be loaded from and saved in
// Must be a folder with images or an xml file named "recognized.xml" in it.
String database_path;
// Path to haar cascade XML file
String face_cascade_path;

// Threshold after which the program will consider the
// guessed name as valid, about 65% - 75% is normal
int validity_threshold;
// ID of the used camera,
// usualy 0 if only one cam is connected
int cameraID;
// Scaling factor of the displayed live video stream
float video_scaling_factor;

// Name of the subject whose face will be associated with
String subject_name;
// ID of this subject
int subject_id;

// Text will be scaled depending on the face's size by this factor
float dynamic_text_scaling_factor = 3.3;
// Mode in which the program is currently running
// true:    scanning
// false:   learning
bool is_scanning_mode = true;

CascadeClassifier face_cascade;
string window_name = "Detection de visages";

int main(int argc, const char * argv[]){
    
    // Set variables according to user's inputs
    if(argc < 7){MissingArgsMessage(); exit(EXIT_FAILURE); return -1;}
    database_path           =   argv[1];
    face_cascade_path       =   argv[2];
        
    validity_threshold      =   stoi(argv[3]);
    cameraID                =   stoi(argv[4]);
    video_scaling_factor    =   stof(argv[5]);
        
    subject_name            =   argv[6];
    subject_id              =   stoi(argv[7]);
    
    CreditsMessage();
    
    VersionMessage(CV_VERSION);
    
    // Load Haar Cascade
    if( !face_cascade.load(face_cascade_path)){ ErrorLoadingHaarMessage(); exit(EXIT_FAILURE); return -1;}
    
    // Check if catalogue exist
    lookForFile("recognizer.xml", database_path.c_str());
    
    // Initialize our LBPH recognizer
    Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
    
    // Read video stream
    VideoCapture cap(cameraID); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    
    while (true) {
        Mat frame;
        cap >> frame;
        // Apply classifier to the frame
        if(!frame.empty()){
            detectAndDisplay(frame);
        }else{
            EmptyFrameMessage();
            break;
        }
        
        int key = waitKey(1);
        if( (char)key == 'q' ) { break;}
        
    }
    
    ExitMessage();
    exit(EXIT_SUCCESS);
    return 0;
}

// c.f. https://openclassrooms.com/courses/parcourir-les-dossiers-avec-dirent-h
bool lookForFile(const char* filename, const char* path)
{
    DIR *dirp;
    struct dirent *dp;
    
    
    if ((dirp = opendir(path)) == NULL) {
        InvalidDirectoryMessage(path);
        exit(EXIT_FAILURE);
        return false;
    }
    
    
    do {
        if ((dp = readdir(dirp)) != NULL) {
            if (strcmp(dp->d_name, filename) != 0)
                continue;
            
            
            FileFoundMessage(filename, path);
            closedir(dirp);
            return true;
            
            
        }
    } while (dp != NULL);
    
    FileNotFoundMessage(filename, path);
    closedir(dirp);
    return false;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    vector<Rect> faces;
    Mat frame_gray;
    
    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    // Normalize bins to 255
    equalizeHist( frame_gray, frame_gray );
    
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.3, 5, 0|CV_HAAR_SCALE_IMAGE, Size(70, 70) );
    
    for( size_t i = 0; i < faces.size(); i++ )
    {
        rectangle(frame, Point(faces.at(i).x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar( 0, 255, 0 ));
    }
    // Display image
    imshow( window_name, frame );
}
