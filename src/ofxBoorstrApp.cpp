#include "ofxBootstrApp.h"

#define DEFAULT_PARAMS_FILE "params.xml"

using namespace ofxBootstrApp;

void App::setup(){
    setupParameters();
    loadParameters(paramsFileParam.get());

    if(logFileParam.get() != "")
        redirectLogging(logFileParam.get());

    if(logLevelParam.get() != "")
        setLogLevel(logLevelParam.get());

    // calculate time between two frames ("delta-time")
    dt = 1.0f/ofGetFrameRate();
}

void App::exit(ofEventArgs &args){
    saveParameters(paramsFileParam.get());
    ofLog() << "Done, ciao.";
}

void App::setupParameters(){
    parameters.setName("ofApp");
    parameters.add(versionParam.set("version", "0.0.0"));
    parameters.add(logFileParam.set("log-file", ""));
    parameters.add(logLevelParam.set("log-level", ""));
    parameters.add(paramsFileParam.set("params-file", DEFAULT_PARAMS_FILE));
}

void App::loadParameters(const string& filename){
    ofLog() << "Loading parameters from file: " << filename;
    std::shared_ptr <ofBaseFileSerializer> serializer = std::make_shared<ofXml>();
    serializer->load(filename);
    serializer->deserialize(parameters);
}

void App::saveParameters(const string& filename){
    ofLog() << "Saving parameters to file: " << filename;
    std::shared_ptr <ofBaseFileSerializer> serializer = std::make_shared<ofXml>();
    serializer->load(filename);
    serializer->serialize(parameters);
    serializer->save(filename);
}

void App::redirectLogging(const string& filename){
    // setup logging; destination
    ofLog() << "Redirecting logging output to: " << logFileParam.get();
    ofLogToFile(filename);
}

void App::setLogLevel(const string& newLevel){
    string level = ofToLower(ofTrim(newLevel));
    ofLogLevel lvl;

    if(level == "")
        return;

    if(level == "verbose"){
        lvl = OF_LOG_VERBOSE;
    } else if(level == "notice"){
        lvl = OF_LOG_NOTICE;
    } else if(level == "warning"){
        lvl = OF_LOG_WARNING;
    } else if(level == "error"){
        lvl = OF_LOG_ERROR;
    } else if(level == "fatal"){
        lvl = OF_LOG_FATAL_ERROR;
    } else if(level == "silent"){
        lvl = OF_LOG_SILENT;
    } else {
        ofLogWarning() << "Unknown log level value: " << level;
        return;
    }

    ofLog() << "Set log level to: " << level;
    ofSetLogLevel(lvl);
}
