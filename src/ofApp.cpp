#include "ofApp.h"

void ofApp::drawEnzyme(const Enzyme& enzyme_v) {
    // draws reaction lines
    for (Reaction *reaction : enzyme_v.GetReactions()) {
        drawReaction(*reaction, enzyme_v.GetXPos(), enzyme_v.GetYPos());
    }
    
    double enzyme_efficacy = pathway.GetEnzymeEfficacy(enzyme_v);
    //enzyme colour should be dark turquoise if very effective and paler turqoise if not so effective
    double colour_fraction = (enzyme_efficacy > COLOUR_THRESHHOLD ? COLOUR_THRESHHOLD : enzyme_efficacy);
    int non_blue_shade = COLOUR_THRESHHOLD - ((colour_fraction * MAX_COLOUR_VAL) > MAX_COLOUR_VAL ? MAX_COLOUR_VAL : (colour_fraction * MAX_COLOUR_VAL + 1));
    ofColor enzyme_colour((non_blue_shade * NON_COLOUR_BASE_VAL), (non_blue_shade * NON_COLOUR_BASE_VAL), MAX_COLOUR_VAL);

    // draws enzyme border
    ofSetColor(ofColor::orange);
    int border_x_pos = enzyme_v.GetXPos() - (ENZYME_WIDTH / 2 + ENZYME_BORDER);
    int border_y_pos = enzyme_v.GetYPos() - (ENZYME_HEIGHT / 2 + ENZYME_BORDER);
    ofDrawRectangle(border_x_pos , border_y_pos, ((2 * ENZYME_BORDER) + ENZYME_WIDTH), ((2 * ENZYME_BORDER) + ENZYME_HEIGHT));
    
    // draw enzyme centre
    ofSetColor(enzyme_colour);
    ofDrawRectangle((enzyme_v.GetXPos() - (ENZYME_WIDTH / 2)), (enzyme_v.GetYPos() - (ENZYME_HEIGHT / 2)), ENZYME_WIDTH, ENZYME_HEIGHT);
    
    // draw enzyme name
    ofSetColor(ofColor::orange);
    ofDrawBitmapString(enzyme_v.GetName(), (float) enzyme_v.GetXPos() - 9, (float) enzyme_v.GetYPos() + 3);
}

void ofApp::drawMetabolite(Metabolite* metabolite_v) {
    // draw metabolite border
    ofSetColor(ofColor::black);
    ofDrawCircle((float) metabolite_v->GetXPos(), (float) metabolite_v->GetYPos(), (METABOLITE_RADIUS + METABOLITE_BORDER));
    
    // determine metabolite colour based on its concentration in the cell
    double curr_num_particles = pathway.curr_state[metabolite_v];
    double init_num_particles = metabolite_v->GetInitNumParticles();
    double colour_fraction = curr_num_particles / (init_num_particles * 2 + 1);
    colour_fraction = (colour_fraction > COLOUR_THRESHHOLD ? COLOUR_THRESHHOLD : colour_fraction);
    int non_red_shade = NON_COLOUR_BASE_VAL - ((colour_fraction * MAX_COLOUR_VAL) > MAX_COLOUR_VAL ? MAX_COLOUR_VAL : (colour_fraction * MAX_COLOUR_VAL + 1));
    
    // draws the metabolite
    ofColor metabolite_colour(MAX_COLOUR_VAL, non_red_shade, non_red_shade);
    ofSetColor(metabolite_colour);
    ofDrawCircle((float) metabolite_v->GetXPos(), (float) metabolite_v->GetYPos(), METABOLITE_RADIUS);
    ofSetColor(metabolite_colour.getInverted());
    long num_particles = pathway.curr_state[metabolite_v];
    std::string metabolite_info = metabolite_v->GetShortname() + "\n" + std::to_string(num_particles);
    ofDrawBitmapString(metabolite_info, (float) metabolite_v->GetXPos() - (METABOLITE_RADIUS / 2), (float) metabolite_v->GetYPos());
}

void ofApp::drawReaction(const Reaction& reaction_v, int enzyme_x_pos, int enzyme_y_pos) {
    ofSetColor(ofColor::black);
    for (Metabolite *product : reaction_v.GetProducts()) {
        ofVec2f arrowTailPoint(enzyme_x_pos, enzyme_y_pos);
        ofVec2f arrowHeadPoint(product->GetXPos(), product->GetYPos());
        ofDrawArrow(arrowHeadPoint, arrowTailPoint, 0.0);
    }
}

void ofApp::drawToolbar() {
    ofSetColor(ofColor::cornflowerBlue);
    ofDrawRectangle(0, 0, (2 * TOOLBAR_BORDER + TOOLBAR_WIDTH), (2 * TOOLBAR_BORDER + TOOLBAR_HEIGHT));
    ofSetColor(ofColor::orange);
    ofDrawRectangle(TOOLBAR_BORDER, TOOLBAR_BORDER, TOOLBAR_WIDTH, TOOLBAR_HEIGHT);
    ofSetColor(ofColor::royalBlue);
    
    ofDrawBitmapString("~TOOLBAR~", 10, 20);
    ofDrawBitmapString("Press any key to pause/unpause", 10, 32);
    ofDrawBitmapString(("seconds passed: " + std::to_string(secondsPassed)), 10, 44);
    if (bPause == true) {
        ofDrawBitmapString("PAUSED", 10, 56);
    } else {
        ofDrawBitmapString("PLAYING", 10, 56);
    }
}

//--------------------------------------------------------------
void ofApp::setup() {
    std::string filename = "/Users/Kate/Documents/GitHub/Useful_Libraries/of_v0.9.8_osx_release/apps/myApps/final-project-KatherineRitchie/data/methanogenesis.json";
    pathway = Pathway(filename);
    ofSetWindowTitle(pathway.GetName());
    secondsPassed = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
    if (bPause == false) {
        secondsPassed += 1;
        pathway.incrementTime();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::paleGoldenRod, ofColor::paleGreen, OF_GRADIENT_CIRCULAR);
    for (Enzyme *enzyme : pathway.GetEnzymes()) {
        drawEnzyme(*enzyme);
    }
    for (Metabolite *metabolite : pathway.GetMetabolites()) {
        drawMetabolite(metabolite);
    }
    drawToolbar();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    bPause = !bPause;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

