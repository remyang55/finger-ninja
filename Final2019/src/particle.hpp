#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include "ofMain.h"

constexpr int kDefaultParticleRadius = 2;

class Particle {

public:
	Particle();
	Particle(float sx, float sy);

	void SetPos(float sx, float sy);
	void SetVel(float vx, float vy);
	void SetAcc(float ax, float ay);
	void AddPos(float sx, float sy);
	void AddVel(float vx, float vy);
	void AddAcc(float ax, float ay);
	void ResetAcc();

	void UpdateState();
	void Draw() const;

	ofVec2f GetPos() const;
	ofVec2f GetVel() const;
	ofVec2f GetAcc() const;

private:
	ofVec2f s_;  // position vector
	ofVec2f v_;  // velocity vector
	ofVec2f a_;  // acceleration vector
	int particle_radius_;
};

#endif  // PARTICLE_HPP_
