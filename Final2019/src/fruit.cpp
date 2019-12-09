#include "fruit.hpp"

#include <cmath>
#include <vector>

#include "ofMain.h"

#include "particle.hpp"

Fruit::Fruit() : Fruit(0, 0, false) {
}

Fruit::Fruit(float sx, float sy, bool is_explosive) {
  is_explosive_ = is_explosive;
  hit_count_ = 0;
  update_count_ = 0;

  SetPos(sx, sy);
  SetVel(0, 0);
  SetAcc(0, 0);

  for (int i = 0; i < kNumParticles; ++i) {
    float r = ofRandom(0, kRadius);
    float theta = ofRandom(0, 2 * kPi);
    Particle particle{sx + r * cos(theta), sy + r * sin(theta)};
    particles_.push_back(particle);
  }
}

void Fruit::SetPos(float sx, float sy) {
  float x_diff = sx - pos_.x;
  float y_diff = sy - pos_.y;
  pos_.set(sx, sy);
  for (auto &particle : particles_) {
    particle.AddPos(x_diff, y_diff);
  }
}

void Fruit::SetVel(float vx, float vy) {
  vel_.set(vx, vy);
  for (auto &particle : particles_) {
    particle.SetVel(vx, vy);
  }
}

void Fruit::SetAcc(float ax, float ay) {
  acc_.set(ax, ay);
  for (auto &particle : particles_) {
    particle.SetAcc(ax, ay);
  }
}

void Fruit::AddAcc(float ax, float ay) {
  acc_.x += ax;
  acc_.y += ay;
  for (auto &particle : particles_) {
    particle.AddAcc(ax, ay);
  }
}

void Fruit::ResetAcc() {
  acc_.set(0, 0);
  for (auto &particle : particles_) {
    particle.SetAcc(0, 0);
  }
}

void Fruit::HitFruit() {
  ++hit_count_;
}

void Fruit::UpdateState() {
  vel_ += acc_;  // v = v0 + at
  s_ += vel_;  // s = s0 + vt

  if (hit_count_ == kTargetHitCount) {
    ++update_count_;
  }

  for (auto &particle : particles_) {
    particle.AddVel(particle.GetAcc().x, particle.GetAcc().y);
    particle.AddPos(particle.GetVel().x, particle.GetVel().y);

    //if fruit is hit, make it explode
    if (hit_count_ == kTargetHitCount && update_count_ < kMaxUpdateCount) {
      float vx = ofRandom(kMinExplosionSpeed, kMaxExplosionSpeed);
      float vy = ofRandom(kMinExplosionSpeed, kMaxExplosionSpeed);
      particle.SetVel(vx, vy);
    }
  }
}

void Fruit::Draw() const {
  if (is_explosive_) {
    ofSetColor(ofColor::black);
  } else {
    ofSetColor(ofColor::orange);
  }

  for (const auto &particle : particles_) {
    particle.Draw();
  }
}

bool Fruit::IsExplosive() const {
  return is_explosive_;
}

bool Fruit::IsHit() const {
  return hit_count_ == kTargetHitCount;
}

ofVec2f Fruit::GetPos() const {
  return pos_;
}

ofVec2f Fruit::GetVel() const {
  return vel_;
}

ofVec2f Fruit::GetAcc() const {
  return acc_;
}

std::vector<Particle> Fruit::GetParticles() const {
  return particles_;
}
