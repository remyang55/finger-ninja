#include "ofApp.h"

#include <cmath>

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "fruit.hpp"
#include "fruit_cannon.hpp"

void ofApp::setup() {
  ofSetVerticalSync(true);
  ofSetFrameRate(kFps);

  font_.load("kiyana.otf", kFontSize);
  background_music_.load("background_music.mp3");
  background_music_.setVolume(0.5); //lower the volume to half the original
  background_music_.play();
  background_music_.setLoop(true);
  fruit_throw_sound_.load("fruit_throw.mp3");
  bomb_throw_sound_.load("bomb_throw.mp3");
  fruit_slash_sound_.load("fruit_slash.mp3");
  hit_bomb_sound_.load("hit_bomb.mp3");
  hit_bomb_sound_.setVolume(1.5);

  player_pts_ = 0;
  player_hp_ = 3;
  is_game_over_ = false;
  cannon_delay_ = kCannonDelayInitial;
  last_time_ = 0;

  webcam_.setup(kDetectionWidth, kDetectionHeight);
  webcam_render_.allocate(kDetectionWidth, kDetectionHeight);
  hue_.allocate(kDetectionWidth, kDetectionHeight);
  sat_.allocate(kDetectionWidth, kDetectionHeight);
  val_.allocate(kDetectionWidth, kDetectionHeight);

  mask_pixels_ = new unsigned char[kDetectionWidth * kDetectionHeight];
  target_img_.allocate(kDetectionWidth, kDetectionHeight);
}

void ofApp::update() {
  if (!is_game_over_) {
    ReadPlayerPosition();
    ExecuteGameLogic();
  } else {
    if (!hit_bomb_sound_.isPlaying()) {
      background_music_.setPaused(false);
    }
  }
}

void ofApp::draw() {
  if (!is_game_over_) {
    ofSetColor(ofColor::black);
    font_.drawString("Points: " + std::to_string(player_pts_), kPointsXLoc, kPointsYLoc);
    font_.drawString("Lives: " + std::to_string(player_hp_), kLivesXLoc, kLivesYLoc);
    for (const auto &fruit : fruits_) {
      fruit.Draw();
    }

    //draw tracked object location
    ofSetColor(ofColor::blue);
    ofDrawCircle(target_loc_.x, target_loc_.y, kCursorRadius);
  } else {
    ofSetColor(ofColor::black);
    font_.drawString("Game Over!", kGameOverXLoc, kGameOverYLoc);
    font_.drawString("You scored " + std::to_string(player_pts_) + " points", kPointsFinalXLoc,
                     kPointsFinalYLoc);
  }
}

void ofApp::ReadPlayerPosition() {
  webcam_.update();
  if (webcam_.isFrameNew()) {
    auto pixels = webcam_.getPixels();
    pixels.mirror(false, true);
    webcam_render_.setFromPixels(pixels.getData(), kDetectionWidth, kDetectionHeight);

    webcam_render_.convertRgbToHsv();
    webcam_render_.convertToGrayscalePlanarImages(hue_, sat_, val_);
    hue_.flagImageChanged();
    sat_.flagImageChanged();
    val_.flagImageChanged();

    unsigned char *hue_pixels = hue_.getPixels().getData();
    unsigned char *sat_pixels = sat_.getPixels().getData();
    unsigned char *val_pixels = val_.getPixels().getData();

    for (int i = 0; i < kDetectionWidth * kDetectionHeight; ++i) {
      if ((hue_pixels[i] >= kHueMin && hue_pixels[i] <= kHueMax)
          && (sat_pixels[i] >= kSatMin && sat_pixels[i] <= kSatMax)
          && (val_pixels[i] >= kValMin && val_pixels[i] <= kValMax)) {
        mask_pixels_[i] = kWhitePixel;
      } else {
        mask_pixels_[i] = kBlackPixel;
      }
    }

    target_img_.setFromPixels(mask_pixels_, kDetectionWidth, kDetectionHeight);
    target_contour_.findContours(target_img_, kDetectionMinArea, kDetectionWidth * kDetectionHeight,
                                 kDetectionZones, false, true);

    //if a target is found
    if (target_contour_.blobs.size() > 0) {
      auto target = target_contour_.blobs[0];
      target_loc_.x = target.centroid.x * (ofGetWidth() / kDetectionWidth);
      target_loc_.y = target.centroid.y * (ofGetHeight() / kDetectionHeight);
    }
  }
}

void ofApp::ExecuteGameLogic() {
  if (ofGetElapsedTimeMillis() - last_time_ >= cannon_delay_) {

    //if fired fruit is explosive, play bomb_throw sound, else fruit_throw sound
    if(cannon_.FireFruit(fruits_)) {
      bomb_throw_sound_.play();
    } else {
      fruit_throw_sound_.play();
    }
    cannon_delay_ = kCannonDelayInitial / GetCannonDelayFactor(ofGetElapsedTimeMillis());
    last_time_ = ofGetElapsedTimeMillis();
  }

  cannon_.CheckFruits(fruits_, player_hp_); //delete fruits that are out of the screen
  if (player_hp_ == 0) {
    is_game_over_ = true;
  }

  for (auto &fruit : fruits_) {
    //update fruit location
    fruit.ResetAcc();
    if (!fruit.IsHit()) {
      fruit.AddAcc(0, kAccFruitIntact);
    } else {
      fruit.AddAcc(0, kAccFruitHit);
    }
    fruit.UpdateState();

    //check if player has sliced fruit
    float x_diff = target_loc_.x - fruit.GetPos().x;
    float y_diff = target_loc_.y - fruit.GetPos().y;
    float dist_to_fruit = sqrt(pow(x_diff, 2) + pow(y_diff, 2));

    if (dist_to_fruit < kRadius && !fruit.IsHit()) {
      if (fruit.IsExplosive()) {
        background_music_.setPaused(true);
        background_music_.setPosition(0);
        hit_bomb_sound_.play();
        is_game_over_ = true;
        break;
      }

      ++player_pts_;
      fruit_slash_sound_.play();
      fruit.HitFruit();
    }
  }
}

float ofApp::GetCannonDelayFactor(int elapsed_time) {
  return 3 / (1 + exp(-0.02 * (elapsed_time / 1000) + 2)) + 0.7;
}
