#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "ofMain.h"

constexpr kDefaultRadius = 2;

class Particle {

public:
	Particle();

	void SetPos(float sx, float sy);
	void SetVel(float vx, float vy);
	void SetAcc(float ax, float ay);
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
	int radius_;
};

#endif  // PARTICLE_H_
