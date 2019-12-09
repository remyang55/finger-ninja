#include "catch.hpp"

#include <vector>

#include "ofMain.h"

#include "../src/fruit.hpp"

TEST_CASE("Fruit and all its particles' position, velocity, and acceleration are set correctly",
    "[fruit]") {
  Fruit fruit;

  SECTION("Position set correctly") {
    ofVec2f original_pos = fruit.GetPos();
    std::vector<Particle> original_particles = fruit.GetParticles();

    fruit.SetPos(10, 10);
    REQUIRE(fruit.GetPos() == ofVec2f{10, 10});

    int i = 0;
    bool all_particles_shifted_correctly = true;
    for (const auto &particle : fruit.GetParticles()) {
      if (fruit.GetPos() - original_pos != particle.GetPos() - original_particles[i].GetPos()) {
        all_particles_shifted_correctly = false;
        break;
      }
      ++i;
    }
    REQUIRE(all_particles_shifted_correctly);
  }
  SECTION("Velocity set correctly") {
    fruit.SetVel(5, 5);
    REQUIRE(fruit.GetVel() == ofVec2f{5, 5});

    bool all_particles_vel_set = true;
    for (const auto &particle : fruit.GetParticles()) {
      if (fruit.GetVel() != particle.GetVel()) {
        all_particles_vel_set = false;
        break;
      }
    }
    REQUIRE(all_particles_velocity_set);
  }
  SECTION("Acceleration set correctly") {
    fruit.SetAcc(0, 9.81);
    REQUIRE(fruit.GetAcc() == ofVec2f{0, 9.81});

    bool all_particles_acc_set = true;
    for (const auto &particle : fruit.GetParticles()) {
      if (fruit.GetAcc() != particle.GetAcc()) {
        all_particles_acc_set = false;
        break;
      }
    }
    REQUIRE(all_particles_acc_set);
  }
  SECTION("Acceleration reset correctly") {
    fruit.SetAcc(8.8, 9.9);
    fruit.ResetAcc();
    REQUIRE(fruit.GetAcc() == ofVec2f{0, 0});

    bool all_particles_acc_zero = true;
    for (const auto &particle : fruit.GetParticles()) {
      if (particle.GetAcc() != ofVec2f{0, 0}) {
        all_particles_acc_zero = false;
        break;
      }
    }
    REQUIRE(all_particles_acc_zero);
  }
}

TEST_CASE("Fruit acceleration and all its particles' acceleration added correctly", "[fruit]") {
  Fruit fruit{10, 50};
  fruit.SetAcc(3.5, 6);
  std::vector<Particle> original_particles = fruit.GetParticles();

  fruit.AddAcc(0, 9.81);
  REQUIRE(particle.GetAcc() == ofVec2f{3.5, 15.81});

  int i = 0;
  bool all_particles_acc_added = true;
  for (const auto &particle : fruit.GetParticles()) {
    if (particle.GetAcc() - original_particles[i].GetAcc() != ofVec2f{0, 9.81}) {
      all_particles_acc_added = false;
      break;
    }
    ++i;
  }
  REQUIRE(all_particles_acc_added);
}

TEST_CASE("Fruit and all its particles' position and velocity change correctly based on "
          "acceleration", "[fruit]") {
  Fruit fruit{5, 10};
  fruit.SetAcc(20.5, 31.4);
  fruit.UpdateState();

  //fruit should move according to the equations v = v0 + at, and s = s0 + vt, where t = 1
  REQUIRE(fruit.GetVel() == ofVec2f{20.5, 31.4});
  REQUIRE(fruit.GetPos() == ofVec2f{25.5, 41.4});

  bool all_particles_updated = true;
  for (const auto &particle : fruit.GetParticles()) {
    if (particle.Vel() != ofVec2f{20.5, 31.4}) {
      all_particles_updated = false;
      break;
    }
  }
  REQUIRE(all_particles_updated);
}

TEST_CASE("Fruit returns correct status on whether it is hit", "[fruit]") {
  Fruit fruit;
  REQUIRE(!fruit.IsHit());

  fruit.HitFruit();
  REQUIRE(fruit.IsHit());
}

TEST_CASE("Fruit returns correct status on whether it is explosive", "[fruit]") {
  Fruit fruit1{0, 0, false};
  REQUIRE(!fruit1.IsExplosive());

  Fruit fruit2{0, 0, true};
  REQUIRE(fruit2.IsExplosive());
}
