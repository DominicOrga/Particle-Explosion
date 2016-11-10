#include "Swarm.h"
#include <iostream>

namespace horizongames {
	Swarm::Swarm(): m_previousTime(0) {
		m_pParticles = new Particle[PARTICLE_COUNT];
	}

	Swarm::~Swarm() {
		delete[] m_pParticles;
	}

	const Particle* const Swarm::getParticles() {
		return m_pParticles;
	}

	void Swarm::update(int& elapsedTime) {
		int deltaTime = elapsedTime - m_previousTime;

		for (int i = 0; i < PARTICLE_COUNT; i++)
			m_pParticles[i].update(deltaTime);

		m_previousTime = elapsedTime;
	}
}