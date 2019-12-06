#ifndef FRUIT_HPP_
#define FRUIT_HPP_

#include <vector>

#include "ofMain.h"

#include "particle.hpp"

constexpr int kRadius = 30; //radius of the whole fruit
constexpr int kNumParticles = 500; //number of particles the fruit is composed of
constexpr float kPi = 3.14159;

class Fruit {

public:
	Fruit();
	Fruit(float sx, float sy);

	void SetPos(float sx, float sy);
	void SetVel(float vx, float vy);
	void SetAcc(float ax, float ay);
	void AddAcc(float ax, float ay);
	void ResetAcc();

	void HitFruit(int force);

	void UpdateState();
	void Draw() const;

	ofVec2f GetPos() const;
	ofVec2f GetVel() const;
	ofVec2f GetAcc() const;
	std::vector<Particle> GetParticles() const;
	bool IsHit() const;

private:
	ofVec2f s_;  // position vector
	ofVec2f v_;  // velocity vector
	ofVec2f a_;  // acceleration vector
	std::vector<Particle> particles_;
	int hit_count_;
};

#endif  // FRUIT_HPP_
