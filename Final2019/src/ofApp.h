#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "fruit.hpp"
#include "fruit_cannon.hpp"

constexpr int kFps = 60;

constexpr int kCannonDelayInitial = 2000; //in milliseconds
constexpr int kCannonHeightBelowScreen = 5;
constexpr int kCannonSpeed = 20;
constexpr float kCannonMinAngle = kPi / 3;
constexpr float kCannonMaxAngle = 2 * kPi / 3;

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

	void mouseDragged(int x, int y, int button);
	
	float GetCannonDelayFactor(int elapsed_time); //elapsed_time in milliseconds

	ofTrueTypeFont font;

	//VARIABLES FOR GAME
	int player_pts;
	bool is_game_over;
	std::vector<Fruit> fruits;
	FruitCannon cannon{ 0, ofGetWidth(), ofGetHeight() + kCannonHeightBelowScreen,
		kCannonSpeed, kCannonMinAngle, kCannonMaxAngle };

	int cannon_delay; //in milliseconds
	float last_time; //the last time the cannon was fired
	

	//VARIABLES FOR HAND TRACKING
	ofVideoGrabber webcam;
	ofxCvColorImage webcam_render;
	ofxCvColorImage webcam_render_hsv;

	ofxCvGrayscaleImage hue;
	ofxCvGrayscaleImage sat;
	ofxCvGrayscaleImage val;

	unsigned char *mask_pixels; //represents a "mask" of the frame based on specified HSV range
	ofxCvGrayscaleImage target_img;
	ofxCvContourFinder target_contour;
	ofVec2f target_loc;
};
