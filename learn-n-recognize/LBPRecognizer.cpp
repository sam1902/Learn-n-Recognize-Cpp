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

LBPRecognizer::LBPRecognizer(){
    this->model = createLBPHFaceRecognizer();
    InitEmptyLBPRMessage();
}

bool LBPRecognizer::load(string path){
    if (FILE *file = fopen(path.c_str(), "r")) {
        fclose(file);
        this->model->load(path);
        this->isFaceRecognizerEmpty = false;
        return true;
    } else {
        return false;
    }
}

void LBPRecognizer::save(string path){
    this->model->save(path);
}

void LBPRecognizer::train(vector<Mat> src, vector<int> labels){
    this->model->train(src, labels);
    this->isFaceRecognizerEmpty = false;
}

void LBPRecognizer::update(vector<Mat> src, vector<int> labels){
    if(!this->isEmpty())
        this->model->update(src, labels);
}

void LBPRecognizer::recognize(Mat frame, int* id, double* confidence){
    this->model->predict(frame, *id, *confidence);
}

// Should be possible, however it'd be too long to make sure the used id
// (or so called "label") doesn't aleady exist so I'll use SQLite with
// unique, auto increment id and so the id (a.k.a. label) will be unique
//inline string LBPRecognizer::getName(int id){
//    return this->model->getLabelInfo(id);
//}
//
//inline int LBPRecognizer::getID(string name){
//    return this->model->getLabelsByString(name)[0];
//}

void LBPRecognizer::drawNameAndConf(Mat* frame, Rect face, string name, string conf){
    putText(*frame, name + "(" + conf + " %)", Point(face.x, face.y), FONT_HERSHEY_SIMPLEX, 8, Scalar(0,255,0));
    return;
}

inline bool LBPRecognizer::isEmpty(){
    return this->isFaceRecognizerEmpty;
}
