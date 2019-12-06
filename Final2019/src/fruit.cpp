#include "fruit.hpp"

#include <cmath>

#include "ofMain.h"

#include "particle.hpp"

Fruit::Fruit() : Fruit(0, 0) {	
}

Fruit::Fruit(float sx, float sy) {
	SetPos(sx, sy);
	SetVel(0, 0);
	SetAcc(0, 0);
	hit_count_ = 0;

	for (int i = 0; i < kNumParticles; ++i) {
		float r = ofRandom(0, kRadius);
		float theta = ofRandom(0, 2 * kPi);
		Particle particle{ sx + r * cos(theta), sy + r * sin(theta) };
		particles_.push_back(particle);
	}
}

void Fruit::SetPos(float sx, float sy) { 
	float x_diff = sx - s_.x;
	float y_diff = sy - s_.y;
	s_.set(sx, sy);
	for (auto &particle : particles_) {
		particle.AddPos(x_diff, y_diff);
	}
}

void Fruit::SetVel(float vx, float vy) { 
	v_.set(vx, vy);
	for (auto& particle : particles_) {
		particle.SetVel(vx, vy);
	}
}

void Fruit::SetAcc(float ax, float ay) { 
	a_.set(ax, ay);
	for (auto& particle : particles_) {
		particle.SetAcc(ax, ay);
	}
}

void Fruit::AddAcc(float ax, float ay) {
	a_.x += ax;
	a_.y += ay;
	for (auto& particle : particles_) {
		particle.AddAcc(ax, ay);
	}
}

void Fruit::ResetAcc() {
	a_.set(0, 0);
	for (auto& particle : particles_) {
		particle.SetAcc(0, 0);
	}
}

void Fruit::HitFruit() {
	hit_count_ += 1;
}

void Fruit::UpdateState() {
	v_ += a_;  // v = v0 + at
	s_ += v_;  // s = s0 + vt

	if (hit_count_ == 0) {
		//all particles move together as a whole, if fruit is still intact
		for (auto& particle : particles_) {
			particle.AddVel(particle.GetAcc().x, particle.GetAcc().y);
			particle.AddPos(particle.GetVel().x, particle.GetVel().y);
		}
	} else {
		for (auto& particle : particles_) {
			if (hit_count_ == 1) {
				particle.SetVel(ofRandom(-1, 1), ofRandom(-2, 2));
			}
			particle.AddVel(particle.GetAcc().x, particle.GetAcc().y);
			particle.AddPos(particle.GetVel().x, particle.GetVel().y);
		}
	}
}

void Fruit::Draw() const {
	for (const auto &particle : particles_) {
		particle.Draw();
	}
}

ofVec2f Fruit::GetPos() const { 
	return s_; 
}

ofVec2f Fruit::GetVel() const { 
	return v_; 
}

ofVec2f Fruit::GetAcc() const { 
	return a_; 
}

bool Fruit::IsHit() const {
	return hit_count_ != 0;
}
