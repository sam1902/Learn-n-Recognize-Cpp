//
//  HaarCascade.hpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 25/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#ifndef HaarCascade_hpp
#define HaarCascade_hpp

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "Message.hpp"

using std::string;
using std::vector;

using cv::Scalar;
using cv::Mat;
using cv::Rect;
using cv::Size;
using cv::Point;
using cv::CascadeClassifier;

class HaarCascade{
private:
    CascadeClassifier face_cascade;
public:
    HaarCascade(string path);

    vector<Rect> detectFaces(Mat* frame);
    void drawRect(Mat* frame, vector<Rect> faces);
    bool LoadHaarCatalogue(string path);
};

#endif /* HaarCascade_hpp */
