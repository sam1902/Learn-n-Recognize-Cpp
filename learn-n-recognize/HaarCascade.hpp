//
//  HaarCascade.hpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 25/12/2016.
//  Copyright © 2016 Samuel Prevost. All rights reserved.
//

#ifndef HaarCascade_hpp
#define HaarCascade_hpp

#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>

#include "Message.hpp"

using namespace std;
using namespace cv;

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
