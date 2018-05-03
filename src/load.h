//
// Created by Katherine Ritchie on 4/19/18.
//

#ifndef LOAD_H
#define LOAD_H
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/prettywriter.h" // for stringify JSON
#include <cstdio>

#include <string>

// Accepts a file path string and returns a string of file contents
std::string FileToString(std::string filename);

#endif //LOAD_H
