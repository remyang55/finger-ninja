#include "fruit_cannon.hpp"

#include "ofMain.h"

FruitCannon::FruitCannon(int left_bound, int right_bound, int height, int speed, float min_angle, 
		float max_angle) {
	left_bound_ = left_bound;
	right_bound_ = right_bound;
	height_ = height;
	speed_ = speed;
	min_angle_ = min_angle;
	max_angle_ = max_angle;
}

void FruitCannon::FireFruit(std::vector<Fruit> &fruits) {
	float x_coord = ofRandom(left_bound_, right_bound_);
	float y_coord = height_;
	float r = speed_;
	float theta = min_angle_ + (max_angle_ - min_angle_) 
		* (x_coord - left_bound_) / (right_bound_ - left_bound_);

	bool is_explosive = false;
	float prob = ofRandom(0, 100);
	if (prob < kExplosivePercentage) {
		is_explosive = true;
	}

	Fruit fruit{ x_coord, y_coord, is_explosive };
	fruit.SetVel(r * cos(theta), -r * sin(theta));

	fruits.push_back(fruit);
}

void FruitCannon::CheckFruits(std::vector<Fruit> &fruits, int &player_hp) {
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

		if (is_fruit_out_of_screen) {
			if (!fruit.IsHit() && !fruit.IsExplosive()) {
				--player_hp;
			}
			it = fruits.erase(it);
		} else {
			++it;
		}
	}
}
