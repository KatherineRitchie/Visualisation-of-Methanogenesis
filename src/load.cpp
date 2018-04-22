//
// Created by Katherine Ritchie on 4/19/18.
//

#include "load.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace rapidjson;

void runJson() {
    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    std::cout << "original json is: " << json << std::endl;

    Document document;

    document.Parse(json);
}

std::string FileToString(std::string filename) {
    std::string line;
    std::ifstream myfile(filename);
    std::string file_string;
    if (myfile.is_open()) {
        std::cout<< "file is open";
        std::cout << (getline (myfile,line) ? "true" : "false");
        while ( getline (myfile,line) ) {
            std::cout << "inside file";
            std::cout << line << std::endl;
            file_string += line;
        }
        myfile.close();
    } else {
        std::cout << "Unable to open file";
    }
    return file_string;
}