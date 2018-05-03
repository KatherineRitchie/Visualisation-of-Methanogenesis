#include "ofMain.h"
#include "ofApp.h"

#include "metabolite.h"
#include "reaction.h"
#include "enzyme.h"
#include "load.h"

#include <map>
#include <string>

//========================================================================
int main( ) {
    ofSetupOpenGL(1200, 600, OF_WINDOW);
    ofSetFrameRate(12); // An appropriate framerate
    ofRunApp(new ofApp());
}

