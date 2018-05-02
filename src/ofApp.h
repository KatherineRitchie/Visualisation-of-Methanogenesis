#pragma once

#include "ofMain.h"
#include "pathway.h"
#include "ofxGui.h"
#include <iomanip>

class ofApp : public ofBaseApp{
    Pathway pathway;
    int secondsPassed;
    bool bPause = true;
    
    private:
    void drawEnzyme(const Enzyme& enzyme_v);
    void drawMetabolite(Metabolite* metabolite_);
    void drawReaction(const Reaction& reaction_v, int enzyme_x_pos, int enzyme_y_pos);
    void drawToolbar();

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
};

