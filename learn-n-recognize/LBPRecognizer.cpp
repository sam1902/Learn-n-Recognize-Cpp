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
    WarningInitEmptyLBPRMessage();
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
    string prefix = "LBPH_recognizer_";
    
    // If our path doesn't end with / we need to add one:
    if(path[path.size()-1] != '/')
        prefix = "/" + prefix;
    
    string fullpath = path + prefix + timestamp("%d-%m-%Y_%H-%M-%S_%Z") + ".xml";
    this->model->save(fullpath);
    SuccessSavingLBPRMessage(fullpath);
}

void LBPRecognizer::train(vector<Mat> src, vector<int> labels){
    this->model->train(this->toGrey(src), labels);
    this->isFaceRecognizerEmpty = false;
    this->hasBeenEdited         = true;
}

void LBPRecognizer::update(vector<Mat> src, vector<int> labels){
    if(!this->isEmpty()){
        this->model->update(this->toGrey(src), labels);
        this->hasBeenEdited = true;
    }else{
        ErrorUpdateNotInitializedLBPR();
        this->train(src, labels);
    }
}
void LBPRecognizer::recognize(Mat frame, int* id, double* confidence){
    double raw_conf;
    this->model->predict(this->toGrey(frame), *id, raw_conf);
    if((100 - raw_conf) < 0){
        *confidence = 0;
    }else{
        *confidence = 100 - raw_conf;
    }
}

/* The following methods should be possible,
 however it'd be too long to make sure the used id
 (or so called "label") doesn't aleady exist so I'll use SQLite with
 unique, auto increment id and so the id (a.k.a. label) will be unique

inline string LBPRecognizer::getName(int id){
    return this->model->getLabelInfo(id);
}

inline int LBPRecognizer::getID(string name){
    return this->model->getLabelsByString(name)[0];
}
*/

void LBPRecognizer::drawNameAndConf(Mat* frame, Rect face, string name, string conf){
    putText(*frame, name + "(" + conf + " %)", Point(face.x, face.y), FONT_HERSHEY_COMPLEX, FONT_SIZE, Scalar(0,255,0));
    return;
}

Mat LBPRecognizer::toGrey(Mat src){
    Mat output;
    cvtColor(src, output, COLOR_BGR2GRAY);
    return output;
}

vector<Mat> LBPRecognizer::toGrey(vector<Mat> src){
    vector<Mat> output;
    for (int i = 0; i < src.size(); i++) {
        Mat out;
        cvtColor(src[i], out, COLOR_BGR2GRAY);
        output.push_back(out);
    }
    return output;
}
