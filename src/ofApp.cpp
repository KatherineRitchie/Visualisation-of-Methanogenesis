#include "ofApp.h"

void ofApp::drawEnzyme(const Enzyme& enzyme_v) {
    for (Reaction *reaction : enzyme_v.GetReactions()) {
        drawReaction(*reaction, enzyme_v.GetXPos(), enzyme_v.GetYPos());
    }
    
    double enzyme_efficacy = pathway.GetEnzymeEfficacy(enzyme_v);
    //enzyme colour should be dark turquoise if very effective and paler turqoise if not so effective
    int blue_shade = (((enzyme_efficacy * 255) + 200) >= 255 ? 255 : ((enzyme_efficacy * 255) + 200));
    ofColor enzyme_colour = ofColor(50, (enzyme_efficacy * 255) + 20, blue_shade);
    
    ofSetColor(enzyme_colour.getInverted());
    ofDrawRectangle((float) enzyme_v.GetXPos() - 27, (float) enzyme_v.GetYPos() - 17, 54.0, 34.0);
    
    ofSetColor(enzyme_colour);
    ofDrawRectangle((float) enzyme_v.GetXPos() - 25, (float) enzyme_v.GetYPos() - 15, 50.0, 30.0);
    
    ofSetColor(enzyme_colour.getInverted());
    ofDrawBitmapString(enzyme_v.GetName(), (float) enzyme_v.GetXPos() - 9, (float) enzyme_v.GetYPos() + 3);
}

void ofApp::drawMetabolite(Metabolite* metabolite_v) {
    ofSetColor(0, 0, 0);
    ofDrawCircle((float) metabolite_v->GetXPos(), (float) metabolite_v->GetYPos(), 21.0);
    
    double curr_num_particles = pathway.curr_state[metabolite_v];
    double init_num_particles = metabolite_v->GetInitNumParticles();
    double colour_fraction = curr_num_particles / (init_num_particles * 2 + 1);
    colour_fraction = (colour_fraction > 0.85 ? 0.85 : colour_fraction);
    int non_red_shade = 205 - ((colour_fraction * 255) > 255 ? 255 : (colour_fraction * 255));
    
    ofColor colour(255, non_red_shade, non_red_shade);
    ofSetColor(colour);
    ofDrawCircle((float) metabolite_v->GetXPos(), (float) metabolite_v->GetYPos(), 20.0);
    ofSetColor(colour.getInverted());
    long num_particles = pathway.curr_state[metabolite_v];
    std::string metabolite_info = metabolite_v->GetShortname() + "\n" + std::to_string(num_particles);
    ofDrawBitmapString(metabolite_info, (float) metabolite_v->GetXPos() - 10, (float) metabolite_v->GetYPos());
}

void ofApp::drawReaction(const Reaction& reaction_v, int enzyme_x_pos, int enzyme_y_pos) {
    ofSetColor(0,0,0);
    for (Metabolite *product : reaction_v.GetProducts()) {
        ofVec2f arrowTailPoint(enzyme_x_pos, enzyme_y_pos);
        ofVec2f arrowHeadPoint(product->GetXPos(), product->GetYPos());
        ofDrawArrow(arrowHeadPoint, arrowTailPoint, 0.0);
    }
}

void ofApp::drawToolbar() {
    ofSetColor(ofColor::cornflowerBlue);
    ofDrawRectangle(0, 0, 285, 70);
    ofSetColor(ofColor::orange);
    ofDrawRectangle(5, 5, 275, 60);
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

