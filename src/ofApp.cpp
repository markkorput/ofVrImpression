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

    if(texturePathParam.get() != ""){
        ofLog() << "loading image: " << texturePathParam.get();
        image.load(texturePathParam.get());
    }

    updateMeshForTexture(image.getTexture());

    ofSetWindowTitle("ofVrImpression - " + versionParam.get());
}

void ofApp::setupParameters(){
    ofxBootstrApp::App::setupParameters();
    parameters.setName("ofVrImpression");
    parameters.add(texturePathParam.set("texture-path", "data/texture.jpg"));
}

void ofApp::update(){

}

void ofApp::draw(){
    ofClear(0);

    cam.begin();
    image.getTexture().bind();
    sphereMesh.draw();
    image.getTexture().unbind();
    cam.end();

    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 10);
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
