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

//HSV (20, 100, 100) -> (30, 255, 255) is the range for yellow
constexpr int kHueMin = 20;
constexpr int kSatMin = 100;
constexpr int kValMin = 100;
constexpr int kHueMax = 30;
constexpr int kSatMax = 255;
constexpr int kValMax = 255;

constexpr int kBlackPixel = 0;
constexpr int kWhitePixel = 255;

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

	unsigned char* mask_pixels; //represents a "mask" of the frame based on specified HSV range
	ofxCvGrayscaleImage target;
	ofxCvContourFinder target_contour;
};
