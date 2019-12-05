#include "ofApp.h"

#include "particle.h"

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	for (int i = 0; i < 100; ++i) {
		Particle particle;
		float vx = ofRandom(-2, 2);
		float vy = ofRandom(-2, 2);
		particle.SetPos(500, 400);
		particle.SetVel(vx, vy);
		particles.push_back(particle);
	}
}

void ofApp::update(){
	for (Particle& particle : particles) {
		particle.ResetAcc();
		//note: add acc/forces here
		particle.UpdateState();
	}
}

void ofApp::draw(){
	ofSetColor(ofColor::black);
	for (const Particle& particle : particles) {
		particle.Draw();
	}
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
