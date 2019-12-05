#include "particle.h"

Particle::Particle() {
	SetPos(0, 0);
	SetVel(0, 0);
	SetAcc(0, 0);
}

void Particle::SetPos(float sx, float sy) { 
	s_.set(sx, sy); 
}

void Particle::SetVel(float vx, float vy) { 
	v_.set(vx, vy); 
}

void Particle::SetAcc(float ax, float ay) { 
	a_.set(ax, ay); 
}

ofVec2f Particle::GetPos() const { 
	return s_; 
}

ofVec2f Particle::GetVel() const { 
	return v_; 
}

ofVec2f Particle::GetAcc() const { 
	return a_; 
}
