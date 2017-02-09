//
//  main.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 11/11/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>
// Usefull includes for OpenCV projects:
//#include <opencv2/face.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv/cvaux.hpp>
//#include <opencv2/objdetect/objdetect.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

// Un échec #include <ConfigFile.hpp>
#include "AskUser.hpp"
#include "Database.hpp"
#include "Message.hpp"
#include "ArgumentManager.hpp"
#include "HaarCascade.hpp"
#include "LBPRecognizer.hpp"

// Set default mode to scan
#define DEFAULT_MODE SCAN
// Set the number of frame before learning the stack of frame we saved before
#define NUMBER_OF_FRAMES_BEFORE_LEARNING 30

void SaveAndExit(LBPRecognizer* rec, string pathToFolder);

/** Global variables **/

/* Modes:
 *  - SCAN  : Scanning mode, detect faces and write their name
 *  - LEARN : Learning mode, learn new faces by associating them with their name
 */
enum Mode { SCAN, LEARN };
// The selected mode
Mode currentMode = DEFAULT_MODE;

/** END: Global variables **/

int main(int argc, const char * argv[]){
    /** Main variables **/
    
    // Clear the console
    ClearMessage();
    // Display credits
    CreditsMessage();
    
    // Arguments handler, check if every args are provided
    ArgumentManager* am = new ArgumentManager(argc, argv);
    
    // Display current OpenCV version
    // (3.1.0-dev for now)
    VersionMessage(CV_VERSION);
    
    // Database containing subject's name and id
    Database* db = new Database();
    // If we've got a path to an already existing db, open it
    // otherwise, create one in the allocated directory
    if(am->database_path.size() != 0)
        db->open(am->database_path);
    else
        db->create(am->save_path);
    
    // Haar Cascade detect human faces and get us their positions
    HaarCascade* hc = new HaarCascade(am->face_cascade_path);
    
    // LBPR recognize and identify the faces, it gives us their id
    LBPRecognizer* rec;
    if(am->recognizer_path.size() != 0)
        rec = new LBPRecognizer(am->recognizer_path);
    else
        rec = new LBPRecognizer();
    
    // Open camera image stream
    cv::VideoCapture cap(am->cameraID);
    // If we failed, exit program
    if(!cap.isOpened()) {
        ErrorOpeningCameraMessage();
        exit(EXIT_FAILURE);
    }
    
    // This will contain the position of every faces
    vector<Rect> faces;
    // This will contain the current frame we will work with
    Mat currentFrame;
    // This will contain the name of the subject we are learning the face
    string subject_name;
    // This will contain the id of the subject we are learning the face
    int subject_id = NULL;
    
    // This will contain some of the last frames to update/train the recognizer later with it
    vector<Mat> framesToLearn;
    
    /** END: Main variables **/
    
    while (true) {
        switch (currentMode) {
            // Scanning mode
            case SCAN:
                ScanningModeMessage();
                Countdown(3);
                while (true){
                    // Save the current frame
                    cap >> currentFrame;
                    // Detect every faces on it
                    faces = hc->detectFaces(&currentFrame);
                    for(int i = 0; i < faces.size(); i++){
                        // if we've initialized our LBPR
                        if(!rec->isEmpty()){
                            // id of the detected face
                            int id = -1;
                            // confidence of the detection
                            double confidence = 0.0;
                            // currentFrame(faces[i]) crop workingFrame to the Rect faces[i]
                            // Get subject's id from image using LBPH
                            rec->recognize(currentFrame(faces[i]), &id, &confidence);
                            // Draw detected name and confidence on the current frame
                            if(confidence >= am->validity_threshold)
                                rec->drawNameAndConf(&currentFrame, faces[i], db->getSubjectName(id), to_string(confidence));
                            else
                                rec->drawNameAndConf(&currentFrame, faces[i], " ? ", "-");
                        }else{
                            // otherwise, we can't recognize the faces
                            rec->drawNameAndConf(&currentFrame, faces[i], " ? ", "-");
                        }
                    }
                    // Draw rectangle around every faces
                    hc->drawRect(&currentFrame, faces);
                    // Display the frame
                    imshow("Learn'n'Recognize", currentFrame);
                    
                    // Wait 1ms for key
                    char key = (char)cv::waitKey(1);
                    // Save and exit if we pressed 'q'
                    if( key == 'q' ) { SaveAndExit(rec, am->save_path); }
                    // If we pressed 'l'
                    if( key == 'l' ) {
                        // Go to learning
                        currentMode = LEARN;
                        break;
                    }
                }
                break;
            // Learning mode
            case LEARN:
                
                if (AskYesNo("Est-ce-que le sujet existe déjà dans la base de donnée ? (Y/n)\n")){
                    /* Subject already exist in database */
                    
                    if (AskYesNo("Connaissez-vous l'identifiant du sujet dans la base de donnée ? (Y/n)\n")){
                        /* We know the subject's id */
                        string givenIDstr = AskUser("Quel est l'identifiant du sujet ?");
                        int givenID;
                        if(!IsNumber(givenIDstr))
                            givenID = -1;
                        else
                            givenID = stoi(givenIDstr);
                        
                        string tmp;
                        while(!db->isSubjectIDValid(givenID)){
                            InvalidIDSubjet();
                            while(!IsNumber(tmp)){
                                tmp = AskUser("L'identifiant doit être une donnée numérique.\n Veuillez réessayer:\n ");
                            }
                            givenID = stoi(tmp);
                        }
                        subject_id = givenID;
                        SuccessFindSubject();
                        
                        subject_name = db->getSubjectName(subject_id);
                        DisplayNameSubject(subject_name);
                        
                    }else if(AskYesNo("Connaissez-vous le nom du sujet dans la base de donnée ? (Y/n)\n")){
                        /* We know the subject's name */
                        
                        string givenName = AskUser("Quel est le nom du sujet ?\n");
                        while(!db->isSubjectNameValid(givenName)){
                            givenName = AskUser("Nom du sujet invalide ! Veuillez réessayer:\n ");
                        }
                        subject_name = givenName;
                        SuccessFindSubject();
                        
                        subject_id = db->getSubjectID(subject_name);
                        DisplayIDSubject(to_string(subject_id));
                    }else{
                        /* We got neither the subject's name, nor his id... */
                        currentMode = SCAN;
                        break;
                    }
                    
                }else{
                    /* New subject */
                    
                    { // Get the new name
                        string tmpName = AskUser("Quel est est le nom du nouveau sujet ?\n");
                        while (db->isSubjectNameValid(tmpName)) {
                            tmpName = AskUser("Le nom demandé est déjà pris, veuillez en choisir un autre: \n");
                        }
                        subject_name = tmpName;
                    }
                    
                    // Insert subject into db and get his new id
                    subject_id = db->insertSubject(subject_name);
                    // Exit learning mode if we failed to insert the subject into db
                    if(subject_id == -1){
                        currentMode = SCAN;
                        break;
                    }
                    SuccessInsertSubjectMessage(subject_name, to_string(subject_id));
                }
                
                // Tell the user what da hell is happning
                LearningModeMessage();
                // Wait 7 sec
                Countdown(7);
                
                while (true){
                    // Save the current frame
                    cap >> currentFrame;
                    // Detect every faces on it
                    faces = hc->detectFaces(&currentFrame);
                    
                    // Theoretically faces.size() = 1 , but meh
                    for (int i = 0; i < faces.size(); i++) {
                        // Here, we add the faces to a stack to learn them when they'll be
                        // a bunch of them
                        framesToLearn.push_back(currentFrame(faces[i]));
                    }
                    
                    // If we've got enough frames
                    if(framesToLearn.size() > NUMBER_OF_FRAMES_BEFORE_LEARNING){
                        vector<int> labels(framesToLearn.size());
                        for (int i = 0; i < framesToLearn.size(); i++) {
                            labels[i] = subject_id;
                        }
                        if(rec->isEmpty())
                            rec->train(framesToLearn, labels);
                        else
                            rec->update(framesToLearn, labels);
                        // Since we don't wanna re-learn the same frame, clear the stack
                        framesToLearn.clear();
                    }
                    
                    // Draw rectangles around faces
                    hc->drawRect(&currentFrame, faces);
                    
                    // Display the frame
                    imshow("Learn'n'Recognize", currentFrame);
                    
                    // Wait 1ms for key
                    char key = (char)cv::waitKey(1);
                    // Save and exit if we pressed 'q'
                    if( key == 'q' ) { SaveAndExit(rec, am->save_path); }
                    // If we pressed 's' or spacebar
                    if( key == 's' || key == ' ') {
                        // Reset name and id
                        subject_id = NULL;
                        subject_name = "";
                        // Go to scanning mode
                        currentMode = SCAN;
                        break;
                    }
                }
                break;
        }
    }
    return 0;
}

void SaveAndExit(LBPRecognizer* rec, string pathToFolder){
    // pathToFolder with or without the ending '/', it'll be normalized
    
    // Save our recognizer
    rec->save(pathToFolder);
    // Say goodbye
    ExitMessage();
    exit(EXIT_SUCCESS);
    return;
}
