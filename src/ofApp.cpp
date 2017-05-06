#include "ofApp.h"

void ofApp::setup(){
    // ofxBootstrApp::App's setup method takes care of;
    // - setting up parameters
    // - loading parameters
    // - redirecting loggings output according to parameter configuration
    // - sets log level based on ofxBootstrApp::App::logLevelParam
    ofxBootstrApp::App::setup();

    ofSetVerticalSync(true);
    ofSetFrameRate(60);

    ofSpherePrimitive p = ofSpherePrimitive(100.0,60);
    sphereMesh = p.getMesh();

    if(imagePathParam.get() != "")
        loadImage(imagePathParam.get());

    ofSetWindowTitle("ofVrImpression - " + versionParam.get());
}

void ofApp::setupParameters(){
    ofxBootstrApp::App::setupParameters();
    parameters.setName("ofVrImpression");
    parameters.add(imagePathParam.set("texture-path", "data/texture.jpg"));
}

void ofApp::update(){
    cam.setPosition(0,0,0);
}

void ofApp::draw(){
    ofClear(0);

    cam.begin();
    if(texture){
        ofSetColor(255);
        texture->bind();
        sphereMesh.draw();
        texture->unbind();
    } else {
        ofSetColor(255,0,0);
        sphereMesh.drawWireframe();
    }
    cam.end();

    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 10);
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    for(auto file: dragInfo.files){
        imagePathParam.set(file);
        loadImage(file);
    }
}

bool ofApp::loadImage(const string& path){
    ofLog() << "loading image: " << path;
    bool bPrevious = false;
    ofVec2f previousDimensions;

    // remember dimensions of previous image for normalization if a new image gets loaded
    if(image.isAllocated()){
        bPrevious = true;
        previousDimensions.set(image.getWidth(), image.getHeight());
    }

    // try to load specified image
    if(!image.load(path)){
        ofLogWarning() << "failed to load image: " << path;
        return false;
    }

    if(bPrevious){
        // normalize; undo denormalization for previous image's texture
        normalizeMeshTexCoord(sphereMesh, previousDimensions, true);
    }

    // denormalize for the new image dimensions (the default shader needs denormalized texcoords)
    normalizeMeshTexCoord(sphereMesh, ofVec2f(image.getWidth(), image.getHeight()));

    // point our main texture to the loaded image's texture
    texture = &image.getTexture();
    return true;
}

void ofApp::normalizeMeshTexCoord(ofMesh &mesh, const ofVec2f &textureDimensions, bool normalize){
    if(normalize){
        // assume current texCoords are denormalized (pixel-based, not percentage-based)
        // and convert to normalized texCoords
        for(int i=0; i<mesh.getNumVertices(); i++){
            ofVec2f texCoord = mesh.getTexCoord(i);
            texCoord.x /= textureDimensions.x;
            texCoord.y = -(texCoord.y / textureDimensions.y) + 1.0;
            mesh.setTexCoord(i, texCoord);
        }

        return;
    }

    // assumes current texCoord are normalized (percentage-based),
    // and denormalizes them (make them pixel-based)
    for(int i=0; i<mesh.getNumVertices(); i++){
        ofVec2f texCoord = mesh.getTexCoord(i);
        texCoord.x *= textureDimensions.x;
        texCoord.y = (1.0 - texCoord.y) * textureDimensions.y;
        mesh.setTexCoord(i, texCoord);
    }
}

//--------------------------------------------------------------
// main.cpp
//--------------------------------------------------------------

int main(){
    ofSetupOpenGL(1024,768,OF_WINDOW);
    ofRunApp(new ofApp());
}
