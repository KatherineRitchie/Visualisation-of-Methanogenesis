//
// Created by Katherine Ritchie on 4/19/18.
//

#ifndef LOAD_H
#define LOAD_H
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/prettywriter.h" // for stringify JSON
#include <cstdio>

#include <string>

void runJson();

std::string FileToString(std::string filename);

#endif //LOAD_H
