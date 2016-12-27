//
//  LBPRecognizer.hpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 25/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#ifndef LBPRecognizer_hpp
#define LBPRecognizer_hpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Message.hpp"

using namespace std;
using namespace cv;
using namespace face;

class LBPRecognizer {
private:
    bool isFaceRecognizerEmpty = true;
    Ptr<cv::face::FaceRecognizer> model;
public:
    LBPRecognizer(string path);
    LBPRecognizer();
    bool load(string path);
    void save(string path);
    void recognize(Mat frame, int* id, double* confidence);
    void drawNameAndConf(Mat* frame, Rect face, string name, string conf);
    inline bool isEmpty();
    void train(vector<Mat> src, vector<int> labels);
    void update(vector<Mat> src, vector<int> labels);
};


#endif /* LBPRecognizer_hpp */
