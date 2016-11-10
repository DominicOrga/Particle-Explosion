#include "Particle.h"
#include <iostream>

namespace horizongames {

	Particle::Particle(): m_x(0), m_y(0) {
		m_direction = 2 * M_PI * ((double) rand() / RAND_MAX);
		m_momentum = 0.01 * ((double) rand() / RAND_MAX);
		m_momentum *= m_momentum;
	};

	Particle::~Particle() {};

	void Particle::update(int& deltaTime) {

		m_direction += deltaTime * 0.0002;

		double xMomentum = m_momentum * cos(m_direction);
		double yMomentum = m_momentum * sin(m_direction);

		m_x += xMomentum * deltaTime;
		m_y += yMomentum * deltaTime;
	}
}