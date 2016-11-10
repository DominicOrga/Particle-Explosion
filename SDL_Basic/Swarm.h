#pragma once

#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"
#include "Screen.h"

namespace horizongames {
	
	class Swarm {
	public:
		const static int PARTICLE_COUNT = 5000;
	
	private:
		Particle* m_pParticles;
		int m_previousTime;

	public:
		Swarm();
		~Swarm();
		const Particle* const getParticles();
		void update(int& elapsedTime);
	};
}

#endif