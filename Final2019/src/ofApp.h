#ifndef OFAPP_H_
#define OFAPP_H_

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "fruit.hpp"
#include "fruit_cannon.hpp"

/**
 * If you would like to track an object of a different color, adjust the HSV ranges here!
 * By default, HSV (20, 100, 100) -> (30, 255, 255) is the range for yellow
 */
constexpr int kHueMin = 20;
constexpr int kSatMin = 100;
constexpr int kValMin = 100;
constexpr int kHueMax = 30;
constexpr int kSatMax = 255;
constexpr int kValMax = 255;

constexpr int kFps = 60;

constexpr int kFontSize = 50;
constexpr int kPointsXLoc = 6;
constexpr int kPointsYLoc = 60;
constexpr int kLivesXLoc = 6;
constexpr int kLivesYLoc = 120;
constexpr int kCursorRadius = 5;
constexpr int kGameOverXLoc = 350;
constexpr int kGameOverYLoc = 350;
constexpr int kPointsFinalXLoc = 260;
constexpr int kPointsFinalYLoc = 420;

constexpr int kCannonDelayInitial = 2000; //in milliseconds
constexpr int kCannonHeightBelowScreen = 5; //must be less than radius of a fruit
constexpr int kCannonSpeed = 20; //how fast fruits are fired
constexpr float kCannonMinAngle = kPi / 3;
constexpr float kCannonMaxAngle = 2 * kPi / 3;

constexpr float kAccFruitIntact = 0.3; //vertical acceleration of fruits before hit
constexpr float kAccFruitHit = 0.6; //vertical acceleration of fruits' particles after hit

constexpr int kDetectionWidth = 256; //width of window to draw webcam on
constexpr int kDetectionHeight = 192; //height of window to draw webcam on
constexpr int kDetectionMinArea = 50;
constexpr int kDetectionZones = 1; //number of contours to detect

constexpr int kBlackPixel = 0;
constexpr int kWhitePixel = 255;

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

 private:
  void ReadPlayerPosition();
  void ExecuteGameLogic();
  float GetCannonDelayFactor(int elapsed_time); //elapsed_time in milliseconds

  ofTrueTypeFont font_;

  ofSoundPlayer background_music_;
  ofSoundPlayer fruit_throw_sound_;
  ofSoundPlayer bomb_throw_sound_;
  ofSoundPlayer fruit_slash_sound_;
  ofSoundPlayer hit_bomb_sound_;

  //VARIABLES FOR GAME
  int player_pts_;
  int player_hp_;
  bool is_game_over_;

  std::vector<Fruit> fruits_;
  FruitCannon cannon_{0, ofGetWidth(), ofGetHeight() + kCannonHeightBelowScreen,
                      kCannonSpeed, kCannonMinAngle, kCannonMaxAngle};
  int cannon_delay_; //in milliseconds
  float last_time_; //the last time the cannon was fired

  //VARIABLES FOR OBJECT TRACKING
  ofVideoGrabber webcam_;
  ofxCvColorImage webcam_render_;

  ofxCvGrayscaleImage hue_;
  ofxCvGrayscaleImage sat_;
  ofxCvGrayscaleImage val_;

  unsigned char *mask_pixels_; //represents a "mask" of the frame based on specified HSV range
  ofxCvGrayscaleImage target_img_;
  ofxCvContourFinder target_contour_;
  ofVec2f target_loc_;
};

#endif  // OFAPP_H_
