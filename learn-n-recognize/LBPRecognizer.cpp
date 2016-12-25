//
//  LBPRecognizer.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 25/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#include "LBPRecognizer.hpp"

LBPRecognizer::LBPRecognizer(string path){
    this->model = createLBPHFaceRecognizer();
    if(!this->load(path))
        ErrorLoadingLBPRMessage();
    else
        SuccessLoadingLBPRMessage();
}

bool LBPRecognizer::load(string path){
    if (FILE *file = fopen(path.c_str(), "r")) {
        fclose(file);
        this->model->load(path);
        return true;
    } else {
        return false;
    }
}

void LBPRecognizer::recognize(Mat frame, int* id, double* confidence){
    this->model->predict(frame, *id, *confidence);
}

void LBPRecognizer::drawNameAndConf(Mat* frame, Rect face, string name, string conf){
    putText(*frame, name + "(" + conf + " %)", Point(face.x, face.y), FONT_HERSHEY_SIMPLEX, 8, Scalar(0,255,0));
    return;
}
