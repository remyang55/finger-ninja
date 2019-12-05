#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "ofMain.h"

class Particle {
public:
	Particle();

	void SetPos(float sx, float sy);
	void SetVel(float vx, float vy);
	void SetAcc(float ax, float ay);
	void AddAcc(float ax, float ay);
	void ResetAcc();

	void UpdateState();

	ofVec2f GetPos() const;
	ofVec2f GetVel() const;
	ofVec2f GetAcc() const;

private:
	ofVec2f s_;  // position vector
	ofVec2f v_;  // velocity vector
	ofVec2f a_;  // acceleration vector
};

#endif  // PARTICLE_H_
