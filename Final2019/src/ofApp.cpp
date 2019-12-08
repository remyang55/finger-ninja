#include "ofApp.h"

#include <cmath>

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "fruit.hpp"
#include "fruit_cannon.hpp"

void ofApp::setup() {
	ofSetVerticalSync(true);
	ofSetFrameRate(kFps);
	
	webcam.setup(kDetectionWidth, kDetectionHeight);
	webcam_render.allocate(kDetectionWidth, kDetectionHeight);
	webcam_render_hsv.allocate(kDetectionWidth, kDetectionHeight);
	hue.allocate(kDetectionWidth, kDetectionHeight);
	sat.allocate(kDetectionWidth, kDetectionHeight);
	val.allocate(kDetectionWidth, kDetectionHeight);

	mask_pixels = new unsigned char[kDetectionWidth * kDetectionHeight];
	target_img.allocate(kDetectionWidth, kDetectionHeight);
	
	font.load("kiyana.otf", 50);
	player_pts = 0;
	player_hp = 3;
	is_game_over = false;
	cannon_delay = kCannonDelayInitial;
	last_time = 0;
}

void ofApp::update() {
	
	webcam.update();
	if (webcam.isFrameNew()) {
		auto pixels = webcam.getPixels();
		pixels.mirror(false, true);
		webcam_render.setFromPixels(pixels.getData(), kDetectionWidth, kDetectionHeight);

		webcam_render_hsv = webcam_render;
		webcam_render_hsv.convertRgbToHsv();
		webcam_render_hsv.convertToGrayscalePlanarImages(hue, sat, val);

		hue.flagImageChanged();
		sat.flagImageChanged();
		val.flagImageChanged();

		unsigned char *hue_pixels = hue.getPixels().getData();
		unsigned char *sat_pixels = sat.getPixels().getData();
		unsigned char *val_pixels = val.getPixels().getData();

		for (int i = 0; i < kDetectionWidth * kDetectionHeight; ++i) {
			if ((hue_pixels[i] >= kHueMin && hue_pixels[i] <= kHueMax)
					&& (sat_pixels[i] >= kSatMin && sat_pixels[i] <= kSatMax)
					&& (val_pixels[i] >= kValMin && val_pixels[i] <= kValMax)) {
				mask_pixels[i] = kWhitePixel;
			} else {
				mask_pixels[i] = kBlackPixel;
			}
		}
		
		target_img.setFromPixels(mask_pixels, kDetectionWidth, kDetectionHeight);
		target_contour.findContours(target_img, 50, (kDetectionWidth * kDetectionHeight), 1, false, true);
		
		//if a target is found
		if (target_contour.blobs.size() > 0) {
			ofxCvBlob target = target_contour.blobs[0];
			target_loc.x = target.centroid.x * (ofGetWidth() / kDetectionWidth);
			target_loc.y = target.centroid.y * (ofGetWidth() / kDetectionWidth);
		}
	}
	

	if (!is_game_over) {
		if (ofGetElapsedTimeMillis() - last_time >= cannon_delay) {
			cannon.FireFruit(fruits);
			cannon_delay = kCannonDelayInitial / GetCannonDelayFactor(ofGetElapsedTimeMillis());
			last_time = ofGetElapsedTimeMillis();
		}

		cannon.CheckFruits(fruits, player_hp);
		if (player_hp == 0) {
			is_game_over = true;
		}

		for (auto &fruit : fruits) {
			fruit.ResetAcc();
			if (!fruit.IsHit()) {
				fruit.AddAcc(0, kAccFruitIntact);
			}
			else {
				fruit.AddAcc(0, kAccFruitHit);
			}
			fruit.UpdateState();
		}

		for (auto& fruit : fruits) {
			float x_diff = target_loc.x - fruit.GetPos().x;
			float y_diff = target_loc.y - fruit.GetPos().y;
			float dist_to_fruit = sqrt(pow(x_diff, 2) + pow(y_diff, 2));

			if (dist_to_fruit < kRadius && !fruit.IsHit()) {
				if (fruit.IsExplosive()) {
					is_game_over = true;
					break;
				}

				++player_pts;
				fruit.HitFruit();
			}
		}
	}
}

void ofApp::draw() {
	if (!is_game_over) {
		ofSetColor(ofColor::black);
		font.drawString("Points: " + std::to_string(player_pts), 6, 60);
		font.drawString("Lives: " + std::to_string(player_hp), 6, 120);
		for (const auto &fruit : fruits) {
			fruit.Draw();
		}

		//draw tracked object location
		ofSetColor(ofColor::blue);
		ofDrawCircle(target_loc.x, target_loc.y, 5);
	} else {
		ofSetColor(ofColor::black);
		font.drawString("Game Over!", 350, 350);
		font.drawString("You scored " + std::to_string(player_pts) + " points", 260, 420);
	}
}

void ofApp::mouseDragged(int x, int y, int button) {
	
}

float ofApp::GetCannonDelayFactor(int elapsed_time) {
	return 3 / (1 + exp(-0.02 * (elapsed_time / 1000) + 2)) + 0.7;
}
