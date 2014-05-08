#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
	fft.setup(1024, OF_FFT_WINDOW_HAMMING, OF_FFT_BASIC);
    fft.setUseNormalization(true);
    beacon.setup("AB997D38-4F9A-4AC4-8BBB-AB31128D13C3", 1, 1, -58);
}

//--------------------------------------------------------------
void ofApp::update(){
    fft.update();
    vector<float> bins = fft.getBins();
    float sum = 0;
    float maxVal = 0;
    int maxIdx = 0;
    for (int i=0; i<bins.size(); ++i) {
        float b = bins[i];
        sum += b;
        if (b > maxVal) {
            maxVal = b;
            maxIdx = i;
        }
    }
    
    float ratio = bins[maxIdx] / sum;
    if (!active && bins[maxIdx]/sum > 0.30 && (33 < maxIdx && maxIdx < 42)) {
        ofLogNotice() << "fired";
        active = true;
        startTime = ofGetElapsedTimef();
        beacon.startAdvertise();
    }
    
    if (active) {
        float elapsed = ofGetElapsedTimef() - startTime;
        if (elapsed > 10) {
            ofLogNotice() << "stopping beacon advertising";
            beacon.stopAdvertise();
            active = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
	
	ofPushMatrix();
	ofTranslate(16, 16);
	ofSetColor(255);
	ofDrawBitmapString("Frequency Domain", 0, 0);
	plot(fft.getBins(), 128);
	ofPopMatrix();
	
	string msg = ofToString((int) ofGetFrameRate()) + " fps";
	ofDrawBitmapString(msg, ofGetWidth() - 80, ofGetHeight() - 20);
}

void ofApp::plot(vector<float>& buffer, float scale) {
	ofNoFill();
	int n = MIN(1024, buffer.size());
	ofRect(0, 0, n, scale);
	ofPushMatrix();
	ofTranslate(0, scale);
	ofScale(1, -scale);
	ofBeginShape();
	for (int i = 0; i < n; i++) {
		ofVertex(i, buffer[i]);
	}
	ofEndShape();
	ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
