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
    //! loads the specified image and makes sure sphereMesh gets updated if necessary
    bool loadImage(const string& path);

    //! changes the texcoords of all vertices in the mesh to match with the given texture's dimensions
    static void normalizeMeshTexCoord(ofMesh &mesh, const ofVec2f &textureDimensions, bool normalize=false);

private:
    ofParameter<string> imagePathParam;

    ofImage image;
    ofTexture* texture;
    ofMesh sphereMesh;
    // ofCamera cam;
    ofEasyCam cam;
};
