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

    if(!image.load(path))
        return false;

    texture = &image.getTexture();
    updateMeshForTexture(image.getTexture());
    return true;
}

void ofApp::updateMeshForTexture(ofTexture &texture){
    for(int i=0; i<sphereMesh.getNumVertices(); i++){
        ofVec2f texCoord = sphereMesh.getTexCoord(i);
        texCoord.x *= texture.getWidth();
        texCoord.y  = (1.0 - texCoord.y) * texture.getHeight();
        sphereMesh.setTexCoord(i, texCoord);
    }
}

//--------------------------------------------------------------
// main.cpp
//--------------------------------------------------------------

int main(){
    ofSetupOpenGL(1024,768,OF_WINDOW);
    ofRunApp(new ofApp());
}
