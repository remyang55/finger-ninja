#ifndef FRUIT_HPP_
#define FRUIT_HPP_

#include <vector>

#include "ofMain.h"

#include "particle.hpp"

/**
 * This class represents a Fruit that the player will slice to earn points. An important
 * distinction between this class and the Particle class is that the player actually interacts
 * with this class e.g. collision detection and adding points to the player.
 *
 * Note: the position, velocity, and acceleration vectors in this class are entirely distinct from
 * those of the Particles in the vector particles_ and must be kept separately because these are
 * actually used to update the Fruit's central location (which is the reference point to which
 * collision detection is accomplished), whereas the vectors inside the Particle class are purely
 * for graphical/animation means.
 */

constexpr int kRadius = 30; //radius of the whole fruit
constexpr int kNumParticles = 500; //number of particles the fruit is composed of
constexpr float kPi = 3.14159;

constexpr int kTargetHitCount = 1; //number of times fruit should be hit
constexpr int kMaxUpdateCount = 2; //number of times fruit is updated before it explodes on screen
constexpr int kMinExplosionSpeed = -4;
constexpr int kMaxExplosionSpeed = 4;

class Fruit {
 public:
  Fruit();
  Fruit(float sx, float sy, bool is_explosive);

  void SetPos(float sx, float sy);
  void SetVel(float vx, float vy);
  void SetAcc(float ax, float ay);
  void AddAcc(float ax, float ay);
  void ResetAcc();

  void HitFruit();

  void UpdateState();
  void Draw() const;

  bool IsExplosive() const;
  bool IsHit() const;
  ofVec2f GetPos() const;
  ofVec2f GetVel() const;
  ofVec2f GetAcc() const;
  std::vector<Particle> GetParticles() const;

 private:
  bool is_explosive_;
  int hit_count_;
  int update_count_; //number of times update() has been called on the Fruit, after it is hit

  ofVec2f s_;  //position vector
  ofVec2f v_;  //velocity vector
  ofVec2f a_;  //acceleration vector
  std::vector<Particle> particles_; //particles that compose the fruit
};

#endif  // FRUIT_HPP_
