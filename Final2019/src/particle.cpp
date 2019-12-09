#include "particle.hpp"

#include "ofMain.h"

Particle::Particle() : Particle(0, 0) {
}

Particle::Particle(float sx, float sy, int radius) {
  SetPos(sx, sy);
  SetVel(0, 0);
  SetAcc(0, 0);
  particle_radius_ = radius;
}

void Particle::SetPos(float sx, float sy) {
  pos_.set(sx, sy);
}

void Particle::SetVel(float vx, float vy) {
  vel_.set(vx, vy);
}

void Particle::SetAcc(float ax, float ay) {
  acc_.set(ax, ay);
}

void Particle::AddPos(float sx, float sy) {
  pos_.x += sx;
  pos_.y += sy;
}

void Particle::AddVel(float vx, float vy) {
  vel_.x += vx;
  vel_.y += vy;
}

void Particle::AddAcc(float ax, float ay) {
  acc_.x += ax;
  acc_.y += ay;
}

void Particle::ResetAcc() {
  acc_.set(0, 0);
}

ofVec2f Particle::GetPos() const {
  return pos_;
}

ofVec2f Particle::GetVel() const {
  return vel_;
}

ofVec2f Particle::GetAcc() const {
  return acc_;
}

void Particle::UpdateState() {
  vel_ += acc_;  // v = v0 + at
  pos_ += vel_;  // s = s0 + vt
}

void Particle::Draw() const {
  ofDrawCircle(pos_.x, pos_.y, particle_radius_);
}
