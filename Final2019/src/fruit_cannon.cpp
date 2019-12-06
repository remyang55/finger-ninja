#include "fruit_cannon.hpp"

#include "ofMain.h"

FruitCannon::FruitCannon(int left_bound, int right_bound, int height, int speed) {
	left_bound_ = left_bound;
	right_bound_ = right_bound;
	height_ = height;
	speed_ = speed;
}

void FruitCannon::FireFruit(std::vector<Fruit> &fruits) {
	float x_coord = ofRandom(left_bound_, right_bound_);
	float y_coord = height_;
	float r = speed_;
	float theta = kPi / 3 + kPi / 3 * (x_coord - left_bound_) / (right_bound_ - left_bound_);

	Fruit fruit{ x_coord, y_coord };
	fruit.SetVel(r * cos(theta), -r * sin(theta));
	
	fruits.push_back(fruit);
}
