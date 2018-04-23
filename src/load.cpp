//
// Created by Katherine Ritchie on 4/19/18.
//

#include "load.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace rapidjson;

void runJson() {
    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    std::cout << "original json is: " << json << std::endl;

    Document document;
    if (document.Parse(json).HasParseError()) {
        std::cout << "inside runJson - something is wrong with this json!!!" << std::endl;
        return;
    }
    std::cout << "document does not have parse error \n";
    printf("hello = %s\n", document["hello"].GetString());
    return;
}

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