#include "ofApp.h"

void ofApp::drawEnzyme(Enzyme enzyme_v) {
    ofSetColor(50, 150, 230);
    ofDrawRectangle((float) enzyme_v.GetXPos() - 10.0, (float) enzyme_v.GetYPos() - 15.0, 50.0, 30.0);
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(enzyme_v.GetName(), (float) enzyme_v.GetXPos(), (float) enzyme_v.GetYPos());
    for (Reaction reaction : enzyme_v.GetReactions()) {
        drawReaction(reaction, enzyme_v.GetXPos(), enzyme_v.GetYPos());
    }
}

void ofApp::drawMetabolite(Metabolite metabolite_v) {
    ofSetColor(metabolite_v.GetNumParticles() * 5);
    ofDrawRectangle((float) metabolite_v.GetXPos() - 20.0, (float) metabolite_v.GetYPos() - 15.0, 50.0, 30.0);
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(metabolite_v.GetShortname(), (float) metabolite_v.GetXPos(), (float) metabolite_v.GetYPos());
    ofDrawBitmapString(std::to_string(metabolite_v.GetNumParticles()), (float) metabolite_v.GetXPos() + 20.0, (float) metabolite_v.GetYPos());
}

void ofApp::drawReaction(Reaction reaction_v, int enzyme_x_pos, int enzyme_y_pos) {
    ofSetColor(0,0,0);
//    for (Metabolite reactant : reaction_v.GetReactants()) {
//        ofVec2f arrowTailPoint(reactant.GetXPos(), reactant.GetYPos());
//        ofVec2f arrowHeadPoint(enzyme_x_pos, enzyme_y_pos);
//        ofDrawArrow(arrowTailPoint, arrowHeadPoint, 10.0);
//    }
    for (Metabolite product : reaction_v.GetProducts()) {
        ofVec2f arrowTailPoint(enzyme_x_pos, enzyme_y_pos);
        ofVec2f arrowHeadPoint(product.GetXPos(), product.GetYPos());
        ofDrawArrow(arrowHeadPoint, arrowTailPoint, 10.0);
    }
    ofVec2f arrowTailPoint (0,0);
    ofVec2f arrowHeadPoint (100, 150);
    ofDrawArrow(arrowTailPoint, arrowHeadPoint, 20.0);
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Stupid Chemical Simulation");
    ofSetBackgroundColor(255, 200, 200);
    std::string filename = "/Users/Kate/Documents/GitHub/Useful_Libraries/of_v0.9.8_osx_release/apps/myApps/final-project-KatherineRitchie/data/methanogenesis.json";
    pathway_ = Pathway(filename);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    for (Metabolite metabolite : pathway_.GetMetabolites()) {
        drawMetabolite(metabolite);
    }
    for (Enzyme enzyme : pathway_.GetEnzymes()) {
        drawEnzyme(enzyme);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

