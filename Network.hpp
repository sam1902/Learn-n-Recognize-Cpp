//
//  Network.hpp
//  learn-n-recognize
//
//  Created by Samuel Prevost on 09/02/2017.
//  Copyright © 2017 Samuel Prevost. All rights reserved.
//

#ifndef Network_hpp
#define Network_hpp

#include <cstdio>
#include <iostream>
#include <curl/curl.h>

#include "Message.hpp"

bool downloadFile(std::string url, std::string outfilename);

#endif /* Network_hpp */
