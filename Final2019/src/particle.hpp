#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include "ofMain.h"

/**
 * This class represents one small part of a Fruit. An important distinction between this class
 * and the Fruit class is that there is no logic checking done here. The only reason for this
 * class is graphical; that the fruit will look like it is "exploding" when the player slices it.
 */

constexpr int kDefaultParticleRadius = 3;

class Particle {
 public:
  Particle();
  Particle(float sx, float sy, int radius = kDefaultParticleRadius);

  void SetPos(float sx, float sy);
  void SetVel(float vx, float vy);
  void SetAcc(float ax, float ay);
  void AddPos(float sx, float sy);
  void AddVel(float vx, float vy);
  void AddAcc(float ax, float ay);
  void ResetAcc();

  ofVec2f GetPos() const;
  ofVec2f GetVel() const;
  ofVec2f GetAcc() const;

  void UpdateState();
  void Draw() const;

 private:
  ofVec2f pos_;
  ofVec2f vel_;
  ofVec2f acc_;
  int particle_radius_;
};

#endif  // PARTICLE_HPP_
