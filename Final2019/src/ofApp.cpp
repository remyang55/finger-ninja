#include "ofApp.h"

#include "fruit.hpp"

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	cannon.FireFruit(fruits);
}

void ofApp::update() {
	for (auto &fruit : fruits) {
		fruit.ResetAcc();
		if (!fruit.IsHit()) {
			fruit.AddAcc(0, 0.3);
		}
		else {
			fruit.AddAcc(0, 0.8);
		}
		fruit.UpdateState();
	}
}

void ofApp::draw() {
	ofSetColor(ofColor::black);
	for (auto &fruit : fruits) {
		fruit.Draw();
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
void ofApp::mouseDragged(int x, int y, int button) {
	for (auto &fruit : fruits) {
		float dist_to_fruit = sqrt(pow(x - fruit.GetPos().x, 2) + pow(y - fruit.GetPos().y, 2));
		if (dist_to_fruit < kRadius) {
			fruit.HitFruit();
		}
	}
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
