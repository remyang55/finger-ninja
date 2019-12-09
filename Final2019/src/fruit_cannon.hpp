#ifndef FRUIT_CANNON_HPP_
#define FRUIT_CANNON_HPP_

#include <vector>

#include "fruit.hpp"

constexpr int kExplosivePercentage = 30; //percent chance that the fruit fired is explosive

class FruitCannon {
 public:
  FruitCannon(int left_bound, int right_bound, int height, int speed, float min_angle,
              float max_angle);

  bool FireFruit(std::vector<Fruit> &fruits);
  void CheckFruits(std::vector<Fruit> &fruits, int &player_hp);

 private:
  int left_bound_; //x coordinate of left side of screen
  int right_bound_; //x coordinate of right side of screen
  int height_; //y coordinate of the cannon
  int speed_; //speed at which the fruits are fired
  float min_angle_; //angle a fruit would be fired at, from the left of screen
  float max_angle_; //angle a fruit would be fired at, from the right of screen
};

#endif  // FRUIT_CANNON_HPP_
