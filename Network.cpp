//
//  Network.cpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 09/02/2017.
//  Copyright © 2017 Samuel Prevost. All rights reserved.
//

#include "Network.hpp"

bool downloadFile(std::string url, std::string outfilename){
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl)
    {
        fp = std::fopen(outfilename.c_str(),"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
        if(res != CURLE_OK){
            ErrorDownloadingFile(url, "Status code " + std::to_string(res) + " : " + (std::string)curl_easy_strerror(res));
            return false;
        }
        SuccessDownloadingFile(url, outfilename, "Status code " + std::to_string(res) + " : " + (std::string)curl_easy_strerror(res));
        return true;
    }else{
        ErrorDownloadingFile(url, "Couldn't initialise curl with curl_easy_init()");
        return false;
    }
}
