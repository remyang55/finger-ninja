#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "fruit.hpp"
#include "fruit_cannon.hpp"

constexpr int kFps = 60;

constexpr int kCannonHeightBelowScreen = 5;
constexpr int kCannonSpeed = 20;
constexpr float kCannonMinAngle = kPi / 3;
constexpr float kCannonMaxAngle = 2 * kPi / 3;
constexpr int kCannonDelay = 2000; //milliseconds

constexpr float kAccFruitIntact = 0.3; // vertical acceleration of fruits before hit
constexpr float kAccFruitHit = 0.6; // vertical acceleration of fruits' particles after hit

constexpr int kWindowWidth = 512; //width of window to draw webcam on
constexpr int kWindowHeight = 384; //height of window to draw webcam on

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofTrueTypeFont font;

	//VARIABLES FOR GAME
	std::vector<Fruit> fruits;
	FruitCannon cannon{ 0, ofGetWidth(), ofGetHeight() + kCannonHeightBelowScreen,
		kCannonSpeed, kCannonMinAngle, kCannonMaxAngle };
	float last_time; //the last time the cannon was fired
	int player_pts;

	//VARIABLES FOR HAND TRACKING
	ofVideoGrabber webcam;
	ofxCvColorImage webcam_render;
	ofxCvColorImage webcam_render_hsv;
	ofxCvGrayscaleImage hue;
	ofxCvGrayscaleImage sat;
	ofxCvGrayscaleImage val;

};
