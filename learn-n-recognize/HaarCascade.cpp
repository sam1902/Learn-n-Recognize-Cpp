//
//  HaarCascade.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 25/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include "HaarCascade.hpp"

HaarCascade::HaarCascade(string path){
    if(!this->LoadHaarCatalogue(path))
        ErrorLoadingHaarMessage();
    else
        SuccessLoadingHaarMessage();
}

bool HaarCascade::LoadHaarCatalogue(string path){
    return this->face_cascade.load(path);
}

vector<Rect> HaarCascade::detectFaces(){
    vector<Rect> faces;
    Mat frame_gray;
    
    cvtColor( this->workingFrame, frame_gray, CV_BGR2GRAY );
    // Normalize bins to 255
    equalizeHist( frame_gray, frame_gray );
    
    //-- Detect faces
    this->face_cascade.detectMultiScale( frame_gray, faces, 1.3, 5, 0|CV_HAAR_SCALE_IMAGE, Size(70, 70) );
    return faces;
}

Mat HaarCascade::drawRect(vector<Rect> faces){
    Mat frame = this->workingFrame;
    for( size_t i = 0; i < faces.size(); i++ )
    {
        rectangle(frame, Point(faces.at(i).x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar( 0, 255, 0 ));
    }
    return frame;
}
