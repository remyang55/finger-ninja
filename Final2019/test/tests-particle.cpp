#include "catch.hpp"

#include "ofMain.h"

#include "../src/particle.hpp"

TEST_CASE("Particle position, velocity, and acceleration are set correctly", "[particle]") {
  Particle particle;

  SECTION("Position set correctly") {
    particle.SetPos(10, 10);
    REQUIRE(particle.GetPos() == ofVec2f{10, 10});
  }
  SECTION("Velocity set correctly") {
    particle.SetVel(5, 5);
    REQUIRE(particle.GetVel() == ofVec2f{5, 5});
  }
  SECTION("Acceleration set correctly") {
    particle.SetAcc(0, 9.81);
    REQUIRE(particle.GetAcc() == ofVec2f{0, 9.81});
  }
  SECTION("Acceleration reset correctly") {
    particle.SetAcc(8.8, 9.9);
    particle.ResetAcc();
    REQUIRE(particle.GetAcc() == ofVec2f{0, 0});
  }
}

TEST_CASE("Particle position, velocity, and acceleration are added correctly", "[particle]") {
  Particle particle{10, 50};
  particle.SetVel(2.2, 3.3);
  particle.SetAcc(3.5, 6);

  SECTION("Position added correctly") {
    particle.AddPos(10, 10);
    REQUIRE(particle.GetPos() == ofVec2f{20, 60});
  }
  SECTION("Velocity added correctly") {
    particle.AddVel(5, 5);
    REQUIRE(particle.GetVel() == ofVec2f{7.2, 8.3});
  }
  SECTION("Acceleration added correctly") {
    particle.AddAcc(0, 9.81);
    REQUIRE(particle.GetAcc() == ofVec2f{3.5, 15.81});
  }
}

TEST_CASE("Particle position and velocity change correctly based on acceleration", "[particle]") {
  Particle particle{5, 10};
  particle.SetAcc(20.5, 31.4);
  particle.UpdateState();

  //particle should move according to the equations v = v0 + at, and s = s0 + vt, where t = 1
  REQUIRE(particle.GetVel() == ofVec2f{20.5, 31.4});
  REQUIRE(particle.GetPos() == ofVec2f{25.5, 41.4});
}
