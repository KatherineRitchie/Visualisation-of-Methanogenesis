//
// Created by Katherine Ritchie on 4/19/18.
//

#include "load.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace rapidjson;

std::string FileToString(std::string filename) {
    std::string line;
    std::ifstream myfile(filename);
    std::string file_string;
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            file_string += line;
        }
        myfile.close();
    } else {
        std::cout << "Unable to open file";
    }
    return file_string;
}