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
#include "LBPRecognizer.hpp"

// Set default mode to scan
#define DEFAULT_MODE SCAN

using namespace std;
using namespace cv;

/** Global variables **/

/* Modes:
 *  - SCAN  : Scanning mode, detect faces and write their name
 *  - LEARN : Learning mode, learn new faces by associating them with their name
 */
enum Mode { SCAN, LEARN };
// The selected mode
Mode currentMode = DEFAULT_MODE;

int main(int argc, const char * argv[]){
    // Clear the console
    ClearMessage();
    // Display credits
    CreditsMessage();
    // Display current OpenCV version
    // (3.1.0-dev for now)
    VersionMessage(CV_VERSION);
    
    // Arguments handler, check if every args are provided
    ArgumentManager* am = new ArgumentManager(argc, argv);
    // Database containing subject's name and id
    Database* db = new Database(am->database_path);
    // Haar Cascade detect human faces and get us their positions
    HaarCascade* hc = new HaarCascade(am->face_cascade_path);
    // LBPR recognize and identify the faces, it gives us their id
    LBPRecognizer* rec = new LBPRecognizer(am->recognizer_path);
    
    // Open camera image stream
    VideoCapture cap(am->cameraID);
    // If we failed, exit program
    if(!cap.isOpened()) {
        ErrorOpeningCameraMessage();
        exit(EXIT_FAILURE);
    }
    
    // This will contain the position of every faces
    vector<Rect> faces;
    // This will contain the current frame we will work with
    Mat currentFrame;
    while (true) {
        // Save the current frame
        cap >> currentFrame;
        // Detect every faces on it
        faces = hc->detectFaces(&currentFrame);
        
        switch (currentMode) {
            // Scanning mode
            case SCAN:
                for(int i = 0; i < faces.size(); i++){
                    // id of the detected face
                    int id = -1;
                    // confidence of the detection
                    double confidence = 0.0;
                    // currentFrame(faces[i]) crop workingFrame to the Rect faces[i]
                    // Get subject's id from image using LBPH
                    rec->recognize(currentFrame(faces[i]), &id, &confidence);
                    // Draw detected name and confidence on the current frame
                    rec->drawNameAndConf(&currentFrame, faces[i], db->getSubjectName(id), to_string(confidence));
                }
                // Draw rectangle around every faces
                hc->drawRect(&currentFrame, faces);
                
                break;
            // Learning mode
            case LEARN:
                // TODO: Work here and debug scanning mode
                break;
        }
        
        // Display the marked frame
        imshow("Learn'n'Recognize", currentFrame);
        
        // Wait 1ms for key
        int key = waitKey(1);
        // Exit if we pressed 'q'
        if( (char)key == 'q' ) { break;}
    }
    
    // Say goodbye
    ExitMessage();
    exit(EXIT_SUCCESS);
    return 0;
}

