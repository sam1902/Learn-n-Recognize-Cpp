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

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Message.hpp"
#include "Database.hpp"
#include "ArgumentManager.hpp"
#include "HaarCascade.hpp"

using namespace std;
using namespace cv;

/** Global variables */
enum Mode { SCAN, LEARN };

int main(int argc, const char * argv[]){
    
    ClearMessage();
    CreditsMessage();
    VersionMessage(CV_VERSION);
    
    
    ArgumentManager* am = new ArgumentManager(argc, argv);
//    Database* db = new Database(am->database_path);
    HaarCascade* hc = new HaarCascade(am->face_cascade_path);
    
    VideoCapture cap(am->cameraID); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        exit(EXIT_FAILURE);
    
    vector<Rect> faces;
    while (true) {
        cap >> hc->workingFrame;
        faces = hc->detectFaces();
    
        imshow("Detection de visages", hc->drawRect(faces));
        int key = waitKey(1);
        if( (char)key == 'q' ) { break;}
    }
    ExitMessage();
    exit(EXIT_SUCCESS);
    return 0;
}

