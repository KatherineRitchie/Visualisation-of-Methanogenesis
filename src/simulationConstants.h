//
// Created by Katherine Ritchie on 5/2/18.
//

#ifndef SIMULATIONCONSTANTS_H
#define SIMULATIONCONSTANTS_H

#include <math.h>

// Chemistry constants
const double AVOGADROS_NUM = 6.023;
const double AVOGRADROS_POW = pow(10.0, 23);
const double LITRES_IN_A_FEMTOLITRE = pow(10.0, -15);

// Graphics constants
const int TOOLBAR_BORDER = 5;
const int TOOLBAR_WIDTH = 275;
const int TOOLBAR_HEIGHT = 60;

const int METABOLITE_BORDER = 1;
const int METABOLITE_RADIUS = 20;

const int ENZYME_WIDTH = 50;
const int ENZYME_HEIGHT = 30;
const int ENZYME_BORDER = 2;

const int MAX_COLOUR_VAL = 255;
const int NON_COLOUR_BASE_VAL = 150;
const double COLOUR_THRESHHOLD = 0.8;

#endif //SIMULATIONCONSTANTS_H
