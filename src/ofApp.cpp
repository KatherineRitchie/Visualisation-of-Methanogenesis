#include "ofApp.h"

void ofApp::drawEnzyme(const Enzyme& enzyme_v) {
    ofSetColor(0, 0, 0);
    for (Reaction *reaction : enzyme_v.GetReactions()) {
        drawReaction(*reaction, enzyme_v.GetXPos(), enzyme_v.GetYPos());
    }
    ofSetColor(50, 150, 230);
    ofDrawRectangle((float) enzyme_v.GetXPos() - 25, (float) enzyme_v.GetYPos() - 15, 50.0, 30.0);
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(enzyme_v.GetName(), (float) enzyme_v.GetXPos() - 9, (float) enzyme_v.GetYPos() + 3);
}

void ofApp::drawMetabolite(Metabolite* metabolite_v) {
    //double colour_val = (pathway_.curr_state[metabolite_v] * 255) / (pathway_.StringToMetabolite(metabolite_v->GetShortname())->GetNumParticles() * 2 );
    //ofDrawRectangle((float) metabolite_v->GetXPos() - 20.0, (float) metabolite_v->GetYPos() - 15.0, 50.0, 30.0);
    ofSetColor(0, 0, 0);
    ofDrawCircle((float) metabolite_v->GetXPos(), (float) metabolite_v->GetYPos(), 21.0);
    ofSetColor((int) pathway_.curr_state[metabolite_v] * 255 / 100000);
    ofDrawCircle((float) metabolite_v->GetXPos(), (float) metabolite_v->GetYPos(), 20.0);
    ofSetColor(ofColor::green);
    int num_particles = pathway_.curr_state[metabolite_v];
    std::string metabolite_info = metabolite_v->GetShortname() + "\n" + std::to_string(num_particles);
    ofDrawBitmapString(metabolite_info, (float) metabolite_v->GetXPos() - 10, (float) metabolite_v->GetYPos());
}

void ofApp::drawReaction(const Reaction& reaction_v, int enzyme_x_pos, int enzyme_y_pos) {
    ofSetColor(0,0,0);
//    for (Metabolite reactant : reaction_v.GetReactants()) {
//        ofVec2f arrowTailPoint(reactant.GetXPos(), reactant.GetYPos());
//        ofVec2f arrowHeadPoint(enzyme_x_pos, enzyme_y_pos);
//        ofDrawArrow(arrowTailPoint, arrowHeadPoint, 10.0);
//    }
    for (Metabolite *product : reaction_v.GetProducts()) {
        ofVec2f arrowTailPoint(enzyme_x_pos, enzyme_y_pos);
        ofVec2f arrowHeadPoint(product->GetXPos(), product->GetYPos());
        ofDrawArrow(arrowHeadPoint, arrowTailPoint, 0.0);
    }
}

void ofApp::drawToolbar() {
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(std::to_string(seconds_passed_), 10, 10);
}

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetBackgroundColor(255, 200, 200);
    std::string filename = "/Users/Kate/Documents/GitHub/Useful_Libraries/of_v0.9.8_osx_release/apps/myApps/final-project-KatherineRitchie/data/methanogenesis.json";
    pathway_ = Pathway(filename);
    ofSetWindowTitle(pathway_.GetName());
    seconds_passed_ = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    seconds_passed_ += 1;
    pathway_.incrementTime();
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (Enzyme *enzyme : pathway_.GetEnzymes()) {
        drawEnzyme(*enzyme);
    }
    for (Metabolite *metabolite : pathway_.GetMetabolites()) {
        drawMetabolite(metabolite);
    }
    drawToolbar();
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

