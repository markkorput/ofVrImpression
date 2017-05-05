#pragma once

#include "ofMain.h"
#include "ofxBootstrApp.h"

class ofApp : public ofxBootstrApp::App {

public:
    void setup();
    void setupParameters();
    void update();
    void draw();
    void dragEvent(ofDragInfo dragInfo);

private:
    // loads the specified image and makes sure sphere mesh gets updated if necessary
    bool loadImage(const string& path);
    //! changes the texcoords of all vertices in our sphere mesh to match with the given texture's dimensions
    void updateMeshForTexture(ofTexture &texture);

private:
    ofParameter<string> imagePathParam;

    ofImage image;
    ofTexture* texture;;
    ofMesh sphereMesh;
    // ofCamera cam;
    ofEasyCam cam;
};
