#pragma once

#include "ofMain.h"
#include "ofxBootstrApp.h"

class ofApp : public ofxBootstrApp::App {

public:
    void setup();
    void setupParameters();
    void update();
    void draw();


private:
    //! changes the texcoords of all vertices in our sphere mesh to match with the given texture's dimensions
    void updateMeshForTexture(ofTexture &texture);

private:
    ofParameter<string> texturePathParam;

    ofImage image;
    ofTexture videoTexture;
    ofMesh sphereMesh;
    // ofCamera cam;
    ofEasyCam cam;

};
