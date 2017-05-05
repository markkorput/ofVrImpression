//--------------------------------------------------------------
// ofApp.h
//--------------------------------------------------------------

#include "ofMain.h"
#include "ofxBootstrApp.h"

class ofApp : public ofxBootstrApp::App {

public:
    void setup();
    void setupParameters();
    void update();
    void draw();

private:
    ofParameter<string> texturePathParam;
};


//--------------------------------------------------------------
// ofApp.cpp
//--------------------------------------------------------------

void ofApp::setup(){
    // ofxBootstrApp::App's setup method takes care of;
    // - setting up parameters
    // - loading parameters
    // - redirecting loggings output according to parameter configuration
    // - sets log level based on ofxBootstrApp::App::logLevelParam
    ofxBootstrApp::App::setup();

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
}

//--------------------------------------------------------------
// main.cpp
//--------------------------------------------------------------

int main(){
    ofSetupOpenGL(1024,768,OF_WINDOW);
    ofRunApp(new ofApp());
}
