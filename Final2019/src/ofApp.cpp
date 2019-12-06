#include "ofApp.h"

#include "fruit.hpp"

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	fruit.SetVel(3, 3);
}

void ofApp::update(){
	fruit.ResetAcc();
	fruit.AddAcc(0, 0.05);
	fruit.UpdateState();
}

void ofApp::draw(){
	ofSetColor(ofColor::black);
	fruit.Draw();
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
	float dist_to_fruit = sqrt(pow(x - fruit.GetPos().x, 2) + pow(y - fruit.GetPos().y, 2));
	if (dist_to_fruit < kRadius) {
		std::cout << "collide";
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
