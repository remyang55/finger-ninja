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

void FruitCannon::CheckFruits(std::vector<Fruit> &fruits) {
	auto it = fruits.begin();
	while (it != fruits.end()) {
		bool is_fruit_out_of_screen = true;

		auto fruit = *it;
		for (const auto& particle : fruit.GetParticles()) {
			if (particle.GetPos().x > 0
					&& particle.GetPos().x < right_bound_
					&& particle.GetPos().y < height_) {
				is_fruit_out_of_screen = false;
				break;
			}
		}

		if (fruit.IsHit() && is_fruit_out_of_screen) {
			it = fruits.erase(it);
		} else {
			++it;
		}
	}
}
