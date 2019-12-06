#ifndef FRUIT_CANNON_HPP_
#define FRUIT_CANNON_HPP_

#include <vector>

#include "fruit.hpp"

class FruitCannon {

public:
	FruitCannon(int left_bound, int right_bound, int height, int speed);

	void FireFruit(std::vector<Fruit> &fruits);
	void CheckFruits(std::vector<Fruit> &fruits);

private:
	int left_bound_;
	int right_bound_;
	int height_;
	int speed_;
	std::vector<Fruit> fruits_;
};

#endif  // FRUIT_CANNON_HPP_
