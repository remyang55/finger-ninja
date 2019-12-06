#include "particle.hpp"

Particle::Particle() : Particle(0, 0) {
}

Particle::Particle(float sx, float sy) {
	SetPos(sx, sy);
	SetVel(0, 0);
	SetAcc(0, 0);
	particle_radius_ = kDefaultParticleRadius;
}

void Particle::SetPos(float sx, float sy) {
	s_.set(sx, sy);
}

void Particle::SetVel(float vx, float vy) {
	v_.set(vx, vy);
}

void Particle::SetAcc(float ax, float ay) {
	a_.set(ax, ay);
}

void Particle::AddPos(float sx, float sy) {
	s_.x += sx;
	s_.y += sy;
}

void Particle::AddVel(float vx, float vy) {
	v_.x += vx;
	v_.y += vy;
}

void Particle::AddAcc(float ax, float ay) {
	a_.x += ax;
	a_.y += ay;
}

void Particle::ResetAcc() {
	a_.set(0, 0);
}

void Particle::UpdateState() {
	v_ += a_;  // v = v0 + at
	s_ += v_;  // s = s0 + vt
}

void Particle::Draw() const {
	ofDrawCircle(s_.x, s_.y, particle_radius_);
}

ofVec2f Particle::GetPos() const {
	return s_;
}

ofVec2f Particle::GetVel() const {
	return v_;
}

ofVec2f Particle::GetAcc() const {
	return a_;
}
